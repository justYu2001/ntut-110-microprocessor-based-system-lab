import cv2 as cv
from device.adc_sensor import ADC_Sensor
from config import settings

class Camera:
    def __init__(self):
        self.capture = None

        if settings.mode == "development":
            self.capture = cv.VideoCapture(0)
        
        else:
            gst_str = ("nvarguscamerasrc ! "
               "video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)NV12, framerate=(fraction)30/1 ! "
               "nvvidconv ! video/x-raw, width=(int)1280, height=(int)720, format=(string)BGRx ! "
               "videoconvert ! appsink")

            self.capture = cv.VideoCapture(gst_str, cv.CAP_GSTREAMER)

    def generate_frames(self):
        while True:
            ret, frame = self.capture.read()

            if not ret:
                break

            if ADC_Sensor.get_value() > 600:
                frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

            _, jpeg = cv.imencode('.jpg', frame)

            yield (b'--frame\r\n'
                b'Content-Type: image/jpeg\r\n\r\n' + jpeg.tobytes() + b'\r\n')

camera = Camera()