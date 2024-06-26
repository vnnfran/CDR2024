import cv2
from picar import front_wheels, back_wheels
import picar
import threading
from picar.SunFounder_PCA9685 import Servo

picar.setup()

rear_wheels_enable = True
front_wheels_enable = True

bw = back_wheels.Back_Wheels()
fw = front_wheels.Front_Wheels()


bw.speed = 0
fw.turn(72)

cap = cv2.imshow('/home/pi/Desktop/RC Handcraft/aurora.jpg',1)
y= 0
fw.offset = 0

def cam():
    global cap

def movement():
    global y
    if y == ord('w'):
        bw.speed = 60
        bw.backward()
        fw.turn(72)
    
    elif y == ord('s'):
        bw.speed = 60
        bw.forward()
        fw.turn(72)
    
    elif y == ord('q'):
        bw.speed = 60
        bw.backward()
        fw.turn(0)
    
    elif y == ord('6'):
        bw.speed = 60
        bw.backward()
        fw.turn(92)
        
    elif y == ord('a'):
        bw.speed = 60
        bw.forward()
        fw.turn(0)
    
    elif y == ord('d'):
        bw.speed = 60
        bw.forward()
        fw.turn(92)
        
    elif y == ord('z'):
        bw.stop()
            
        # Add other movement commands here

if __name__ == "__main__":
    while True:
        y = cv2.waitKey(1) & 0xFF
        cam()
        movement()
        
    cap.release()
    cv2.destroyAllWindows()

