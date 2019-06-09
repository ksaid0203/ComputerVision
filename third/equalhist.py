
import cv2
import numpy as np

img = cv2.imread('VM2F9231GRAYBAD.jpg', 0)

histeq = cv2.equalizeHist(img)

#cv2.imshow('Input', img)
#cv2.imshow('Histogram equalized', histeq)
cv2.imwrite('hello.jpg',histeq)
cv2.waitKey(0)

