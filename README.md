photo_booth
===========

Trying to create a photo booth for my wedding.
Project start: 11-03-2020

Components used:
----------------

* Raspberry Pi 3B (https://www.raspberrypi.org/products/raspberry-pi-3-model-b/) 
* Canon EOS 700d (https://www.canon.de/for_home/product_finder/cameras/digital_slr/eos_700d/)
* Waveshare 7 inch screen (https://www.waveshare.com/wiki/7inch_LCD_for_Pi)
* DSLR power supply (https://www.amazon.de/subtel®-Qualitäts-Netzteil-Canon-Rebel/dp/B00MUHPO8Y/)


Raspi setup
-----------

* install a fresh Raspbian Buster image
* setup with ssh enabled
* edit `/boot/config.txt` according to the waveshare instructions:

For Raspberry Pi 2B/3B/3B+/Zero/Zero W
```
dtoverlay=dpi24
enable_dpi_lcd=1
display_default_lcd=1
dpi_group=2
dpi_mode=87
dpi_output_format=0x6f005
hdmi_cvt 1024 600 60 6 0 0 0
```

For Raspberry Pi 4 B, you need to add these lines between `[pi4]` and `[all]`.
You also need to remove the line `dtoverlay=vc4-fkms-V3D` from `config.txt` as seen below.
```
[pi4]
# Enable DRM VC4 V3D driver on top of the dispmanx display stack
#dtoverlay=vc4-fkms-v3d
max_framebuffers=2
dpi_timings=1024 0 0 0 88 600 0 0 0 0 0 0 0 60 0 26000000 6
 
[all]
#dtoverlay=vc4-fkms-v3d
dtoverlay=dpi24
enable_dpi_lcd=1
display_default_lcd=1
dpi_group=2
dpi_mode=87
dpi_output_format=0x6f005
hdmi_cvt 1024 600 60 6 0 0 0
disable_overscan=1
```

__I also needed to rotate my screen by adding the following to the bottom:__
```
display_rotate=2
```
lcd_rotate?

## Fixing VNC resolution
`sudo nano /boot/config.txt `

```
framebuffer_width=1600
framebuffer_height=900

# dtoverlay=vc4-fkms-v3d
```

## Websites with info
* `https://batchloaf.wordpress.com/2019/07/11/using-canon-eos-70d-dslr-as-a-usb-web-cam-in-xubuntu-linux-19-04/`
* `https://www.stevemurch.com/build-a-photo-booth-for-your-next-party/2019/12`
* `https://medium.com/nerdery/dslr-webcam-setup-for-linux-9b6d1b79ae22`


## Install dependencies
`sudo apt-get install gphoto2 (v4l2loopback-source ?) (v4l2loopback-dkms ?)`

```
sudo apt-get install        \
  gstreamer1.0-plugins-bad  \
  gstreamer1.0-plugins-base \
  gstreamer1.0-plugins-good \
  gstreamer1.0-plugins-ugly \
  gstreamer1.0-tools        \
  libgstreamer1.0-0
```

## Kill blocking processes
```
pi@raspberrypi4:~ $ ps -A | grep photo
  688 ?        00:00:00 gvfs-gphoto2-vo
  738 ?        00:00:00 gvfsd-gphoto2
pi@raspberrypi4:~ $ kill 688 738
pi@raspberrypi4:~ $ ps -A | grep photo
pi@raspberrypi4:~ $
```

## Check output
`sudo gphoto2 --capture-movie --stdout`


## Start capturing

Did not work: `gphoto2 --stdout --capture-movie | gst-launch-1.0 fdsrc ! decodebin3 name=dec ! queue ! videoconvert ! v4l2sink device=/dev/video0`

```
pi@raspberrypi4:~ $ sudo modprobe v4l2loopback
pi@raspberrypi4:~ $ find /dev -name video*
/dev/video0
/dev/video12
/dev/video11
/dev/video10
pi@raspberrypi4:~ $ gphoto2 --stdout --capture-movie | ffmpeg -i - -vcodec rawvideo -pix_fmt yuv420p -threads 0 -f v4l2 /dev/video0
```

## Check with VLC

* Open the `VLC` media player
* Select `Media` --> `Open Capture Device` --> `Video Device Name`
* Enter `/dev/video0`
* Press `Play`