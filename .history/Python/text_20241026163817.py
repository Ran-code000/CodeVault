import time
get_ts = lambda:time.time()
print(get_ts())
nums = [1, 3, 2, 8, 10, 6]
nums.sort(reverse = True)
print(nums)
chars = ['1', '2','3']
print(chars)
res = map(int, chars)
print(res)
print(list(res))
temp = [int(val) for val in chars]
print(temp)
print(sum(list([int(val) for val in chars])))
from functools import reduce
res = reduce(lambda x, y: x + y, range(1, 11))