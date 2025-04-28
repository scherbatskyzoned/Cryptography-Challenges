from pwn import *
from Crypto.Cipher import AES 
from string import hexdigits


# Sistema col padding 

HOST = "130.192.5.212" 
PORT = 6542

flag = "CRYPTO25{"

flag_edt = flag

server = remote(HOST, PORT)
possible_chars = hexdigits + '-' + '}'

# while True:
#     flag = flag_edt
#     if (len(flag) >= 16):
#         break
#     for char_to_try in possible_chars:
#         flag_edt = flag + char_to_try
#         always_padding = b"A" * 11
#         other_padding = b"A" * (AES.block_size - len(flag_edt))
#         pt = always_padding + other_padding + flag_edt.encode() + other_padding
#         # print(f"trying {flag_edt}")
#         server.sendlineafter(b"> ", "enc".encode())
#         server.sendlineafter(b"> ", pt.hex().encode())

#         ct_hex = server.recvline().strip().decode()
#         # print(ct_hex)
#         ct_bytes = bytes.fromhex(ct_hex)
#         # print(ct_bytes)
#         if (ct_bytes[AES.block_size:2*AES.block_size] == ct_bytes[2*AES.block_size:3*AES.block_size]):
#             print(f"correct char: {char_to_try}")
#             break

# print(f"First block: {flag_edt}")

## Get 2nd block
# flag = "CRYPTO25{ad3c6c1"
# i = 1

# while True:
#     if (len(flag) >= 32):
#         break
#     for char_to_try in possible_chars:
#         flag_edt = flag[i:] + char_to_try
#         assert(len(flag_edt) == 16)
#         always_padding = b"A" * 11
#         other_padding = b"A" * (AES.block_size - i)
#         pt = always_padding + flag_edt.encode() + other_padding
#         print(f"trying {flag_edt}")
#         server.sendlineafter(b"> ", "enc".encode())
#         server.sendlineafter(b"> ", pt.hex().encode())

#         ct_hex = server.recvline().strip().decode()
#         ct_bytes = bytes.fromhex(ct_hex)
#         if (ct_bytes[AES.block_size:2*AES.block_size] == ct_bytes[3*AES.block_size:4*AES.block_size]):
#             print(f"correct char: {char_to_try}")
#             i+=1
#             flag += char_to_try
#             break

# print(f"Second block: {flag_edt}")

## Get third block
flag = "CRYPTO25{ad3c6c1e-5cac-4c87-b5c3"
i = 1

while True:
    if (len(flag) >= 46):
        break
    for char_to_try in possible_chars:
        flag_edt = flag[AES.block_size+i:] + char_to_try
        assert(len(flag_edt) == 16)
        always_padding = b"A" * 11
        other_padding = b"A" * (AES.block_size - i)
        pt = always_padding + flag_edt.encode() + other_padding
        print(f"trying {flag_edt}")
        server.sendlineafter(b"> ", "enc".encode())
        server.sendlineafter(b"> ", pt.hex().encode())

        ct_hex = server.recvline().strip().decode()
        ct_bytes = bytes.fromhex(ct_hex)
        if (ct_bytes[AES.block_size:2*AES.block_size] == ct_bytes[4*AES.block_size:5*AES.block_size]):
            print(f"correct char: {char_to_try}")
            i+=1
            flag += char_to_try
            break

print(f"Third block: {flag_edt}")


print(f"Flag: {flag}")