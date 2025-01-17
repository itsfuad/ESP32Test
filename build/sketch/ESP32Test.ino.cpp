#line 1 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
// libraries to be manually installed:
// 1. Preferences

#include <Arduino.h>
#include <WiFi.h>
#include <driver/adc.h>
#include <Preferences.h> 
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_adc_cal.h"
#include "mbedtls/aes.h"
#include "mbedtls/sha256.h"

// Constants for GPIO tests
const int TEST_GPIO_OUTPUT = 4;  // GPIO to test output
const int TEST_GPIO_INPUT = 5;   // GPIO to test input
const int ADC_PIN = 36;          // ADC pin to test (VP)

// Counter to track the number of deep sleep cycles
RTC_DATA_ATTR int sleepCounter = 0;

#line 22 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void setup();
#line 48 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testSystem();
#line 75 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testMemory();
#line 93 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testFlash();
#line 115 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testGPIO();
#line 136 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testADC();
#line 153 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testWiFi();
#line 172 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testPSRAM();
#line 192 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testTimer();
#line 203 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void testCrypto();
#line 251 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void loop();
#line 22 "D:\\dev\\ESP32\\ESP32Test\\ESP32Test.ino"
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== ESP32 Arduino Diagnostic Test ===\n");

  Serial.printf("Deep sleep cycle count: %d\n", sleepCounter);

  if (sleepCounter == 0) { // Limit to 1 cycles
    testSystem();
    testMemory();
    testFlash();
    testGPIO();
    testADC();
    testWiFi();
    testPSRAM();
    testTimer();
    testCrypto();
    Serial.println("Going to deep sleep for 10 seconds");
    esp_deep_sleep(10e6);
  } else {
    Serial.println("Woke up from deep sleep");
    Serial.println("\n=== Diagnostic Test Complete ===");
    Serial.println("All cycles completed.");
  }
}

void testSystem() {
  Serial.println("=== System Information ===");
  
  // CPU information
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  
  Serial.printf("CPU Cores: %d\n", chip_info.cores);
  Serial.printf("CPU Revision: %d\n", chip_info.revision);
  Serial.printf("CPU Frequency: %d MHz\n", getCpuFrequencyMhz());
  
  // Reset reason
  esp_reset_reason_t reason = esp_reset_reason();
  Serial.print("Reset reason: ");
  switch (reason) {
    case ESP_RST_POWERON: Serial.println("Power-on"); break;
    case ESP_RST_EXT: Serial.println("External pin"); break;
    case ESP_RST_SW: Serial.println("Software"); break;
    case ESP_RST_PANIC: Serial.println("Exception/Panic"); break;
    case ESP_RST_INT_WDT: Serial.println("Interrupt watchdog"); break;
    case ESP_RST_TASK_WDT: Serial.println("Task watchdog"); break;
    case ESP_RST_DEEPSLEEP: Serial.println("Deep sleep"); break;
    case ESP_RST_BROWNOUT: Serial.println("Brownout"); break;
    default: Serial.println("Unknown"); break;
  }
}

void testMemory() {
  Serial.println("\n=== Memory Test ===");
  
  Serial.printf("Total heap: %d bytes\n", ESP.getHeapSize());
  Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("Minimum free heap: %d bytes\n", ESP.getMinFreeHeap());
  Serial.printf("Maximum allocatable heap: %d bytes\n", ESP.getMaxAllocHeap());
  
  // Test memory allocation
  void* testPtr = malloc(1024);
  if (testPtr != NULL) {
    Serial.println("Memory allocation test: PASSED");
    free(testPtr);
  } else {
    Serial.println("Memory allocation test: FAILED");
  }
}

void testFlash() {
  Serial.println("\n=== Flash Memory ===");
  
  Serial.printf("Flash size: %d bytes\n", ESP.getFlashChipSize());
  Serial.printf("Flash speed: %d Hz\n", ESP.getFlashChipSpeed());
  
  // Test flash write/read
  Preferences prefs;
  if (prefs.begin("test", false)) {
    uint32_t testValue = 12345;
    prefs.putUInt("test_key", testValue);
    uint32_t readValue = prefs.getUInt("test_key", 0);
    prefs.end();
    
    if (testValue == readValue) {
      Serial.println("Flash R/W test: PASSED");
    } else {
      Serial.println("Flash R/W test: FAILED");
    }
  }
}

void testGPIO() {
  Serial.println("\n=== GPIO Test ===");
  
  // Configure test pins
  pinMode(TEST_GPIO_OUTPUT, OUTPUT);
  pinMode(TEST_GPIO_INPUT, INPUT_PULLDOWN);
  
  // Test HIGH
  digitalWrite(TEST_GPIO_OUTPUT, HIGH);
  delay(100);
  bool highTest = digitalRead(TEST_GPIO_INPUT) == HIGH;
  
  // Test LOW
  digitalWrite(TEST_GPIO_OUTPUT, LOW);
  delay(100);
  bool lowTest = digitalRead(TEST_GPIO_INPUT) == LOW;
  
  Serial.printf("GPIO HIGH test: %s\n", highTest ? "PASSED" : "FAILED");
  Serial.printf("GPIO LOW test: %s\n", lowTest ? "PASSED" : "FAILED");
}

void testADC() {
  Serial.println("\n=== ADC Test ===");
  
  analogReadResolution(12);
  int samples = 10;
  int total = 0;
  
  for(int i = 0; i < samples; i++) {
    total += analogRead(ADC_PIN);
    delay(10);
  }
  
  float average = total / samples;
  Serial.printf("ADC average reading: %.2f\n", average);
  Serial.printf("ADC voltage: %.2fV\n", (average * 3.3) / 4095.0);
}

void testWiFi() {
  Serial.println("\n=== WiFi Test ===");
  
  WiFi.mode(WIFI_STA);
  Serial.println("Scanning for networks...");
  int networks = WiFi.scanNetworks();
  
  if (networks == 0) {
    Serial.println("No networks found");
  } else {
    Serial.printf("Networks found: %d\n", networks);
    for (int i = 0; i < networks; ++i) {
      Serial.printf("%d: %s (RSSI: %d)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }
  }
  
  WiFi.scanDelete();
}

void testPSRAM() {
  Serial.println("\n=== PSRAM Test ===");
  
  if (psramFound()) {
    Serial.printf("PSRAM size: %d bytes\n", ESP.getPsramSize());
    Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
    
    // Test PSRAM allocation
    void* psramPtr = ps_malloc(1024);
    if (psramPtr != NULL) {
      Serial.println("PSRAM allocation test: PASSED");
      free(psramPtr);
    } else {
      Serial.println("PSRAM allocation test: FAILED");
    }
  } else {
    Serial.println("No PSRAM detected");
  }
}

void testTimer() {
  Serial.println("\n=== Timer Test ===");
  
  unsigned long start = micros();
  delay(1000);  // Test 1 second delay
  unsigned long elapsed = micros() - start;
  
  Serial.printf("Timer test (should be ~1000000 microseconds): %lu\n", elapsed);
  Serial.printf("Timer accuracy: %.2f%%\n", (abs(elapsed - 1000000.0) / 1000000.0) * 100);
}

void testCrypto() {
  Serial.println("\n=== Crypto Test ===");

  // Test SHA-256 hashing
  const char* testString = "Hello, ESP32!";
  unsigned char sha256Hash[32];
  mbedtls_sha256_context sha256_ctx;
  mbedtls_sha256_init(&sha256_ctx);
  mbedtls_sha256_starts(&sha256_ctx, 0);
  mbedtls_sha256_update(&sha256_ctx, (const unsigned char*)testString, strlen(testString));
  mbedtls_sha256_finish(&sha256_ctx, sha256Hash);
  mbedtls_sha256_free(&sha256_ctx);

  Serial.print("SHA-256 hash: ");
  for (int i = 0; i < 32; i++) {
    Serial.printf("%02x", sha256Hash[i]);
  }
  Serial.println();

  // Test AES encryption/decryption
  const char* aesKey = "1234567890123456"; // 16 bytes key for AES-128
  const char* aesPlainText = "ESP32 AES Test";
  uint8_t aesCipherText[16];
  uint8_t aesDecryptedText[16];
  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char*)aesKey, 128);
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)aesPlainText, aesCipherText);

  Serial.print("AES encrypted text: ");
  for (int i = 0; i < 16; i++) {
    Serial.printf("%02x", aesCipherText[i]);
  }
  Serial.println();

  mbedtls_aes_setkey_dec(&aes, (const unsigned char*)aesKey, 128);
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, aesCipherText, aesDecryptedText);

  Serial.print("AES decrypted text: ");
  for (int i = 0; i < 16; i++) {
    Serial.printf("%c", aesDecryptedText[i]);
  }
  Serial.println();

  mbedtls_aes_free(&aes);
  esp_aes_free(&aes);
}

void loop() {
  // Empty loop - tests run once in setup()
}

