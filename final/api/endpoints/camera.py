from fastapi import APIRouter
from fastapi.responses import HTMLResponse, StreamingResponse
from pydantic import BaseModel

from device import camera

router = APIRouter()

@router.get("/camera", response_class = HTMLResponse)
def video_feed():
    return StreamingResponse(camera.generate_frames(), media_type = 'multipart/x-mixed-replace; boundary=frame')

class CameraMode(BaseModel):
    mode: str

@router.patch("/set_camera_mode")
def set_camera_mode(mode_model: CameraMode):
    camera.set_mode(mode_model.mode)
    return mode_model