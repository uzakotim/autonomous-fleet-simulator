from app.network.udp_command_client import UDPCommandClient
from app.services.telemetry_service import TelemetryService
from app.config import settings

class VehicleCommandService:

    def __init__(self, udp_client):
        self.client = udp_client

    def stop(self):
        self.client.stop(
            settings.SIMULATOR_HOST,
            settings.SIMULATOR_COMMAND_PORT,
        )

    def resume(self):
        self.client.resume(
            settings.SIMULATOR_HOST,
            settings.SIMULATOR_COMMAND_PORT,
        )

    def reroute(self, latitude: float, longitude: float):
        self.client.reroute(
            settings.SIMULATOR_HOST,
            settings.SIMULATOR_COMMAND_PORT,
            latitude,
            longitude,
        )