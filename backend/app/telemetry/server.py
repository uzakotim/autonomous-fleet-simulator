import asyncio

import json

from app.schemas.telemetry import Telemetry
from app.services.telemetry_service import TelemetryService
from app.cache.redis_cache import RedisCache
from app.repositories.telemetry_repository import TelemetryRepository
from app.database.unit_of_work import UnitOfWork
from app.websocket.broadcaster import broadcaster
import traceback


cache = RedisCache()

uow = UnitOfWork()
telemetry_service = TelemetryService(cache, uow, broadcaster) 

class TelemetryProtocol(asyncio.DatagramProtocol):

    def datagram_received(self, data, addr):

        try:

            payload = json.loads(data.decode())
            print(payload)

            telemetry = Telemetry(**payload)

            task = asyncio.create_task(
                telemetry_service.process(telemetry)
            )

            def handle_error(fut):
                try:
                    fut.result()
                except Exception as e:
                    traceback.print_exc()

            task.add_done_callback(handle_error)

        except Exception as e:
           traceback.print_exc()


async def start_udp_server(port: int):
    loop = asyncio.get_running_loop()

    transport, protocol = await loop.create_datagram_endpoint(
        lambda: TelemetryProtocol(),
        local_addr=("0.0.0.0", port),
    )

    return transport