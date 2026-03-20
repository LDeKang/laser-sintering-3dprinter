/**
 * SLS Nylon 3D Printer - Configuration.h
 * 
 * 选择性激光烧结尼龙3D打印机配置文件
 * 主板: MKS Robin Nano V3.1 (STM32F407VE)
 * 激光: 40W 半导体激光 450nm
 * 材料: 尼龙 (PA12/PA6)
 */

#pragma once
#define CONFIGURATION_H_VERSION 02010201

//============================= Basic Info =============================
#define STRING_CONFIG_H_AUTHOR "(SLS-Nylon, MKS Robin Nano V3.1)"
#define SHOW_BOOTSCREEN
#define SHOW_CUSTOM_BOOTSCREEN

//============================= Board Selection =============================
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3_1
#endif

//============================= Serial Settings =============================
#define SERIAL_PORT -1        // USB
#define SERIAL_PORT_2 1       // UART1 for WiFi
#define BAUDRATE 115200

//============================= Laser Feature =============================
// Enable laser control for SLS
#define LASER_FEATURE
#if ENABLED(LASER_FEATURE)
  #define LASER_SAFETY_TIMEOUT_MS 1000    // Laser auto-off after 1s without movement
  #define LASER_POWER_INLINE
  #define LASER_POWER_INLINE_TRAPEZOID
  #define LASER_POWER_INLINE_TRAPEZOID_CONT
  
  // Laser PWM settings
  #define SPINDLE_LASER_PWM_PIN PC6       // MKS Robin Nano V3.1 laser pin
  #define SPINDLE_LASER_FREQUENCY 1000    // 1kHz PWM
  #define SPINDLE_LASER_USE_PWM
  
  // Laser power range (0-255 or 0-1000)
  #define SPINDLE_LASER_POWERUP_DELAY 50
  #define SPINDLE_LASER_POWERDOWN_DELAY 50
  
  // M3/M5 laser control commands
  #define SPINDLE_LASER_ENA_PIN PC7       // Laser enable pin
#endif

//============================= Stepper Drivers =============================
#define X_DRIVER_TYPE TMC2209
#define Y_DRIVER_TYPE TMC2209
#define Z_DRIVER_TYPE TMC2209
#define E0_DRIVER_TYPE TMC2209
#define E1_DRIVER_TYPE TMC2209

// TMC2209 UART settings
#define TMC_UART_SW_SERIAL
#define X_SERIAL_TX_PIN PA9
#define X_SERIAL_RX_PIN PA10
#define Y_SERIAL_TX_PIN PA9
#define Y_SERIAL_RX_PIN PA10
#define Z_SERIAL_TX_PIN PA9
#define Z_SERIAL_RX_PIN PA10
#define E0_SERIAL_TX_PIN PA9
#define E0_SERIAL_RX_PIN PA10
#define E1_SERIAL_TX_PIN PA9
#define E1_SERIAL_RX_PIN PA10

// TMC2209 current settings (mA)
#define X_CURRENT 800
#define Y_CURRENT 800
#define Z_CURRENT 1000
#define E0_CURRENT 600    // Powder spreading motor
#define E1_CURRENT 600

//============================= Axis Settings =============================
// SLS mechanical scanning - XY moves laser head
#define X_MIN_ENDSTOP_INVERTING false
#define Y_MIN_ENDSTOP_INVERTING false
#define Z_MIN_ENDSTOP_INVERTING false

// Steps per mm (to be calibrated)
#define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400, 400, 400 }

// Max feedrates (mm/s)
#define DEFAULT_MAX_FEEDRATE { 300, 300, 5, 50, 50 }

// Acceleration (mm/s^2)
#define DEFAULT_MAX_ACCELERATION { 3000, 3000, 100, 10000, 10000 }
#define DEFAULT_ACCELERATION 1500
#define DEFAULT_RETRACT_ACCELERATION 3000
#define DEFAULT_TRAVEL_ACCELERATION 1500

//============================= Temperature =============================
// No hotend for SLS, but may need heated bed/chamber
#define TEMP_SENSOR_BED 1
#define TEMP_BED_RESIDENCY_TIME 10
#define TEMP_BED_WINDOW 1
#define TEMP_BED_HYSTERESIS 3

// Bed temperature for nylon preheating
#define TEMP_BED_MAX 200

//============================= Bed Leveling =============================
// Disable for SLS (no bed leveling needed)
//#define PROBE_MANUALLY
//#define AUTO_BED_LEVELING_BILINEAR

//============================= LCD / Display =============================
#define MKS_TS35_V2_0
#define TFT_COLOR_UI
#define TFT_THEME MKS_TFT_THEME

//============================= SD Card =============================
#define SDSUPPORT
#define SD_DETECT_PIN PA3

//============================= WiFi =============================
#define ESP3D_WIFISUPPORT
#define WEBSOCKET_FEATURE

//============================= Advanced =============================
// Disable extruder (E0 used for powder spreading)
#define EXTRUDERS 0

// SLS doesn't use traditional hotend
#define TEMP_SENSOR_0 0

// Enable EEPROM for settings storage
#define EEPROM_SETTINGS
#define EEPROM_CHITCHAT

//============================= Safety =============================
#define USE_WATCHDOG
#define EMERGENCY_PARSER
#define PARK_HEAD_ON_PAUSE

//============================= Custom G-code =============================
// SLS specific commands
#define CUSTOM_USER_MENU_TITLE "SLS Functions"
#define CUSTOM_USER_MENU_SCRIPT "M3 S0\nG28"

//============================= End of Configuration =============================
