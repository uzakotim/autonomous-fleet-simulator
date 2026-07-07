import json

from app.cache.redis_client import client


class RedisCache:

    def update_vehicle(self, telemetry):

        key = f"vehicle:{telemetry.vehicle_id}"

        payload = {
            "vehicle_id": telemetry.vehicle_id,
            "x": telemetry.x,
            "y": telemetry.y,
            "speed": telemetry.speed,
            "heading": telemetry.heading,
        }

        client.set(
            key,
            json.dumps(payload)
        )


    def get_vehicle(self, vehicle_id):

        key = f"vehicle:{vehicle_id}"

        return client.get(key)