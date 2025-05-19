from pwn import remote
from fractions import Fraction
from Crypto.Util.number import long_to_bytes

# THIS WORKED 

HOST = "130.192.5.212"
PORT = 6647

e = 65537

# 1) establish one persistent connection
conn = remote(HOST, PORT)

# 2) read n and the flag ciphertext c
n = int(conn.recvline().decode().strip())
c = int(conn.recvline().decode().strip())

# 3) we track x = m/n in [0,1] exactly as a Fraction
low = Fraction(0, 1)
high = Fraction(1, 1)

# 4) precompute the multiplier s = Enc(2) = 2^e mod n
s = pow(2, e, n)

# 5) iteratively do the LSB oracle attack
c_temp = c
nbits = n.bit_length()
for i in range(nbits):
    # shift ciphertext to get Enc(2^i * m)
    c_temp = (c_temp * s) % n

    # query the oracle for LSB of decrypted(c_temp)
    conn.sendline(str(c_temp).encode())
    bit = int(conn.recvline().strip())

    # binary‐search on x = m/n
    mid = (low + high) / 2
    if bit == 0:
        # LSB=0 ⇒ 2*m < n ⇒ m/n < ½ ⇒ x in [low, mid]
        high = mid
    else:
        # LSB=1 ⇒ 2*m ≥ n ⇒ m/n ≥ ½ ⇒ x in [mid, high]
        low = mid

    # (optional) you can print progress every 100 bits:
    if i % 100 == 0:
        print(f"[+] recovered ~{i}/{nbits} bits; interval width = {(high-low):.2%}")

    # early stop once interval narrows to a single integer
    if (high - low) * n < 1:
        break

# 6) reconstruct m = floor(high * n) and decode
m_recovered = (high * n).numerator // (high * n).denominator
flag = long_to_bytes(m_recovered)
print("Recovered flag:", flag.decode())
