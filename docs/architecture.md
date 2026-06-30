Autonomous Vehicle Fleet Simulator — Architecture

Overview

This project simulates a fleet of autonomous vehicles operating in a real-world city environment.

Each vehicle is an independent C++ process that communicates with a backend platform. The backend manages fleet state, missions, and visualization.

The system demonstrates:

* Distributed systems
* Real-time communication
* Autonomous navigation
* Backend engineering
* Cloud deployment

⸻

High-Level Architecture

                         User Browser
                              |
                              |
                     Next.js Dashboard
                              |
                         WebSocket
                              |
                              v
                      FastAPI Backend
                  /          |          \
                 /           |           \
             Redis       PostgreSQL      API
          Live State     History       Commands
                 \           |           /
                  \          |          /
                 Vehicle Simulation Network
                              |
        +---------------------+---------------------+
        |                     |                     |
    Vehicle 001          Vehicle 002          Vehicle N
       C++                  C++                  C++
        |                    |                    |
        +-----------------------------------------+
                    City Map Graph
              OpenStreetMap Road Data

⸻

Components

1. Vehicle Simulator

Language:

* C++20

Each vehicle runs as an independent process.

Responsibilities:

* Maintain vehicle state
* Navigate roads
* Simulate sensors
* Send telemetry
* Receive commands

Example:

vehicle_001
vehicle_002
vehicle_003

⸻

Vehicle State

Each vehicle contains:

VehicleState {
    id
    position
    speed
    heading
    status
}

Example:

Vehicle 12
Position:
41.311, 69.279
Speed:
50 km/h
Status:
Moving

⸻

2. Backend

Technology:

* FastAPI
* Python

Responsibilities:

* Receive telemetry
* Manage vehicles
* Send commands
* Provide APIs
* Handle WebSocket connections

⸻

API Examples

GET /vehicles
GET /fleet/status
POST /vehicle/{id}/command
GET /missions

⸻

3. Redis

Purpose:

Real-time state storage.

Stores:

* Current vehicle location
* Active missions
* Temporary information

Example:

vehicle:001
{
 position,
 speed,
 status
}

Redis is optimized for fast reads/writes.

⸻

4. PostgreSQL

Purpose:

Permanent storage.

Stores:

* Vehicle information
* Trip history
* Telemetry logs

Example tables:

vehicles
missions
telemetry
users

⸻

5. Frontend Dashboard

Technology:

* Next.js
* React
* Tailwind

Displays:

* City map
* Vehicle positions
* Routes
* Fleet status

⸻

Communication

Vehicle → Backend

Protocol:

UDP

Reason:

* Low latency
* Real-time updates

Example:

Vehicle
  |
  |
 UDP packet
  |
  v
Backend

⸻

Backend → Vehicle

Protocol:

WebSocket

Used for:

* Commands
* Route changes
* Emergency stops

⸻

Deployment

Docker containers:

frontend
backend
postgres
redis
vehicle simulator

Run:

docker compose up

⸻

Future Extensions

Possible additions:

* ROS2 integration
* LiDAR simulation
* Computer vision
* Traffic simulation
* Reinforcement learning
* Real robot connection