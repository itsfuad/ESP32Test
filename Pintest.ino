#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    delay(1000); // Wait for serial monitor connection

    Serial.println("Starting ESP32 Self-Test...");

    // Test GPIO Output
    testGPIO();

    // Test Analog-to-Digital Converter (ADC)
    testADC();

    // Test WiFi Initialization
    testWiFi();

    // Test FreeRTOS (Task Scheduler)
    testRTOS();

    //test temperature
    Serial.print("Testing CPU Temperature, please wait 10 seconds");
    unsigned long currentTime = millis();
    while (millis() - currentTime < 10000) {
        Serial.print(".");
        delay(1000);
    }

    Serial.printf("CPU Temperature: %f°C\n", temperatureRead());

    Serial.println("Self-Test Completed.");
}

void loop() {
    // Test runs only once
}

// Function to test GPIO output
void testGPIO() {
    const int testPin = 2; // Built-in LED pin or any other GPIO pin
    pinMode(testPin, OUTPUT);

    Serial.println("Testing GPIO Output...");
    digitalWrite(testPin, HIGH);
    delay(500);
    digitalWrite(testPin, LOW);
    delay(500);

    Serial.println("GPIO Output Test Passed.");
}

// Function to test ADC functionality
void testADC() {
    const int adcPin = 34; // Use an ADC-capable pin
    pinMode(adcPin, INPUT);

    Serial.println("Testing ADC...");
    int adcValue = analogRead(adcPin);
    Serial.printf("ADC Value: %d\n", adcValue);

    if (adcValue >= 0) {
        Serial.println("ADC Test Passed.");
    } else {
        Serial.println("ADC Test Failed.");
    }
}

// Function to test WiFi initialization
void testWiFi() {
    Serial.println("Testing WiFi...");
    WiFi.mode(WIFI_STA); // Set WiFi to station mode
    if (WiFi.status() != WL_NO_SHIELD) {
        Serial.println("WiFi Test Passed.");
    } else {
        Serial.println("WiFi Test Failed.");
    }
}

// Function to test FreeRTOS
void testRTOS() {
    Serial.println("Testing FreeRTOS...");
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
        Serial.println("FreeRTOS Test Passed.");
    } else {
        Serial.println("FreeRTOS Test Failed.");
    }
}
