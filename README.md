# MKS Robin Nano V3 3D 打印机固件

基于 Marlin 2.0.9.2 的 MKS Robin Nano V3 标准 FDM 3D 打印机固件。

> **注意**: 本项目由 SLS 激光烧结项目转换而来，保留了原始 SLS 配置备份。

---

## 硬件配置

| 组件 | 型号 | 说明 |
|------|------|------|
| **主板** | MKS Robin Nano V3 | STM32F407VET6, 168MHz |
| **驱动** | TMC2209 x 5 | UART 模式，静音驱动 |
| **屏幕** | MKS TS35 | 3.5寸 TFT 触摸屏 |
| **热端** | 标准 E3D V6 或类似 | 100k 热敏电阻 |
| **热床** | 标准铝基板热床 | 100k 热敏电阻 |
| **挤出机** | BMG / Titan 或类似 | 93 steps/mm (BMG) |

---

## 固件特性

### TMC2209 配置
- ✅ UART 通信模式
- ✅ 256 微步插值
- ✅ StealthChop 静音模式
- ✅ 驱动器状态监控
- ✅ M122 调试命令

### 挤出机配置
- ✅ 线性推进 (Linear Advance)
- ✅ 固件回抽 (FW Retract)
- ✅ 标准 BMG 挤出机参数

### 温度控制
- ✅ PID 热端温度控制
- ✅ 热床温度控制
- ✅ 热端热保护
- ✅ 热床热保护

---

## 快速开始

### 1. 克隆仓库

```bash
git clone https://github.com/LDeKang/laser-sintering-3dprinter.git
cd laser-sintering-3dprinter/firmware/marlin-sls
```

### 2. 安装 PlatformIO

```bash
pip install platformio
```

### 3. 编译固件

```bash
pio run -e mks_robin_nano_v3_usb_flash_drive
```

### 4. 刷入固件

编译完成后，固件位于 `.pio/build/mks_robin_nano_v3_usb_flash_drive/Robin_nano_v3.bin`

1. 将 `Robin_nano_v3.bin` 复制到 SD 卡根目录
2. 插入 SD 卡到主板
3. 开机自动刷入
4. 刷入完成后屏幕显示 "Update Success"

---

## 目录结构

```
├── firmware/
│   ├── marlin-sls/          # Marlin 固件源码
│   │   ├── Marlin/
│   │   │   ├── Configuration.h      # 主配置文件
│   │   │   ├── Configuration_adv.h  # 高级配置
│   │   │   └── ...
│   │   └── platformio.ini
│   ├── README_RESTORE.md    # 恢复说明
│   └── sls_to_fdm.py        # SLS 转 FDM 脚本
├── docs/                     # 文档
│   ├── architecture.md      # 架构设计
│   ├── design-spec-v1.0.md  # 设计规格
│   └── ...
├── hardware/                 # 硬件资料
├── gcode/                    # G-code 脚本
└── cad/                      # CAD 模型
```

---

## 常用 G-code 命令

### TMC2209 调试
```gcode
M122          ; 报告所有 TMC 驱动器状态
M906 X800     ; 设置 X 轴电流为 800mA
M913 X50      ; 设置 X 轴 StealthChop 速度阈值
```

### 温度控制
```gcode
M104 S200     ; 设置热端温度 200°C
M140 S60      ; 设置热床温度 60°C
M109 S200     ; 等待热端达到 200°C
M190 S60      ; 等待热床达到 60°C
```

### 挤出机校准
```gcode
M92 E93       ; 设置 E 轴步数 (BMG 挤出机)
M500          ; 保存到 EEPROM
M503          ; 查看当前配置
```

### 线性推进
```gcode
M900 K0.22    ; 设置线性推进 K 值
M900 K0       ; 禁用线性推进
```

---

## 配置说明

### 关键配置参数

| 参数 | 值 | 说明 |
|------|-----|------|
| `X/Y/Z_CURRENT` | 800mA | TMC2209 运行电流 |
| `E0_CURRENT` | 800mA | 挤出机电流 |
| `DEFAULT_AXIS_STEPS_PER_UNIT` | {80,80,400,93} | X,Y,Z,E 步数 |
| `TEMP_SENSOR_0` | 1 | 热端传感器类型 |
| `TEMP_SENSOR_BED` | 1 | 热床传感器类型 |
| `LIN_ADVANCE_K` | 0.22 | 线性推进系数 |

### 挤出机步数校准

如果挤出长度不准确，按以下步骤校准：

1. 在耗材上标记 100mm 位置
2. 发送 `G1 E100 F100` 挤出 100mm
3. 测量实际挤出长度（假设为 98mm）
4. 计算新步数：`93 × (100/98) = 94.9`
5. 设置新步数：`M92 E94.9`
6. 保存：`M500`

---

## 版本历史

| 版本 | 日期 | 说明 |
|------|------|------|
| v1.0.0 | 2026-03-28 | 初始 FDM 配置，从 SLS 项目转换 |

---

## 相关链接

- [Makerbase MKS Robin Nano V3](https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X)
- [Marlin Firmware](https://marlinfw.org/)
- [TMC2209  datasheet](https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC2209_Datasheet_V103.pdf)

---

## 许可证

本项目基于 Marlin Firmware，遵循 GPL-3.0 许可证。

---

*原 SLS 激光烧结项目配置已备份在 `firmware/marlin-sls/Marlin/Configuration.h.sls.backup`*
