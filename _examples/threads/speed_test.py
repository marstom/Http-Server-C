#! python3


import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect(("localhost", 8989))
    s.sendall(b"../../server.c\n")
    data = s.recv(4096).decode()

print("received:")
print(data)