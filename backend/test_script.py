import socket
import json

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

packet = {
    "vehicle_id": 1,
    "x": 10,
    "y": 15,
    "speed": 8,
    "heading": 180
}

sock.sendto(
    json.dumps(packet).encode(),
    ("127.0.0.1", 5005)
)