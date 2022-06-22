from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from config import settings
from device.adc import initialize_adc_sensor
from api.api import api_router
from ws.app import websocket_app

if settings.mode == "production":
    initialize_adc_sensor()

app = FastAPI()

app.mount("/websocket", websocket_app)
app.include_router(api_router, prefix = '/api')
app.mount("/", StaticFiles(directory = "public", html = True), name = "public")