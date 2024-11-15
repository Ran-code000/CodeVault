import time
get_ts = lambda:time.time()
print(get_ts())
nums = [1, 3, 2, 8, 10, 6]
nums.sort(key=lambda x : True if(x % 2) else False, reverse = False)
print(nums)