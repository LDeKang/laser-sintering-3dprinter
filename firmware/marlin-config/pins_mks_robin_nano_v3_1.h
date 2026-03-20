/**
 * MKS Robin Nano V3.1 Pin Mapping
 * For SLS Laser Sintering Printer
 * 
 * Based on MKS Robin Nano V3.X schematic
 * Reference: https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X
 */

#ifndef PINS_MKS_ROBIN_NANO_V3_1_H
#define PINS_MKS_ROBIN_NANO_V3_1_H

// ==================== MCU INFO ====================
// STM32F407VET6
// - Core: ARM Cortex-M4, 168MHz
// - Flash: 512KB
// - RAM: 128KB
// - Package: LQFP100

// ==================== STEPPER PINS ====================

// X Axis
#define X_STEP_PIN         PE3
#define X_DIR_PIN          PE2
#define X_ENABLE_PIN       PE4
#define X_CS_PIN           PA15  // TMC2209 UART

// Y Axis
#define Y_STEP_PIN         PE0
#define Y_DIR_PIN          PB9
#define Y_ENABLE_PIN       PE1
#define Y_CS_PIN           PA15  // Shared UART

// Z Axis
#define Z_STEP_PIN         PB5
#define Z_DIR_PIN          PB4
#define Z_ENABLE_PIN       PB8
#define Z_CS_PIN           PA15  // Shared UART

// E0 Axis (Powder Spreading)
#define E0_STEP_PIN        PB3
#define E0_DIR_PIN         PD6
#define E0_ENABLE_PIN      PB7
#define E0_CS_PIN          PA15  // Shared UART

// E1 Axis (Reserved)
#define E1_STEP_PIN        PA15  // Check schematic
#define E1_DIR_PIN         PA8
#define E1_ENABLE_PIN      PD7
#define E1_CS_PIN          PA15  // Shared UART

// ==================== LASER PINS ====================
// PWM capable pins on STM32F407:
// - PC6 (TIM3_CH1, TIM8_CH1)
// - PC7 (TIM3_CH2, TIM8_CH2)
// - PC8 (TIM3_CH3, TIM8_CH3)
// - PA8 (TIM1_CH1)

#define SPINDLE_LASER_PWM_PIN    PC6   // PWM output for laser power
#define SPINDLE_LASER_ENA_PIN    PC7   // Laser enable
#define SPINDLE_LASER_DIR_PIN    -1    // Not used for laser

// ==================== TEMPERATURE PINS ====================

#define TEMP_0_PIN         PC1   // Hotend (if used for preheat)
#define TEMP_BED_PIN       PC0   // Bed/Platform temperature
#define TEMP_CHAMBER_PIN   PC2   // Chamber temperature (optional)

// ==================== HEATER PINS ====================

#define HEATER_0_PIN       PC6   // Hotend (shared with laser, use relay)
#define HEATER_BED_PIN     PC7   // Bed heater

// ==================== FAN PINS ====================

#define FAN_PIN            PA0   // Part cooling fan
#define FAN1_PIN           PA1   // Laser cooling fan (critical!)
#define FAN2_PIN           PA2   // Chamber circulation

// ==================== ENDSTOP PINS ====================

#define X_MIN_PIN          PA12
#define X_MAX_PIN          PA11
#define Y_MIN_PIN          PC6
#define Y_MAX_PIN          PC7
#define Z_MIN_PIN          PA8
#define Z_MAX_PIN          PC8

// ==================== PROBE ====================

#define PROBE_TARE_PIN     PA4   // Bed leveling probe (optional)

// ==================== SD CARD ====================

#define SD_DETECT_PIN      PD12
#define SD_SS_PIN          PA4

// ==================== LCD/TS35 ====================

#define TFT_CS_PIN         PG12
#define TFT_DC_PIN         PG10
#define TFT_RST_PIN        PG11
#define TFT_BACKLIGHT_PIN  PD13

#define TOUCH_CS_PIN       PG9
#define TOUCH_IRQ_PIN      PA15

// ==================== WIFI ====================

#define WIFI_RX_PIN        PD9
#define WIFI_TX_PIN        PD8
#define WIFI_RESET_PIN     PD11

// ==================== USB ====================

#define USB_DETECT_PIN     PA9

// ==================== DEBUG ====================

#define DEBUG_PIN          PA13  // SWDIO
#define DEBUG_PIN2         PA14  // SWCLK

// ==================== SLS SPECIFIC ====================

// Laser interlock (safety)
#define LASER_INTERLOCK_PIN    PB0   // Door switch
#define LASER_ESTOP_PIN        PB1   // Emergency stop

// Powder level sensor
#define POWDER_LEVEL_PIN       PC3

// Chamber atmosphere sensor (optional)
#define O2_SENSOR_PIN          PC4

#endif // PINS_MKS_ROBIN_NANO_V3_1_H
