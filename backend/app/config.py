from pydantic_settings import BaseSettings


class Settings(BaseSettings):

    APP_NAME: str = "Fleet Backend"

    APP_VERSION: str = "0.1"

    HOST: str = "0.0.0.0"

    PORT: int = 8000

    UDP_PORT: int = 5005

    DATABASE_URL: str = "postgresql://fleet:fleet@localhost:5432/fleetdb"
    
    SIMULATOR_HOST: str = "127.0.0.1"
    
    SIMULATOR_COMMAND_PORT: int = 5006
    
    class Config:
        env_file = ".env"


settings = Settings()