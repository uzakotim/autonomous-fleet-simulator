from functools import lru_cache

from app.cache.redis_cache import RedisCache
from app.database.unit_of_work import UnitOfWork
from app.services.fleet_service import FleetService
from collections.abc import Generator
from fastapi import Depends

@lru_cache
def get_cache():
    return RedisCache()


def get_uow() -> Generator[UnitOfWork, None, None]:
    uow = UnitOfWork()

    try:
        yield uow
    finally:
        uow.close()


def get_fleet_service(
    uow: UnitOfWork = Depends(get_uow),
) -> FleetService:
    return FleetService(
        cache=get_cache(),
        uow=uow,
    )

from app.network.udp_command_client import UDPCommandClient
from app.services.vehicle_command_service import VehicleCommandService


def get_vehicle_command_service():

    udp_client = UDPCommandClient()

    return VehicleCommandService(udp_client)