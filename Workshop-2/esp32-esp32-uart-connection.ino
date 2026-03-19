/* BELOW IS THE CODE TO UPLOAD FOR ESP32 #1 */
// ESP32 #1

HardwareSerial mySerial(2);  // UART2

void setup() {
  Serial.begin(115200);      
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX, TX
}

void loop() {

  // Send message
  Serial2.println("Ping from ESP32 #1");
  Serial.println("Sent: Ping");

  delay(500);  // small wait for reply

  // Check for reply
  if (mySerial.available()) {
    String reply = mySerial.readStringUntil('\n');
    Serial.print("Received reply: ");
    Serial.println(reply);
  }

  delay(1000);
}


/* BELOW IS THE CODE TO UPLOAD FOR ESP32 #2 */

// ESP32 #2



HardwareSerial mySerial(2);  // UART2

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX, TX
}

void loop() {

  if (mySerial.available()) {
    String message = mySerial.readStringUntil('\n');

    Serial.print("Received: ");
    Serial.println(message);

    // Send reply
    Serial2.println("Pong from ESP32 #2");
    Serial.println("Sent: Pong");
  }
}

