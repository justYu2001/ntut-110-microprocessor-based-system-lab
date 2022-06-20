from fastapi import APIRouter
from fastapi.responses import HTMLResponse, StreamingResponse
import cv2 as cv

from config import settings

router = APIRouter()

def open_cam_onboard(width, height):
    gst_str = ("nvarguscamerasrc ! "
               "video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)NV12, framerate=(fraction)30/1 ! "
               "nvvidconv ! video/x-raw, width=(int){}, height=(int){}, format=(string)BGRx ! "
               "videoconvert ! appsink").format(width, height)
    return cv.VideoCapture(gst_str, cv.CAP_GSTREAMER)

def generate_frames():
    cap = None

    if settings.mode == "development":
        cap = cv.VideoCapture(0)
    else:
        cap = open_cam_onboard(1280, 720)

    while True:
        res, frame = cap.read()
        if not res:
            break
        _, jpeg = cv.imencode('.jpg', frame)

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + jpeg.tobytes() + b'\r\n')

@router.get("/camera", response_class = HTMLResponse)
def video_feed():
    return StreamingResponse(generate_frames(), media_type = 'multipart/x-mixed-replace; boundary=frame')