# -*- coding: utf-8 -*-
# UDPPingerServer.py
# We will need the following module to generate randomized lost packets import random
import random
import time
from datetime import datetime, timedelta
from socket import *

# Create a UDP socket 
# Notice the use of SOCK_DGRAM for UDP packets
#serverSocket = socket(socket.AF_INET, socket.SOCK_DGRAM) # Assign IP address and port number to socket
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', 12000))
serverSocket.settimeout(10)
#send_time = time.time()
temp_time = datetime.now().strftime("%H:%M:%S.%f")
send_time = float(temp_time.split(':')[2])
while True:
    try:
        # Generate random number in the range of 0 to 10
        rand = random.randint(0, 10)    
        # Receive the client packet along with the address it is coming from 
        message, address = serverSocket.recvfrom(1024)
        #Second and Microsecond
        temp_time = datetime.now().strftime("%H:%M:%S.%f")
        cur_time = float(temp_time.split(':')[2])

        recv_time = float(message.split(':')[2])
        ping_number = int(message.split(' ')[1])+1
        # Capitalize the message from the client
        message = message.upper()
        # If rand is less is than 4, we consider the packet lost and do not respond
        if rand < 4:
            print "Can't Receive Packet(Ping) Num : %d  #Time Difference : %f" % \
                    (ping_number, cur_time - send_time)
            temp_time = datetime.now().strftime("%H:%M:%S.%f")
            send_time = float(temp_time.split(':')[2])
            continue
        
        print 'Packet(Ping) Num : %d  #Time Difference : %f' % \
                (ping_number, cur_time - recv_time)
        # Otherwise, the server responds    
        serverSocket.sendto(message, address)
        temp_time = datetime.now().strftime("%H:%M:%S.%f")
        send_time = float(temp_time.split(':')[2])
    except timeout:
        print 'Client is Dead'
        break

serverSocket.close()
