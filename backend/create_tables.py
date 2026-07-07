
from app.database.database import engine
from app.database.base import Base

from app.database.models.vehicle import Vehicle
from app.database.models.telemetry import TelemetryRecord


Base.metadata.create_all(engine)

print("Database initialized.")