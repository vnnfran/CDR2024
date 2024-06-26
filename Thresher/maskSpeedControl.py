import cv2 as cv
import numpy as np
import os
import time
import picar
from picar import front_wheels, back_wheels
from picar.SunFounder_PCA9685 import Servo

# Setup ruedas
picar.setup()
bw = back_wheels.Back_Wheels()
fw = front_wheels.Front_Wheels()
MIDDLE_TOLERANT = 5
FW_ANGLE_MAX    = 135
FW_ANGLE_MIN    = 0
FW_STRAIGHT     = 75

# Valores iniciales carrito
bw.speed = 0
fw.turn(FW_STRAIGHT)
motor_speed = 65 #45,50 ok
obstacle_count = 0
flag = False
moving = True

# Controlador proporcional
kp = 0.8		# 0.8 ok

# Variables para funcion centroide
imgwidth =  600 - 50
imgheight = 230 - 50

# Abrir camara
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

# Funcion para encontrar el centroide
def find_centroid(bw_im):
    # Tamano de la ventana 
    global imgheight
    global imgwidth
    
    # Reinicia promedio por frame
    xFinal = 0
    
    # Recorre frame de izq-der, arriba-abajo
    for y in range(1, imgheight,5):
        # Reinicia promedio y suma por fila
        xProm = 0; N = 0

        # Recorre pixeles de 5 en 5
        for x in range(1, imgwidth,5):
            tile = bw_im[y,x]
            
            # Mide color del pixel, 255 = blanco
            if tile == 255:
                # Si es blanco, se suma valor pixel
                xProm += x
                N += 1
                
        # Se obtiene centroide por fila
        if N > 0:
            xProm = int(xProm / N) 

        xFinal += xProm
    
    # Se obtiene centroide por frame
    xFinal = int(xFinal / (imgheight/5))
    # Marcar centroide en video
    cv.circle(bw_im, (xProm, imgheight//2), 4, (0,0,255),2)

    return xFinal

def movement(xFinal):
    # Obtiene diferencia de centroide video a mitad de cuadro
    error = (600-50)/2 - xFinal

    fw_angle= FW_STRAIGHT - int((error)*kp)
    
    if error > 100:
        motor_speed = 40
    else:
        motor_speed = 80
    
    bw.speed = motor_speed

    # Corrección de ángulo en caso de sobrepasar los límites
    if fw_angle<FW_ANGLE_MIN:
        fw_angle=FW_ANGLE_MIN
    
    if fw_angle>FW_ANGLE_MAX:
        fw_angle=FW_ANGLE_MAX
        
    #fw.turn(72)
    fw.turn(fw_angle)
          
    return error, fw_angle
        
def mask_blue(frame):
    global obstacle_count
    global flag
    # Club
    #lower_blue = np.array([103, 63, 155])
    #upper_blue = np.array([133, 255, 255])
    # Celda
    lower_blue = np.array([74, 57, 27])
    upper_blue = np.array([151, 255,255])
    blue_mask = cv.inRange(frame, lower_blue, upper_blue)
    pixel_count = cv.countNonZero(blue_mask)
    if pixel_count >= 5000 and flag == False:
        obstacle_count += 1
        flag = True
    elif pixel_count >= 5000 and flag == True:
        pass
    elif pixel_count < 30 and flag == True:
        flag = False
    else:
        pass

    return blue_mask, pixel_count

def mask_orange(frame):
    global moving
    # Celda
    lower_orange = np.array([17, 0, 213])
    upper_orange = np.array([36,255,255])
    orange_mask = cv.inRange(frame, lower_orange, upper_orange)
    pixel_count = cv.countNonZero(orange_mask)
    if pixel_count >= 15000:
        moving = False
    else:
        pass

    return orange_mask

while(True):
    # Guarda frame del video
    success, im = cap.read()

    # Recorta imagen para mejor procesamiento
    im = im[50:230, 70:620]
    im = cv.bilateralFilter(im, 5, 100, 100)
    im = cv.cvtColor(im, cv.COLOR_BGR2HSV)

    # Club
    #lColor = np.array([4,0,0])
    #dColor = np.array([179,165,231]) # 20,20,20
    # Celda
    #lColor = np.array([9,14,7])
    #dColor = np.array([179,102,170]) # 20,20,20
    lColor = np.array([0,14,27])
    dColor = np.array([179,255,216]) # 20,20,20
    lBlue = np.array([0,40,255])
    dBlue = np.array([179,236,255]) # 20,20,20
    bw_im = cv.inRange(im, lColor, dColor)
    bl_im = cv.inRange(im, lBlue, dBlue)
    #bl_im = cv.bitwise_not(bl_im)
    
    #bw_im = cv.bitwise_and(bw_im, bl_im)
    
    # Manda a llamar funcion centroide
    xF = find_centroid(bw_im)
    # Dependiendo centroide, cambia angulo ruedas
    err, angle = movement(xF)
    imsh = cv.resize(bw_im, (275, 75))
    cv.imshow("1", imsh)
    
    # Terminar ciclo
    if cv.waitKey(1) & 0xFF == ord('q') or moving == False:
        if moving == False:
            fw.turn(72)
            time.sleep(1)
        else:
            pass
        motor_speed = 0; bw.speed = 0;
        break

cap.release()
cv.destroyAllWindows()