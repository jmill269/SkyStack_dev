#!/usr/bin/env python2
from dronekit import connect, VehicleMode
import time
import sys

connection_string = "udp:10.0.0.48:14550"

print ("Connecting to vehicle on: %s" % (connection_string))
vehicle = connect(connection_string, wait_ready=True) #Connect to the vehicle

#Print some vehicle parameters to confirm connection. 

print ("Vehicle Attribute Overview:")
print ("Battery: %s" % vehicle.battery)
print ("Last Heartbeat: %s" % vehicle.last_heartbeat)
print ("Is armable?: %s" % vehicle.is_armable)
print ("Ensuring mode is in Stabilize") #Settable

vehicle.mode = VehicleMode("STABILIZE")
#If vehicle is armable then arm it and wait until it is armed.
time.sleep(3)

#Waiting for input from shell script
print ("Waiting on Input")
test = 1

while test == 1:
	for line in sys.stdin:
		if line == 1:
			#Tell the gimbal to point straight down.

			vehicle.gimbal.rotate(90,0,0)
			print ("Gimbal should be looking down")
		if line == 2:
			#Tell gimbal to look forward
			vehicle.gimbal.rotate(0,0,0)
			print ("Gimbal should be looking forward")
		if line == 3:
			#Tell gimbal to look up
			vehicle.gimbal.rotate(-90,0,0)
			print ("Gimbal should be looking up")
		if line == 4:
			vehicle.close()
			print ("Vehicle Connection Closed")
			test = 0


