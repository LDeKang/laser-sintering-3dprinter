/**
 * Marlin Firmware Configuration
 * For MKS Robin Nano V3.1 SLS Printer
 * 
 * Hardware:
 * - Board: MKS Robin Nano V3.1 (STM32F407VET6)
 * - Drivers: 5x TMC2209 (UART)
 * - Screen: MKS TS35
 * - Laser: 40W 450nm, PWM control
 * - Material: Nylon (PA)
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// ==================== BASIC SETTINGS ====================

#define CONFIGURATION_H_VERSION 02010201

#define STRING_CONFIG_H_AUTHOR "(SLS Nylon Printer)"

#define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3_1

#define SERIAL_PORT 3  // USB
#define SERIAL_PORT_2 1  // UART for WiFi
#define BAUDRATE 115200

// ==================== LASER FEATURE ====================

#define LASER_FEATURE
#define LASER_SAFETY_TIMEOUT_MS 1000

// Laser PWM pin (need to verify from schematic)
// MKS Robin Nano V3.1: PC6, PC7, PC8 available for PWM
#define SPINDLE_LASER_PWM_PIN PC6
#define SPINDLE_LASER_FREQUENCY 1000
#define SPINDLE_LASER_USE_PWM

// M3/M5 laser control
#define SPINDLE_LASER_ENA_PIN PC7  // Enable pin

// ==================== STEPper DRIVERS ====================

#define X_DRIVER_TYPE TMC2209
#define Y_DRIVER_TYPE TMC2209
#define Z_DRIVER_TYPE TMC2209
#define E0_DRIVER_TYPE TMC2209
#define E1_DRIVER_TYPE TMC2209

#define TMC_UART_SW_SERIAL
#define TMC_SW_SCK_PIN  PA13
#define TMC_SW_MISO_PIN PA14
#define TMC_SW_MOSI_PIN PA15

// TMC2209 current settings (mA)
#define X_CURRENT 800
#define Y_CURRENT 800
#define Z_CURRENT 1000
#define E0_CURRENT 600  // Powder spreading motor
#define E1_CURRENT 600

// ==================== MOTION SETTINGS ====================

// Steps per mm (need calibration)
#define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400, 400 }

#define DEFAULT_MAX_FEEDRATE { 300, 300, 5, 25 }
#define DEFAULT_MAX_ACCELERATION { 3000, 3000, 100, 10000 }

#define DEFAULT_ACCELERATION 3000
#define DEFAULT_RETRACT_ACCELERATION 3000
#define DEFAULT_TRAVEL_ACCELERATION 3000

// ==================== THERMAL SETTINGS ====================

// Nylon sintering temp ~180-200°C
#define HEATER_0_MAXTEMP 275
#define BED_MAXTEMP 150

// Preheat for nylon
#define PREHEAT_1_LABEL "Nylon"
#define PREHEAT_1_TEMP_HOTEND 200
#define PREHEAT_1_TEMP_BED 100

// ==================== LCD SETTINGS ====================

#define MKS_TS35_V2_0
#define TFT_COLOR_UI
#define TFT_THEME MKS_Theme

// ==================== WIFI SETTINGS ====================

#define MKS_WIFI_MODULE
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PWD  "YOUR_PASSWORD"

// ==================== ADVANCED ====================

#define EEPROM_SETTINGS
#define SDSUPPORT
#define LONG_FILENAME_HOST_SUPPORT

// SLS specific: Disable extruder cold prevention
#define EXTRUDE_MINTEMP 0

#endif // CONFIGURATION_H
