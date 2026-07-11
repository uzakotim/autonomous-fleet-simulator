# pyright: ignore [reportMissingImports]
from fastapi import FastAPI
from app.config import settings

from contextlib import asynccontextmanager

# Must be imported before any DB interaction so all models are registered
# with Base.metadata and FK references (e.g. telemetry -> vehicles) can resolve.
import app.database.models  # noqa: F401

from app.telemetry.server import start_udp_server


from app.api.fleet import router as fleet_router

from app.websocket.router import router as websocket_router

from app.network.router import router as network_router

@asynccontextmanager
async def lifespan(app):

    transport = await start_udp_server(settings.UDP_PORT)

    print("UDP server started")

    yield

    transport.close()

app = FastAPI(

    title=settings.APP_NAME,

    version=settings.APP_VERSION,

    lifespan=lifespan

)
app.include_router(websocket_router)
app.include_router(fleet_router)
app.include_router(network_router)

@app.get("/")
def root():
    return {
        "service": "Autonomous Fleet Backend",
        "version": "0.1",
        "docs": "/docs",
        "health": "/health",
    }
    
@app.get("/health")

def health():

    return {

        "status": "ok"

    }