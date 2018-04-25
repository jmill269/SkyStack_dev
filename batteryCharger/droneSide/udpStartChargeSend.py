import socket
import time

mainSock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
time.sleep(1)
mainSock.sendto(1,("10.0.0.185",5005)


