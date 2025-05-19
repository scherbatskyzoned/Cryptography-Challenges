import requests
import time
from Crypto.Util.number import long_to_bytes, bytes_to_long

URL = "http://130.192.5.212:6522"
session = requests.Session()

def predict_expires():
    now = int(time.time())
    expires = now + 30 * 24 * 60 * 60
    return expires

def forge_cookie(orig_cookie_bytes, orig_plaintext, new_plaintext):
    # Recover the keystream
    keystream = bytes([c ^ p for c, p in zip(orig_cookie_bytes, orig_plaintext.encode())])

    # Forge new ciphertext
    forged = bytes([k ^ p for k, p in zip(keystream, new_plaintext.encode())])

    return forged

def try_expires_shifts(expires, shifts, cookie, nonce, username):
    for shift in shifts:
        new_expires = str(expires - shift)
        new_plaintext = f"username={username}&expires={new_expires}&admin=1"
        print(f"[*] Trying with expires = {new_expires}")

        try:
            forged_cookie_bytes = forge_cookie(cookie, 
                                                f"username={username}&expires={str(expires)}&admin=1", 
                                                new_plaintext)
        except Exception as e:
            print(f"[!] Failed to forge cookie: {e}")
            continue

        forged_cookie_long = bytes_to_long(forged_cookie_bytes)
        nonce_long = bytes_to_long(nonce)

        params = {
            "nonce": nonce_long,
            "cookie": forged_cookie_long
        }

        r = session.get(URL + "/flag", params=params)
        print("[*] Server response:")
        print(r.text)

        if "flag" in r.text.lower():
            print("[+] Got the flag!")
            break
        else:
            print("[-] Didn't work, trying next...")

def main():
    username = "attacker"
    params = {
        "username": username,
        "admin": "1"
    }

    print("[*] Logging in...")

    local_time_before = int(time.time())
    r = session.get(URL + "/login", params=params)
    local_time_after = int(time.time())

    data = r.json()
    nonce = long_to_bytes(data["nonce"])
    cookie = long_to_bytes(data["cookie"])

    print(f"[*] Got nonce ({len(nonce)} bytes) and cookie ({len(cookie)} bytes)")

    predicted_expires = predict_expires()
    print(f"[*] Predicted expires: {predicted_expires}")

    # Define shifts (seconds to subtract from expires)
    shifts_in_days = list(range(300, 500))  # Try substracting 300 days up to 500 days
    shifts_in_seconds = [d * 24 * 60 * 60 for d in shifts_in_days]    # Try original expires, minus ~5, ~10, ~15, ~20, ~25 days

    try_expires_shifts(predicted_expires, shifts_in_seconds, cookie, nonce, username)

if __name__ == "__main__":
    main()
