Below is a link to the source code:

https://randomnerdtutorials.com/video-streaming-with-raspberry-pi-camera/

If it doesn't work, and is sending an error like "mmal: mmal failed to
 establish connection" among other errors then attempt following fix. 

sudo apt-get update
sudo apt-get install --reinstall libraspberrypi0 libraspberrypi-{bin,dev,doc} raspberrypi-bootloader
sudo reboot

The above commands essentially undo sudo rpi-update. Which was suggested to use during openCV Installation.

 Apparently rpi-update can install unstable updates and 
cause more harm than good. 
