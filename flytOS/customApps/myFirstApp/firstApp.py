#Template from flytbase documentation. 

#!/usr/bin/env python

from flyt_python import api
drone = api.navigation(timeout=120000) # instance of flyt navigation class
time.sleep(3)
# Write your own logic below #
#
# When done, shutdown the drone interface
drone.disconnect()
