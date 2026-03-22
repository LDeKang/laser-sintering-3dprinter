# SLS Nylon 3D Printer - Marlin Firmware Setup

## 硬件配置
- **主板**: MKS Robin Nano V3.1 (STM32F407VE, 168MHz)
- **屏幕**: MKS TS35 V2.0 (3.5寸 TFT)
- **WiFi**: ESP8266/ESP32 模块
- **驱动**: 5x TMC2209 (UART模式)
- **激光**: 40W 半导体激光 450nm
- **材料**: 尼龙 (PA12/PA6)

## 文件说明

### Configuration.h
- 主板选择: `BOARD_MKS_ROBIN_NANO_V3_1`
- 激光控制: `LASER_FEATURE` 启用
- 激光PWM引脚: `PC6` (需确认)
- 激光使能引脚: `PC7` (需确认)
- TMC2209 UART配置
- 步进电机电流设置

### Configuration_adv.h
- 加热腔温度控制
- TMC2209高级设置
- S曲线加速度
- 自定义SLS菜单

## 编译步骤

### 1. 安装 PlatformIO
```bash
pip install platformio
```

### 2. 复制配置文件
将 `Configuration.h` 和 `Configuration_adv.h` 复制到 Marlin 目录:
```
Marlin-2.1.2.1-src/Marlin/Configuration.h
Marlin-2.1.2.1-src/Marlin/Configuration_adv.h
```

### 3. 修改 platformio.ini
确保环境设置为:
```ini
default_envs = mks_robin_nano_v3_usb_flash_drive
```

### 4. 编译
```bash
cd Marlin-2.1.2.1-src
pio run -e mks_robin_nano_nano_v3_usb_flash_drive
```

### 5. 烧录
将生成的 `Robin_nano_v3.bin` 复制到SD卡根目录，插入主板开机自动更新。

## 激光引脚确认

**重要**: 激光PWM引脚需要根据实际硬件连接确认。

MKS Robin Nano V3.1 可用PWM引脚:
- PC6 (TIM3_CH1)
- PC7 (TIM3_CH2) 
- PC8 (TIM3_CH3)
- PC9 (TIM3_CH4)
- PA8 (TIM1_CH1)

当前配置使用 PC6 作为PWM输出，PC7 作为使能信号。

## SLS G-code 指令

### 激光控制
```gcode
M3 S128      ; 激光开启，功率50% (0-255)
M3 S255      ; 激光全开
M5           ; 激光关闭
```

### 扫描移动
```gcode
G1 X10 Y20 F3000   ; 激光扫描移动 (激光自动开启)
G0 X0 Y0 F6000     ; 快速移动 (激光自动关闭)
```

### 铺粉控制
```gcode
G1 E10 F1000   ; 铺粉电机前进 (送粉)
G1 E-5 F2000   ; 铺粉电机后退 (刮平)
```

## 待确认事项

- [ ] 激光PWM引脚实际连接
- [ ] 激光使能信号引脚
- [ ] XY轴限位开关引脚
- [ ] Z轴限位开关引脚
- [ ] 铺粉电机方向
- [ ] 加热腔温度传感器类型
- [ ] 步进电机步进数校准

## 参考文档

- [MKS Robin Nano V3.X 资料](https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X)
- [Marlin Laser Feature](https://marlinfw.org/docs/features/laser.html)
- [TMC2209 UART配置](https://marlinfw.org/docs/features/tmc_drivers.html)
