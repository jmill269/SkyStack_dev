import sys

while True:
	line = sys.stdin.readline()
	line = line.replace("[","")
	line = line.replace("]","")
	values = line.split(',')
	xtrans = values[0]
	ytrans = values[1]
	ztrans = values[2]
	print(ytrans)
	#print("Y Translation: %s" % ytrans)
	#print("Z Translation: %s" % ztrans)
