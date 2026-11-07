from fastapi import FastAPI
from fastapi.responses import FileResponse
from fastapi.routing import StaticFiles

from routes.camera import router as camera_router
from routes.motor_control import router as controls_router

app = FastAPI()

app.mount("/static", StaticFiles(directory="./web/static"), name="static")
app.include_router(camera_router)
app.include_router(controls_router)


@app.get("/")
def dashboard():
    return FileResponse("web/index.html")
