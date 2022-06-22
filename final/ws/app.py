from xxlimited import new
from fastapi import FastAPI
from fastapi import FastAPI, WebSocket
import asyncio
import subprocess
from config import settings
from device import ADC_Sensor, camera

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
            subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller on", shell = True)
        
        elif newTimeString == "daytime" and settings.mode == "production":
            subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller off", shell = True)

        if timeString != newTimeString:
            timeString = newTimeString
            await websocket.send_text(timeString)
    
    subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller off", shell = True)

@websocket_app.websocket("/has_person")
async def getTime(websocket: WebSocket):
    await websocket.accept()

    while True:
        await asyncio.sleep(1)
        if camera.hasPerson():
            if settings.mode == "production":
                subprocess.run("./led_controller/driver/controller LED1 on", shell = True)

            await websocket.send_text("has person")
        else:
            if settings.mode == "production":
                subprocess.run("./led_controller/driver/controller LED1 off", shell = True)

            await websocket.send_text("no person")
    
    subprocess.run("./led_controller/driver/controller LED1 off", shell = True)