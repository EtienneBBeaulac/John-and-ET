import numpy as np


with open('rand_nums.txt', 'wt') as f:
    for _ in range(100000):
        rand_int = np.random.randint(0, 10)
        f.write(str(rand_int) + " ")
