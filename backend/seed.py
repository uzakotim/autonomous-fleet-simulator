"""
Seed script: inserts initial vehicles so FK constraints on telemetry are satisfied.
Run once after create_tables.py:
    python seed.py
"""

import app.database.models  # noqa: F401 – registers all models with Base.metadata

from app.database.session import SessionLocal
from app.database.models.vehicle import Vehicle


def seed():
    session = SessionLocal()
    try:
        # Only insert if not already present
        existing = session.query(Vehicle).filter_by(id=1).first()
        if not existing:
            session.add(Vehicle(id=1, name="Vehicle-1"))
            session.commit()
            print("Seeded vehicle id=1.")
        else:
            print("Vehicle id=1 already exists, skipping.")
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()


if __name__ == "__main__":
    seed()
