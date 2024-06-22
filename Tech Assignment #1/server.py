from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/data', methods=['POST'])
def receive_data():
    try:
        data = request.get_json()  # Mendapatkan data JSON dari request
        temperature = data['temperature']
        humidity = data['humidity']
        print(f"Received data - Temperature: {temperature}, Humidity: {humidity}")

        # Proses data sesuai kebutuhan Anda di sini
        # Misalnya, simpan ke database atau file, atau lakukan analisis

        response = {
            "status": "success",
            "message": "Data received",
            "received_data": data
        }
        return jsonify(response), 200
    except Exception as e:
        print(f"Error: {e}")
        response = {
            "status": "error",
            "message": "Failed to process data"
        }
        return jsonify(response), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
