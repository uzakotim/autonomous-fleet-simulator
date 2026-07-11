from fastapi import APIRouter, Depends

from app.api.dependencies import get_vehicle_command_service
from app.schemas.vehicle_commands import RerouteRequest
from app.services.vehicle_command_service import VehicleCommandService

router = APIRouter(
    prefix="/vehicles",
    tags=["Vehicle Commands"],
)


@router.post("/{vehicle_id}/stop")
def stop_vehicle(
    vehicle_id: int,
    service: VehicleCommandService = Depends(
        get_vehicle_command_service,
    ),
):
    service.stop()

    return {
        "success": True,
        "message": "Stop command sent",
    }


@router.post("/{vehicle_id}/resume")
def resume_vehicle(
    vehicle_id: int,
    service: VehicleCommandService = Depends(
        get_vehicle_command_service,
    ),
):
    service.resume()

    return {
        "success": True,
        "message": "Resume command sent",
    }


@router.post("/{vehicle_id}/reroute")
def reroute_vehicle(
    vehicle_id: int,
    request: RerouteRequest,
    service: VehicleCommandService = Depends(
        get_vehicle_command_service,
    ),
):
    service.reroute(
        request.latitude,
        request.longitude,
    )

    return {
        "success": True,
        "message": "Reroute command sent",
    }