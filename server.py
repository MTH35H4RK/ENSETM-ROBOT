from flask import Flask, request
import random
import requests

# Define a global variable
traffic_response = ''

# Load configuration from a file or environment variables
IP_ADDRESS = '192.168.0.100'

app = Flask(__name__)

# Endpoint to check if server is working
@app.route('/CHECK/<param>')
def check(param):
    # Return a success response
    return 'SUCCESS'

# Endpoint to handle accidents
@app.route('/ACCIDENT/<param>')
def accident(param):
    if param == 'XXXXX':
        # Do some processing to get A1 or A2, and set the result to the `response` variable
        response = random.choice(['A1', 'A2'])
        # Send the response to the Arduino
        send_to_arduino('ACCIDENT', response)
        # Return the response
        return response
    else:
        # Return a failed response
        return 'FAILED'

# Endpoint to handle hospitals
@app.route('/HOSPITAL/<param>')
def hospital(param):
    global traffic_response
    if param == 'XXXXX':
        # Do some processing to get H1 or H2, and set the result to the `response` variable
        response = random.choice(['H1', 'H2'])
        # If the response is H1, set the traffic light to V11 or V12
        if response == 'H1':
            traffic_response = random.choice(['V11', 'V12'])
        # If the response is H2, set the traffic light to V21 or V22
        else:
            traffic_response = random.choice(['V21', 'V22'])
         
        # Send the response to the Arduino
        send_to_arduino('HOSPITAL', response)
        # Return the response
        return response
    else:
        # Return a failed response
        return 'FAILED'



# Endpoint to handle traffic lights
@app.route('/LIGHT/<param>')
def light(param):
    if param == 'XXXXX':
        # Do some processing to get RED or GREEN, and set the result to the `response` variable
        response = random.choice(['RED', 'GREEN'])
        return response
        
        
    else:
        # Return a failed response
        return 'FAILED'

# Endpoint to handle traffic control
@app.route('/TRAFFIC/<param>')
def traffic(param):
    if param == 'XXXXX':
        # GET empty traffic
        response = traffic_response
        # Send the traffic light control signal to the Arduino
        send_to_arduino('TRAFFIC', response)
        # Return the response
        return response
    else:
        # Return a failed response
        return 'FAILED'

# Function to send data to the Arduino
def send_to_arduino(endpoint, data):
    # Use try-except block to catch network errors
    try:
        # Send a POST request to the Arduino endpoint with the data
        response = requests.post(f'http://{IP_ADDRESS}:8080/{endpoint}', json={'data': data})
        # Check if the response is successful
        if response.status_code == 200 and response.text == 'OK':
            return True
        else:
            return False
    except requests.exceptions.RequestException as e:
        # Handle network errors by logging the error message
        print(f'Error sending data to Arduino: {e}')
        return False

# Endpoint to handle changing the traffic light to green
@app.route('/GREEN/<param>')
def green(param):
    if param == 'XXXXX':
        # Do some processing to change the light to green, and set the result to the response variable
        response = 'CHANGED'
        # Return the response
        return response
    else:
        # Return a failed response
        return 'FAILED'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
