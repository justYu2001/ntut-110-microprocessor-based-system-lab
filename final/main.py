from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
import subprocess

from config import settings
from api import api_router
from ws import websocket_app

app = FastAPI()

app.mount("/websocket", websocket_app)
app.include_router(api_router, prefix = '/api')
app.mount("/", StaticFiles(directory = "public", html = True), name = "public")

@app.on_event("shutdown")
def shutdown():
    if settings.mode == "production":
        subprocess.run("./led_controller/driver/controller LED1 off", shell = True)
        subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller off", shell = True)