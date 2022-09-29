import sys
import cv2 as cv
import numpy as np

img = cv.imread("IMG_2859.jpg")
cv.imshow('Image',img)

number_black = np.sum(img == 225) # filter img so red is black, easier than doing the exact rgb value of the red on screen
