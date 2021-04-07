import socket
import random

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect(('localhost', 8080))
    sock.sendall(bytes(f"./tests/testfiles/f{random.randint(1, 4)}.txt\n", "utf-8"))
    data = sock.recv(4096)
# print(data)