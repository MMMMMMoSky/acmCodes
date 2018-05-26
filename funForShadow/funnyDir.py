# -*- coding: utf-8 -*-
while True:
    a = input()
    f = open("dirCmd.bat", "a")
    f.write("mkdir "+"\""+a+"\"\n")
    f.write("cd "+"\""+a+"\"\n")
    f.close()
