# Next Try

So, I was able to get the camera working as video input device.
However, the framerate and stability was not good enough to serve my purposes.

So, the new plan is as follows:
* attach a display to the HDMI output of my DSLR
* use `gphoto2` to control the camera, e.g. capture
* after capturing, download the photos and do some post-processing
* maybe there is even a way to display the processed image

## Remote trigger

While playing around with `gphoto2` I encountered the following behavior:
When issuing commands to the camera, the display will go black.
I did not yet find a way to re-enable it from within `gphoto2`.
However, pressing the capture button did the job for me.
So, as a last resort to re-enable the display I constructed a wired remote trigger for the camera, that can be controlled by the Raspberry Pi.

```
          focus   capture
             |    |
             V    V
    ___________  ___
       |   |   \/   \
    ___|___|___/\___/

     |   |   |     |
     |__ |   |    R22k
     |       |     |
     |     R22k    \
     |       |      \
     |       \     |
     |        \    |
     |       |     |
     |_______|_____|
```

In my case I need a 2.5mm headphone jack.
I salvaged an old phone headset, that I don't use anymore.
It had 4 contacts instead of 3, so I connected the two parts at the back together.
The switches in the drawing will be simulated by the raspberry pi.
When you close any of the circuit, a current of about 60µA will flow.
The Pi should be able to handle that, but I added the two resistor just to be sure.
If the resistance is too high, the capture will not be triggered.
If you don't have any resistors laying around, I guess you could leave them out.

## Connecting it to the Raspberry Pi

```
    ___________  ___
       |   |   \/   \
    ___|___|___/\___/

     |   |   |     |
     |__ |   |     |
     |       |     |
     |       |     Pin 18, GPIO 24
     |       |      
     |       Pin 16, GPIO 23
     |       
    Pin 14, GND
```

I connected the trigger to the GPIO pins of the Raspberry Pi.
The trigger is active low, so you need to set the output to `0` in order to trigger a capture. In some cases the camera will need some time to actually capture an image, so be patient. Afterwards you can set the pins to `1` again.