from datetime import datetime, timezone
from typing import Optional

from pydantic import BaseModel, Field


class Telemetry(BaseModel):

    vehicle_id: int

    x: float

    y: float

    speed: float

    heading: float

    battery: float

    timestamp: datetime = Field(
        default_factory=lambda: datetime.now(timezone.utc)
    )