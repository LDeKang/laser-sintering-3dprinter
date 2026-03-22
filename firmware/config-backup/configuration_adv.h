/**
 * SLS Nylon 3D Printer - Configuration_adv.h
 * 
 * 高级配置
 */

#pragma once
#define CONFIGURATION_ADV_H_VERSION 02010201

//============================= Temperature =============================
// Heated chamber for nylon
#define HEATER_CHAMBER_PIN PA1
#define TEMP_SENSOR_CHAMBER 1
#define CHAMBER_MAXTEMP 180
#define CHAMBER_MINTEMP 5

//============================= Laser Advanced =============================
#if ENABLED(LASER_FEATURE)
  // Laser power scaling
  #define LASER_POWER_TRAP
  
  // G-code controlled laser
  #define LASER_MOVE_G0_OFF
  #define LASER_MOVE_G1_ON
  
  // Laser menu
  #define LASER_MENU
#endif

//============================= TMC2209 Advanced =============================
#define TMC_DEBUG
#define MONITOR_DRIVER_STATUS
#define CURRENT_STEP_DOWN 50
#define REPORT_CURRENT_CHANGE
#define STOP_ON_ERROR

// Hybrid Threshold (switch between StealthChop and SpreadCycle)
#define HYBRID_THRESHOLD
#define X_HYBRID_THRESHOLD 100
#define Y_HYBRID_THRESHOLD 100
#define Z_HYBRID_THRESHOLD 4
#define E0_HYBRID_THRESHOLD 30
#define E1_HYBRID_THRESHOLD 30

// Sensorless homing (if enabled)
//#define SENSORLESS_HOMING
//#define X_STALL_SENSITIVITY 8
//#define Y_STALL_SENSITIVITY 8

//============================= Motion =============================
#define S_CURVE_ACCELERATION
#define LIN_ADVANCE
#define LIN_ADVANCE_K 0
#define STEALTHCHOP_XY
#define STEALTHCHOP_Z
#define STEALTHCHOP_E

//============================= LCD Advanced =============================
#if ENABLED(TFT_COLOR_UI)
  #define TFT_FONT NOTOSANS
  #define TFT_THEME MKS_TFT_THEME
  #define TFT_COLOR_SCRIPTS
#endif

//============================= SD Card Advanced =============================
#define SD_PROCEDURE_DEPTH 1
#define SD_FINISHED_STEPPERRELEASE true
#define SD_FINISHED_RELEASECOMMAND "M84 X Y Z E"
#define SDCARD_READONLY

//============================= Babystepping =============================
#define BABYSTEPPING
#define BABYSTEP_WITHOUT_HOMING
#define BABYSTEP_ALWAYS_AVAILABLE
#define BABYSTEP_DISPLAY_TOTAL

//============================= Host Communications =============================
#define HOST_ACTION_COMMANDS
#define HOST_PROMPT_SUPPORT
#define HOST_STATUS_NOTIFICATIONS

//============================= Power Loss Recovery =============================
//#define POWER_LOSS_RECOVERY
//#define PLR_ENABLED_DEFAULT false
//#define POWER_LOSS_ZHOME

//============================= Experimental =============================
// SLS specific features
#define GCODE_MOTION_MODES
#define GCODE_MACROS
#define CUSTOM_MENU_MAIN
#define CUSTOM_MENU_MAIN_TITLE "SLS Control"

// Custom menu items for SLS
#define CUSTOM_MENU_MAIN_SCRIPT_DONE "M117 SLS Ready"
#define CUSTOM_MENU_MAIN_SCRIPT_AUDIBLE_FEEDBACK

//============================= Developer =============================
#define MARLIN_DEV_MODE
//#define DEBUG_GCODE_PARSER
//#define DEBUG_LASER_FEATURE

//============================= End of Advanced Configuration =============================
