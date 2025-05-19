from pwn import *
from Crypto.Cipher import AES
from string import hexdigits

HOST = "130.192.5.212"
PORT = 6541

flag = "CRYPTO25{"
flag_edt = flag
server = remote(HOST, PORT)

possible_chars = hexdigits + '-' + '}'

# Get 1st block
# while True:
#     flag = flag_edt
#     if len(flag) >= 16:
#         break
#     for char_to_try in printable:
#         flag_edt = flag + char_to_try
#         padding = "A" * (AES.block_size-len(flag_edt))
#         pt = (padding + flag_edt + padding).encode()

#         # print(f"Trying {flag_edt}")
#         server.sendlineafter(b"> ", "enc".encode())
#         server.sendlineafter(b"> ", pt.hex().encode())

#         ct_hex = server.recvline().strip().decode()
#         ct_bytes = bytes.fromhex(ct_hex)

#         if (ct_bytes[:AES.block_size] == ct_bytes[AES.block_size:2*AES.block_size]):
#             print(f"correct char: {char_to_try}")
#             break
# print(f"First block: {flag_edt}")

# Get 2nd block
# flag = "CRYPTO25{96ce8a9"
# i = 1
# while True:

#     if len(flag) >= 46:
#         break
#     for char_to_try in possible_chars:
#         flag_edt = flag[i:] + char_to_try
#         print(f"Trying {flag_edt}")
#         assert(len(flag_edt)==16)
#         padding = "A" * (16-i)
#         pt = (flag_edt + padding).encode()

#         server.sendlineafter(b"> ", "enc".encode())
#         server.sendlineafter(b"> ", pt.hex().encode())

#         ct_hex = server.recvline().strip().decode()
#         ct_bytes = bytes.fromhex(ct_hex)

#         if (ct_bytes[:AES.block_size] == ct_bytes[2*AES.block_size:3*AES.block_size]):
#             print(f"correct char: {char_to_try}")
#             flag = flag + char_to_try
#             i+=1
#             break

# print(f"Second block: {flag}")

flag = "CRYPTO25{96ce8a93-d548-4f88-bc6c"

i = 1
while True:
    if len(flag) >= 46:
        break
    for char_to_try in possible_chars:
        flag_edt = flag[16+i:] + char_to_try
        print(f"Trying {flag_edt}")
        assert(len(flag_edt)==16)
        padding = "A" * (16-i)
        pt = (flag_edt + padding).encode()

        server.sendlineafter(b"> ", "enc".encode())
        server.sendlineafter(b"> ", pt.hex().encode())

        ct_hex = server.recvline().strip().decode()
        ct_bytes = bytes.fromhex(ct_hex)

        if (ct_bytes[:AES.block_size] == ct_bytes[3*AES.block_size:4*AES.block_size]):
            print(f"correct char: {char_to_try}")
            flag = flag + char_to_try
            i+=1
            break

print(f"Flag: {flag}")

server.close()


