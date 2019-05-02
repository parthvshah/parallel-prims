import os
os.system("make clean")
os.system("make bench")
for x in range(100, 20000+1, 100):
    os.system("./bench "+str(x)+" >> 4threads.txt")
os.system("make clean")
