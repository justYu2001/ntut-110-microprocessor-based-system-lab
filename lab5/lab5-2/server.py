from urllib.request import Request
from fastapi import FastAPI, Response, status, WebSocket, Request
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from typing import Optional
from pydantic import BaseModel
from modules.device import Device
import asyncio

app = FastAPI()
templates = Jinja2Templates(directory = 'public')
app.mount('/public', StaticFiles(directory = 'public', html = True), name = "public")

device = Device()


@app.get('/')
async def root(request: Request):
    return templates.TemplateResponse("index.html", { "request": request })

class OperationBody(BaseModel):
    operation: str
    stateList: Optional[list]
    times: Optional[int]

@app.post("/operations", status_code = 201)
async def createOperation(body: OperationBody, response: Response):
    if body.operation == 'set state':
        if body.stateList == None:
            response.status_code = status.HTTP_400_BAD_REQUEST
            return { "message": "沒有給定狀態列表" }

        if len(body.stateList) != 4:
            response.status_code = status.HTTP_400_BAD_REQUEST
            return { "message": "狀態列表長度有誤，狀態列表長度必須為 4" }

        device.setAllLedStatus(body.stateList)
        return { "message": "LED 狀態更新成功" }

    elif body.operation == 'shine':
        if body.times == None:
            response.status_code = status.HTTP_400_BAD_REQUEST
            return { "message": "沒有給定閃爍次數" }

        await device.shine(body.times)
        return { "message": "LED 閃爍成功" }
    
    else:
        response.status_code = status.HTTP_400_BAD_REQUEST
        return { "message": "無法執行此操作" }

@app.websocket("/leds")
async def getLedStateList(websocket: WebSocket):
    async def sentLedStateList(ledStateList):
        await websocket.send_json({ 'stateList': ledStateList })

    await websocket.accept()
    while True:
        await device.onLedStateChange(sentLedStateList)

@app.websocket("/adc")
async def getADCValue(websocket: WebSocket):
    await websocket.accept()
    while True:
        adcValue = device.getADCValue()
        await websocket.send_text(str(adcValue))
        await asyncio.sleep(1)