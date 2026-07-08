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
            "battery": telemetry.battery,
            "timestamp": telemetry.timestamp.isoformat(),
        }

        client.set(
            key,
            json.dumps(payload),
            ex=30
        )


    def get_vehicle(self, vehicle_id):

        key = f"vehicle:{vehicle_id}"

        data = client.get(key)

        if data is None:
            return None

        return json.loads(data)

    def get_all_vehicles(self):

        vehicles = []

        for key in client.scan_iter("vehicle:*"):

            data = client.get(key)

            if data:
                vehicles.append(json.loads(data))

        return vehicles