# syscon

## Dependencies
1. Catch2 version3
2. Gnuplot

## Installation

### Install Catch2

```
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install

```

### Install Gnuplot

```
sudo apt install gnuplot
```

## Road map

|Completed|Description|Date of Completition|
|:-------:|:----------|:------------------:|
|Yes       |Low pass filter (Frst order system)|Feb. 16, 2023   |
|Yes       |Bode plot|Feb. 16, 2023|
|          |High pass filter (First order system)||
|          |Documentation update||
|          |Code optimization||
|          |Release 0.2|
|          |Low pass filter (Second order system)||
|          |High pass filter (Second order system)||
|          |Documentation update||
|          |Code optimization||
|          |Release 0.5|
|          |Input shaping||
|          |Documentation update||
|          |Code optimization|
|          |Release 0.7|
|          |Notch filter||
|          |Documentation update||
|          |Code optimization|
|          |Release 1.0|
