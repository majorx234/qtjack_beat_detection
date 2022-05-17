///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of QtJack.                                            //
//    Copyright (C) 2014-2015 Jacob Dawid <jacob@omg-it.works>               //
//                                                                           //
//    QtJack is free software: you can redistribute it and/or modify          //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    QtJack is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with QtJack. If not, see <http://www.gnu.org/licenses/>.          //
//                                                                           //
//    It is possible to obtain a closed-source license of QtJack.             //
//    If you're interested, contact me at: jacob@omg-it.works                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#ifndef MP3PLAYER_MAINWINDOW_HPP_
#define MP3PLAYER_MAINWINDOW_HPP_

// QtJack includes
#include <Client>
#include <Processor>
#include <RingBuffer>

// Qt includes
#include <QMainWindow>
#include <QAudioDecoder>

namespace Ui {
class Mp3PlayerMainWindow;
}

class Mp3PlayerMainWindow : public QMainWindow, public QtJack::Processor
{
    Q_OBJECT

public:
    explicit Mp3PlayerMainWindow(QWidget *parent = 0);
    ~Mp3PlayerMainWindow();

    void setupJackClient();
    void setupMp3Decoder();
    void process(int samples);

protected slots:
    void on_toolButtonFileChoose_clicked();

    void decodingError(QAudioDecoder::Error error);
    void transferSamples();

protected:
    void timerEvent(QTimerEvent*);

private:
    Ui::Mp3PlayerMainWindow *ui;

    QAudioDecoder _audioDecoder;

    QtJack::Client _client;
    QtJack::AudioPort _outLeft;
    QtJack::AudioPort _outRight;

    QtJack::AudioRingBuffer _ringBufferLeft;
    QtJack::AudioRingBuffer _ringBufferRight;
};

#endif // MP3PLAYER_MAINWINDOW_HPP_
