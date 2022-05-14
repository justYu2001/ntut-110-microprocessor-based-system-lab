from urllib.request import Request
from fastapi import FastAPI, Response, status, Request
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from typing import Optional
from pydantic import BaseModel
from modules.device import Device

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
    print(body)
    if body.operation == 'set state':
        if body.stateList == None:
            response.status_code = status.HTTP_400_BAD_REQUEST
            return { "message": "沒有給定狀態列表" }

        if len(body.stateList) != 2:
            response.status_code = status.HTTP_400_BAD_REQUEST
            return { "message": "狀態列表長度有誤，狀態列表長度必須為 2" }

        device.setAllLedState(body.stateList)
        return { "stateList": device.getAllLedState() }

    elif body.operation == 'shine':
        if body.times == None:
            response.status_code = status.HTTP_400_BAD_REQUEST
            return { "message": "沒有給定閃爍次數" }

        device.shine(body.times)
        return { "time": 800 }
    
    else:
        response.status_code = status.HTTP_400_BAD_REQUEST
        return { "message": "無法執行此操作" }

@app.get("/adc", status_code = 200)
async def getAdcValue():
    return device.getADCValue()