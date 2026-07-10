from sqlalchemy.orm import Session

from app.database.models.telemetry import TelemetryRecord


class TelemetryRepository:

    def __init__(self, session: Session):
        self.session = session

    def save(self, telemetry):
        record = TelemetryRecord(
            vehicle_id=telemetry.vehicle_id,
            latitude=telemetry.latitude,
            longitude=telemetry.longitude,
            speed=telemetry.speed,
            heading=telemetry.heading,
            battery=telemetry.battery,
            timestamp=telemetry.timestamp,
        )

        self.session.add(record)
        self.session.commit()
        self.session.refresh(record)

        return record

    def get_history(self, vehicle_id: int, limit: int = 100):
        return (
            self.session.query(TelemetryRecord)
            .filter(TelemetryRecord.vehicle_id == vehicle_id)
            .order_by(TelemetryRecord.timestamp.desc())
            .limit(limit)
            .all()
        )

    def get_latest(self, vehicle_id: int):
        return (
            self.session.query(TelemetryRecord)
            .filter(TelemetryRecord.vehicle_id == vehicle_id)
            .order_by(TelemetryRecord.timestamp.desc())
            .first()
        )