# pyright: ignore [reportMissingImports]
from fastapi import FastAPI
from app.config import settings

from contextlib import asynccontextmanager

# Must be imported before any DB interaction so all models are registered
# with Base.metadata and FK references (e.g. telemetry -> vehicles) can resolve.
import app.database.models  # noqa: F401

from app.telemetry.server import start_udp_server


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


@app.get("/health")

def health():

    return {

        "status": "ok"

    }