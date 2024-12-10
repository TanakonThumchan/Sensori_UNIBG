#include <Arduino_APDS9960.h>

int proximity, gesture;
int r, g, b;
bool detection;

void setup() {

  Serial.begin(9600);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  } else {
    APDS.setGestureSensitivity(80);
    APDS.setLEDBoost(3);
  }
}

void loop() {
  if (APDS.proximityAvailable()) {
    // - 0   => close
    // - 255 => far
    // - -1  => error
    proximity = APDS.readProximity();
    /*Serial.print("PR=");
    Serial.println(proximity);*/
  }

  if (APDS.gestureAvailable()) {
    gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        Serial.println("DETECTION STOP");
        detection = false;
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        detection = true;
        Serial.println("DETECTION START");
        break;

      default:
        Serial.println("Unknown gesture");
        break;
    }
  }

  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);

    Serial.print(r * 255 / 4097);
    Serial.print(",");
    Serial.print(g * 255 / 4097);
    Serial.print(",");
    Serial.println(b * 255 / 4097);

    analogWrite(LEDR, 255 - (r * 255 / 4097));
    analogWrite(LEDG, 255 - (g * 255 / 4097));
    analogWrite(LEDB, 255 - (b * 255 / 4097));
  }

  /*if (proximity >= 100 && proximity <= 200) {
    if (detection || true) {
      Serial.print(r);
      Serial.print(",");
      Serial.print(g);
      Serial.print(",");
      Serial.println(b);
    }
  }*/
}
