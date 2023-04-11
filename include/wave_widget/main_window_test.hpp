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

#ifndef MAIN_WINDOW_TEST_HPP_
#define MAIN_WINDOW_TEST_HPP_

#include <QMainWindow>
// QtJack includes
#include <Client>
#include <Processor>
#include <RingBuffer>

#include "wave_widget.hpp"

class MainWindowTest : public QMainWindow, public QtJack::Processor
{
  Q_OBJECT
 public:
  explicit MainWindowTest(QWidget *parent = 0);
  ~MainWindowTest();
  void setupJackClient();
  void process(int samples) override;
  void audio_process_fct();
 signals:
  void on_limits_ready(float,float,float,float); 
 private:
  int timerId;
  WaveWidget wave_widget;
  QtJack::Client _client;
  unsigned int _sample_rate;
  jack_nframes_t last_frame_time;
  QtJack::AudioPort _audio_in_port[2];
  QtJack::AudioRingBuffer _audio_ring_buffer[2];
  size_t _audio_buffer_size;
  QtJack::AudioSample* _audio_buffer[2];
  size_t _new_samples_in_audio_buffer;
 protected:
  void timerEvent(QTimerEvent *event);
};

#endif // MAIN_WINDOW_TEST_HPP_
