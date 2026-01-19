# Terrashroom REST API

The Terrashroom exposes a REST API via ESPHome's web server component. All endpoints are available at `http://<device-ip>/`.

## Authentication

All endpoints require HTTP Basic Auth:
- Username: `admin` (configurable)
- Password: Your `web_password` from secrets.yaml

## Endpoints

### System Information

#### GET /json
Returns complete device state as JSON.

```bash
curl -u admin:password http://192.168.1.100/json
```

Response includes all sensors, switches, lights, and their current states.

### Sensors (Read-Only)

#### GET /sensor/{id}
Get current sensor value.

| Sensor ID | Description |
|-----------|-------------|
| `chamber_temperature` | Temperature in °F |
| `chamber_temperature_celsius` | Temperature in °C |
| `chamber_humidity` | Relative humidity % |

```bash
curl -u admin:password http://192.168.1.100/sensor/chamber_humidity
```

### Switches

#### GET /switch/{id}
Get switch state.

#### POST /switch/{id}/turn_on
Turn switch on.

#### POST /switch/{id}/turn_off
Turn switch off.

#### POST /switch/{id}/toggle
Toggle switch state.

| Switch ID | Description |
|-----------|-------------|
| `uv_led_switch` | UV LED power |
| `camera_power_switch` | Camera module power |
| `blower_enable_switch` | Blower control enable |
| `testing_animation_switch` | Yellow test animation |

```bash
# Turn on UV LED
curl -X POST -u admin:password http://192.168.1.100/switch/uv_led_switch/turn_on

# Toggle camera
curl -X POST -u admin:password http://192.168.1.100/switch/camera_power_switch/toggle
```

### Lights (PWM Outputs)

#### GET /light/{id}
Get light state and brightness.

#### POST /light/{id}/turn_on
Turn light on (optionally with brightness).

#### POST /light/{id}/turn_off
Turn light off.

| Light ID | Description |
|----------|-------------|
| `fan1_light` | Fan 1 (exhaust) speed |
| `fan2_light` | Fan 2 (intake) speed |
| `blower_light` | Blower speed |
| `atomizer_light` | Atomizer power |
| `heater_light` | Heater power |
| `base_lights` | Base LED strip |
| `canopy_lights` | Canopy LED strip |

```bash
# Set fan to 50%
curl -X POST -u admin:password \
  -H "Content-Type: application/json" \
  -d '{"brightness": 128}' \
  http://192.168.1.100/light/fan1_light/turn_on

# Turn off heater
curl -X POST -u admin:password http://192.168.1.100/light/heater_light/turn_off
```

### Number Inputs

#### GET /number/{id}
Get current value.

#### POST /number/{id}/set?value={value}
Set new value.

| Number ID | Description | Range |
|-----------|-------------|-------|
| `blower_speed_number` | Blower speed setpoint | 0.392 - 1.0 |

```bash
# Set blower to 75%
curl -X POST -u admin:password \
  "http://192.168.1.100/number/blower_speed_number/set?value=0.75"
```

### Select Inputs

#### GET /select/{id}
Get current option.

#### POST /select/{id}/set?option={option}
Set new option.

| Select ID | Options |
|-----------|---------|
| `addressable_default_animation` | Off, Solid White, Solid Blue |

```bash
# Set LEDs to solid white
curl -X POST -u admin:password \
  "http://192.168.1.100/select/addressable_default_animation/set?option=Solid%20White"
```

### Buttons

#### POST /button/{id}/press
Trigger button action.

| Button ID | Description |
|-----------|-------------|
| `read_water_level` | Run water level self-test |

```bash
curl -X POST -u admin:password http://192.168.1.100/button/read_water_level/press
```

### Binary Sensors

#### GET /binary_sensor/{id}
Get binary sensor state.

| Sensor ID | Description |
|-----------|-------------|
| `water_level_sensor` | Water level low (true = problem) |

```bash
curl -u admin:password http://192.168.1.100/binary_sensor/water_level_sensor
```

## LED Effects

The addressable LED strips support effects that can be triggered via the API:

```bash
# Set base lights to warning chase effect
curl -X POST -u admin:password \
  -H "Content-Type: application/json" \
  -d '{"effect": "Warning Chase"}' \
  http://192.168.1.100/light/base_lights/turn_on
```

Available effects:
- `Startup Chase` - Green chase pattern
- `Warning Chase` - Red chase pattern
- `Testing Chase` - Yellow chase pattern

## Example Scripts

### Smoke Test

```bash
#!/bin/bash
IP="192.168.1.100"
AUTH="admin:password"

echo "Testing Terrashroom API at $IP"

# Check sensors
echo "Temperature: $(curl -s -u $AUTH http://$IP/sensor/chamber_temperature | jq -r '.value')°F"
echo "Humidity: $(curl -s -u $AUTH http://$IP/sensor/chamber_humidity | jq -r '.value')%"

# Check water level
WATER=$(curl -s -u $AUTH http://$IP/binary_sensor/water_level_sensor | jq -r '.state')
if [ "$WATER" = "ON" ]; then
  echo "WARNING: Water level LOW"
else
  echo "Water level: OK"
fi
```

### Toggle All Fans Off

```bash
#!/bin/bash
IP="192.168.1.100"
AUTH="admin:password"

curl -X POST -u $AUTH http://$IP/light/fan1_light/turn_off
curl -X POST -u $AUTH http://$IP/light/fan2_light/turn_off
curl -X POST -u $AUTH http://$IP/light/blower_light/turn_off

echo "All fans disabled"
```

## Notes

- All brightness values are 0-255 (mapped to 0-100% duty)
- The blower has a minimum effective duty of ~39.2% due to hardware constraints
- Changes take effect immediately; no restart required
- The device automatically saves state across reboots for most entities
