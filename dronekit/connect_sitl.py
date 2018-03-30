print "Connecting to SITL"
import dronekit_sitl
from dronekit import connect, VehicleMode

vehicle = connect('tcp:127.0.0.1:5760', wait_ready=True)
