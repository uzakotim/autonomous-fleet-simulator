# Import all models here so SQLAlchemy's metadata is aware of every table
# before create_all() or FK resolution happens.
from app.database.models.vehicle import Vehicle
from app.database.models.telemetry import TelemetryRecord

__all__ = ["Vehicle", "TelemetryRecord"]
