from app.database.session import SessionLocal

from app.repositories.telemetry_repository import TelemetryRepository


class UnitOfWork:

    def __init__(self):
        self.session = SessionLocal()
        self.telemetry = TelemetryRepository(self.session)

    def commit(self):
        self.session.commit()

    def rollback(self):
        self.session.rollback()

    def close(self):
        self.session.close()

    def reset(self):
        """Close the current session and open a fresh one."""
        self.session.close()
        self.session = SessionLocal()
        self.telemetry = TelemetryRepository(self.session)