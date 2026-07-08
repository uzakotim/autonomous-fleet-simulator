from app.logger import logger
from app.cache.redis_cache import RedisCache
from app.database.unit_of_work import UnitOfWork
from app.services.base_service import BaseService
from app.schemas import VehicleResponse
from app.schemas import VehicleStatusResponse
from app.schemas import TelemetryResponse
from app.schemas import FleetStatusResponse


class FleetService(BaseService):

    def __init__(
        self,
        cache: RedisCache,
        uow: UnitOfWork,
    ):
        super().__init__(cache, uow)



    def get_all_vehicles(self):
        vehicles = self.uow.vehicle.get_all()

        return [
            VehicleResponse.model_validate(vehicle)
            for vehicle in vehicles
    ]

    def get_vehicle(self, vehicle_id):
        vehicle = self.uow.vehicle.get_by_id(vehicle_id)

        if vehicle is None:
            return None

        return VehicleResponse.model_validate(vehicle)

  

    def get_current_status(self, vehicle_id):
        status = self.cache.get_vehicle(vehicle_id)

        if status is None:
            return None

        return VehicleStatusResponse(**status)



    def get_vehicle_history(self, vehicle_id, limit=100):
        history = self.uow.telemetry.get_history(vehicle_id, limit)

        return [
            TelemetryResponse.model_validate(record)
            for record in history
        ]

    def get_fleet_status(self):
        """
        Returns fleet-wide statistics.

        PostgreSQL:
            - total registered vehicles

        Redis:
            - current online vehicles
            - movement state
        """

        registered = self.uow.vehicle.get_all()

        registered_ids = {
            vehicle.id
            for vehicle in registered
        }

        active = [
            vehicle
            for vehicle in self.cache.get_all_vehicles()
            if vehicle["vehicle_id"] in registered_ids
        ]

        total = len(registered)

        online = len(active)

        moving = sum(
            1
            for vehicle in active
            if vehicle["speed"] > 0
        )

        stopped = len(active) - moving

        status = {
            "total": total,
            "online": online,
            "offline": total - online,
            "moving": moving,
            "stopped": stopped,
        }

        logger.info("Fleet status requested: %s", status)

        return FleetStatusResponse(**status)