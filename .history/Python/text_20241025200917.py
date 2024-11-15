import time
st = time.time()
print(st)
st1 = time.localtime(st)
print(st1)
print(time.strftime("%Y-%m-%d %H:%M:%S", st1))
s1 = "Sep 20 2024"
print(time.strptime(s1, "%b %d %Y"))
import calendar
print(calendar.calendar(2024))
print(calendar.month(2024,10))
print(time.gmtime())
import datetime
print(datetime.datetime.now())
print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))[[[[[[[[[[===========]]]]]]]]]]