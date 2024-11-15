import time
st = time.time()
print(st)
st1 = time.localtime(st)
print(st1)
time.strftime("%Y-%m-%d %H:%M:%S", st1)

