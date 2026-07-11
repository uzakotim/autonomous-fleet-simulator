from pydantic import BaseModel


class RerouteRequest(BaseModel):
    latitude: float
    longitude: float


class CommandResponse(BaseModel):
    success: bool
    message: str