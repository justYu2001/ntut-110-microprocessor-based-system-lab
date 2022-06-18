from fastapi import APIRouter
from fastapi.responses import HTMLResponse, StreamingResponse
import cv2 as cv

router = APIRouter()

def generate_frames():
    cap = cv.VideoCapture(0)
    while True:
        res, frame = cap.read()
        if not res:
            break
        ret, jpeg = cv.imencode('.jpg', frame)

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + jpeg.tobytes() + b'\r\n')

@router.get("/camera", response_class = HTMLResponse)
def video_feed():
    return StreamingResponse(generate_frames(), media_type = 'multipart/x-mixed-replace; boundary=frame')