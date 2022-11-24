/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>
#include <esp_now.h>
#include <HardwareSerial.h>

// define pins
#define output10 10
#define receiver 33
#define transmitter 32

// Replace with your network credentials
const char* ssid = "Turtle";
const char* password = "Pedroche87";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output10State = "off";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  // Initialize G10(LED) as OUTPUT
  pinMode(output10, OUTPUT);

  // Init transmitter as output and receiver as input
  pinMode(receiver, INPUT);
  pinMode(transmitter, OUTPUT);

  // Set G10 to LOW
  digitalWrite(output10, LOW);


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {  // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");  // print a message out in the serial port
    String currentLine = "";        // make a String to hold incoming data from the client

    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected

      currentTime = millis();

      if (client.available()) {  // if there's bytes to read from the client,
        char c = client.read();  // read a byte, then
        Serial.write(c);         // print it out the serial monitor
        header += c;

        if (c == '\n') {  // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /10/on") >= 0) {
              Serial.println("GPIO 10 on");
              output10State = "on";
              digitalWrite(output10, HIGH);
            } else if (header.indexOf("GET /10/off") >= 0) {
              Serial.println("GPIO 10 off");
              output10State = "off";
              digitalWrite(output10, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            // To not have issues with character on web page
            client.println("<meta charset=\"UTF-8\">");

            //to refresh the page every 5 seconds for data update
            client.println("<meta http-equiv=\"refresh\" content=\"5\" >");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>test Web Server</h1>");

            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>GPIO 10 - State " + output10State + "</p>");
            // If the output26State is off, it displays the ON button
            if (output10State == "off") {
              client.println("<p><a href=\"/10/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/10/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            //To Show Data
            //characters 
            //Speed
            double temp = analogRead(receiver);
            String speed = String(temp);
            client.println("<p class=\"par\">test </p>");
            // if ( temp < 21)
            client.println("<p> <span class=\"inpu\" style=\"background-color: #198754!important; color:#f8f9fa!important;\"> " + speed + " </span></p>");
            // else if ( temp > 24)
            //   client.println("<p> <span class=\"lm35\" style=\"background-color: #dc3545!important; color:#f8f9fa!important;\"> " + celsius + "°C </span></p>");
            // else
            //   client.println("<p> <span class=\"lm35\" style=\"background-color: #ffc107!important; color:#212529!important;\"> " + celsius + "°C </span></p>");

            // String test = analogRead(receiver);
            // client.println("<p class=\"par\">testing</p>");
            // client.println("<p class=\"par\"> test </p>");
            
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}