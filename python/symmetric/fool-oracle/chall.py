from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
from secret import flag

assert (len(flag) == len("CRYPTO25{}") + 36) # 46 => padded to 48
# + CRYPTO25{96ce8a9 + 2nd block of flag + 3rd block of flag
# 15*A + C + 
# RYPTO25{96ce8a9_
# RYPTO25{96ce8a9_ 

key = get_random_bytes(24)
flag = flag.encode()


def encrypt() -> bytes:
    data = bytes.fromhex(input("> ")) # 2 bytes
    payload = data + flag # 2 bytes + flag
    # -d548-4f88-bc6c*
    # AAAAAAAAAAAAAAAC
    # RYPTO25{96ce8a93
    # -d548-4f88-bc6c_
    # ________________

    cipher = AES.new(key=key, mode=AES.MODE_ECB)
    print(cipher.encrypt(pad(payload, AES.block_size)).hex())


def main():
    menu = \
        "What do you want to do?\n" + \
        "quit - quit the program\n" + \
        "enc - encrypt something\n" + \
        "help - show this menu again\n" + \
        "> "

    while True:
        cmd = input(menu).strip()

        if cmd == "quit":
            break
        elif cmd == "help":
            continue
        elif cmd == "enc":
            encrypt()


if __name__ == '__main__':
    main()
