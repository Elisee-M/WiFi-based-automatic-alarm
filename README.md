
# 🚀💥 WiFi-Powered NTP Alarm Blaster 3000™ 🕒🔔

Welcome to the future of alarms — say goodbye to missed meetings, awkward oversleeps, and outdated clocks!  
This little monster syncs with internet time, flashes lights, makes noise, and shows off with a shiny LCD.  
Made with love (and coffee) by **Elisee MUGIRANEZA** ☕❤️

---

## 🎉 What It Does

- 🌐 Connects to your WiFi like a boss
- 🛰️ Syncs time from the internet via NTP (hello Google!)
- ⌚ Shows the live time on a slick I2C 16x2 LCD screen
- 💡 Triggers an alarm (buzzer or LED rave!) when the clock hits THE TIME™
- 🧠 Checks every second — because that's what legends do

---

## 🧰 Ingredients (Hardware)

- 🧠 **ESP8266** (NodeMCU or similar)
- 🖥️ **16x2 LCD** with I2C interface
- 🔊 **Buzzer** or ✨ **LED** wired to D7 (GPIO13)
- 📶 Your **WiFi Network**

---

## 📚 The Magical Libraries

You’ll need these from the Arduino Library Manager:

- `ESP8266WiFi` — WiFi wizardry
- `WiFiUdp` — talks UDP like a pro
- `NTPClient` — brings you time, from space!
- `LiquidCrystal_I2C` — LCD talking tool
- `Wire` — speaks I2C fluently

---

## 🛠️ Quick Start Guide

1. Plug in your ESP8266 and open `Arduino_Wifi_based_Alarm.ino`.
2. Replace this stuff with your network secrets:

```cpp
const char* ssid = "Your Wifi name";
const char* password = "Wifi password";
```

3. Set your timezone offset if you're not in Kigali:

```cpp
const long utcOffsetInSeconds = 7200; // Kigali, Rwanda = GMT+2
```

4. Flash it. Watch it. Love it. 😎

---

## 🧨 How It Alarms

- It checks the time like a hawk every second 🦅
- If the current time matches a *hardcoded* alarm time (you can edit this!)
- It **activates the alarm pin** (GPIO13) and makes some noise or blinks
- Modify `checkAlarmTimes()` to make it wake you up with precision

---

## 📺 Display Magic

- Shows the time in the glorious `HH:MM:SS` format
- Day of the week in all its three-letter glory (e.g. Mon, Tue...)

---

## 👑 Author & Credits

Made by **Elisee MUGIRANEZA**  
[GitHub: Elisee-M](https://github.com/Elisee-M)

---

## 🔮 Coming Soon?

- Web interface to set your alarms from your phone 📱
- EEPROM alarm saving 💾
- Different alarm patterns (beeps, songs, memes??)

---

## ⚖️ License

MIT — go wild, just give credit.

