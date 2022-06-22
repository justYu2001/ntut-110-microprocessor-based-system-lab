from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles

from api import api_router
from ws import websocket_app

app = FastAPI()

app.mount("/websocket", websocket_app)
app.include_router(api_router, prefix = '/api')
app.mount("/", StaticFiles(directory = "public", html = True), name = "public")