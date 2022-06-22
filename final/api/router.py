from fastapi import APIRouter

from api.endpoints import camera

api_router = APIRouter()
api_router.include_router(camera.router)