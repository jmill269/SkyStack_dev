import RPi.GPIO as GPIO
import time
import socket
#Setup UDP Communication
UDP_IP="10.0.0.185" #This is the local IP Address of this device, the StationSide Py.
UDP_PORT=5005

mainSock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
mainSock.bind((UDP_IP, UDP_PORT))

#Setup Pins
back=3
enter=2

#Setup Outputs
GPIO.setmode(GPIO.BCM)
GPIO.setup(enter, GPIO.OUT, initial=0)
GPIO.setup(back, GPIO.OUT, initial=0)
#Create pushbutton function

def pushButton(num):

        if num==back:
                GPIO.output(back,1)
                time.sleep(.2)
                GPIO.output(back,0)
        if num==enter:
                GPIO.output(enter,1)
                time.sleep(.2)
                GPIO.output(enter,0)
        return;

#Create push and hold button function (used to start charging)

def pushHoldButton(num):
        if num==back:
                GPIO.output(back,1)
                time.sleep(1.5)
                GPIO.output(back,0)
        if num==enter:
                GPIO.output(enter,1)
                time.sleep(1.5)
                GPIO.output(enter,0)

        return;
#---Main Program

while True:
        data, addr = mainSock.recvfrom(1024) #Buffer size is 1024 bytes
        print "received Message:", data
        data=int(data)
        if data==1:
                pushHoldButton(enter)
                time.sleep(1)
                mainSock.close()
                break

