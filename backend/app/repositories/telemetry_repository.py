from app.database.session import SessionLocal
from app.database.models.telemetry import TelemetryRecord

class TelemetryRepository:

    def save(self, telemetry):
        session = SessionLocal()

        try:

            record = TelemetryRecord(
                vehicle_id=telemetry.vehicle_id,
                x=telemetry.x,
                y=telemetry.y,
                speed=telemetry.speed,
                heading=telemetry.heading
            )
            session.add(record)
            session.commit()
        except Exception:
            session.rollback()
            raise   
        finally:
            session.close()