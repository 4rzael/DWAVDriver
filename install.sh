#!/bin/bash

if [ -a "/usr/bin/apt-get" ]
	then
		echo "installing dependencies"
		sudo apt-get install libudev-dev libxtst-dev xinerama-dev
fi

echo "Retreiving xdotool"
git clone https://github.com/jordansissel/xdotool.git

if [ $? -eq 1 ]
	then
		return "1"
fi

echo "installing xdotool"
make -C ./xdotool/ && make install -C ./xdotool/

if [ $? -eq 1 ]
	then
		return "1"
fi

echo "compiling the driver"
gcc *.c -o touch && echo "success"

if [ $? -eq 1 ]
	then
		return "1"
fi
