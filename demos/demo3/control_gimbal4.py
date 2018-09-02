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

print ("Waiting on Input")

for line in sys.stdin:

	newLine=line.replace("[","")
	newline=newline.replace("]","")
	values = line.split(',')
	ytrans = values[1]
	if ytrans > #NEEDS MORE WORK
	vehicle.gimbal.rotate(90,0,0)


 #close vehicle for proper shutdown.
#vehicle.close()
#print ("Vehicle Connection Closed")
