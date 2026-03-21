# MKS 官方固件移植分析报告

## 1. 关键发现

### 1.1 MKS 核心定制组件

| 组件 | 路径 | 说明 |
|-----|------|------|
| **LVGL UI** | `Marlin/src/lcd/extui/mks_ui/` | 完整的彩色触摸UI |
| **MKS 引脚定义** | `Marlin/src/pins/stm32f4/pins_MKS_ROBIN_NANO_V3*.h` | V3/V3.1 主板支持 |
| **图片资源** | `Firmware/mks_pic/` | UI 图片资源文件 |
| **字体资源** | `Firmware/mks_font/` | 字体文件 |
| **WiFi 模块** | `Marlin/src/lcd/extui/mks_ui/wifi*.cpp` | MKS WiFi 支持 |
| **构建脚本** | `buildroot/share/PlatformIO/scripts/mks_*.py` | 固件打包脚本 |

### 1.2 引脚定义差异对比

| 功能 | MKS 官方 | 我们的配置 | 状态 |
|-----|---------|-----------|------|
| X_STEP_PIN | PE3 | PE3 | ✅ 一致 |
| X_DIR_PIN | PE2 | PE2 | ✅ 一致 |
| X_ENABLE_PIN | PE4 | PE4 | ✅ 一致 |
| Y_STEP_PIN | PE0 | PE0 | ✅ 一致 |
| Y_DIR_PIN | PB9 | PB9 | ✅ 一致 |
| Y_ENABLE_PIN | PE1 | PE1 | ✅ 一致 |
| Z_STEP_PIN | PB5 | PB5 | ✅ 一致 |
| Z_DIR_PIN | PB4 | PB4 | ✅ 一致 |
| Z_ENABLE_PIN | PB8 | PB8 | ✅ 一致 |
| E0_STEP_PIN | PD6 | PB3 | ❌ **不同** |
| E0_DIR_PIN | PD3 | PD6 | ❌ **不同** |
| E0_ENABLE_PIN | PB3 | PB7 | ❌ **不同** |
| E1_STEP_PIN | PD15 | PA15 | ❌ **不同** |
| E1_DIR_PIN | PA1 | PA8 | ❌ **不同** |
| E1_ENABLE_PIN | PA3 | PD7 | ❌ **不同** |
| TMC UART TX | PD5/PD7/PD4/PD9/PD8 | PA9 | ❌ **不同** |
| HEATER_0_PIN | PE5 | PC6 | ❌ **不同** |
| HEATER_BED_PIN | PA0 | PC7 | ❌ **不同** |
| FAN_PIN | PC14 | PA0 | ❌ **不同** |
| FAN1_PIN | PB1 | PA1 | ❌ **不同** |

### 1.3 关键差异说明

**⚠️ 重大问题：我们的引脚定义与 MKS 官方完全不匹配！**

MKS Robin Nano V3 的引脚定义是固定的硬件设计，我们的配置中很多引脚是错误的。

#### 正确的 MKS Robin Nano V3 引脚（来自官方）：

```cpp
// 步进电机
#define X_STEP_PIN        PE3
#define X_DIR_PIN         PE2
#define X_ENABLE_PIN      PE4

#define Y_STEP_PIN        PE0
#define Y_DIR_PIN         PB9
#define Y_ENABLE_PIN      PE1

#define Z_STEP_PIN        PB5
#define Z_DIR_PIN         PB4
#define Z_ENABLE_PIN      PB8

#define E0_STEP_PIN       PD6      // 我们错误地配置为 PB3
#define E0_DIR_PIN        PD3      // 我们错误地配置为 PD6
#define E0_ENABLE_PIN     PB3      // 我们错误地配置为 PB7

#define E1_STEP_PIN       PD15     // 我们错误地配置为 PA15
#define E1_DIR_PIN        PA1      // 我们错误地配置为 PA8
#define E1_ENABLE_PIN     PA3      // 我们错误地配置为 PD7

// TMC2209 UART - 软件串行
#define X_SERIAL_TX_PIN   PD5      // 我们错误地配置为 PA9
#define Y_SERIAL_TX_PIN   PD7
#define Z_SERIAL_TX_PIN   PD4
#define E0_SERIAL_TX_PIN  PD9
#define E1_SERIAL_TX_PIN  PD8

// 加热器
#define HEATER_0_PIN      PE5      // 我们错误地配置为 PC6
#define HEATER_BED_PIN    PA0      // 我们错误地配置为 PC7

// 风扇
#define FAN_PIN           PC14     // 我们错误地配置为 PA0
#define FAN1_PIN          PB1      // 我们错误地配置为 PA1
```

## 2. 移植策略

### 2.1 必须修复的问题

1. **引脚定义错误** - 使用 MKS 官方引脚定义
2. **缺少 LVGL UI** - 移植 MKS 的彩色触摸界面
3. **缺少资源文件** - 添加图片/字体资源
4. **构建脚本** - 添加 MKS 固件打包脚本

### 2.2 移植步骤

```
Step 1: 修复引脚定义
  └── 使用 MKS 官方 pins_MKS_ROBIN_NANO_V3_common.h
  └── 添加我们的激光引脚定义

Step 2: 移植 LVGL UI
  └── 复制 Marlin/src/lcd/extui/mks_ui/ 到我们的工程
  └── 修改配置启用 TFT_LVGL_UI

Step 3: 添加资源文件
  └── 创建 Firmware/mks_pic/ 目录
  └── 创建 Firmware/mks_font/ 目录
  └── 添加图片转换脚本

Step 4: 更新构建配置
  └── 添加 platformio.ini MKS 环境
  └── 添加固件打包脚本

Step 5: 集成激光功能
  └── 在 LVGL UI 中添加激光控制界面
  └── 配置激光引脚和安全功能
```

## 3. 文件清单

### 需要移植的文件

```
Marlin/src/lcd/extui/mks_ui/          (整个目录)
Marlin/src/pins/stm32f4/pins_MKS_ROBIN_NANO_V3.h
Marlin/src/pins/stm32f4/pins_MKS_ROBIN_NANO_V3_common.h
buildroot/share/PlatformIO/scripts/mks_robin_nano35.py
Firmware/mks_pic/*.bin
Firmware/mks_font/*.bin
```

### 需要修改的文件

```
Marlin/Configuration.h
Marlin/Configuration_adv.h
platformio.ini
```

## 4. 建议

1. **立即停止使用当前的引脚定义** - 会导致硬件损坏
2. **使用 MKS 官方引脚定义作为基础**
3. **在此基础上添加 SLS 激光功能**
4. **保留 LVGL UI 以获得完整的 MKS 生态支持**

## 5. 下一步行动

要我立即开始：
1. 下载并整理所有需要移植的文件？
2. 修复引脚定义？
3. 创建完整的移植计划？
