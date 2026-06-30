# pyrefly: ignore [missing-import]
from fastapi import FastAPI


app = FastAPI()


@app.get("/")
def hello():
    return {
        "status": "fleet backend running"
    }