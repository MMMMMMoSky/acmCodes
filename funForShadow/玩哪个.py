# coding: utf-8

import random

def 玩哪个():
    a = random.randint(0, 100)
    if a&1 : print("王者荣耀")
    else: print("吃鸡")

if __name__ == "__main__":
    玩哪个()

