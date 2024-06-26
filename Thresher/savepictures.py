import cv2 as cv
import os
import numpy as np

# Create a directory to save the frames if it doesn't exist
#save_dir = '/home/pi/Desktop/Aut/pictures'
#if not os.path.exists(save_dir):
    #os.makedirs(save_dir)

# Initialize webcam
cap = cv.VideoCapture(0)
cap.set(3 , 640) # width        
cap.set(4 , 480) # height       
cap.set(10, 80) # brightness     min: 0   , max: 255 , increment:1  
cap.set(11, 200) # contrast       min: 0   , max: 255 , increment:1     
cap.set(12, 170) # saturation     min: 0   , max: 255 , increment:1
cap.set(13, 10) # hue         
cap.set(14, 35) # gain           min: 0   , max: 127 , increment:1
cap.set(15, -6) # exposure       min: -7  , max: -1  , increment:1
cap.set(17, 4500) # white_balance  min: 4000, max: 7000, increment:1
cap.set(28, 0) # focus          min: 0   , max: 255 , increment:5


# Counter for frame number
frame_num = 0

while True:
    # Capture frame-by-frame
    ret, im = cap.read()
    #im = cv.resize(im, (224, 224))
    #im = im[50:600, 50:600]
    #im = cv.cvtColor(im, cv.COLOR_BGR2HSV)
    #lColor = np.array([0,0,0])
    #dColor = np.array([179,68,175]) # 20,20,20
    #im = cv.inRange(im, lColor, dColor)

    # Display the resulting frame
    cv.imshow('Frame', im)

    # Save the frame
    #frame_path = os.path.join(save_dir, f'frame_{frame_num}.jpg')
    #cv.imwrite(frame_path, im)
    #frame_num += 1

    # Press 'q' to exit the loop
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close all windows
cap.release()
cv.destroyAllWindows()