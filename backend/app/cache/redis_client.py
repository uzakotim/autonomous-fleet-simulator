import redis
from app.config import settings

client = redis.Redis(
    host="localhost",
    port=6379,
    decode_responses=True
)