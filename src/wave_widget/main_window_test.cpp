///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of qtjack_bpm_tab                                    //
//    Copyright (C) 2022 <majorx234@googlemail.com>                          //
//                                                                           //
//    qtjack_bpm_tab is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    qtjack_bpm_tab is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with qtjack_bpm_tab. If not, see <http://www.gnu.org/licenses/>. //
//                                                                           //
//    It is possible to obtain a closed-source license of QtJack.            //
//    If you're interested, contact me at: majorx234@gmail.com               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "main_window_test.hpp"
#include "wave_widget.hpp"

MainWindowTest::MainWindowTest(QWidget *parent)
  : QMainWindow(parent)
  , Processor(_client)
  , wave_widget(this)
  , _sample_rate(48000)
  , _audio_buffer_size(48000*30)
  , super_circular_buffer{SuperCircularBuffer<float>(300,1024),SuperCircularBuffer<float>(300,1024)}
{
  setCentralWidget(&wave_widget);
  setupJackClient();
  connect(this, &MainWindowTest::on_limits_ready, 
          &wave_widget, &WaveWidget::setChunk);
  timerId = startTimer(50);
}

MainWindowTest::~MainWindowTest() {
  killTimer(timerId);
}

void MainWindowTest::setupJackClient() {
  _client.connectToServer("Wave Widget");
  _sample_rate = _client.sampleRate();

  // 30 seconds audiobuffer
  _audio_buffer_size = _sample_rate *30; 
  _audio_buffer[0] =
      (QtJack::AudioSample*)malloc(_audio_buffer_size
                                   * sizeof(QtJack::AudioSample));
  _audio_buffer[1] =
      (QtJack::AudioSample*)malloc(_audio_buffer_size
                                   * sizeof(QtJack::AudioSample));
  // audio port
  _audio_in_port[0] = _client.registerAudioInPort("in 1");
  _audio_in_port[1] = _client.registerAudioInPort("in 2");
  _audio_ring_buffer[0] = QtJack::AudioRingBuffer();
  _audio_ring_buffer[1] = QtJack::AudioRingBuffer();
  _client.setMainProcessor(this);
  _client.activate();
}

void MainWindowTest::process(int samples) {
  // audio part
  _audio_in_port[0].buffer(samples).push(_audio_ring_buffer[0]);
  _audio_in_port[1].buffer(samples).push(_audio_ring_buffer[1]);
  super_circular_buffer[0].add_chunk(_audio_buffer[0]);
  super_circular_buffer[1].add_chunk(_audio_buffer[1]);
}

void MainWindowTest::timerEvent(QTimerEvent *event) {
  audio_process_fct();
}

void MainWindowTest::audio_process_fct() {
  int max_elemets[2];
  max_elemets[0] = _audio_buffer_size;
  max_elemets[1] = _audio_buffer_size;

  int timeInMillisec = 1000;
  size_t ring_buffer_right_size =
      _audio_ring_buffer[0].numberOfElementsAvailableForRead();
  size_t ring_buffer_left_size =
      _audio_ring_buffer[1].numberOfElementsAvailableForRead();
  //need to copy, not more than buffer size
  max_elemets[0] = ring_buffer_right_size < _audio_buffer_size ?
                   ring_buffer_right_size : _audio_buffer_size;
  // norm to 1024
  max_elemets[0] = 1024*(max_elemets[0] / 1024);
  int s0 = _audio_ring_buffer[0].read(_audio_buffer[0], max_elemets[0]);

  //need to copy, not more than buffer size
  max_elemets[1] = ring_buffer_left_size < _audio_buffer_size ?
                   ring_buffer_left_size : _audio_buffer_size;
  // norm to 1024
  max_elemets[1] = 1024*(max_elemets[1] / 1024);
  // copy data from ringbuffer to audio buffer
  int s1 = _audio_ring_buffer[1].read(_audio_buffer[1], max_elemets[1]);

  // Process read data here _audio_buffer[*]
  float limits[4] = {0.0, 0.0, 0.0, 0.0};
  for (int j = 0; j < max_elemets[0]; j++) {
    if(_audio_buffer[0][j] < limits[2*0]) {
      limits[2*0] = _audio_buffer[0][j];
    } else if (_audio_buffer[0][j] > limits[2 * 0 + 1]) {
      limits[2*0+1] = _audio_buffer[0][j];
    }
    if(_audio_buffer[1][j] < limits[2*1]) {
      limits[2*1] = _audio_buffer[1][j];
    } else if (_audio_buffer[1][j] > limits[2 * 1 + 1]) {
      limits[2*1+1] = _audio_buffer[1][j];
    }
    if(j%128 == 127) {
      emit on_limits_ready(limits[0],limits[1],limits[2],limits[3]);
      limits[0] = 0;
      limits[1] = 0;
      limits[2] = 0;
      limits[3] = 0;
    }
  }
  //super_circular_buffer[0].add_chunk(_audio_buffer[0]);
  //super_circular_buffer[1].add_chunk(_audio_buffer[1]);
  //if(chunk_counter_ > 300 && (chunk_counter_ % 46 == 0)) {
  //  emit on_buffer_ready_to_calc_bpm();
  //}
  //chunk_counter_++;

}