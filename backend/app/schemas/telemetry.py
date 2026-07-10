from datetime import datetime, timezone
from typing import Optional

from pydantic import BaseModel, Field, ConfigDict


class Telemetry(BaseModel):
    """Input schema — used to parse raw UDP payloads from vehicles."""

    vehicle_id: int

    latitude: float
    longitude: float

    speed: float

    heading: float

    battery: float


    timestamp: datetime = Field(
        default_factory=lambda: datetime.now(timezone.utc)
    )


class TelemetryResponse(BaseModel):
    """Output schema — used to serialise DB records in API responses."""

    model_config = ConfigDict(from_attributes=True)

    vehicle_id: int

    latitude: float
    longitude: float

    speed: float

    heading: float

    battery: float

    timestamp: datetime = Field(
        default_factory=lambda: datetime.now(timezone.utc)
    )

class VehicleStatusResponse(BaseModel):

    vehicle_id: int

    latitude: float
    longitude: float

    speed: float
    heading: float

    battery: float

    timestamp: str