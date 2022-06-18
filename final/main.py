from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from ws.app import websocket_app

app = FastAPI()

app.mount("/websocket", websocket_app)
app.mount("/", StaticFiles(directory = "public", html = True), name = "public")