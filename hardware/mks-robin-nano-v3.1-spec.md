# MKS Robin Nano V3.1 硬件规格

## 主板概述

| 参数 | 规格 |
|------|------|
| 型号 | MKS Robin Nano V3.1 |
| 厂商 | Makerbase (创客基地) |
| MCU | STM32F407VET6 |
| 内核 | ARM Cortex-M4 |
| 主频 | 168 MHz |
| Flash | 512 KB |
| RAM | 128 KB |
| 封装 | LQFP100 |

## 电源规格

| 参数 | 规格 |
|------|------|
| 输入电压 | 12V / 24V DC |
| 逻辑电压 | 3.3V |
| 热端电流 | 15A (MOSFET) |
| 热床电流 | 15A (MOSFET) |
| 风扇输出 | 3x PWM (1A each) |

## 步进驱动

| 参数 | 规格 |
|------|------|
| 驱动数量 | 5路 |
| 驱动类型 | TMC2209 (UART模式) |
| 微步进 | 256细分 |
| 电流范围 | 0.5-1.5A RMS |
| 静音模式 | StealthChop2 |
| 堵转检测 | StallGuard4 |

## 接口列表

### 步进电机接口
- X轴: 4pin PH2.0
- Y轴: 4pin PH2.0
- Z轴: 4pin PH2.0
- E0轴: 4pin PH2.0
- E1轴: 4pin PH2.0

### 温度传感器
- TH0 (热端): 2pin
- TB (热床): 2pin
- TH1 (扩展): 2pin

### 加热输出
- HE0 (热端): 2pin 螺丝端子
- HB (热床): 2pin 螺丝端子

### 风扇输出
- FAN0: 2pin JST
- FAN1: 2pin JST
- FAN2: 2pin JST

### 限位开关
- X-MIN, X-MAX: 3pin JST
- Y-MIN, Y-MAX: 3pin JST
- Z-MIN, Z-MAX: 3pin JST

### 扩展接口
- BLTouch: 5pin JST
- 断料检测: 3pin JST
- WiFi模块: 8pin排针
- USB: Type-B
- TF卡槽: 板载

## SLS项目适配

### 激光控制
- PWM输出: PC6 (TIM3_CH1)
- 使能信号: PC7
- 频率: 1kHz (可配置)
- 电压: 3.3V/5V (需确认)

### 铺料电机
- 使用E0轴驱动
- TMC2209电流设置: 600-800mA
- 方向控制: 正转铺料，反转回收

### 安全接口
- 门开关: 建议接Z-MAX或自定义
- 急停: 建议接RESET或自定义
- 激光冷却风扇: 必须接FAN1 (常开)

## 引脚分配图

```
                    [MKS Robin Nano V3.1]
                         
    [USB]                                    [POWER]
      |                                         |
   [TF卡]    [TFT35]    [WiFi]    [驱动UART]   [热端] [热床]
      |         |          |          |          |      |
   +--------------------------------------------------------+
   |                                                        |
   |   [X] [Y] [Z] [E0] [E1]  <- 步进电机接口               |
   |                                                        |
   |   [X-MIN] [Y-MIN] [Z-MIN]  <- 限位开关                 |
   |   [X-MAX] [Y-MAX] [Z-MAX]                              |
   |                                                        |
   |   [TH0] [TB] [TH1]  <- 温度传感器                       |
   |                                                        |
   |   [FAN0] [FAN1] [FAN2]  <- 风扇输出                    |
   |                                                        |
   |   [BLTouch] [Runout]  <- 扩展接口                       |
   |                                                        |
   +--------------------------------------------------------+
```

## 参考资料

- 官方GitHub: https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X
- 原理图: 待下载
- 引脚图: 待下载
- Marlin固件: https://github.com/makerbase-mks/Mks-Robin-Nano-Marlin2.0-Firmware

## 待确认事项

- [ ] 激光PWM引脚电压 (3.3V or 5V)
- [ ] 激光使能信号极性
- [ ] WiFi模块型号 (ESP8266 or ESP32)
- [ ] 屏幕固件版本
