from fastapi import APIRouter
from fastapi.responses import HTMLResponse, StreamingResponse

from device import camera

router = APIRouter()

@router.get("/camera", response_class = HTMLResponse)
def video_feed():
    return StreamingResponse(camera.generate_frames(), media_type = 'multipart/x-mixed-replace; boundary=frame')