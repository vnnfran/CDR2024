import time
import cv2
import threading 
from picar import front_wheels, back_wheels
from picar.SunFounder_PCA9685 import Servo
import picar
from RPi import GPIO

# Setup for the GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setup(13, GPIO.IN)  # Channel 1 for forward/backward
GPIO.setup(12, GPIO.IN)  # Channel 2 for left/right

picar.setup()
rear_wheels_enable  = True
front_wheels_enable = True
bw = back_wheels.Back_Wheels()
fw = front_wheels.Front_Wheels()
picar.setup()
y = 0
fw.offset = 0
bw.speed = 0
fw.turn(100)
cap = cv2.VideoCapture(0)

width, height = 886, 608 # Width of camera, #Height of Camera 
cap.set(cv2.CAP_PROP_FRAME_WIDTH, width) 
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)

def movement():
    def read_pwm(channel):
        GPIO.setup(channel, GPIO.IN)
        start = time.time()
        while GPIO.input(channel) == GPIO.LOW:
            start = time.time()
        while GPIO.input(channel) == GPIO.HIGH:
            end = time.time()
        duration = (end - start) * 1000000
        return duration
        


    # Control functions
    def forward():
        print('Moving Forward')
        bw.forward()
        bw.speed = 99  # Set speed, adjust as necessary

    def backward():
        print('Moving Backward')
        bw.backward()
        bw.speed = 99  # Set speed, adjust as necessary

    def stop():
        print('Stopping')
        bw.stop()

    def turn_left():
        print('Turning Left')
        fw.turn_left()

    def turn_right():
        print('Turning Right')
        fw.turn_right()

    def straight():
        print('Turning Straight')
        fw.turn_straight()

    # Thread to handle RC commands
    def rc_control():
        while True:
            ch1 = read_pwm(13)
            ch2 = read_pwm(12)

            #Threshold values may need adjusting based on your RC setup
            if ch1 < 1300:
                backward()
            elif ch1 > 1700:
                forward()
            else:
                stop()

            if ch2 < 1200:
                turn_right()
            elif ch2 > 1800:
                turn_left()
            else:
                straight()

            time.sleep(0.1)
        

    # Start the RC control thread
    rc_thread = threading.Thread(target=rc_control)
    rc_thread.daemon = True
    rc_thread.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        GPIO.cleanup()
        print("Program terminated.")
        
# def cam():
    # global Dashboard2
    # while True:
        # ret, frame = cap.read()
        # if not ret:
            # break
        # frame = cv2.resize(frame, (226, 200))
        # cv2.imshow('frame', frame)
        # if cv2.waitKey(1) & 0xFF == ord('q'):
            # break
    # cap.release()
    # cv2.destroyAllWindows()
    
       
if __name__ == "__main__":
    while True: 
        b = threading.Thread(target = movement)
        b.start()
        b.join()

