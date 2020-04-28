#!/bin/bash

echo "Running gphoto2 processes:"
ps -A | grep gphoto2

echo "Killing gphoto2 processes"
killall --regexp gphoto2

echo "Running gphoto2 processes:"
ps -A | grep gphoto2

echo "Loading v4l2loopback driver"
sudo modprobe v4l2loopback

echo "Available video devices:"
find /dev -name video*

set -euo pipefail

# gphoto2 --stdout --capture-movie | gst-launch-1.0 fdsrc ! decodebin3 name=dec ! queue ! videoconvert ! v4l2sink device=/dev/video0