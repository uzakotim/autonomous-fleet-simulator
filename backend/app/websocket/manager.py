from fastapi import WebSocket
from typing import List
import asyncio


class ConnectionManager:
    """
    Keeps track of all active websocket connections.
    """

    def __init__(self):
        self._connections: List[WebSocket] = []
        self._lock = asyncio.Lock()

    async def connect(self, websocket: WebSocket):
        await websocket.accept()

        async with self._lock:
            self._connections.append(websocket)

    async def disconnect(self, websocket: WebSocket):
        async with self._lock:
            if websocket in self._connections:
                self._connections.remove(websocket)

    async def broadcast(self, message: dict):
        disconnected = []

        async with self._lock:

            for ws in self._connections:

                try:
                    await ws.send_json(message)

                except Exception:
                    disconnected.append(ws)

            for ws in disconnected:
                self._connections.remove(ws)


manager = ConnectionManager()