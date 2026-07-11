import json
import socket
from typing import Any


class UDPCommandClient:
    """
    Sends JSON commands to a simulator over UDP.
    """

    def __init__(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def send(
        self,
        host: str,
        port: int,
        payload: dict[str, Any],
    ) -> None:
        message = json.dumps(payload).encode("utf-8")
        self._socket.sendto(message, (host, port))

    def stop(
        self,
        host: str,
        port: int,
    ):
        self.send(
            host,
            port,
            {
                "command": "stop",
            },
        )

    def resume(
        self,
        host: str,
        port: int,
    ):
        self.send(
            host,
            port,
            {
                "command": "resume",
            },
        )

    def reroute(
        self,
        host: str,
        port: int,
        latitude: float,
        longitude: float,
    ):
        self.send(
            host,
            port,
            {
                "command": "reroute",
                "latitude": latitude,
                "longitude": longitude,
            },
        )