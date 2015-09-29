#!/bin/bash

if [ -a "/usr/bin/apt-get" ]
	then
		echo "installing dependencies"
		sudo apt-get install libudev-dev
fi

echo "compiling the driver"

make all && \
echo "success"

echo "installing the driver"

cp calibrateDWAV /usr/bin/ && \
cp DWAVDriver && \
echo "sucess"