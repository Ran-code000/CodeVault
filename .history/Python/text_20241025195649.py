import time
st = time.time()
print(st)
st1 = time.localtime(st)
print(st1)
print(time.strftime("%Y-%m-%d %H:%M:%S", st1))
s1 = "Sep. 20 2024"
print(time.strptime(s1, "%B %d %Y"))
