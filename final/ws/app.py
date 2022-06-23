from xxlimited import new
from fastapi import FastAPI, WebSocketDisconnect
from fastapi import FastAPI, WebSocket
import asyncio
import subprocess
from config import settings
from device import ADC_Sensor, camera

websocket_app = FastAPI()

@websocket_app.websocket("/time")
async def getTime(websocket: WebSocket):
    await websocket.accept()
    time_string = "daytime"
    
    while True:
        await asyncio.sleep(1)
        ADC_value = ADC_Sensor.get_value()
        if camera.get_mode() == "auto":
            new_time_string = "night" if ADC_value > 800 else "daytime"
        else:
            new_time_string = camera.get_mode()

        if new_time_string == "night" and settings.mode == "production":
            subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller on", shell = True)
        
        elif new_time_string == "daytime" and settings.mode == "production":
            subprocess.run("echo nvidia | sudo -S ./led_controller/multithread/controller off", shell = True)

        if time_string != new_time_string:
            time_string = new_time_string
            await websocket.send_text(time_string)
        
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
