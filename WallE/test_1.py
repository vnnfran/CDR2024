import cv2
import depthai as dai
import numpy as np

pipeline = dai.Pipeline()

camRgb = pipeline.create(dai.node.ColorCamera)
xoutVideo = pipeline.create(dai.node.XLinkOut)

xoutVideo.setStreamName("video")

camRgb.setBoardSocket(dai.CameraBoardSocket.RGB)
camRgb.setResolution(dai.ColorCameraProperties.SensorResolution.THE_1080_P)
camRgb.setFps(30)

camRgb.video.link(xoutVideo.input)

with dai.Device(pipeline) as device:
    video = device.getOutputQueue(name="video", maxSize=30, blocking=True)

    while True:
        videoIn = video.get()
        frame = videoIn.getCvFrame()

        # Convertir la imagen de BGR a HSV
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Definir los rangos de color en HSV
        lower_red = np.array([0, 120, 70])
        upper_red = np.array([10, 255, 255])

        lower_orange = np.array([10, 100, 20])
        upper_orange = np.array([25, 255, 255])

        lower_yellow = np.array([25, 100, 20])
        upper_yellow = np.array([35, 255, 255])

        lower_green = np.array([35, 100, 20])
        upper_green = np.array([85, 255, 255])

        lower_blue = np.array([85, 100, 20])
        upper_blue = np.array([125, 255, 255])

        # Crear máscaras de color
        mask_red = cv2.inRange(hsv, lower_red, upper_red)
        mask_orange = cv2.inRange(hsv, lower_orange, upper_orange)
        mask_yellow = cv2.inRange(hsv, lower_yellow, upper_yellow)
        mask_green = cv2.inRange(hsv, lower_green, upper_green)
        mask_blue = cv2.inRange(hsv, lower_blue, upper_blue)

        # Combinar todas las máscaras
        combined_mask = cv2.bitwise_or(mask_red, mask_orange)
        combined_mask = cv2.bitwise_or(combined_mask, mask_yellow)
        combined_mask = cv2.bitwise_or(combined_mask, mask_green)
        combined_mask = cv2.bitwise_or(combined_mask, mask_blue)

        # Aplicar la máscara combinada a la imagen original
        result = cv2.bitwise_and(frame, frame, mask=combined_mask)

        # Encontrar contornos
        contours, _ = cv2.findContours(combined_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for contour in contours:
            # Filtrar contornos por área
            area = cv2.contourArea(contour)
            if area > 100:  # Ajusta este valor según el tamaño de las pelotitas
                # Calcular el centroide
                M = cv2.moments(contour)
                if M["m00"] != 0:
                    cX = int(M["m10"] / M["m00"])
                    cY = int(M["m01"] / M["m00"])
                    # Dibujar el centroide en la imagen
                    cv2.circle(result, (cX, cY), 5, (255, 255, 255), -1)
                    cv2.putText(result, "centroide", (cX - 25, cY - 25), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)

        # Mostrar la imagen original y la imagen con la máscara aplicada
        cv2.imshow("Imagen de la cámara de profundidad", frame)
        cv2.imshow("Colores resaltados", result)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cv2.destroyAllWindows()