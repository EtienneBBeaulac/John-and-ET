import socket
import thread
import os


class Result(object):
	pass

def client_thread(clientsocket, address, filename):
    print str(address) + " connected"

    clientsocket.send(filename)
    print "made it here"
    m = clientsocket.recv(2048)
    result.r = m

    clientsocket.close()


if __name__ == '__main__':
    # try:
    filenames = [ name for name in os.listdir('airport-data/data/') ]
    num_files = len(filenames)

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('', 11001))
    s.listen(10)

    print "Server listening on port 11000"

    threads = []
    j = 0
    while True:
        (clientsocket, address) = s.accept()
        threads.append(Result())
        thread.start_new_thread(client_thread, (clientsocket, address, filenames[j]))
        j += 1

    # except Exception(e):
    #     print e


    s.close()

"""
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 11000))

s.listen(5)

start = 0
threads = []
while 1:
	(clientsocket, address) = s.accept()
	threads.append(Result())
	thread.start_new_thread(client_thread, (clientsocket, address, start, threads[-1]))
	start = start + 10

	if start > 50:
		for result in threads:
			print result.r
		break
"""
