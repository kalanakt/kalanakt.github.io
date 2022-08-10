from pyodide.http import pyfetch
import asyncio

async def get_random_name(e): 
    response = await pyfetch(url="https://random-data-api.com/api/name/random_name", method="GET")
    data = await response.json()
    first_name = data.get('first_name')
    middle_name = data.get('middle_name')
    last_name = data.get('last_name') 
    output =  f"Random name: {first_name} {middle_name} {last_name}"
    pyscript.write('output', output)