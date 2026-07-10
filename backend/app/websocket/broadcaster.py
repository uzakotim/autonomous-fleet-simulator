from .manager import manager


class FleetBroadcaster:

    async def telemetry(self, telemetry):

        await manager.broadcast(
            {
                "type": "telemetry",

                "vehicle_id": telemetry.vehicle_id,

                "latitude": telemetry.latitude,

                "longitude": telemetry.longitude,

                "speed": telemetry.speed,

                "heading": telemetry.heading,

                "status": telemetry.status,

                "battery": telemetry.battery
            }
        )


broadcaster = FleetBroadcaster()