import queue
import numpy as np

# array1 = np.arange(0, 10, 1)
# array2 = np.arange(10, 20, 1)

# array = np.array([array1, array2])

# myQueue = queue.Queue()

# myQueue.put(array)

# array1 = np.arange(0, 100, 1)
# array2 = np.arange(100, 200, 1)

# array = np.array([array1, array2])

# myQueue.put(array)

# # ----------------------------
# with open('test.txt', 'ab') as f:
#     while not myQueue.empty():
#         data = myQueue.get()
#         print(data)
#         np.savetxt(f, np.transpose(data), fmt='%d', delimiter=' ')
try:
    with open('./test/test.txt', 'w') as f:
        ...
except:
    print('无法创建文件')