# Mushroom Species Profiles

This document describes the growing parameters for different mushroom species supported by Terrashroom.

## Profile System (Future)

When implemented, the Terrashroom will include a profile selection system that automatically configures:
- Humidity setpoint
- Temperature setpoint
- FAE (Fresh Air Exchange) interval and duration

Select a species and growth phase from the web UI, and the system adjusts parameters accordingly.

## Species Parameters

### Pink Oyster (Pleurotus djamor)

Fast-growing, warm-weather oyster mushroom. Pink color, delicate texture.

| Phase | Humidity | Temp (°F) | FAE Interval | FAE Duration |
|-------|----------|-----------|--------------|--------------|
| Colonization | 80% | 77°F | 4 hours | 30 sec |
| Fruiting | 87% | 70°F | 30 min | 60 sec |

**Notes:**
- Tolerates higher temperatures than other oysters
- Quick colonization (7-14 days)
- Fruits in flushes; expect 3-4 flushes
- Color fades when cooked

### Blue Oyster (Pleurotus ostreatus var. columbinus)

Cold-weather oyster with striking blue caps. Robust flavor.

| Phase | Humidity | Temp (°F) | FAE Interval | FAE Duration |
|-------|----------|-----------|--------------|--------------|
| Colonization | 80% | 72°F | 4 hours | 30 sec |
| Fruiting | 87% | 60°F | 30 min | 60 sec |

**Notes:**
- Requires cold shock to initiate fruiting
- Best flavor at lower temperatures
- Color fades to gray as mushrooms mature

### Lion's Mane (Hericium erinaceus)

Brain-boosting medicinal mushroom. Cascading white spines.

| Phase | Humidity | Temp (°F) | FAE Interval | FAE Duration |
|-------|----------|-----------|--------------|--------------|
| Colonization | 75% | 70°F | 6 hours | 20 sec |
| Fruiting | 92% | 64°F | 1 hour | 45 sec |

**Notes:**
- Very high humidity required for fruiting
- Slow colonization (3-4 weeks)
- Harvest when spines begin to elongate
- Sensitive to CO2; needs good FAE

### Shiitake (Lentinula edodes)

Classic culinary mushroom. Rich umami flavor.

| Phase | Humidity | Temp (°F) | FAE Interval | FAE Duration |
|-------|----------|-----------|--------------|--------------|
| Colonization | 75% | 75°F | 6 hours | 20 sec |
| Fruiting | 82% | 65°F | 1 hour | 45 sec |

**Notes:**
- Long colonization (6-12 weeks on logs, 2-3 weeks on sawdust)
- Benefits from cold shock and "slapping" blocks
- Lower humidity than oysters to prevent cap spots
- Caps should curl under before harvest

### King Trumpet (Pleurotus eryngii)

Thick-stemmed oyster with meaty texture. Mild flavor.

| Phase | Humidity | Temp (°F) | FAE Interval | FAE Duration |
|-------|----------|-----------|--------------|--------------|
| Colonization | 75% | 72°F | 6 hours | 20 sec |
| Fruiting | 87% | 60°F | 45 min | 60 sec |

**Notes:**
- Needs cold temperatures for fruiting
- Top-fruiting; cut X in top of bag
- Harvest when cap begins to flatten
- Most forgiving of low humidity among oysters

## General Guidelines

### Humidity

- **Below setpoint**: Atomizer runs in "spritz" mode with blower assist
- **At setpoint (±3%)**: Maintain current state
- **Above 96%**: Emergency flush to protect electronics

### Temperature

- **Below setpoint (±2°F)**: Heater increases duty gradually
- **At setpoint**: Maintain current duty
- **Above setpoint**: Heater turns off immediately
- **Above 95°F**: Emergency shutdown

### Fresh Air Exchange

FAE serves two purposes:
1. Removes CO2 buildup (high CO2 causes elongated stems)
2. Helps regulate humidity

More FAE = lower humidity and CO2
Less FAE = higher humidity and CO2

### Transitioning Phases

When switching from Colonization to Fruiting:
1. Select new phase in web UI
2. System gradually adjusts to new setpoints
3. Consider manual cold shock for species that benefit from it

## Custom Profiles

To add custom species or adjust parameters:

1. Edit `esphome/includes/profile_data.h`
2. Add new species to the `get_profile()` function
3. Recompile and flash

Example addition:
```cpp
else if (species == "Reishi") {
  if (phase == "Colonization") {
    profile = {75.0f, 75.0f, 21600, 20};
  } else if (phase == "Fruiting") {
    profile = {90.0f, 75.0f, 7200, 30};
  }
}
```

## References

- [Stamets, P. "Growing Gourmet and Medicinal Mushrooms"](https://fungi.com/)
- [North Spore Growing Guides](https://northspore.com/pages/growing-guides)
- [FreshCap Mushrooms](https://learn.freshcap.com/)
