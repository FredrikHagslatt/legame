# Le Game

# Setup & Build

## Linux (debian based)
```
sudo apt update
sudo apt install -y build-essential
sudo apt install -y libsdl2-dev
sudo apt install -y libsdl2-image-dev
sudo apt install -y libsdl2-mixer-dev
sudo apt install -y libsdl2-image-dev
sudo apt install -y libsdl2-ttf-dev

mkdir build && cd build
cmake ..
make
```

## Windows (mingw64)
```
Install mingw64 according to their instructions:
https://www.msys2.org/
Also install Ninja in the msys shell
run pacman -S mingw-w64-x86_64-ninja

mkdir build
cd build
cmake ..
mingw32-make
cd ..
```