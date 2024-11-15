import time
tm = time.time()
print(tm)
print(time.localtime(tm))
print(time.mktime(time.localtime(tm)))
stm = time.localtime()
print