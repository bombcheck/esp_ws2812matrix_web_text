// Include NeoPixel Specific Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
// Include ESP Specific Libraries
#include <ESP8266httpUpdate.h>
#include "espneotext.h"

// Define ESP-01 PIN
#define PIN 1

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800
);

// Define Your WiFi Connection Information
const char* WiFi_SSID = "<SSID-HERE>";
const char* WiFi_PASS = "<PASSWORD-HERE>";

// Set Defaults
String dispText;
String dispColor;
int disp = 0;
int pixelsInText;
int x = matrix.width();

const uint16_t colors[] = {
  matrix.Color(255, 0, 0),
  matrix.Color(0, 255, 0),
  matrix.Color(0, 0, 255)
};

// Create an instance of the server and specify the port to listen on as an argument.
WiFiServer server(80);


void setup(){
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(80);
  matrix.setTextColor(matrix.Color(80,255,0));
  //matrix.setTextColor(colors[0]);
  //Serial.begin(115200); // DEBUG
  delay(10);

  // Connect to WiFi network
  //Serial.println(); // DEBUG
  //Serial.print("Connecting to "); // DEBUG
  //Serial.println(WiFi_SSID); // DEBUG

  WiFi.begin(WiFi_SSID,WiFi_PASS);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    //Serial.print("."); // DEBUG
  }
  //Serial.println(""); // DEBUG
  //Serial.println("WiFi Connected"); // DEBUG

  // Start the server
  server.begin();
  //Serial.println("Server Started"); // DEBUG

  // Print the IP address
  //Serial.println(WiFi.localIP()); // DEBUG
}





void loop(){
  // Check if a client has connected
  WiFiClient client = server.available();
  // Wait until the client sends some data
  if(!client){ return; }
    //Serial.println("Client Connected"); // DEBUG

  // Color Options
  // http://www.javascripter.net/faq/hextorgb.htm
  // Process the Request/GET - Strips out everything in order.
  String command0 = client.readStringUntil('?');
    //Serial.print("Command0: "); // DEBUG
    //Serial.println(command0); // DEBUG
  String allParams = client.readStringUntil(' ');
    //Serial.print("Query Parameter: "); // DEBUG
    //Serial.println(allParams); // DEBUG

  
  if(allParams.indexOf("line=") >= 0){
    disp = 1; // true
    dispText = allParams.substring(allParams.indexOf("=")+1,allParams.indexOf("&rgb="));
    dispText.replace("+"," ");
    dispText.replace("%20"," ");
    dispText.replace("%21","!");
    dispText.replace("%27","'");
    pixelsInText = (dispText.length() * 7)+8;
      //Serial.print("Scroll Text: ");       // DEBUG
      //Serial.println(dispText);            // DEBUG

    // Set user prefered color
    dispColor = allParams.substring(allParams.indexOf("&rgb=")+5,allParams.length());
      //Serial.print("Scroll Text Color: "); // DEBUG
      //Serial.println(dispColor);           // DEBUG
    // Lame check for any other parameters. Need a better way to do this!
    if(dispColor.indexOf("&") == -1){
      int r = dispColor.substring(0,dispColor.indexOf(",")).toInt();
        //Serial.println(r_val); // DEBUG
      int g = dispColor.substring(int(dispColor.indexOf(","))+1,(dispColor.lastIndexOf(","))).toInt();
        //Serial.println(g_val); // DEBUG
      int b = dispColor.substring(int(dispColor.lastIndexOf(","))+1).toInt();
        //Serial.println(b_val); // DEBUG

      matrix.setTextColor(matrix.Color(r,g,b));
    }

    if(disp){
      while(x + 17 > (matrix.width() - pixelsInText)){
        matrix.fillScreen(0);
        matrix.setCursor(--x, 0);
        matrix.print(dispText);
        matrix.show();
        delay(100);
      }
      x = matrix.width();
    }

    // Display form page again so it's not blank! ------------------
    // Prepare the response
    String resp = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    resp += displayPage;
    // Send the response to the client
    while(resp.length()>2000){
      String dummy = resp.substring(0,2000);
      client.print(dummy);
      resp.replace(dummy," ");
    }
    client.flush();
    client.print(resp);
    delay(10);
    // The client will actually be disconnected, when the function returns and 'client' object is destroyed!
    //Serial.println("Client Disconnected!"); // DEBUG

  }else{
    // Display requested form page -----------------------------------
    // Prepare the response
    String resp = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    resp += displayPage;
    // Send the response to the client
    while(resp.length()>2000){
      String dummy = resp.substring(0,2000);
      client.print(dummy);
      resp.replace(dummy," ");
    }
    client.flush();
    client.print(resp);
    delay(10);
    // The client will actually be disconnected, when the function returns and 'client' object is destroyed!
    //Serial.println("Client Disconnected!"); // DEBUG
  }
}
