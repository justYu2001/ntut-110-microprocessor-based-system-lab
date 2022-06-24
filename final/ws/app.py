from fastapi import FastAPI
from fastapi import FastAPI, WebSocket
import asyncio
import subprocess
import requests
import json
from config import settings
from device import ADC_Sensor, camera

websocket_app = FastAPI()

def push_message(message):
    webhook_url = 'https://script.google.com/macros/s/AKfycbwTXPtKrcVBtsbx6kejWC--7l8ttPAyXTcvTEgpRKoNOcNCUeqlrWu9KJ5hARksIXlOgg/exec'
    data = {"message": message}
    requests.post(webhook_url, json.dumps(data))

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
            
            message = ""
            if time_string == "night":
                message = "夜晚模式"
            else:
                message = "白天模式"

            push_message("監視器已切換成" + message)
            
            await websocket.send_text(time_string)
        
@websocket_app.websocket("/has_person")
async def getTime(websocket: WebSocket):
    await websocket.accept()

    data = "no person"

    while True:
        new_data = ""
        await asyncio.sleep(1)
        if camera.hasPerson():
            if settings.mode == "production":
                subprocess.run("./led_controller/driver/controller LED1 on", shell = True)
            new_data = "has person"
        else:
            if settings.mode == "production":
                subprocess.run("./led_controller/driver/controller LED1 off", shell = True)
            
            new_data = "no person"

        if data != new_data:
            data = new_data

            if data == "has person":
                push_message("有可疑人士經過")

        await websocket.send_text(data)