# Terrashroom

An ESPHome-based controller for automated mushroom growing chambers.

## Features

- **Environmental Control**: Temperature, humidity, and fresh air exchange management
- **Species Profiles**: Pre-configured parameters for popular mushroom species
- **Web Interface**: Real-time monitoring and control via browser
- **REST API**: Automation and integration with external systems
- **LED Indicators**: Visual status with addressable RGB strips
- **Safety Guards**: Emergency flush and temperature limits

## Quick Start

```bash
# Clone the repository
git clone https://github.com/lbaker2/terrashroom.git
cd terrashroom/esphome

# Create your configuration files
cp terrashroom.example.yaml terrashroom.yaml
cp secrets.example.yaml secrets.yaml

# Edit secrets.yaml with your WiFi and passwords
# Edit terrashroom.yaml with your network settings

# Flash (first time via USB, then OTA)
esphome run terrashroom.yaml --device /dev/cu.YOUR_SERIAL_PORT
```

See [docs/SETUP.md](docs/SETUP.md) for detailed instructions.

## Repository Structure

```
terrashroom/
├── esphome/                    # ESPHome configuration
│   ├── terrashroom.example.yaml  # Template for user config
│   ├── terrashroom-base.yaml     # Shareable base config
│   ├── secrets.example.yaml      # Template for secrets
│   ├── packages/                 # Modular config packages
│   │   ├── core/                 # Board, WiFi, logging
│   │   ├── hardware/             # Outputs, sensors, lights
│   │   ├── control/              # Control loop stubs
│   │   ├── profiles/             # Species profile stubs
│   │   └── ui/                   # Web UI components
│   ├── includes/                 # C++ header files
│   └── scripts/                  # Build helper scripts
├── hardware/                   # Pinouts and wiring docs
├── docs/                       # User documentation
│   ├── SETUP.md                # Setup guide
│   ├── API.md                  # REST API reference
│   └── PROFILES.md             # Mushroom species profiles
└── tests/                      # Test harness (TODO)
```

## Hardware

The Terrashroom controller is built around an ESP32 with the following peripherals:

| Function | GPIO | Type |
|----------|------|------|
| Fan 1 (exhaust) | 32 | PWM |
| Fan 2 (intake) | 33 | PWM |
| Blower | 25 | PWM |
| Atomizer | 13 | PWM |
| Heater | 12 | PWM (strapping pin) |
| UV LED | 18 | Digital |
| Water sensor | 23 | Input |
| Water enable | 15 | Digital (strapping pin) |
| Camera power | 26 | Digital |
| Base LEDs | 5 | WS2812 (24 LEDs) |
| Canopy LEDs | 14 | WS2812 (64 LEDs) |
| I2C SDA | 21 | HDC1080 sensor |
| I2C SCL | 22 | HDC1080 sensor |

See [hardware/pinout.md](hardware/pinout.md) for complete details.

## Web Interface

Access the Terrashroom at `http://<static_ip>/` (default: `192.168.1.100`)

The web UI provides:
- Real-time temperature and humidity readings
- Manual control of fans, blower, atomizer, heater
- LED strip color and effect selection
- Water level monitoring
- UV LED and camera power control

## REST API

All controls are accessible via REST:

```bash
# Get current humidity
curl -u admin:password http://192.168.1.100/sensor/chamber_humidity

# Turn on UV LED
curl -X POST -u admin:password http://192.168.1.100/switch/uv_led_switch/turn_on

# Set fan speed to 50%
curl -X POST -u admin:password \
  -d '{"brightness": 128}' \
  http://192.168.1.100/light/fan1_light/turn_on
```

See [docs/API.md](docs/API.md) for complete API reference.

## Mushroom Profiles

Supported species with pre-configured growing parameters:

| Species | Colonization Temp | Fruiting Temp | Fruiting Humidity |
|---------|-------------------|---------------|-------------------|
| Pink Oyster | 77°F | 70°F | 87% |
| Blue Oyster | 72°F | 60°F | 87% |
| Lion's Mane | 70°F | 64°F | 92% |
| Shiitake | 75°F | 65°F | 82% |
| King Trumpet | 72°F | 60°F | 87% |

See [docs/PROFILES.md](docs/PROFILES.md) for detailed species information.

## Development

### Prerequisites

- ESPHome (`pip install esphome` or `brew install esphome`)
- Python 3.8+
- USB serial driver for your programmer

### Building

```bash
# Validate configuration
esphome config esphome/terrashroom.yaml

# Compile without flashing
esphome compile esphome/terrashroom.yaml

# Compile and flash
esphome run esphome/terrashroom.yaml
```

### Project Architecture

The configuration uses ESPHome's package system for modularity:

- **terrashroom.yaml**: User's local entry point with secrets and network config
- **terrashroom-base.yaml**: Shareable base that imports all packages
- **packages/**: Modular components organized by function

This structure enables:
- Remote package imports from GitHub
- Clean separation of user-specific and shareable config
- Easy updates without touching user configuration

## Safety Notes

- **GPIO12 and GPIO15** are ESP32 strapping pins. Avoid external pull-ups/pull-downs.
- **Humidity > 96%** triggers emergency fan flush to protect electronics.
- **Temperature > 95°F** triggers heater shutdown.
- The water sensor is only powered during reads to prevent tank heating/corrosion.

## Roadmap

- [ ] Implement humidity control loop with PID-style adjustments
- [ ] Implement temperature control with gradual heater ramping
- [ ] Implement FAE scheduling with species-specific intervals
- [ ] Add species profile selection to web UI
- [ ] Create REST API test suite
- [ ] Camera integration for timelapse
- [ ] Native HDC3022 sensor support

## License

MIT License - See LICENSE file for details.

## Contributing

Contributions welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request

For bugs or feature requests, open an issue on GitHub.
