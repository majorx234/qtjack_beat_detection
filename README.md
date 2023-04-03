# qtjack_beat_detection
- WIP!
 - planned: visualize audio input 
 - planned: visualize detected beats

## Info
Dependencies:

* Qt 5.4 or greater (https://github.com/majorx234/qtjack)
* QJack, which itself depends on Jack2

On Ubuntu, you need to install dependencies:
```
sudo apt-get install libjack-jackd2-dev
```

On Arch Linux:
```
sudo pacman -S jack2 qt5-base
```

If you have any questions feel free to drop me a mail me at
```
majorx234@googlemail.com

```

## Usage
- build project:
```
git clone https://github.com/majorx234/qtjack_beat_detection.git
cd qtjack_beat_detection
mkdir build
cd build
cmake ..
make
```
## Reference 
- uses parts of analyzerplugin concept of Mixxx: (https://github.com/mixxxdj/mixxx.git)
- uses parts of qm-vamp-plugins: (queenmarybeatdetection & TempoTrackV2) (https://github.com/c4dm/qm-vamp-plugins)
- uses Kissfft: (https://github.com/mborgerding/kissfft)
- uses idea for visualization of wave by Matthias Nagorni (https://www.heise.de/hintergrund/Parallelprogrammierung-mit-C-und-Qt-Teil-3-Plattformunabhaengige-Audioprogrammierung-1576739.html)
- used idea behind beat this BPM detection (https://www.clear.rice.edu/elec301/Projects01/beat_sync/beatalgo.html)  

## History
- 2023-04-02 Move beatdetection algos to extra repo
- 2022-06-23 Implement library for Beat This BPM detection algo and test functions
- 2022-05-23 Modify QM bpm detection

## ToDo
- beat detection on audio data
