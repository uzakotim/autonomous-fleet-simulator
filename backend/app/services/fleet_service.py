from app.cache.redis_cache import RedisCache
from app.database.unit_of_work import UnitOfWork
from app.services.base_service import BaseService


class FleetService(BaseService):

    def __init__(
        self,
        cache: RedisCache,
        uow: UnitOfWork,
    ):
        super().__init__(cache, uow)

    def get_all_vehicles(self):
        return self.uow.vehicle.get_all()

    def get_vehicle(self, vehicle_id):
        return self.uow.vehicle.get_by_id(vehicle_id)

    def get_current_status(self, vehicle_id):
        return self.cache.get_vehicle(vehicle_id)

    def get_vehicle_history(self, vehicle_id, limit=100):
        return self.uow.telemetry.get_history(vehicle_id, limit)

    def get_fleet_status(self):
        
        fleet_status = []

        vehicles = self.get_all_vehicles()

        for vehicle in vehicles:

            latest_telemetry = self.get_current_status(vehicle.id)

            fleet_status.append({
                "vehicle": vehicle,
                "latest_telemetry": latest_telemetry,
            })

        return fleet_status

    