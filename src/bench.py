import os
os.system("make clean")
os.system("make bench")
for x in range(100, 20000+1, 100):
    os.system("./bench "+str(x)+" >> 2threads.txt")
