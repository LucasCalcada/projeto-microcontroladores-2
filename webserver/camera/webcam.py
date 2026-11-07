import cv2

from .video_source import VideoSource


class WebCam(VideoSource):
    def __init__(
        self, device: int = 0, width: int = 640, height: int = 480, quality: int = 70
    ):
        self.camera = cv2.VideoCapture(device)
        self.width = width
        self.height = height
        self.quality = quality

        if not self.camera.isOpened():
            raise RuntimeError("Não foi possível abrir a webcam")

    def generate_frame(self):
        success, frame = self.camera.read()

        if not success:
            return None

        return frame

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
        self.camera.release()
