#! python3
import requests



re = requests.request("GET", "http://localhost:8001/www/index.html")
re = requests.request("GET", "http://localhost:8001/www/big.png")
