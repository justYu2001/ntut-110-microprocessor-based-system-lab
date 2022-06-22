import cv2 as cv
from device.adc_sensor import ADC_Sensor
from config import settings

class Camera:
    def __init__(self):
        self.hog = cv.HOGDescriptor()
        self.hog.setSVMDetector(cv.HOGDescriptor_getDefaultPeopleDetector())

        self.capture = None

        if settings.mode == "development":
            self.capture = cv.VideoCapture(0)
        
        else:
            gst_str = ("nvarguscamerasrc ! "
                       "video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)NV12, framerate=(fraction)30/1 ! "
                       "nvvidconv ! video/x-raw, width=(int)1280, height=(int)720, format=(string)BGRx ! "
                       "videoconvert ! appsink")

            self.capture = cv.VideoCapture(gst_str, cv.CAP_GSTREAMER)

        self.current_frame = None
        self.ret = False

    def generate_frames(self):
        while True:
            self.ret, self.current_frame = self.capture.read()

            if not self.ret:
                break

            frame = self.current_frame

            if ADC_Sensor.get_value() > 900:
                frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

            _, jpeg = cv.imencode('.jpg', self.current_frame)

            yield (b'--frame\r\n'
                b'Content-Type: image/jpeg\r\n\r\n' + jpeg.tobytes() + b'\r\n')

    def hasPerson(self):
        face_cascade = cv.CascadeClassifier('./device/haarcascade_frontalface_default.xml')

        if not self.ret:
            return False

        gray = cv.cvtColor(self.current_frame, cv.COLOR_BGR2GRAY)
        
        faces = face_cascade.detectMultiScale(gray, 1.1, 4)

        return len(faces) > 0


camera = Camera()