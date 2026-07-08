from fastapi import APIRouter, Depends, HTTPException

from app.schemas import (
    FleetStatusResponse,
    TelemetryResponse,
    VehicleResponse,
    VehicleStatusResponse,
)
from app.services.fleet_service import FleetService
from app.api.dependencies import get_fleet_service

router = APIRouter(
    prefix="/fleet",
    tags=["Fleet"],
)


@router.get(
    "/vehicles",
    response_model=list[VehicleResponse],
)
def get_vehicles(

    service: FleetService = Depends(get_fleet_service),
):

    return service.get_all_vehicles()

@router.get(
    "/vehicles/{vehicle_id}",
    response_model=VehicleResponse,
)
def get_vehicle(

    vehicle_id: int,

    service: FleetService = Depends(get_fleet_service),
):

    vehicle = service.get_vehicle(vehicle_id)

    if vehicle is None:
        raise HTTPException(
            status_code=404,
            detail="Vehicle not found",
        )

    return vehicle

@router.get(
    "/vehicles/{vehicle_id}/status",
    response_model=VehicleStatusResponse,
)
def get_vehicle_status(

    vehicle_id: int,

    service: FleetService = Depends(get_fleet_service),
):

    status = service.get_current_status(vehicle_id)

    if status is None:
        raise HTTPException(
            status_code=404,
            detail="Vehicle offline",
        )

    return status

@router.get(
    "/vehicles/{vehicle_id}/history",
    response_model=list[TelemetryResponse],
)
def get_history(

    vehicle_id: int,

    limit: int = 100,

    service: FleetService = Depends(get_fleet_service),
):

    return service.get_vehicle_history(
        vehicle_id,
        limit,
    )

@router.get(
    "/status",
    response_model=FleetStatusResponse,
)
def get_status(

    service: FleetService = Depends(get_fleet_service),
):

    return service.get_fleet_status()