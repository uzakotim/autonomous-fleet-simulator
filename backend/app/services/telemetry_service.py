from app.repositories import telemetry_repository
from app.logger import logger
from app.services.base_service import BaseService


class TelemetryService(BaseService):

    def __init__(self, cache, uow, broadcaster):
        super().__init__(cache, uow)
        self.broadcaster = broadcaster

    def process(self, telemetry):

        print("TelemetryService called!")
        try:
            self.cache.update_vehicle(telemetry)
            self.uow.telemetry.save(telemetry)
            self.uow.commit()
        except Exception:
            self.uow.rollback()
            raise
        finally:
            self.uow.reset()
        
        logger.info(f"Vehicle {telemetry.vehicle_id} processed.")
        self.broadcaster.telemetry(telemetry)