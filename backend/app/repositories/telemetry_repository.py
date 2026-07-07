from app.database.session import SessionLocal
from app.database.models.telemetry import TelemetryRecord
from sqlalchemy.orm import Session


class TelemetryRepository:

    def __init__(self, session: Session):

        self.session = session

    def save(self, telemetry):
        record = TelemetryRecord(
            vehicle_id=telemetry.vehicle_id,
            x=telemetry.x,
            y=telemetry.y,
            speed=telemetry.speed,
            heading=telemetry.heading,
            battery=telemetry.battery,
        )
        self.session.add(record)