# Architecture Decisions

## Why C++ for Vehicles?

Decision:

Use C++20 for simulation nodes.

Reasons:

* Industry standard in robotics
* High performance
* Used in autonomous vehicles
* Strong systems programming practice

---

## Why FastAPI?

Decision:

Use FastAPI backend.

Reasons:

* Fast development
* Python ecosystem
* Easy API creation
* Good async support

---

## Why UDP for Telemetry?

Decision:

Vehicle telemetry uses UDP.

Reasons:

* Low latency
* Suitable for frequent updates
* Lost packet is acceptable

Example:

Missing one GPS update is not critical.

---

## Why WebSocket for Commands?

Decision:

Use WebSocket for backend-to-vehicle communication.

Reasons:

* Persistent connection
* Real-time messages
* Bidirectional communication

---

## Why Redis?

Decision:

Use Redis for live state.

Reasons:

* Extremely fast
* Designed for real-time workloads
* Pub/Sub support

---

## Why PostgreSQL?

Decision:

Use PostgreSQL for permanent data.

Reasons:

* Reliable storage
* SQL support
* Good analytics capabilities

---

## Why Docker?

Decision:

Containerize all services.

Reasons:

* Same environment everywhere
* Easier deployment
* Reproducible setup

---

## Why OpenStreetMap?

Decision:

Use real-world maps.

Reasons:

* Real roads
* Real coordinates
* Realistic simulation

---

## Scaling Strategy

Current:

```
1 backend

N vehicles
```

Future:

```
multiple backend services

hundreds/thousands of vehicles
```

Possible additions:

* Message queues
* Kubernetes
* Load balancing
* Distributed simulation
