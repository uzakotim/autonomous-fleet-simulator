# Phase 3 --- Backend & Real-Time Fleet Communication (Codex Implementation Guide)

## Objective

Connect the C++ vehicle simulator to a production-style backend.
Vehicles should continuously send telemetry, receive commands, and
expose fleet state through REST APIs and WebSockets.

------------------------------------------------------------------------

# Architecture

                Next.js Dashboard
                       |
                  WebSocket
                       |
                 FastAPI Backend
              /         |        \
          REST API    Redis   PostgreSQL
                       ^
                       |
                 UDP Telemetry
                       |
         +------+------+------+
         |             |      |
     Vehicle 1    Vehicle 2  Vehicle N

------------------------------------------------------------------------

# Deliverables

-   FastAPI backend
-   UDP telemetry server
-   Vehicle registration
-   WebSocket broadcaster
-   Redis live-state cache
-   PostgreSQL persistence
-   Fleet REST API
-   Integration tests

------------------------------------------------------------------------

# Repository Layout

    backend/
    ├── app/
    │   ├── main.py
    │   ├── api/
    │   ├── services/
    │   ├── websocket/
    │   ├── telemetry/
    │   ├── database/
    │   ├── models/
    │   └── schemas/
    ├── tests/
    └── Dockerfile

------------------------------------------------------------------------

# Task 1 --- FastAPI Service

Implement: - Application startup - Health endpoint - Configuration -
Logging

Acceptance: - `GET /health` returns HTTP 200.

------------------------------------------------------------------------

# Task 2 --- UDP Telemetry Receiver

Listen for telemetry packets.

Expected payload:

``` json
{
  "vehicle_id":1,
  "lat":41.31,
  "lon":69.27,
  "speed":12.5,
  "heading":90,
  "status":"moving"
}
```

Acceptance: - Telemetry is parsed and validated.

------------------------------------------------------------------------

# Task 3 --- Redis Live State

Store latest state using vehicle ID as key.

Example:

    vehicle:1

Contains: - latest position - speed - heading - timestamp - status

Acceptance: - Latest state is retrievable in constant time.

------------------------------------------------------------------------

# Task 4 --- PostgreSQL Persistence

Create tables:

## vehicles

-   id
-   name
-   created_at

## telemetry

-   id
-   vehicle_id
-   latitude
-   longitude
-   speed
-   heading
-   timestamp

Acceptance: - Incoming telemetry is persisted.

------------------------------------------------------------------------

# Task 5 --- Fleet REST API

Implement:

-   GET /vehicles
-   GET /vehicles/{id}
-   GET /fleet/status
-   POST /vehicles/{id}/command

Acceptance: - Endpoints return valid JSON.

------------------------------------------------------------------------

# Task 6 --- WebSocket Updates

Create a WebSocket endpoint that broadcasts vehicle updates to connected
clients.

Acceptance: - Dashboard receives live updates without polling.

------------------------------------------------------------------------

# Task 7 --- Command Dispatch

Support commands:

-   stop
-   resume
-   reroute

Design an abstraction for future transport (UDP, TCP, MQTT).

Acceptance: - Command reaches simulated vehicle.

------------------------------------------------------------------------

# Task 8 --- Integration Tests

Test:

-   UDP ingestion
-   Redis updates
-   Database writes
-   REST endpoints
-   WebSocket broadcast

Acceptance: - All integration tests pass.

------------------------------------------------------------------------

# Stretch Goals

-   Authentication
-   Rate limiting
-   Metrics endpoint
-   Prometheus support
-   Structured logging
-   Message queue abstraction

------------------------------------------------------------------------

# Definition of Done

-   [ ] Backend starts
-   [ ] UDP telemetry received
-   [ ] Redis updated
-   [ ] PostgreSQL stores history
-   [ ] REST API functional
-   [ ] WebSocket broadcasting works
-   [ ] Integration tests passing
-   [ ] Docker-ready
