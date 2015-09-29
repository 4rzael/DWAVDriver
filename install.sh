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
cp DWAVDriver /usr/bin/ && \
echo "sucess"

echo "adding the driver at startup"
# This only works on distros using with systemctl (tested on Arch)
touch /usr/lib/systemd/system/DWAVDriver.service && \
echo "[Service]" >> /usr/lib/systemd/system/DWAVDriver.service && \
echo "ExecStart=/usr/bin/DWAVDriver" >> /usr/lib/systemd/system/DWAVDriver.service && \
echo "Restart=always" >> /usr/lib/systemd/system/DWAVDriver.service && \
echo "StandardOutput=syslog" >> /usr/lib/systemd/system/DWAVDriver.service && \
echo "StandardError=syslog" >> /usr/lib/systemd/system/DWAVDriver.service && \
echo "SyslogIdentifier=DWAVDriver" >> /usr/lib/systemd/system/DWAVDriver.service && \
echo "User=root" >> /usr/lib/systemd/system/DWAVDriver.service && \
systemctl enable DWAVDriver.service && \
echo "success"