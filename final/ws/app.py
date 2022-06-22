from fastapi import FastAPI
from fastapi import FastAPI, WebSocket
import asyncio
import subprocess
from config import settings
from device.adc import get_adc_value

websocket_app = FastAPI()

@websocket_app.websocket("/time")
async def getTime(websocket: WebSocket):
    await websocket.accept()
    timeString = "daytime"
    while True:
        await asyncio.sleep(1)
        value = get_adc_value()
        newTimeString = "night" if value > 600 else "daytime"

        if newTimeString == "night" and settings.mode == "production":
            subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller on", shell = True)
        
        elif newTimeString == "daytime" and settings.mode == "production":
            subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller off", shell = True)

        if timeString != newTimeString:
            timeString = newTimeString
            await websocket.send_text(timeString)