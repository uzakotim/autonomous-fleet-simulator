import asyncio

import json

from app.schemas.telemetry import Telemetry
from app.services.telemetry_service import TelemetryService
from app.cache.redis_cache import RedisCache
from app.repositories.telemetry_repository import TelemetryRepository
from app.database.unit_of_work import UnitOfWork
from app.websocket.broadcaster import broadcaster

cache = RedisCache()

uow = UnitOfWork()
telemetry_service = TelemetryService(cache, uow, broadcaster) 

class TelemetryProtocol(asyncio.DatagramProtocol):

    def datagram_received(self, data, addr):

        try:

            payload = json.loads(data.decode())

            telemetry = Telemetry(**payload)

            telemetry_service.process(telemetry)

        except Exception as e:
            print(e)


async def start_udp_server(port: int):
    loop = asyncio.get_running_loop()

    transport, protocol = await loop.create_datagram_endpoint(
        lambda: TelemetryProtocol(),
        local_addr=("0.0.0.0", port),
    )

    return transport