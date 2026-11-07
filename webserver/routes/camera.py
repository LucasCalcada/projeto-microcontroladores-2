from fastapi import APIRouter
from fastapi.responses import StreamingResponse

from camera.video_source import VideoSource
from camera.csi_camera import CsiCamera

router = APIRouter()

camera: VideoSource = CsiCamera()


@router.get("/camera/stream")
def video():
    return StreamingResponse(
        camera.generate_frames(), media_type="multipart/x-mixed-replace; boundary=frame"
    )
