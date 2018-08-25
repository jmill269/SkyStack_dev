from dronekit import connect, VehicleMode

connection_string = "udp:10.0.0.48:14550"

print ("Connecting to vehicle on: %s" % (connection_string))
vehicle = connect(connection_string, wait_ready=True) #Connect to the vehicle

#Print some vehicle parameters to confirm connection. 

print ("Vehicle Attribute Overview:")
print ("Battery: %s" % vehicle.battery)
print ("Last Heartbeat: %s" % vehicle.last_heartbeat)
print ("Is armable?: %s" % vehicle.is_armable)
print ("Ensuring mode is in Guided") #Settable

vehicle.mode = VehicleMode("GUIDED")
#If vehicle is armable then arm it and wait until it is armed.
if vehicle.is_armable == True:
	vehicle.armed = True
	while not vehicle.mode.name=='GUIDED' and not vehicle.armed and not api.exit:
		print (" Arming Vehicle...")
		time.sleep(1)

	print ("Vehicle Armed")

#Tell the gimbal to point straight down.

vehicle.gimbal.rotate(-90,0,0)

 #close vehicle for proper shutdown.
vehicle.close()
print ("Vehicle Connection Closed")
