/**
 * SLS Nylon 3D Printer - Configuration_adv.h (MKS Compatible)
 * 
 * 高级配置
 */

#pragma once
#define CONFIGURATION_ADV_H_VERSION 02010201

//============================= Temperature =============================
// 加热腔体 PID
#if ENABLED(PIDTEMPCHAMBER)
  #define CHAMBER_PID_DEFAULT_P 10.0
  #define CHAMBER_PID_DEFAULT_I 0.5
  #define CHAMBER_PID_DEFAULT_D 100.0
#endif

//============================= Laser Advanced =============================
#if ENABLED(LASER_FEATURE)
  // 激光功率缩放
  #define LASER_POWER_TRAP
  
  // G-code 控制激光
  #define LASER_MOVE_G0_OFF
  #define LASER_MOVE_G1_ON
  
  // 激光菜单
  #define LASER_MENU
  
  // 激光冷却风扇 (必须!)
  #define LASER_COOLING_FAN_PIN PC14
  #define LASER_COOLING_FAN_SPEED 255
#endif

//============================= TMC2209 Advanced =============================
#define TMC_DEBUG
#define MONITOR_DRIVER_STATUS
#define CURRENT_STEP_DOWN 50
#define REPORT_CURRENT_CHANGE
#define STOP_ON_ERROR

// 无传感器归零 (如启用)
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
#if ENABLED(TFT_LVGL_UI)
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

//============================= MKS WiFi =============================
#if ENABLED(MKS_WIFI_MODULE)
  #define WIFI_IO0_PIN PC13
  #define WIFI_IO1_PIN PC7
  #define WIFI_RESET_PIN PE9
#endif

//============================= USB Flash Drive =============================
// MKS Robin Nano V3 支持 USB
#define USB_FLASH_DRIVE_SUPPORT
#define MULTI_VOLUME

//============================= SLS Specific =============================
// 铺料参数
#define SLS_POWDER_SPREAD_DISTANCE 10.0    // 铺料距离 (mm)
#define SLS_POWDER_SPREAD_SPEED 50         // 铺料速度 (mm/s)
#define SLS_LAYER_THICKNESS 0.1            // 层厚 (mm)

// 激光扫描参数
#define SLS_LASER_SCAN_SPEED 100           // 扫描速度 (mm/s)
#define SLS_LASER_PREHEAT_TIME 5000        // 预热时间 (ms)

// 安全参数
#define SLS_DOOR_CHECK_INTERVAL 100        // 门检测间隔 (ms)
#define SLS_MAX_LASER_ON_TIME 30000        // 最大激光开启时间 (ms)

//============================= Experimental =============================
// 调试选项
//#define SLS_DEBUG_MODE
//#define SLS_LOG_SCAN_PATH

//============================= End of Configuration =============================
