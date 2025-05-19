#!/usr/bin/env python3
from random import randint, choice
import sys
from secret import flag


def main():
    print("Username:")
    username = input().strip()

    if username != "player":
        print("Access denied.")
        sys.exit(1)

    ops = ['+', '-', '*']
    for i in range(128):
        a = randint(1, 100)
        b = randint(1, 100)
        op = choice(ops)

        question = f"{a} {op} {b}"
        correct = eval(question)

        print(f"Challenge {i+1}: {question} = ?")
        try:
            answer = input().strip()
            if int(answer) != correct:
                print("Wrong answer. Bye!")
                sys.exit(1)
        except:
            print("Invalid input. Bye!")
            sys.exit(1)

    print(f"Congratulations! Here is your flag: {flag}")


if __name__ == "__main__":
    main()
