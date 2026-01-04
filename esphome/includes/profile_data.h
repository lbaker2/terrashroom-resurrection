#pragma once
#include "esphome.h"
#include <string>

namespace terrashroom {

// Profile parameter structure
struct GrowProfile {
  float humidity;      // Target humidity %
  float temp_f;        // Target temperature °F
  int fae_interval_s;  // FAE interval in seconds
  int fae_duration_s;  // FAE duration in seconds
};

/**
 * Get profile parameters for species and phase.
 * @param species Species name (e.g., "Pink Oyster")
 * @param phase Growth phase ("Colonization" or "Fruiting")
 * @return GrowProfile with target parameters
 */
inline GrowProfile get_profile(const std::string& species, const std::string& phase) {
  // Default profile
  GrowProfile profile = {85.0f, 72.0f, 1800, 60};

  if (species == "Pink Oyster") {
    if (phase == "Colonization") {
      profile = {80.0f, 77.0f, 14400, 30};
    } else if (phase == "Fruiting") {
      profile = {87.0f, 70.0f, 1800, 60};
    }
  }
  else if (species == "Blue Oyster") {
    if (phase == "Colonization") {
      profile = {80.0f, 72.0f, 14400, 30};
    } else if (phase == "Fruiting") {
      profile = {87.0f, 60.0f, 1800, 60};
    }
  }
  else if (species == "Lion's Mane") {
    if (phase == "Colonization") {
      profile = {75.0f, 70.0f, 21600, 20};
    } else if (phase == "Fruiting") {
      profile = {92.0f, 64.0f, 3600, 45};
    }
  }
  else if (species == "Shiitake") {
    if (phase == "Colonization") {
      profile = {75.0f, 75.0f, 21600, 20};
    } else if (phase == "Fruiting") {
      profile = {82.0f, 65.0f, 3600, 45};
    }
  }
  else if (species == "King Trumpet") {
    if (phase == "Colonization") {
      profile = {75.0f, 72.0f, 21600, 20};
    } else if (phase == "Fruiting") {
      profile = {87.0f, 60.0f, 2700, 60};
    }
  }

  return profile;
}

} // namespace terrashroom
