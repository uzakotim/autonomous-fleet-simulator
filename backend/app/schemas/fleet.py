from pydantic import BaseModel


class FleetStatusResponse(BaseModel):

    total: int

    online: int

    offline: int

    moving: int

    stopped: int