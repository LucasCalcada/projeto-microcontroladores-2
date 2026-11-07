from abc import ABC, abstractmethod


class VideoSource(ABC):
    @abstractmethod
    def generate_frame(self):
        pass

    @abstractmethod
    def generate_frames(self):
        pass

    @abstractmethod
    def release(self):
        pass
