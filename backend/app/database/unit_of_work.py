from app.database.session import SessionLocal

from app.repositories.telemetry_repository import TelemetryRepository
from app.repositories.vehicle_repository import VehicleRepository


class UnitOfWork:

    def __init__(self):

        self.session = SessionLocal()

        self.telemetry = TelemetryRepository(self.session)
        self.vehicle = VehicleRepository(self.session)

    def commit(self):
        self.session.commit()

    def rollback(self):
        self.session.rollback()

    def close(self):
        self.session.close()

    def reset(self):

        self.session.close()

        self.session = SessionLocal()

        self.telemetry = TelemetryRepository(self.session)
        self.vehicle = VehicleRepository(self.session)