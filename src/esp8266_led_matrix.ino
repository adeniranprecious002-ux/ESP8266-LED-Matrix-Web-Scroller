/*
  ESP8266 LED Matrix Display with Web Control

  This code sets up an ESP8266 microcontroller to control an LED matrix display.
  It creates a Wi-Fi access point and hosts a web server that allows users to
  input a custom message to be scrolled across the LED matrix.

  Required Libraries:
  - ESPAsyncWebServer
  - ESPAsyncTCP
  - MD_Parola
  - MD_MAX72xx
  - ESP8266WiFi
  - SPI

  Hardware Setup:
  - Connect the LED matrix to the ESP8266 using the specified DATA_PIN, CLK_PIN, and CS_PIN.
*/
#include <Arduino.h>
#include <ESPAsyncTCP.h>       // Provides async TCP support used by ESPAsyncWebServer
#include <SPI.h>               // communication between the MCU and the LED chip
#include <MD_Parola.h>         // for the text effect on the LED matrix
#include <MD_MAX72xx.h>        // Controls LED driver chip at a low level
#include <ESPAsyncWebServer.h> //Allows ESP8266 to run a fast web server that doesn't block the loop
#include <ESP8266WiFi.h>       //Enables Wi-Fi Functions for ESP8266 to create a network

// Hardware type and matrix configuration
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // Number of 8*8 matrix displays chained together
#define MAXDEVICES 4                      // Since we are using four 8*8 matrix
#define DATA_PIN D7                       // GPIO13 (General Purpose INPUT/OUTPUT)
#define CLK_PIN D6                        // GPIO14
#define CS_PIN D8                         // GPIO15

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAXDEVICES); // provides animation for the message to be displayed

// Wi-Fi network name (SSID) and password for the accesss point
const char *ssid = "Your_WiFi_SSID";         // input your wi-fi ssid
const char *password = "Your_WiFi_Password"; // input your wifi password

AsyncWebServer server(80); // Async web server on pot 80 (standard port)
String scrollText = "Welcome!";

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Start Serial Communication

  // Initialize SPI
  SPI.begin();

  // Start LED display
  display.begin();
  display.setIntensity(5);                                                 // Brightness of the display is set to 5 (medium)
  display.displayClear();                                                  // Clear any previous text
  display.displayScroll(scrollText.c_str(), PA_LEFT, PA_SCROLL_LEFT, 100); // scroll the message from left to right with speed 100ms per scroll frame

  // Set up Wi-Fi as access point by using the SSID and the Password
  WiFi.mode(WIFI_STA);        // Set wifi to station mode
  WiFi.begin(ssid, password); // start using wifi in access point mode using SSID and the password
  Serial.println("Connecting to Wifi ...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");
  Serial.println(WiFi.localIP()); // print the IP address of the access point

  // Web page for input to enter the message to be displayed
  // HTML form is created to take input from the user
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
  String html = "<h2>ESP8266 LED Matrix</h2>"
  "<form action='/set' method='GET'>"
  "<input type='text' name='text' placeholder='Enter message'/>"
  "<input type='submit' value='Scroll'/></form>";
  request->send(200, "text/html", html); });
  // Handle message update when the message to be displayed is submitted
  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (request->hasParam("text"))
              {
                scrollText = request->getParam("text")->value(); // Save the message
                display.displayClear();
                display.displayReset();
                display.displayScroll(scrollText.c_str(), PA_LEFT, PA_SCROLL_LEFT, 100); // Scroll the Text
              }
              request->redirect("/"); // Back to the main page after submitting
            });
  server.begin(); // Start the web server
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (display.displayAnimate())
  {
    display.displayReset(); // Loop the message
  }
}
