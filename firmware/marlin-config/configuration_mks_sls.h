/**
 * SLS Nylon 3D Printer - Configuration.h (MKS Compatible)
 * 
 * 选择性激光烧结尼龙3D打印机配置文件
 * 主板: MKS Robin Nano V3.1 (STM32F407VE)
 * 激光: 40W 半导体激光 450nm
 * 材料: 尼龙 (PA12/PA6)
 * 
 * 基于 MKS 官方 Marlin 2.0.x 配置移植到 Marlin 2.1.2.1
 */

#pragma once
#define CONFIGURATION_H_VERSION 02010201

//============================= Basic Info =============================
#define STRING_CONFIG_H_AUTHOR "(SLS-Nylon, MKS Robin Nano V3.1)"
#define SHOW_BOOTSCREEN
#define SHOW_CUSTOM_BOOTSCREEN

//============================= Board Selection =============================
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3
#endif

//============================= Serial Settings =============================
// MKS 官方使用 SERIAL_PORT 3
#define SERIAL_PORT 3
#define BAUDRATE 115200

// USB Serial for PC connection
#define SERIAL_PORT_2 -1
#define BAUDRATE_2 115200

//============================= Laser Feature =============================
// Enable laser control for SLS
#define LASER_FEATURE
#if ENABLED(LASER_FEATURE)
  #define LASER_SAFETY_TIMEOUT_MS 1000    // Laser auto-off after 1s without movement
  #define LASER_POWER_INLINE
  #define LASER_POWER_INLINE_TRAPEZOID
  #define LASER_POWER_INLINE_TRAPEZOID_CONT
  
  // Laser PWM settings - 使用未占用的引脚
  #define SPINDLE_LASER_PWM_PIN PA6       // 激光功率控制 (PWM)
  #define SPINDLE_LASER_FREQUENCY 1000    // 1kHz PWM
  #define SPINDLE_LASER_USE_PWM
  
  // Laser power range
  #define SPINDLE_LASER_POWERUP_DELAY 50
  #define SPINDLE_LASER_POWERDOWN_DELAY 50
  
  // M3/M5 laser control
  #define SPINDLE_LASER_ENA_PIN PA7       // 激光使能
  
  // Laser menu in UI
  #define LASER_MENU
#endif

//============================= SLS Safety =============================
// 激光安全功能
#define SLS_SAFETY_DOOR_PIN PB0           // 安全门开关
#define SLS_ESTOP_PIN PB1                 // 急停按钮

//============================= Stepper Drivers =============================
#define X_DRIVER_TYPE TMC2209
#define Y_DRIVER_TYPE TMC2209
#define Z_DRIVER_TYPE TMC2209
#define E0_DRIVER_TYPE TMC2209
#define E1_DRIVER_TYPE TMC2209

// TMC2209 UART - MKS 官方使用软件串行
#define TMC_USE_SW_SPI
#define TMC_SW_MOSI PD14
#define TMC_SW_MISO PD1
#define TMC_SW_SCK PD0

// TMC2209 电流设置 (mA)
#define X_CURRENT 800
#define Y_CURRENT 800
#define Z_CURRENT 1000
#define E0_CURRENT 600    // 铺料电机
#define E1_CURRENT 600

// TMC2209 高级功能
#define TMC_DEBUG
#define MONITOR_DRIVER_STATUS
#define HYBRID_THRESHOLD
#define X_HYBRID_THRESHOLD 100
#define Y_HYBRID_THRESHOLD 100
#define Z_HYBRID_THRESHOLD 4
#define E0_HYBRID_THRESHOLD 30
#define E1_HYBRID_THRESHOLD 30

//============================= Axis Settings =============================
// SLS 机械扫描 - XY 移动激光头
#define X_MIN_ENDSTOP_INVERTING false
#define Y_MIN_ENDSTOP_INVERTING false
#define Z_MIN_ENDSTOP_INVERTING false

// 每毫米步数 (待校准)
#define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400, 400, 400 }

// 最大进给速度 (mm/s)
#define DEFAULT_MAX_FEEDRATE { 300, 300, 5, 50, 50 }

// 加速度 (mm/s^2)
#define DEFAULT_MAX_ACCELERATION { 3000, 3000, 100, 10000, 10000 }
#define DEFAULT_ACCELERATION 1500
#define DEFAULT_RETRACT_ACCELERATION 3000
#define DEFAULT_TRAVEL_ACCELERATION 1500

// S-Curve 加速度
#define S_CURVE_ACCELERATION

//============================= Temperature =============================
// SLS 不需要热端，但需要加热床/腔体
#define TEMP_SENSOR_BED 1
#define TEMP_BED_RESIDENCY_TIME 10
#define TEMP_BED_WINDOW 1
#define TEMP_BED_HYSTERESIS 3

// 加热腔体 (尼龙烧结需要)
#define HEATER_CHAMBER_PIN PA1
#define TEMP_SENSOR_CHAMBER 1
#define CHAMBER_MAXTEMP 180
#define CHAMBER_MINTEMP 5

// 禁用热端
#define EXTRUDERS 0

//============================= Bed Leveling =============================
#define AUTO_BED_LEVELING_BILINEAR
#define RESTORE_LEVELING_AFTER_G28

//============================= LCD / TFT =============================
// MKS TS35 V2.0 屏幕
#define MKS_TS35_V2_0

// MKS LVGL UI - 彩色触摸界面
#define TFT_LVGL_UI

// WiFi 模块支持
#if ENABLED(TFT_LVGL_UI)
  #define MKS_WIFI_MODULE
#endif

// 触摸屏
#define TOUCH_SCREEN
#define TOUCH_SCREEN_CALIBRATION

//============================= SD Card =============================
#define SDSUPPORT
#define SDCARD_CONNECTION ONBOARD

//============================= Motion =============================
#define LIN_ADVANCE
#define LIN_ADVANCE_K 0

// 微步进调整
#define BABYSTEPPING
#define BABYSTEP_WITHOUT_HOMING
#define BABYSTEP_ALWAYS_AVAILABLE

//============================= Host Communications =============================
#define HOST_ACTION_COMMANDS
#define HOST_PROMPT_SUPPORT
#define HOST_STATUS_NOTIFICATIONS

//============================= EEPROM =============================
#define EEPROM_SETTINGS
#define EEPROM_AUTO_INIT

//============================= LCD Language =============================
#define LCD_LANGUAGE zh_CN
#define DISPLAY_CHARSET_HD44780 JAPANESE

//============================= Print Job =============================
#define PRINTCOUNTER
#define PRINTCOUNTER_SAVE_INTERVAL 60

//============================= Advanced =============================
#define ADVANCED_PAUSE_FEATURE
#define NOZZLE_PARK_FEATURE
#define NOZZLE_CLEAN_FEATURE

//============================= MKS Specific =============================
// MKS 测试模式 (调试用)
//#define MKS_TEST

// MKS PWC 电源控制模块
//#define MKS_PWC

//============================= SLS Specific G-code =============================
// 自定义 G-code 用于 SLS
#define CUSTOM_USER_MENU_TITLE "SLS Functions"
#define CUSTOM_USER_MENU_ITEMS 3
#define USER_DESC_1 "Spread Powder"
#define USER_GCODE_1 "G28\nG1 Z0.1 F300\nG1 E10 F1000"
#define USER_DESC_2 "Laser Test"
#define USER_GCODE_2 "M3 S100\nG4 P1000\nM5"
#define USER_DESC_3 "Home All"
#define USER_GCODE_3 "G28"

//============================= End of Configuration =============================
