# Laser Sintering 3D Printer

3D打印机改装激光烧结设备 - 3D Printer to Laser Sintering Conversion

## 项目概述

将普通 3D 打印机（i3 结构）改装为选择性激光烧结（SLS）设备。

### 核心参数

| 参数 | 值 |
|---|---|
| 激光头重量 | 1kg |
| 铺料机构重量 | 1.5kg |
| 单次铺料量 | 30g |
| 控制固件 | Marlin 2.1.2.1 |
| 主板 | STM32 (BTT SKR Mini E3 V3.0) |
| 激光功率 | 10W 450nm 半导体 |

### 运动方案

- **XY 轴**: 激光头移动扫描
- **Z 轴**: 成型平台下降
- **E 轴**: 改铺料电机，控制刮板往复

## 目录结构

```
├── firmware/          # Marlin 固件配置
├── hardware/          # 硬件设计文件
├── docs/              # 文档
├── gcode/             # G-code 脚本和切片配置
└── cad/               # 3D 模型文件
```

## 开发计划

### Week 1: 固件改造 + 激光控制
- [ ] Marlin 配置（SKR Mini E3 V3.0）
- [ ] 激光 PWM 控制（M3/M5 指令）
- [ ] E 轴改铺料电机逻辑

### Week 2: 切片流程 + 首层测试
- [ ] PrusaSlicer 配置
- [ ] G-code 后处理脚本
- [ ] 单层烧结测试

### Week 3: 多层烧结 + 铺粉调试
- [ ] Z 轴下降 + 铺料联动
- [ ] 3-5 层堆叠测试

### Week 4: 参数优化 + 成型测试
- [ ] 激光功率/速度优化
- [ ] 完整立方体烧结

## 硬件清单

- [ ] 10W 450nm 半导体激光头
- [ ] 激光驱动板（TTL/PWM 控制）
- [ ] 铺料刮板机构
- [ ] 步进电机（铺料用）
- [ ] 尼龙粉末（PA12）

## 参考资料

- [Marlin Firmware](https://marlinfw.org/)
- [SKR Mini E3 V3.0 文档](https://github.com/bigtreetech/BIGTREETECH-SKR-mini-E3)

---

**项目周期**: 1个月  
**开始日期**: 2026-03-14
