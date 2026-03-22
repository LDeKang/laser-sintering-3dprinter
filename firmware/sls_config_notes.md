# SLS激光烧结3D打印机 Marlin固件配置说明

## 硬件平台
- **主板**: BTT SKR Mini E3 V3.0 (STM32F103RCT6)
- **激光**: 10W 450nm半导体激光头
- **驱动**: TMC2209 UART模式

## 核心改造点

### 1. 主板配置
```cpp
#define MOTHERBOARD BOARD_BTT_SKR_MINI_E3_V2_0  // V3兼容V2引脚定义
```

### 2. 激光功能启用
```cpp
#define LASER_FEATURE
#define SPINDLE_LASER_USE_PWM
#define SPINDLE_LASER_PWM_INVERT false
#define SPINDLE_LASER_FREQUENCY 1000  // 1kHz PWM频率
```

### 3. 激光PWM引脚配置
在 `pins_BTT_SKR_MINI_E3_common.h` 中添加：
```cpp
#define SPINDLE_LASER_ENA_PIN           PC8   // 使用HE0引脚(原热端加热)
#define SPINDLE_LASER_PWM_PIN           PC8   // PWM输出
```

### 4. E轴改造为铺料电机
- 禁用热端温度控制
- 禁用挤出机相关功能
- E轴仅用于控制铺料刮板运动

### 5. 禁用FDM功能
- 禁用热端加热 (HEATER_0_PIN 改为激光控制)
- 禁用热床加热 (可选保留用于预热粉末)
- 禁用风扇控制 (FAN_PIN 可改为激光辅助功能)

## G代码映射

| 功能 | G代码 | 说明 |
|------|-------|------|
| 激光开启 | M3 S[功率] | 功率范围0-255或0-1000 |
| 激光关闭 | M5 | 关闭激光 |
| 铺料前进 | G1 E[距离] F[速度] | 控制刮板铺粉 |
| 铺料后退 | G1 E-[距离] F[速度] | 刮板复位 |

## 编译环境
- PlatformIO
- 环境: STM32F103RC_btt

## 安全注意事项
1. 激光功率需根据粉末材料调整
2. 必须安装激光防护罩和急停按钮
3. 首次测试使用低功率验证运动轨迹
