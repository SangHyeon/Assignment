import time
from datetime import datetime, timedelta
from socket import *

clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.settimeout(1)#waiting one second

get_ping = 0
start_time = time.time()#start process time
#initializing max/min rtt time
set_start = True
avg_rtt = 0
ping = 0

while True:
    curtime =  time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime())
    #or using datetime.datetime.now() (import datetime)
    test = "Ping " + str(ping) + " #" + curtime
    addr = ("127.0.0.1", 12000)#server address
    start = time.time()#change timming
    clientSocket.sendto(test, addr)#send to server with test message
    ping += 1
    try:
        message, server = clientSocket.recvfrom(1024)#recieve upper test message from client
        RTT = time.time() - start
        if set_start :
            late_rtt = RTT
            fast_rtt = RTT
            set_start = False
        else :
            if fast_rtt > RTT :
                fast_rtt = RTT
            elif late_rtt < RTT :
                late_rtt = RTT
        #print ping number and upper test message
        print '#RECV : \"%s\"  #RTT : %f' % (message, RTT)
        get_ping += 1
        avg_rtt += RTT

        time.sleep(1)
    except timeout:#if time out
        print 'Request timed out'
    except KeyboardInterrupt :
        whole_time = time.time() - start_time #calculate runnig time
        avg_RTT = avg_rtt / get_ping
        if (ping - get_ping) == 0 :
            data_loss = 0
        else :
            data_loss = ((ping - get_ping)*100)/ping
        print '#Whole Time : %f  #Min : %f  #Max : %f  #Avg : %f  #Loss : %d%%' \
                % (whole_time, fast_rtt, late_rtt, avg_RTT, data_loss)
        break

clientSocket.close()#close this socket
