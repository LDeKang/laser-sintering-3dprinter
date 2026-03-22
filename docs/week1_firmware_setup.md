# SLS激光烧结3D打印机 - Week 1 固件改造记录

## 日期: 2026-03-22

---

## 已完成配置

### 1. 主板配置 (Configuration.h)
```cpp
#define MOTHERBOARD BOARD_BTT_SKR_MINI_E3_V2_0  // V3兼容V2引脚
#define STRING_CONFIG_H_AUTHOR "(SLS Laser Sintering, Claw)"
```

### 2. 激光功能启用 (Configuration_adv.h)
```cpp
#define LASER_FEATURE
#define SPINDLE_LASER_USE_PWM
#define SPINDLE_LASER_PWM_INVERT false
#define SPINDLE_LASER_FREQUENCY 1000  // 1kHz
```

### 3. 激光引脚定义 (pins_BTT_SKR_MINI_E3_common.h)
```cpp
#define SPINDLE_LASER_ENA_PIN   PC8   // 原HE0引脚
#define SPINDLE_LASER_PWM_PIN   PC8   // 原HE0引脚
```

### 4. 热端改造
- `TEMP_SENSOR_0` 改为 `998` (虚拟传感器)
- `HEATER_0_MINTEMP` 设为 `0`
- `HEATER_0_MAXTEMP` 设为 `300`
- 禁用 `THERMAL_PROTECTION_HOTENDS`
- 禁用 `SINGLENOZZLE`

### 5. E轴铺料电机参数
```cpp
#define EXTRUDERS 1
#define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 400, 1600 }  // E: 1600 steps/mm (T8丝杆)
#define DEFAULT_MAX_FEEDRATE          { 200, 200, 4, 50 }      // E: 50mm/s max
#define DEFAULT_MAX_ACCELERATION      { 1000, 1000, 200, 500 } // E: 500mm/s²
```

---

## 硬件连接参考

### SKR Mini E3 V3.0 引脚分配 (SLS模式)

| 功能 | 引脚 | 备注 |
|------|------|------|
| X_STEP | PB13 | XY扫描 |
| X_DIR | PB12 | |
| Y_STEP | PB10 | XY扫描 |
| Y_DIR | PB2 | |
| Z_STEP | PB0 | 成型平台升降 |
| Z_DIR | PC5 | |
| E0_STEP | PB3 | **铺料电机** |
| E0_DIR | PB4 | |
| 激光PWM | PC8 | **原HE0，10W激光驱动** |
| 激光使能 | PC8 | 与PWM共用 |

---

## G代码指令映射

| 指令 | 功能 | 示例 |
|------|------|------|
| `M3 S[n]` | 激光开启，功率n | `M3 S128` (50%功率) |
| `M5` | 激光关闭 | `M5` |
| `G1 E[n] F[速度]` | 铺料电机移动 | `G1 E10 F1000` |
| `G1 X Y F[速度]` | XY扫描移动 | `G1 X50 Y50 F800` |
| `G1 Z[n]` | 成型平台下降 | `G1 Z0.1` (层厚0.1mm) |

---

## 下一步任务

1. **编译测试**
   - 使用PlatformIO编译固件
   - 验证无编译错误

2. **硬件测试**
   - 上传固件到SKR Mini E3 V3
   - 测试激光PWM输出（示波器/万用表）
   - 测试E轴铺料电机运动
   - 测试XY扫描运动

3. **安全功能**
   - 添加激光使能开关检测
   - 添加防护罩门检测
   - 配置急停按钮

4. **切片流程准备**
   - 研究Cura/PrusaSlicer激光模式
   - 创建SLS后处理脚本

---

## 注意事项

1. **激光安全**: 10W 450nm激光属于Class 4，必须佩戴防护眼镜
2. **PWM频率**: 1kHz适合半导体激光器，避免过高频率
3. **铺料精度**: T8丝杆精度约0.01mm，满足SLS需求
4. **热端禁用**: 确认HE0引脚不再用于加热，避免短路
