import socket
import thread
import pandas as pd


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('localhost', 11001))

filename = s.recv(2048)
print filename

# df = pd.read_csv("airport-data/data/" + filename)
# summary_stats = df.describe()
#
# s.send(str(summary_stats))

s.close()
