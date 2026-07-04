from pydantic import BaseModel


class Telemetry(BaseModel):

    vehicle_id: int

    x: float

    y: float

    speed: float

    heading: float