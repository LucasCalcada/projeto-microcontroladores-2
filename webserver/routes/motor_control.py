import asyncio
import struct
from fastapi import APIRouter, WebSocket, WebSocketDisconnect
from smbus2 import SMBus, i2c_msg

router = APIRouter()

I2C_ADDRESS = 0x10

bus = SMBus(1)
i2c_lock = asyncio.Lock()


def send_i2c_command(x, y, rotation):
    payload = struct.pack("<fff", x, y, rotation)
    message = i2c_msg.write(I2C_ADDRESS, payload)
    bus.i2c_rdwr(message)


@router.websocket("/controls")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()

    try:
        while True:
            command = await websocket.receive_json()

            x = float(command["x"])
            y = float(command["y"])
            rotation = float(command["rotation"])

            print(f"[DEBUG] Client send command: {command}")

            async with i2c_lock:
                await asyncio.to_thread(send_i2c_command, x, y, rotation)

            await websocket.send_text("OK")

    except WebSocketDisconnect:
        print("[DEBUG] Client disconnected")
