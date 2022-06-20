from pydantic import BaseSettings

class Settings(BaseSettings):
    mode = "production"

settings = Settings()