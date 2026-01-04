# Terrashroom Setup Guide

This guide walks you through setting up your Terrashroom mushroom growing chamber with ESPHome.

## Prerequisites

- **ESPHome**: Install via `pip install esphome` or `brew install esphome`
- **USB Serial Driver**: For CH340/CH341 chips, install drivers from [WCH](http://www.wch.cn/downloads/CH34XSER_MAC_ZIP.html) or [Adafruit guide](https://learn.adafruit.com/how-to-install-drivers-for-wch-usb-to-serial-chips-ch9102f-ch9102/mac-driver-installation)
- **ESP32 Programmer**: Such as the [universal programmer](https://tinyurl.com/2em7ycs9)

## Quick Start

### 1. Clone the Repository

```bash
git clone https://github.com/lbaker2/terrashroom.git
cd terrashroom/esphome
```

### 2. Create Configuration Files

```bash
# Copy the example files
cp terrashroom.example.yaml terrashroom.yaml
cp secrets.example.yaml secrets.yaml
```

### 3. Edit secrets.yaml

Fill in your actual credentials:

```yaml
wifi_ssid: "YourActualNetworkName"
wifi_password: "YourActualPassword"
ota_password: "a-strong-password-for-updates"
web_password: "a-password-for-web-interface"
```

### 4. Edit terrashroom.yaml

Customize the network settings for your environment:

```yaml
substitutions:
  static_ip: "192.168.1.100"  # Choose an available IP on your network
  gateway: "192.168.1.1"       # Your router's IP address
  subnet: "255.255.255.0"      # Usually this default works
```

### 5. Initial Flash (USB)

Connect the ESP32 programmer to the Terrashroom headers:
- Connect: EN, GPIO0, GND, TX, RX
- Do NOT connect 5V (use external power supply instead)

Find your serial device:
```bash
ls /dev/cu.*
# Look for something like /dev/cu.wchusbserial120
```

Flash the firmware:
```bash
esphome run terrashroom.yaml --device /dev/cu.YOUR_SERIAL_PORT
```

### 6. Subsequent Updates (OTA)

After initial setup, update over-the-air:
```bash
esphome run terrashroom.yaml
```

ESPHome will automatically find the device by its static IP.

## Network Configuration

### Static IP

The Terrashroom uses a static IP for reliable access. Choose an IP outside your router's DHCP range to avoid conflicts.

### Fallback AP

If WiFi connection fails, the device creates a hotspot:
- SSID: `Terrashroom-Setup` (configurable)
- Password: `terrashroom` (configurable)
- IP: `192.168.4.1`

Connect to this hotspot to access the web interface and diagnose issues.

## Web Interface

Access the Terrashroom web UI at `http://<static_ip>/`

Default credentials:
- Username: `admin`
- Password: (from your `secrets.yaml`)

## Troubleshooting

### Device Won't Boot

GPIO12 and GPIO15 are ESP32 strapping pins. If you've added external components to these pins:
1. Disconnect external components
2. Power cycle the device
3. Verify boot before reconnecting

### Can't Find Serial Port

1. Install the CH340 driver
2. Unplug and replug the programmer
3. Check `ls /dev/cu.*` for new devices

### OTA Fails

1. Verify the device is on your network: `ping <static_ip>`
2. Check the password in `secrets.yaml` matches what was flashed
3. Try a USB flash if OTA is completely broken

### WiFi Won't Connect

1. Verify SSID and password are exact (case-sensitive)
2. Ensure your router supports 2.4 GHz (ESP32 doesn't support 5 GHz)
3. Connect to the fallback AP to access diagnostics

## Hardware Connections

See [hardware/pinout.md](../hardware/pinout.md) for complete GPIO assignments.

| Function | GPIO | Notes |
|----------|------|-------|
| Fan 1 (exhaust) | 32 | PWM |
| Fan 2 (intake) | 33 | PWM |
| Blower | 25 | PWM |
| Atomizer | 13 | PWM |
| Heater | 12 | Strapping pin |
| UV LED | 18 | Digital |
| Water sensor | 23 | Input |
| Water enable | 15 | Strapping pin |
| Camera power | 26 | Digital |
| Base LEDs | 5 | WS2812 |
| Canopy LEDs | 14 | WS2812 |

## Next Steps

- [API Documentation](API.md) - REST endpoints for automation
- [Mushroom Profiles](PROFILES.md) - Species-specific growing parameters
