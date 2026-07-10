from fastapi import APIRouter, WebSocket, WebSocketDisconnect

from .manager import manager

router = APIRouter()


@router.websocket("/ws/fleet")
async def fleet_socket(websocket: WebSocket):

    await manager.connect(websocket)

    try:

        while True:

            #
            # Keep socket alive.
            #
            await websocket.receive_text()

    except WebSocketDisconnect:

        await manager.disconnect(websocket)