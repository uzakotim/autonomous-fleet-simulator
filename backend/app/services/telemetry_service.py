from app.repositories import telemetry_repository
from app.logger import logger


class TelemetryService:

    def __init__(self, cache,repository):
        self.cache = cache
        self.repository = repository

    def process(self, telemetry):

        print("TelemetryService called!")
        self.cache.update_vehicle(telemetry)

        self.repository.save(telemetry)

        logger.info(

            f"Vehicle {telemetry.vehicle_id} processed."

        )
        print("Saved to repository!")
        #
        # Phase 3.6
        # websocket.broadcast(telemetry)
        #