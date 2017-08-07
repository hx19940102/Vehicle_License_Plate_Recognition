# Vehicle_License_Plate_Recognition

This project is mainly implemented with C, Opencv 2.4.9 and MFC.

The program could be divided into twp parts:
1. License plate localization
2. Segment numbers and letters out and recognize them

# 1. License plate localization
The original image:
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/plate1.jpg)

(1) Use sobel calculator to get the X-direction derivative.

![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/sobel.png)

(2) Use dilate and erode to remove noise pieces and connect the neighboring regions.

![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/morph.png)

(3) Find the contours based on (2) and get the bounding box. Select the most possible region as the license plate region.

![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/locate.png)

# 2. Segment numbers and letters out and recognize them

(4) Segment ROI of the licnese plate and apply thresholding.

![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/plate.png)
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/plate_.png)

(5) Find contours of each letters and numbers and then segment them out as individuals.
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/segments.jpg)

(6) Apply template matching/feature matching to recognize each number and letter. Maybe in the future will add Convolution Network for classification.

![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/result1.jpg)

# Results
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/result1.jpg)
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/result2.png)
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/result3.png)
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/result4.png)
![alt text](https://github.com/hx19940102/Vehicle_License_Plate_Recognition/blob/master/images/result5.png)
