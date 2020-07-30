import cv2 as cv
import numpy as np

data = cv.imread("lena.jpeg")

resized = cv.resize(data, (70, 100), cv.INTER_NEAREST)
np.savetxt("near_py.txt", resized.flatten(), fmt='%d', delimiter='\n')

resized = cv.resize(data, (70, 100), cv.INTER_LINEAR)
np.savetxt("linear_py.txt", resized.flatten(), fmt='%d', delimiter='\n')
