# method: <<python simple_mission.py --connect udp:127.0.0.1:14551>>
#where the i.p. address is the IP of the mavlink stream.

from dronekit import connect, VehicleMode, LocationGlobalRelative
import time

#Connect to vehicle
import argparse
parser = argparse.ArgumentParser(description='commands')
parser.add_argument('--connect')
args=parser.parse_args()

connection_string=args.connect

print("Connection to the vehicle on %s" %connection_string)
vehicle = connect(connection_string, wait_ready=True)

#--Define the Function for takeoff

def arm_and_takeoff(tgt_altitude):
	print("Pre Arm Checks")

	while not vehicle.is_armable:
		print("Waiting for Vehicle to Initialize")
		time.sleep(1)
	
	print "Vehicle is Initialized"

	vehicle.mode = VehicleMode("GUIDED")
	vehicle.armed=True

	while not vehicle.armed:
		print "Waiting for arming..."
		time.sleep(1)

	print("Vehicle Armed")
	vehicle.simple_takeoff(tgt_altitude)
	print "Takeoff Started"	

	#--wait for drone to reach target altitude

	while True:
		altitude = vehicle.location.global_relative_frame.alt

		if altitude>=tgt_altitude -1:
			print ("Altitude Reached")
			break

		time.sleep(1)

#------Main Program----
arm_and_takeoff(10) #goes to 10m high

vehicle.airspeed = 7 #Sets the default airspeed

print("Going to Waypoint 1")

wp1=LocationGlobalRelative(35.37 , 149.2, 20)

vehicle.simple_goto(wp1)

time.sleep(30) #Waits for 30 seconds but never checks if drone reaches destination

vehicle.mode = VehicleMode("RTL")

time.sleep(20)

vehicle.close()
