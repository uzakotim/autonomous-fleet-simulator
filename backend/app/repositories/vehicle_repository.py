from sqlalchemy.orm import Session

from app.database.models.vehicle import Vehicle


class VehicleRepository:

    def __init__(self, session: Session):
        self.session = session

    def get_all(self):
        return (
            self.session
            .query(Vehicle)
            .order_by(Vehicle.id)
            .all()
        )

    def get_by_id(self, vehicle_id: int):
        return (
            self.session
            .query(Vehicle)
            .filter(Vehicle.id == vehicle_id)
            .first()
        )

    def create(self, name: str):
        vehicle = Vehicle(name=name)

        self.session.add(vehicle)

        return vehicle