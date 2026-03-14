# Week 1 任务清单: 固件改造 + 激光控制

**目标**: 完成 Marlin 固件配置，实现激光 PWM 控制和铺料电机驱动

---

## Day 1-2: Marlin 基础配置

### 任务 1.1: 复制配置文件
- [ ] 复制 `Configuration.h` 和 `Configuration_adv.h`
- [ ] 选择正确的主板配置（BTT SKR Mini E3 V3.0）

### 任务 1.2: 基础参数设置
- [ ] 设置打印机名称: `LaserSintering`
- [ ] 设置 XYZ 行程（根据原打印机）
- [ ] 设置步进电机参数（步数/mm）

---

## Day 3-4: 激光控制配置

### 任务 2.1: 启用激光/主轴功能
```cpp
#define SPINDLE_FEATURE
#define SPINDLE_LASER_PWM_PIN FAN0_PIN  // 激光接风扇口
#define SPINDLE_LASER_FREQUENCY 1000    // 1kHz PWM
#define LASER_POWER_INLINE              // 内联功率控制
```

### 任务 2.2: 激光安全设置
- [ ] 启用激光安全门（可选）
- [ ] 设置激光移动时自动开启
- [ ] 设置空闲时自动关闭

---

## Day 5-7: 铺料电机配置

### 任务 3.1: E 轴改铺料电机
- [ ] 禁用挤出机温度检查
- [ ] 配置 E 轴为线性轴（非挤出）
- [ ] 设置铺料电机步数/mm

### 任务 3.2: 自定义 G-code
- [ ] M201: 铺料前进
- [ ] M202: 铺料复位
- [ ] 每层结束自动调用铺料

---

## 配置文件位置

```
firmware/Marlin-2.1.2.1-src/Marlin/
├── Configuration.h      # 主配置
├── Configuration_adv.h  # 高级配置
└── src/pins/            # 引脚定义
```

---

## 验证清单

- [ ] 固件编译通过
- [ ] M3 S255 开启激光（最大亮度）
- [ ] M5 关闭激光
- [ ] G1 E10 F1000 铺料电机前进
- [ ] G1 E-10 F1000 铺料电机复位

---

**截止日期**: 2026-03-21
