import sys
import time

i=0
while True:
	print(i)
	i+= 1
	sys.stdout.flush()
	time.sleep(2)

