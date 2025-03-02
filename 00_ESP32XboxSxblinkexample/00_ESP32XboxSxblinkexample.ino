
// This is a code to control a led with a xbox series x controller and a esp32 microcontroller.
// Now the xbox controller  header file is included. It can be installed in the library manager
#include <XboxSeriesXControllerESP32_asukiaaa.hpp> // More info about this header file at :https://github.com/asukiaaa/arduino-XboxSeriesXControllerESP32.git

// Required to replace with your xbox address
 XboxSeriesXControllerESP32_asukiaaa::Core
 xboxController("9C:AA:1B:F2:75:D9");
int led = 19; // the led pin


//XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(115200);
  Serial.println("Starting NimBLE Client");
  xboxController.begin();
}

void loop() {
  xboxController.onLoop();
  if (xboxController.isConnected()) {
    if (xboxController.isWaitingForFirstNotification()) {
      Serial.println("waiting for first notification");
    } else {
      Serial.println("Address: " + xboxController.buildDeviceAddressStr());
      Serial.print(xboxController.xboxNotif.toString());
      unsigned long receivedAt = xboxController.getReceiveNotificationAt();
      uint16_t joystickMax = XboxControllerNotificationParser::maxJoy;
      Serial.print("joyLHori rate: ");
      Serial.println((float)xboxController.xboxNotif.joyLHori / joystickMax);
      Serial.print("joyLVert rate: ");
      Serial.println((float)xboxController.xboxNotif.joyLVert / joystickMax);
      Serial.println("battery " + String(xboxController.battery) + "%");
      Serial.println("received at " + String(receivedAt));
      // now  use the  A button to turn the led on
    }    if ( xboxController.xboxNotif.btnA) {
      digitalWrite(led,HIGH);
      // then use the Y Button to turn the led off;
    }    if ( xboxController.xboxNotif.btnY) {
      digitalWrite(led,LOW);
    }
  } else {
    Serial.println("not connected");
    if (xboxController.getCountFailedConnection() > 2) {
      ESP.restart();
    }
  }
  Serial.println("at " + String(millis()));
  delay(500);
}
