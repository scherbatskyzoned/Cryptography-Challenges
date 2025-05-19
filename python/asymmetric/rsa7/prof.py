from pwn import *
from Crypto.Util.number import long_to_bytes

def print_bounds(lower_bound, upper_bound):
    print(f"Lower bound: {lower_bound}")
    print(f"Upper bound: {upper_bound}")

HOST = "130.192.5.212"
PORT = 6647
e = 65537
server = remote(HOST, PORT)
n = int(server.recvline().decode().strip())
ciphertext = int(server.recvline().decode().strip())
print(f"n: {n}")
print(f"ciphertext: {ciphertext}")


upper_bound = n
lower_bound = 0
print_bounds(lower_bound, upper_bound)

m = ciphertext
for i in range(n.bit_length()):
    m = (pow(2, e, n) * m) % n
    server.sendline(str(m).encode())
    bit = server.recvline()
    # print(bit)

    if bit[0] == 1:
        lower_bound = (lower_bound + upper_bound) // 2
    else:
        upper_bound = (lower_bound + upper_bound) // 2

    # print_bounds(lower_bound, upper_bound)

print(lower_bound.to_bytes(n.bit_length()+30, byteorder='big'))
server.close()
