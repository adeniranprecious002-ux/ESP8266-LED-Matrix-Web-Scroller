# ESP8266 LED Matrix Web Scroller

A Wi-Fi controlled LED matrix display using **ESP8266**, **MAX7219**, and an **asynchronous web server**.  
Users can connect to the ESP8266 via a web browser and update scrolling text in real-time.

---

## 🚀 Features

- ESP8266 Wi-Fi connectivity
- Asynchronous web server (non-blocking)
- Real-time text update via browser
- Smooth scrolling text animation
- MAX7219 LED matrix control
- Adjustable display brightness

---

## 🧰 Hardware Requirements

- ESP8266 (NodeMCU / ESP-12)
- MAX7219 LED Matrix (4 × 8x8)
- Jumper wires
- Breadboard (optional)
- Power supply (5V)

---

## 🔌 Pin Connections

| ESP8266 Pin | MAX7219 Pin |
| ---------- | ---------- |
| D7 (GPIO13) | DIN |
| D6 (GPIO14) | CLK |
| D8 (GPIO15) | CS |
| 5V | VCC |
| GND | GND |

---

## 📚 Libraries Used

Install the following libraries from the Arduino Library Manager:

- ESPAsyncTCP
- ESPAsyncWebServer
- MD_Parola
- MD_MAX72xx
- ESP8266WiFi

---

## 🌐 How It Works

1. ESP8266 connects to a Wi-Fi network.
2. A web server runs on port **80**.
3. User opens the ESP8266 IP address in a browser.
4. User enters text via a web form.
5. The message scrolls across the LED matrix in real-time.

---
