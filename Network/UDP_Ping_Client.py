import random
import time
from socket import *

for ping in range(10): # 0~9
    clientSocket = socket(AF_INET, SOCK_DGRAM)
    clientSocket.settimeout(1)#wait one second
    curtime =  time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime())
    Ping = ping+1
    test = "Ping " + str(ping+1) + " " + curtime
    addr = ("127.0.0.1", 12000)#server address
    clientSocket.sendto(test, addr)#send to server with test message
    start = time.time()
    try:
        message, server = clientSocket.recvfrom(1024)#recieve upper test message from client
        RTT = time.time() - start
        #print ping number and TEST(upper 'test')
        print '#RECV : \"%s\"  #RTT : %f' % (message, RTT)
    except timeout:#if time out
        print 'Request timed out'
