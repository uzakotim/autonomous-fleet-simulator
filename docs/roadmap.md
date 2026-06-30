# Development Roadmap

## Phase 0 — Foundation

Goal:

Prepare professional project structure.

Tasks:

* Create repository
* Setup folders
* Setup Git
* Setup Docker
* Setup backend
* Setup frontend
* Setup C++ environment

Checkpoint:

```
[x] Project builds
[x] Docker starts
[x] Frontend runs
[x] Backend runs
[x] C++ compiles
```

---

# Phase 1 — Single Vehicle Simulation

Goal:

Create the first autonomous vehicle.

Tasks:

* Create C++ vehicle class
* Add vehicle state
* Add movement simulation
* Add position updates

Vehicle should:

* Have ID
* Have position
* Have speed
* Move continuously

Checkpoint:

```
Vehicle starts

Vehicle moves

Vehicle outputs telemetry
```

---

# Phase 2 — Map System

Goal:

Use real city data.

Tasks:

* Download OpenStreetMap data
* Parse roads
* Create graph representation

Output:

```
Road network:

Node -> Intersection

Edge -> Road
```

Checkpoint:

```
Map loads

Road graph exists
```

---

# Phase 3 — Navigation

Goal:

Vehicles can travel between locations.

Tasks:

Implement:

* A*
* Dijkstra

Add:

* Destination
* Route generation
* Route following

Checkpoint:

```
Vehicle receives destination

Vehicle reaches destination
```

---

# Phase 4 — Networking

Goal:

Connect simulator and backend.

Tasks:

Add:

* UDP telemetry
* WebSocket commands

Checkpoint:

```
Vehicle sends data

Backend receives data

Backend sends commands
```

---

# Phase 5 — Fleet Simulation

Goal:

Multiple autonomous vehicles.

Tasks:

* Create multiple vehicle processes
* Add IDs
* Add missions
* Add fleet management

Checkpoint:

```
10 vehicles running simultaneously
```

---

# Phase 6 — Backend Data Layer

Goal:

Store fleet information.

Tasks:

Add:

* PostgreSQL
* Redis

Store:

* Vehicles
* Trips
* History

Checkpoint:

```
Data persists

Live state updates
```

---

# Phase 7 — Dashboard

Goal:

Visualize the fleet.

Tasks:

Add:

* Map
* Vehicle markers
* Live updates

Checkpoint:

```
Cars move on map
```

---

# Phase 8 — Docker Deployment

Goal:

Run everything anywhere.

Tasks:

Containerize:

* Frontend
* Backend
* Database
* Redis
* Simulator

Checkpoint:

Command:

```
docker compose up
```

starts everything.

---

# Phase 9 — Cloud Deployment

Goal:

Public demo.

Deploy:

* VPS
* Cloud server

Checkpoint:

Public URL available.
