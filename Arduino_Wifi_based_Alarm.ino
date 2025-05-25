/*
  By Elisee MUGIRANEZA
  https://github.com/Elisee-M
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
const char* ssid     = "Your Wifi name";
const char* password = "Wifi password";

// Alarm Pin
const int alarmPin = 13;  // GPIO 13 (D7 equivalent)
const int led = D5;


// NTP Client Setup
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 7200; // Kigali, Rwanda (GMT+2)
NTPClient timeClient(ntpUDP, "time.google.com", utcOffsetInSeconds, 60000); // Using Google NTP Server, update every 60 seconds

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C address is usually 0x27 or 0x3F

// Function prototypes
bool checkAlarmTimes(int hour, int minute, int second, int dayOfWeek);
void triggerAlarm();

const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup() {
  Serial.begin(115200);
  delay(1000); // Give some time for Serial to initialize
  Serial.println("Starting setup...");

  pinMode(alarmPin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(alarmPin, LOW);  // Turn off alarm initially

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Initializing...");

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  lcd.setCursor(0, 1);
  lcd.print("WiFi Connecting...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led, 1);
    delay(500);
    Serial.print(".");
    digitalWrite(led, 0);
    delay(300);
  }
  Serial.println("\nConnected to WiFi");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected!");


  // Initialize NTP Client
  timeClient.begin();
  if (!timeClient.update()) {
    Serial.println("NTP update failed, retrying in 5 seconds...");
    lcd.setCursor(0, 1);
    lcd.print("NTP failed retry");
    delay(5000);  // Wait 5 seconds before retrying
    timeClient.forceUpdate();  // Force an update if automatic update fails
  }

  lcd.clear();
}

void loop() {
  // Check WiFi connection and reconnect if necessary
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, reconnecting...");
    lcd.setCursor(0, 1);
    lcd.print("WiFi Reconnecting...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nReconnected to WiFi");
    lcd.setCursor(0, 1);
    lcd.print("WiFi Connected!  ");
  }

  // Attempt to update time from NTP
  timeClient.update();

  // Get hours, minutes, and seconds
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();

  // Get date components
  unsigned long epochTime = timeClient.getEpochTime();
  int dayOfWeek = (epochTime / 86400L + 4) % 7;  // Calculate day of the week

  // Print time to Serial Monitor for debugging
  Serial.printf("Time: %02d:%02d:%02d\n", currentHour, currentMinute, currentSecond);

  // Display "ESSA Alarm" and current day abbreviation on the first row
  lcd.setCursor(0, 0);
  lcd.printf("Alarm  %s", daysOfWeek[dayOfWeek]);
  Serial.printf("Alarm  %s", daysOfWeek[dayOfWeek]);
   // Display "ESSA Alarm" with the day abbreviation

  // Display the current time on the second row
  lcd.setCursor(0, 1);
  lcd.printf("Time:   %02d:%02d:%02d", currentHour, currentMinute, currentSecond);

  // Check for alarm times and trigger if needed
  if (checkAlarmTimes(currentHour, currentMinute, currentSecond, dayOfWeek)) {
    triggerAlarm();
  }
  digitalWrite(led, HIGH);

  delay(1000);  // Update every second
}

// Function to check alarm times
bool checkAlarmTimes(int hour, int minute, int second, int dayOfWeek) {
  // Monday, Wednesday, and Friday at 7:30 AM
  if ((dayOfWeek == 1 || dayOfWeek == 3 || dayOfWeek == 5) && hour == 7 && minute == 45 && second == 0) {
    return true;
  }

  if (dayOfWeek >= 1 && dayOfWeek <= 5) {  // Monday to Friday
    if (
      (hour == 6 && minute == 0 && second == 0) ||
      (hour == 7 && minute == 0 && second == 0) ||
      (hour == 8 && minute == 30 && second == 0) || 
      (hour == 9 && minute == 10 && second == 0) ||
      (hour == 9 && minute == 50 && second == 0) ||
      (hour == 10 && minute == 30 && second == 0) ||
      (hour == 11 && minute == 10 && second == 0) ||
      (hour == 11 && minute == 25 && second == 0) ||
      (hour == 12 && minute == 5 && second == 0) ||
      (hour == 12 && minute == 45 && second == 0) ||
      (hour == 13 && minute == 50 && second == 0) ||
      (hour == 14 && minute == 30 && second == 0) || 
      (hour == 15 && minute == 8 && second == 0) ||
      (hour == 15 && minute == 50 && second == 0) ||
      (hour == 16 && minute == 30 && second == 0) ||
      (hour == 18 && minute == 0 && second == 0) ||
      (hour == 19 && minute == 50 && second == 0) 
    ) {
      return true;
    }
  } else if (dayOfWeek == 0 || dayOfWeek == 6) {  // Saturday or Sunday
    if ((hour == 7 && minute == 0 && second == 0) || 
        (hour == 12 && minute == 45 && second == 0) ||
        (hour == 18 && minute == 0 && second == 0) ||
        (hour == 19 && minute == 50 && second == 0)
    ) {
      return true;
    }
  }
  return false;
}

// Function to trigger the alarm
void triggerAlarm() {
  Serial.println("Alarm Triggered!");
  lcd.setCursor(0, 1);
  lcd.print("It's time");
  digitalWrite(alarmPin, HIGH);  // Activate alarm
  digitalWrite(led, LOW);
  delay(10000);                   // Alarm duration (10 seconds)
  digitalWrite(alarmPin, LOW);   // Deactivate alarm
  digitalWrite(led, HIGH);
}

