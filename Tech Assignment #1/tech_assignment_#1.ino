#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 13     // Pin dimana sensor DHT terhubung
#define DHTTYPE DHT11 // Tipe sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

// Ganti dengan kredensial WiFi Anda
const char* ssid = "Arsitektur";
const char* password = "Amaterasa17";

// Ganti dengan URL server Anda
const char* serverName = "http://192.168.100.4:5000/api/data";

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Koneksi ke WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Mengambil data dari sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Membentuk URL untuk request POST
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Data yang akan dikirim dalam format JSON
    String httpRequestData = "{\"temperature\":\"" + String(temperature) + "\",\"humidity\":\"" + String(humidity) + "\"}";

    // Mengirim request POST
    int httpResponseCode = http.POST(httpRequestData);

    // Mendapatkan response dari server
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    // Menutup koneksi
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Delay untuk pengambilan data berikutnya
  delay(6000); // 10 detik
}
