from app.cache.redis_cache import RedisCache
from app.schemas.telemetry import Telemetry


cache = RedisCache()

telemetry = Telemetry(
    vehicle_id=1,
    x=10,
    y=20,
    speed=5,
    heading=90
)

cache.update_vehicle(telemetry)

print(cache.get_vehicle(1))