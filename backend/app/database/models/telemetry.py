from datetime import datetime, timezone

from sqlalchemy import Integer
from sqlalchemy import Float
from sqlalchemy import DateTime

from sqlalchemy.orm import mapped_column
from sqlalchemy.orm import Mapped

from app.database.base import Base


class TelemetryRecord(Base):

    __tablename__ = "telemetry"

    id: Mapped[int] = mapped_column(primary_key=True)

    vehicle_id: Mapped[int] = mapped_column(Integer)

    latitude: Mapped[float]
    longitude: Mapped[float]

    speed: Mapped[float]

    heading: Mapped[float]

    battery: Mapped[float] = mapped_column(default=100)

    timestamp: Mapped[datetime] = mapped_column(
        DateTime(timezone=True),
        default=lambda: datetime.now(timezone.utc),
    )