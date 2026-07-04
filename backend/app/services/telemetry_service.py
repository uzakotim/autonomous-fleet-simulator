from app.schemas.telemetry import Telemetry
from app.logger import logger


class TelemetryService:
    """
    Handles validated telemetry.

    The UDP layer should never contain business logic.
    """

    def process(self, telemetry: Telemetry) -> None:

        logger.info(
            f" Vehicle {telemetry.vehicle_id} | "
            f"x={telemetry.x:.2f} | "
            f"y={telemetry.y:.2f} | "
            f"speed={telemetry.speed:.2f}\n"
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