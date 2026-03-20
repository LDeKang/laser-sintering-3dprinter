# SLS 3D打印机 - 系统架构分析

## 整体架构

```
┌─────────────────────────────────────────────────────────────┐
│                        应用层 (Application)                  │
├─────────────────────────────────────────────────────────────┤
│  切片软件 (PrusaSlicer/Cura)  →  G-code生成                  │
│  上位机控制 (OctoPrint/ESP3D)  →  无线传输                   │
│  触摸屏UI (MKS TS35)  →  本地操作                           │
└─────────────────────────────────────────────────────────────┘
                              ↓ G-code指令
┌─────────────────────────────────────────────────────────────┐
│                      系统层 (Marlin Firmware)                │
├─────────────────────────────────────────────────────────────┤
│  G-code解析器 → 运动规划 → 运动控制 → 外设控制               │
│  ├─ 激光控制 (M3/M5)                                        │
│  ├─ 温度控制 (M140/M190)                                    │
│  ├─ 运动控制 (G0/G1/G28)                                    │
│  └─ 文件系统 (SD卡/WiFi)                                    │
└─────────────────────────────────────────────────────────────┘
                              ↓ HAL抽象层
┌─────────────────────────────────────────────────────────────┐
│                    驱动层 (Hardware Abstraction)             │
├─────────────────────────────────────────────────────────────┤
│  STM32 HAL库 / Arduino框架  →  寄存器操作                    │
│  ├─ GPIO (引脚控制)                                         │
│  ├─ TIM (PWM输出 - 激光功率)                                │
│  ├─ UART (TMC2209通信)                                      │
│  ├─ SPI (屏幕/SD卡)                                         │
│  ├─ ADC (温度采集)                                          │
│  └─ DMA (数据传输)                                          │
└─────────────────────────────────────────────────────────────┘
                              ↓ 硬件信号
┌─────────────────────────────────────────────────────────────┐
│                      硬件层 (Physical Hardware)              │
├─────────────────────────────────────────────────────────────┤
│  STM32F407VE ←→ TMC2209 ←→ 步进电机                         │
│           ←→ 激光驱动板 ←→ 40W激光                           │
│           ←→ 加热MOS管 ←→ 加热床/腔                          │
│           ←→ TFT屏幕控制器                                   │
│           ←→ ESP8266 (WiFi)                                  │
└─────────────────────────────────────────────────────────────┘
```

## 芯片与库的关系

### STM32F407VE 核心参数
- **架构**: ARM Cortex-M4F (带FPU浮点单元)
- **主频**: 168 MHz
- **Flash**: 512 KB
- **RAM**: 128 KB
- **GPIO**: 82个可用引脚

### 库的位置和作用

```
Marlin-2.1.2.1-src/
├── Marlin/
│   └── src/
│       └── HAL/                    ← HAL层在这里
│           ├── HAL.h               ← 通用HAL接口
│           └── STM32/              ← STM32专用实现
│               ├── HAL.cpp         ← STM32 HAL实现
│               ├── fastio.cpp      ← 快速IO操作
│               ├── tim.cpp         ← 定时器/PWM
│               ├── adc.cpp         ← ADC采集
│               ├── spi.cpp         ← SPI通信
│               ├── sdio.cpp        ← SD卡
│               └── usb_serial.cpp  ← USB串口
│
└── buildroot/
    └── share/
        └── PlatformIO/
            └── scripts/
                └── stm32.py        ← 编译脚本
```

### 底层库依赖

```
Marlin
  ├── Arduino Core (STM32duino)     ← 封装HAL
  │   └── STM32 HAL (官方库)         ← ST官方提供
  │       ├── Drivers/STM32F4xx_HAL_Driver/
  │       ├── CMSIS/Core/
  │       └── CMSIS/Device/ST/STM32F4xx/
  │
  └── PlatformIO Framework
      └── framework-arduinoststm32/
```

## 怎么玩开发板？

### 1. 基础验证 (Blink)

```cpp
// 最简单的LED闪烁 - 验证编译烧录
#include <Arduino.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);  // PC13 通常是板载LED
    Serial.begin(115200);
    Serial.println("MKS Robin Nano V3.1 Ready!");
}

void loop() {
    digitalWrite(LED_BUILTIN, LOW);   // LED亮 (低电平有效)
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);  // LED灭
    delay(500);
    Serial.println("Blink!");
}
```

### 2. PWM输出测试 (激光控制基础)

```cpp
// 测试PWM输出 - 激光功率控制原理
#include <Arduino.h>

#define LASER_PIN PC6    // 假设激光PWM接PC6

void setup() {
    Serial.begin(115200);
    
    // 配置PWM: 1kHz频率, 8位分辨率
    analogWriteFrequency(LASER_PIN, 1000);
    analogWriteResolution(8);
    
    Serial.println("PWM Test Ready");
}

void loop() {
    // 渐变测试激光功率
    for (int i = 0; i <= 255; i++) {
        analogWrite(LASER_PIN, i);    // 0-255 对应 0-100%功率
        Serial.print("PWM: ");
        Serial.println(i);
        delay(20);
    }
    delay(1000);
    
    for (int i = 255; i >= 0; i--) {
        analogWrite(LASER_PIN, i);
        Serial.print("PWM: ");
        Serial.println(i);
        delay(20);
    }
    delay(1000);
}
```

### 3. 步进电机控制测试

```cpp
// 测试单个步进电机
#include <Arduino.h>

#define STEP_PIN PA0    // X轴步进
#define DIR_PIN  PC0    // X轴方向
#define EN_PIN   PB0    // X轴使能

void setup() {
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    
    digitalWrite(EN_PIN, LOW);   // 使能电机 (低电平有效)
    Serial.begin(115200);
}

void loop() {
    // 正转1000步
    digitalWrite(DIR_PIN, HIGH);
    for (int i = 0; i < 1000; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(100);  // 脉冲宽度
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(900);  // 控制速度
    }
    delay(500);
    
    // 反转1000步
    digitalWrite(DIR_PIN, LOW);
    for (int i = 0; i < 1000; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(100);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(900);
    }
    delay(500);
}
```

### 4. TMC2209 UART通信测试

```cpp
// 读取TMC2209驱动器状态
#include <TMCStepper.h>

#define TMC_SERIAL Serial2    // 使用UART2
#define R_SENSE 0.11f         // 采样电阻值

TMC2209Stepper driver(&TMC_SERIAL, R_SENSE, 0);  // 地址0

void setup() {
    Serial.begin(115200);
    TMC_SERIAL.begin(115200);
    
    driver.begin();
    driver.toff(4);
    driver.rms_current(800);    // 800mA
    driver.microsteps(16);
    driver.en_spreadCycle(false);
    driver.pwm_autoscale(true);
    
    Serial.println("TMC2209 Test");
}

void loop() {
    Serial.print("Status: ");
    Serial.print(driver.DRV_STATUS(), HEX);
    Serial.print(" | Current: ");
    Serial.print(driver.rms_current());
    Serial.print("mA | Microsteps: ");
    Serial.println(driver.microsteps());
    
    delay(1000);
}
```

## 开发板引脚图 (MKS Robin Nano V3.1)

```
                    ┌─────────────────────┐
    5V/GND          │                     │          5V/GND
    RESET           │    STM32F407VE      │          USB
    3.3V            │                     │          SDIO (SD卡)
                    │                     │          
    X_STEP  ────────┤ PA0                 ├────────  Y_STEP
    X_DIR   ────────┤ PC0                 ├────────  Y_DIR
    X_EN    ────────┤ PB0                 ├────────  Y_EN
    X_UART  ────────┤ PA9  (UART1_TX)     ├────────  Y_UART
                    │                     │
    Z_STEP  ────────┤ PA1                 ├────────  E0_STEP
    Z_DIR   ────────┤ PC1                 ├────────  E0_DIR
    Z_EN    ────────┤ PB1                 ├────────  E0_EN
    Z_UART  ────────┤ PA10 (UART1_RX)     ├────────  E0_UART
                    │                     │
    E1_STEP ────────┤ PA2                 ├────────  FAN0
    E1_DIR  ────────┤ PC2                 ├────────  FAN1
    E1_EN   ────────┤ PB2                 ├────────  FAN2
                    │                     │
    HE0     ────────┤ PA3                 ├────────  BED
    HE1     ────────┤ PA4                 ├────────  TH0 (热敏)
    LASER   ────────┤ PC6  (TIM3_CH1)     ├────────  TH1
                    │                     │
    TFT_CS  ────────┤ PB12                ├────────  TB  (床温)
    TFT_DC  ────────┤ PB13                │
    TFT_RST ────────┤ PB14                │
                    │                     │
    WIFI_TX ────────┤ PA2  (UART2_TX)     │
    WIFI_RX ────────┤ PA3  (UART2_RX)     │
                    └─────────────────────┘
```

## 开发流程

```
1. 硬件到手
   └─→ 检查焊接、电源、短路
       └─→ 烧录Bootloader (如果空白芯片)
           └─→ 烧录测试固件 (Blink)
               └─→ 逐个模块验证 (PWM/步进/UART)
                   └─→ 集成Marlin固件
                       └─→ SLS功能调试
```

## 关键问题

### Q: Marlin怎么控制激光？
```cpp
// Marlin内部流程
G-code "M3 S128" 
  → parser.parse()
  → gcode_M3()
  → cutter.set_power(128)
  → analogWrite(LASER_PIN, 128)  // 最终调用HAL
```

### Q: 怎么调试？
- **串口打印**: `SERIAL_ECHO_MSG("Debug info")`
- **G-code响应**: 发送`M115`查看固件信息
- **实时监控**: `M122`查看TMC驱动状态

### Q: 库在哪里下载？
PlatformIO自动处理：
```ini
; platformio.ini
platform = ststm32
framework = arduino
board = marlin_STM32F407VE
; 自动下载: STM32duino + HAL库
```

---

# Marlin 2.1.2.1 完整文件结构

## 根目录
```
Marlin-2.1.2.1-src/
├── platformio.ini              ← PlatformIO编译配置
├── Makefile                    ← Make编译脚本
├── README.md                   ← 项目说明
│
├── Marlin/                     ← 【核心源码目录】
│   ├── Configuration.h         ← 主配置文件
│   ├── Configuration_adv.h     ← 高级配置文件
│   ├── Version.h               ← 版本信息
│   └── src/                    ← 源代码目录
│
├── buildroot/                  ← 构建工具和资源
│   ├── share/                  ← 共享资源
│   │   ├── PlatformIO/         ← PlatformIO支持文件
│   │   │   ├── scripts/        ← 编译脚本
│   │   │   └── variants/       ← 各主板变体定义
│   │   │       └── MARLIN_F407VE/  ← STM32F407VE配置
│   │   ├── fonts/              ← 字体资源
│   │   └── extras/             ← 额外工具
│   └── tests/                  ← 测试代码
│
├── config/                     ← 示例配置
├── docker/                     ← Docker支持
├── docs/                       ← 文档
└── ini/                        ← PlatformIO环境配置
    ├── stm32f4.ini             ← STM32F4系列配置
    ├── features.ini            ← 功能特性配置
    └── avr.ini, lpc176x.ini... ← 其他平台配置
```

## 核心源码目录 (Marlin/src/)

```
Marlin/src/
│
├── MarlinCore.cpp/.h           ← 【主程序入口】setup() & loop()
│
├── core/                       ← 核心基础设施
│   ├── boards.h                ← 主板定义列表
│   ├── types.h                 ← 基础类型定义
│   ├── serial.h/cpp            ← 串口通信
│   └── utility.cpp             ← 工具函数
│
├── HAL/                        ← 【硬件抽象层 - 关键目录】
│   ├── HAL.h                   ← HAL通用接口
│   ├── platforms.h             ← 平台检测
│   ├── shared/                 ← 共享HAL代码
│   │   ├── eeprom_api.cpp      ← EEPROM接口
│   │   └── servo.cpp           ← 舵机控制
│   │
│   ├── STM32/                  ← 【STM32平台实现】★
│   │   ├── HAL.cpp/.h          ← STM32 HAL主文件
│   │   ├── fastio.cpp/.h       ← 快速GPIO操作
│   │   ├── tim.cpp             ← 定时器/PWM实现
│   │   ├── adc.cpp             ← ADC温度采集
│   │   ├── spi.cpp             ← SPI通信
│   │   ├── MarlinSerial.cpp    ← 串口实现
│   │   ├── eeprom_flash.cpp    ← Flash模拟EEPROM
│   │   └── tft/                ← TFT屏幕驱动
│   │       ├── tft_spi.cpp     ← SPI方式TFT
│   │       └── xpt2046.cpp     ← 触摸屏驱动
│   │
│   ├── AVR/                    ← AVR平台(Arduino Mega)
│   ├── LPC1768/                ← LPC1768平台(Smoothieboard)
│   ├── ESP32/                  ← ESP32平台
│   └── ...                     ← 其他平台
│
├── gcode/                      ← 【G-code解析层】
│   ├── gcode.cpp/.h            ← G-code主解析器
│   ├── parser.cpp/.h           ← 参数解析器
│   ├── queue.cpp/.h            ← G-code队列
│   │
│   ├── motion/                 ← 运动类G-code
│   │   ├── G0_G1.cpp           ← 直线移动
│   │   ├── G28.cpp             ← 回零
│   │   └── G2_G3.cpp           ← 圆弧插补
│   │
│   ├── control/                ← 控制类G-code
│   │   ├── M3-M5.cpp           ← 【激光/主轴控制】★
│   │   ├── M17_M18_M84.cpp     ← 电机使能/禁用
│   │   └── M80_M81.cpp         ← 电源控制
│   │
│   ├── temp/                   ← 温度类G-code
│   │   ├── M104_M109.cpp       ← 热端温度
│   │   └── M140_M190.cpp       ← 热床温度
│   │
│   ├── config/                 ← 配置类G-code
│   │   └── M92.cpp             ← 设置步进数
│   │
│   └── feature/                ← 特性类G-code
│       └── trinamic/           ← TMC驱动配置
│           ├── M122.cpp        ← 诊断信息
│           └── M906.cpp        ← 设置电流
│
├── module/                     ← 【核心功能模块】
│   ├── motion.cpp/.h           ← 运动控制主模块
│   ├── planner.cpp/.h          ← 【运动规划器】★
│   ├── stepper/                ← 步进电机控制
│   │   ├── indirection.cpp     ← 步进信号分发
│   │   ├── trinamic.cpp        ← TMC驱动管理
│   │   └── TMC26X.cpp          ← TMC26X驱动支持
│   │
│   ├── endstops.cpp/.h         ← 限位开关处理
│   ├── probe.cpp/.h            ← 探针控制
│   ├── servo.cpp/.h            ← 舵机控制
│   └── thermistor/             ← 热敏电阻表
│       └── thermistor_*.h      ← 各种型号热敏电阻
│
├── feature/                    ← 【可选功能特性】
│   ├── cutter/                 ← 【激光/刀具控制】★
│   │   └── cutter.cpp/.h       ← 激光功率控制
│   │
│   ├── babystep.cpp            ← 微步调整
│   ├── bltouch.cpp             ← BLTouch探针
│   ├── caselight.cpp           ← 机箱照明
│   ├── controllerfan.cpp       ← 控制器风扇
│   ├── filament/               ← 耗材相关
│   ├── bedlevel/               ← 床面调平
│   │   ├── abl/                ← 自动调平
│   │   └── ubl/                ← 统一床面调平
│   │
│   └── powerloss.cpp           ← 断电续打
│
├── lcd/                        ← 【显示和用户界面】
│   ├── marlinui.cpp/.h         ← UI主模块
│   ├── menu/                   ← 菜单系统
│   │   ├── menu_main.cpp       ← 主菜单
│   │   └── menu_configuration.cpp
│   │
│   ├── tft/                    ← TFT屏幕支持
│   │   ├── tft.cpp             ← TFT核心驱动
│   │   ├── touch.cpp           ← 触摸处理
│   │   └── ui_480x320.cpp      ← 480x320界面
│   │
│   ├── extui/                  ← 外部UI接口
│   │   └── mks_ui/             ← MKS屏幕UI
│   │       └── draw_*.cpp      ← 各界面绘制
│   │
│   └── language/               ← 多语言支持
│       └── language_*.h        ← 各语言文件
│
├── pins/                       ← 【引脚定义】
│   ├── pins.h                  ← 引脚主文件
│   ├── stm32f4/                ← STM32F4系列引脚
│   │   └── pins_MKS_ROBIN_NANO_V3_1.h  ← 【我们的主板】★
│   ├── stm32f1/                ← STM32F1系列
│   ├── mega/                   ← ATmega系列
│   └── ...                     ← 其他平台
│
├── sd/                         ← 【SD卡文件系统】
│   ├── cardreader.cpp/.h       ← SD卡读取
│   ├── Sd2Card.cpp/.h          ← SD卡底层驱动
│   └── usb_flashdrive/         ← U盘支持
│
├── inc/                        ← 包含文件
│   ├── MarlinConfig.h          ← 配置总入口
│   ├── Conditionals_*.h        ← 条件编译
│   └── SanityCheck.h           ← 配置检查
│
└── libs/                       ← 第三方库
    ├── buzzer.cpp              ← 蜂鸣器
    ├── crc16.cpp               ← CRC校验
    └── heatshrink/             ← 数据压缩
```

## 关键文件调用链示例

### 激光控制调用链
```
G-code输入: M3 S128
    ↓
gcode/control/M3-M5.cpp  →  gcode_M3()
    ↓
feature/cutter/cutter.cpp  →  set_power(128)
    ↓
HAL/STM32/tim.cpp  →  analogWrite(pin, 128)
    ↓
STM32duino HAL  →  TIM3->CCR1 = 128
    ↓
硬件PWM输出
```

### 步进控制调用链
```
G-code输入: G1 X10 F3000
    ↓
gcode/motion/G0_G1.cpp
    ↓
module/planner.cpp  →  planner.buffer_line()
    ↓
module/stepper/indirection.cpp  →  stepper ISR
    ↓
HAL/STM32/fastio.cpp  →  digitalWrite(STEP_PIN, HIGH/LOW)
    ↓
GPIO寄存器操作
```

### TMC2209配置调用链
```
G-code输入: M906 X800
    ↓
gcode/feature/trinamic/M906.cpp
    ↓
module/stepper/trinamic.cpp  →  stepperX.rms_current(800)
    ↓
TMCStepper库  →  UART通信
    ↓
HAL/STM32/MarlinSerial.cpp  →  Serial1.write()
    ↓
USART1->DR = data
```

## 编译配置相关

```
ini/
├── stm32f4.ini                 ← STM32F4编译环境
│   ├── env:mks_robin_nano_v3
│   └── env:mks_robin_nano_v3_usb_flash_drive
│
├── features.ini                ← 功能特性开关
└── platformio.ini              ← 主配置文件
    └── default_envs = mks_robin_nano_v3_usb_flash_drive
```

---

## 下一步建议

1. **先跑通基础**: 烧录Blink，确认板子活着
2. **测试PWM**: 用示波器看PC6波形
3. **验证步进**: 接一个电机看转动
4. **集成Marlin**: 用我们写的配置编译烧录
5. **功能验证**: 激光、屏幕、WiFi逐个测试

需要我针对哪个部分详细展开？
