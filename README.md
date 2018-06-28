Setup for Linux:
Install CMake:
```
sudo apt install cmake
```
Install GTest:
```
sudo apt install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```

Install SDL2:
```
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
sudo apt install libsdl2-ttf-dev
```

Compiling:
```
mkdir build
cd build
cmake ..
make
```
Running application:
```
./crossword_puzzle
```

Setup for Windows:

Compiling with MinGW:
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```


