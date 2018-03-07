# ESP8266 - WS2812/NeoPixel NeoMatrix - Text Scroller
Presents a small web ui where you can type a message, choose a color and display the message on your ws2812 NeoPixel NeoMatrix.

## Arduino Libraries Used
### JavaScript Libraries  
- [Spectrum Colorpicker](https://github.com/bgrins/spectrum)  
- [Twitter Bootstrap](http://getbootstrap.com/)  

### Arduino Libraries  
**Make sure to only download these from within the Arduino IDE**  
- [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)  
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)  
- [Adafruit_NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)  
- [ESP8266httpUpdate](https://github.com/esp8266/Arduino)  

## Getting Started
- Download the [Spectrum Colorpicker](https://github.com/bgrins/spectrum) from GitHub and place on your server so that you can access the files from the sketch. Alternatively you can try to link directly to GitHub which the files are currently setup for but not recommended.  
- Download this repo & open in the Arduino IDE  
- Download the required Adafruit libraries from inside the Arduino IDE (You may need to visit Adafruit.com for a [how-to guide](https://learn.adafruit.com/adafruit-arduino-ide-setup/arduino-1-dot-6-x-ide). [Full 3rd party list](https://github.com/arduino/Arduino/wiki/Unofficial-list-of-3rd-party-boards-support-urls#list-of-3rd-party-boards-support-urls))  
- Define Your WiFi Connection Information:  

```c++
const char* WiFi_SSID = "<SSID-HERE>";
const char* WiFi_PASS = "<PASSWORD-HERE>";
```

- Program / upload this repo to your ESP from within the Arduino IDE  
- Connect your WS2812/NeoPixel NeoMatrix
- Find your ESP's IP Address and connect with a browser  
- You may need to adjust the direction of the scrolling code "NEO_MATRIX_RIGHT" w/ "NEO_MATRIX_LEFT"  
- One final note is I am only using a single NeoMatix in this code, you may need to adjust if you have more  
- Have fun!
