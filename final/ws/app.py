from fastapi import FastAPI
from fastapi import FastAPI, WebSocket
import asyncio
import subprocess
from config import settings
from device import ADC_Sensor

websocket_app = FastAPI()

@websocket_app.websocket("/time")
async def getTime(websocket: WebSocket):
    await websocket.accept()
    timeString = "daytime"
    while True:
        await asyncio.sleep(1)
        ADC_value = ADC_Sensor.get_value()
        newTimeString = "night" if ADC_value > 600 else "daytime"

        if newTimeString == "night" and settings.mode == "production":
            subprocess.run("./led_controller/multithread/controller on")
        
        elif newTimeString == "daytime" and settings.mode == "production":
            subprocess.run("./led_controller/multithread/controller off")

        if timeString != newTimeString:
            timeString = newTimeString
            await websocket.send_text(timeString)