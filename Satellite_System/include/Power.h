#ifndef POWER_H
#define POWER_H
/** @brief I2C data (SDA) pin on the ESP. Change to match your wiring. */
#define SDA_Pin 21
/** @brief I2C clock (SCL) pin on the ESP. Change to match your wiring. */
#define SCL_Pin 22

//#include "include/Types.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

//#define MAX_BAT_CAP 10200.00f

// change these values based on the pins used on the ESP

/** @name INA219 Measurement Variables
 *  Most recent readings, updated by take_measurment().
 *  @{
 */
extern float shuntvoltage;  ///< Voltage across the shunt resistor (mV).
extern float busvoltage;    ///< Bus voltage (V).
extern float current_mA;    ///< Current through the shunt (mA).
extern float loadvoltage;   ///< Load voltage, bus voltage + shunt voltage (V).
extern float power_mW;      ///< Power draw (mW).
/** @} */

/** @name State of Charge (SoC) Variables
 *  Used by get_curr_SoC() and get_curr_SoC2() to track battery state.
 *  @{
 */
extern float SoC;                 ///< Estimated state of charge, 0.0 (empty) to 1.0 (full).
extern float q_capacity;          ///< Estimated remaining battery capacity (mAh).
extern float q_max;               ///< Maximum battery capacity (mAh).
extern unsigned long last_time;   ///< Timestamp (ms, from millis()) of the last SoC update.
/** @} */


/** @brief INA219 current/voltage sensor instance. */
extern Adafruit_INA219 ina219;

/**
 * @brief Initializes the I2C bus and the INA219 sensor.
 *
 * Starts I2C on #SDA_Pin / #SCL_Pin, resets #q_capacity to #q_max,
 * records the starting time in #last_time, and attempts to start the INA219.
 *
 * @retval 1 The INA219 was found and initialized successfully.
 * @retval 0 The INA219 was not found (an error is printed to Serial).
 */
int set_up_INA219( void );

/**
 * @brief Reads the INA219 and updates the global measurement variables.
 *
 * Updates #shuntvoltage, #busvoltage, #current_mA, #power_mW, and
 * #loadvoltage.
 *
 * @param flag Set to 1 to print the readings to Serial; any other value
 *             suppresses output.
 *
 * @warning Do not pass 1 when calling from an interrupt context. Serial
 *          printing inside an ISR can crash the program.
 */
void take_measurment( int flag );

/**
 * @brief Estimates the state of charge using a ratio-based update.
 *
 * Takes a new measurement, then subtracts the charge used since the last
 * call from #SoC. The result is clamped to the range [0.0, 1.0].
 *
 * @return The updated state of charge as a fraction (0.0 to 1.0).
 *
 * @note This implementation is marked as needing rework. See
 *       get_curr_SoC2() for a version with consistent unit conversion.
 * @see get_curr_SoC2()
 */
float get_curr_SoC( void );

/**
 * @brief Estimates the state of charge using coulomb counting.
 *
 * Takes a new measurement, converts current (mA) and elapsed time (ms) into
 * consumed charge (mAh), and subtracts it from #q_capacity. #q_capacity is
 * clamped to [0, #q_max], and SoC is computed as #q_capacity / #q_max.
 *
 * @return The updated state of charge as a fraction (0.0 to 1.0).
 *
 * @note Handles millis() rollover through unsigned subtraction.
 * @see get_curr_SoC()
 */
float get_curr_SoC2( void );


#endif