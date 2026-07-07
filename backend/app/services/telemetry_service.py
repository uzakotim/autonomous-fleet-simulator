from app.logger import logger


class TelemetryService:

    def __init__(self, cache):
        self.cache = cache


    def process(self, telemetry):

        self.cache.update_vehicle(telemetry)

        logger.info(
            f"Vehicle {telemetry.vehicle_id} updated."
        )

        #
        # Phase 3.3
        # redis.save(telemetry)
        #

        #
        # Phase 3.4
        # postgres.save(telemetry)
        #

        #
        # Phase 3.6
        # websocket.broadcast(telemetry)
        #