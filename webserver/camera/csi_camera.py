import cv2

from picamera2 import Picamera2

from .video_source import VideoSource


class CsiCamera(VideoSource):
    def __init__(
        self,
        resolution=(1280, 720),
        width: int = 640,
        height: int = 480,
        quality: int = 70,
    ):
        self.width = width
        self.height = height
        self.quality = quality

        self.camera = Picamera2()

        self.camera.configure(
            self.camera.create_video_configuration(
                main={"size": resolution, "format": "RGB888"}
            )
        )

        self.camera.start()

    def generate_frame(self):
        frame = self.camera.capture_array()

        return cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

    def generate_frames(self):
        while True:
            frame = self.generate_frame()

            if frame is None:
                continue

            frame = cv2.resize(frame, (self.width, self.height))

            success, buffer = cv2.imencode(
                ".jpg", frame, [cv2.IMWRITE_JPEG_QUALITY, self.quality]
            )

            if not success:
                continue

            yield (
                b"--frame\r\n"
                b"Content-Type: image/jpeg\r\n\r\n" + buffer.tobytes() + b"\r\n"
            )

    def release(self):
        self.camera.stop()
