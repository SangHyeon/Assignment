# -*- coding: utf-8 -*-
# UDPPingerServer.py
# We will need the following module to generate randomized lost packets import random
import random
import time
from socket import *

# Create a UDP socket 
# Notice the use of SOCK_DGRAM for UDP packets
#serverSocket = socket(socket.AF_INET, socket.SOCK_DGRAM) # Assign IP address and port number to socket
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', 12000))
serverSocket.settimeout(10)
send_time = time.time()
while True:
    try:
        # Generate random number in the range of 0 to 10
        rand = random.randint(0, 10)    
        # Receive the client packet along with the address it is coming from 
        message, address = serverSocket.recvfrom(1024)
        #recv_time = time.time()
        recv_time = time.mktime(time.strptime(message.split('#')[1], \
                "%Y-%m-%d %H:%M:%S"))
        # Capitalize the message from the client
        message = message.upper()
        # If rand is less is than 4, we consider the packet lost and do not respond
        if rand < 4:
            time_diff = time.time() - send_time
            send_time = time.time()
            print "Can't Receive Packet #Time Difference : %f" % time_diff
            continue
        # Otherwise, the server responds    
        serverSocket.sendto(message, address)
        send_time = time.time()
        time_diff = time.time() - recv_time - 32400
        print '#Time Difference : %f' % time_diff
    except timeout:
        print 'Client is Dead'
        break

serverSocket.close()
