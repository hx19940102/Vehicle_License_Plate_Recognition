# Vehicle_License_Plate_Recognition

This project is mainly implemented with C, Opencv 2.4.9 and MFC.

The program could be divided into twp parts:
1. License plate localization
2. Segment numbers and letters out and recognize them

# 1. License plate localization
The original image:
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/tree/master/images/plate1.png)

(1) Use sobel calculator to get the X-direction derivative.

![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/tree/master/images/sobel.png)
