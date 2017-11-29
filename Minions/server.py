import socket
import thread
import os


class Result(object):
	pass

def client_thread(clientsocket, address, filename, result):
    print str(address) + " connected"

    clientsocket.send(filename)
    print "made it here"
    result.r = clientsocket.recv(2048)

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
        if j < num_files:
            (clientsocket, address) = s.accept()
            threads.append(Result())
            thread.start_new_thread(client_thread, (clientsocket, address, filenames[j], threads[-1]))
        j += 1

        if j == num_files:
            for result in threads:
                print result.r
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
