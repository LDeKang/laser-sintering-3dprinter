# SLS Nylon 3D Printer

选择性激光烧结尼龙3D打印机 - Selective Laser Sintering Nylon 3D Printer

## 项目概述

将FDM打印机改装为SLS（选择性激光烧结）设备，使用尼龙粉末材料。

### 核心参数

| 参数 | 值 |
|---|---|
| 技术路线 | SLS (选择性激光烧结) |
| 材料 | 尼龙 (PA12/PA6) |
| 激光器 | 40W 半导体激光 450nm |
| 扫描方式 | XY轴机械扫描 |
| 成型尺寸 | 待确定 |
| 层厚 | 0.08-0.12mm |
| 铺料量 | 30g/次 |
| 预算 | 待评估 |

## 硬件配置

### 主板
- **型号**: Makerbase MKS Robin Nano V3.1
- **MCU**: STM32F407VET6 (ARM Cortex-M4, 168MHz)
- **驱动**: 5x TMC2209 (UART模式)
- **屏幕**: MKS TS35 (3.5寸 TFT触摸屏)
- **WiFi**: ESP8266/ESP32 模块

### 激光系统
- **功率**: 40W
- **波长**: 450nm (蓝光)
- **控制**: PWM调制 (M3/M5指令)

### 运动系统
- **X/Y轴**: 激光头扫描
- **Z轴**: 成型平台下降
- **E轴**: 改铺料电机 (刮板控制)

## 目录结构

```
├── firmware/          # 固件配置
│   ├── marlin/        # Marlin固件配置
│   └── klipper/       # Klipper配置 (备用)
├── hardware/          # 硬件资料
│   ├── schematic/     # 原理图
│   ├── bom/           # 采购清单
│   └── cad/           # 3D模型
├── docs/              # 文档
│   ├── assembly/      # 装配指南
│   ├── operation/     # 操作手册
│   └── calibration/   # 校准指南
├── gcode/             # G-code脚本
└── tests/             # 测试记录
```

## 开发计划

### Week 1: 固件改造 + 激光控制
- [ ] Marlin固件基础配置
- [ ] 激光PWM控制集成
- [ ] TMC2209 UART配置
- [ ] 屏幕UI适配

### Week 2: 切片流程 + 首层测试
- [ ] SLS切片策略
- [ ] 首层烧结测试
- [ ] 功率/速度参数标定

### Week 3: 多层烧结 + 铺粉调试
- [ ] Z轴下降控制
- [ ] 铺料系统调试
- [ ] 层间结合测试

### Week 4: 参数优化 + 成型测试
- [ ] 工艺参数优化
- [ ] 简单几何体打印
- [ ] 文档整理

## Marlin固件配置要点

### 激光控制
```cpp
#define LASER_FEATURE
#define LASER_SAFETY_TIMEOUT_MS 1000
#define SPINDLE_LASER_FREQUENCY 1000
```

### TMC2209 UART
```cpp
#define X_DRIVER_TYPE TMC2209
#define Y_DRIVER_TYPE TMC2209
#define Z_DRIVER_TYPE TMC2209
#define E0_DRIVER_TYPE TMC2209
#define E1_DRIVER_TYPE TMC2209
#define TMC_UART_SW_SERIAL
```

### 主板定义
```cpp
#define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3_1
```

## 参考资料

- [Makerbase GitHub](https://github.com/makerbase-mks)
- [MKS Robin Nano V3.X 资料](https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X)
- [Marlin Firmware](https://marlinfw.org/)

## 项目状态

**当前阶段**: 硬件确认，准备固件开发  
**最后更新**: 2026-03-20  
**版本**: v0.1

---
*原SLM金属打印方案已归档至 `archive/slm-metal/`*
