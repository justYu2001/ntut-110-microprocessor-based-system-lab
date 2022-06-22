from fastapi import FastAPI
from fastapi import FastAPI, WebSocket
import asyncio
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
        if timeString != newTimeString:
            timeString = newTimeString
            await websocket.send_text(timeString)