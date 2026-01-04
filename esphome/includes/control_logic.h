#pragma once
#include "esphome.h"

namespace terrashroom {

// ============================================================
// HUMIDITY CONTROL
// ============================================================

/**
 * Check if spritz cooldown has elapsed.
 * @param last_spritz_time Timestamp of last spritz (millis)
 * @param cooldown_ms Cooldown period in milliseconds
 * @return true if cooldown has elapsed
 */
inline bool spritz_cooldown_elapsed(uint32_t last_spritz_time, uint32_t cooldown_ms) {
  return (millis() - last_spritz_time) >= cooldown_ms;
}

/**
 * Calculate new spritz duration with clamping.
 * @param current_duration Current spritz duration in ms
 * @param adjustment Amount to adjust (positive or negative)
 * @param min_duration Minimum allowed duration
 * @param max_duration Maximum allowed duration
 * @return Clamped new duration
 */
inline int adjust_spritz_duration(int current_duration, int adjustment,
                                   int min_duration, int max_duration) {
  int new_duration = current_duration + adjustment;
  if (new_duration < min_duration) return min_duration;
  if (new_duration > max_duration) return max_duration;
  return new_duration;
}

// ============================================================
// TEMPERATURE CONTROL
// ============================================================

/**
 * Calculate heater duty adjustment.
 * @param current_temp Current temperature reading
 * @param setpoint Target temperature
 * @param tolerance Acceptable deviation from setpoint
 * @param current_duty Current heater duty (0.0 - 1.0)
 * @param max_duty Maximum allowed duty
 * @param step Duty adjustment step size
 * @return New heater duty
 */
inline float calculate_heater_duty(float current_temp, float setpoint,
                                    float tolerance, float current_duty,
                                    float max_duty, float step) {
  if (current_temp > (setpoint + tolerance)) {
    // Too hot - turn off
    return 0.0f;
  } else if (current_temp < (setpoint - tolerance)) {
    // Too cold - increase
    float new_duty = current_duty + step;
    return (new_duty > max_duty) ? max_duty : new_duty;
  }
  // Within tolerance - maintain
  return current_duty;
}

// ============================================================
// FAE CONTROL
// ============================================================

/**
 * Check if FAE cycle is due.
 * @param last_fae_time Timestamp of last FAE cycle (millis)
 * @param interval_s FAE interval in seconds
 * @return true if FAE is due
 */
inline bool fae_due(uint32_t last_fae_time, int interval_s) {
  return (millis() - last_fae_time) >= (interval_s * 1000UL);
}

// ============================================================
// SAFETY
// ============================================================

/**
 * Check if humidity is at critical level requiring flush.
 * @param humidity Current humidity reading
 * @param critical_threshold Threshold for emergency action
 * @return true if flush is needed
 */
inline bool humidity_critical(float humidity, float critical_threshold) {
  return humidity >= critical_threshold;
}

/**
 * Check if temperature is dangerously high.
 * @param temp Current temperature
 * @param max_safe Maximum safe temperature
 * @return true if temperature is dangerous
 */
inline bool temperature_dangerous(float temp, float max_safe) {
  return temp >= max_safe;
}

} // namespace terrashroom
