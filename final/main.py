from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles

from api.api import api_router

app = FastAPI()

app.include_router(api_router, prefix = '/api')
app.mount("/", StaticFiles(directory = "public", html = True), name = "public")