from abc import ABC, abstractmethod
from typing import Any


class VideoSource(ABC):
    @abstractmethod
    def generate_frame(self) -> Any:
        pass

    @abstractmethod
    def generate_frames(self) -> Any:
        pass

    @abstractmethod
    def release(self):
        pass
