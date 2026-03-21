# SLS 3D 打印机固件开发 - 零基础完整学习路线

> **适用对象**: 零 PlatformIO/Marlin 经验的技术负责人  
> **目标**: 从零开始掌握 VSCode + PlatformIO + Marlin 完整开发流程  
> **预计周期**: 6-8 周（每天 2-3 小时）  
> **编写**: Claw (AI 老师傅)  
> **日期**: 2026-03-21

---

## 🎯 学习路线图（重新规划）

```
Phase 1: 工具链基础 (Week 1)
├── Day 1: VSCode 基础操作
├── Day 2: Git 版本控制入门
├── Day 3-4: PlatformIO 核心概念
└── Day 5-7: 第一个编译项目

Phase 2: 嵌入式基础 (Week 2)
├── Day 8-9: STM32 架构认知
├── Day 10-11: 硬件抽象层(HAL)理解
├── Day 12-13: 引脚与GPIO
└── Day 14: 调试技巧入门

Phase 3: Marlin 框架 (Week 3)
├── Day 15-17: Marlin 代码结构
├── Day 18-19: 配置文件详解
├── Day 20-21: 编译与烧录流程
└── Day 22-23: 第一次点亮主板

Phase 4: MKS 生态 (Week 4)
├── Day 24-26: MKS LVGL UI 系统
├── Day 27-28: 屏幕与触摸
└── Day 29-30: WiFi 模块配置

Phase 5: SLS 专项 (Week 5-6)
├── Week 5: 激光控制系统
└── Week 6: 铺料与安全系统

Phase 6: 项目实战 (Week 7-8)
├── Week 7: 移植与调试
└── Week 8: 优化与文档
```

---

## Phase 1: 工具链基础 (Week 1)

### Day 1: VSCode 基础操作

#### 学习目标
- 熟悉 VSCode 界面布局
- 掌握文件操作和代码编辑
- 学会使用扩展插件

#### 实践任务
1. [ ] **界面熟悉**
   - 打开 VSCode，认识左侧活动栏、资源管理器、编辑器区域
   - 练习快捷键：
     - `Ctrl+P` 快速打开文件
     - `Ctrl+Shift+F` 全局搜索
     - `Ctrl+\`` 打开/关闭终端
     - `Ctrl+Shift+P` 命令面板

2. [ ] **安装必要扩展**
   - PlatformIO IDE
   - C/C++ (Microsoft)
   - GitLens
   - 中文语言包（可选）

3. [ ] **文件操作练习**
   - 创建文件夹结构
   - 新建/保存/关闭文件
   - 分屏编辑
   - 文件对比

#### 检查点
- [ ] 能不使用鼠标完成基本文件操作
- [ ] 知道如何查看文件大纲（Outline）
- [ ] 能在终端中执行基本命令

---

### Day 2: Git 版本控制入门

#### 学习目标
- 理解版本控制概念
- 掌握 Git 基本操作
- 学会使用 VSCode 的 Git 功能

#### 核心概念
```
Git 工作流程:
工作区(Working Directory) 
    ↓ git add
暂存区(Staging Area)
    ↓ git commit
本地仓库(Local Repository)
    ↓ git push
远程仓库(Remote Repository)
```

#### 实践任务
1. [ ] **配置 Git**
   ```bash
   git config --global user.name "你的名字"
   git config --global user.email "你的邮箱"
   ```

2. [ ] **基础操作练习**
   ```bash
   # 克隆仓库
   git clone https://github.com/LDeKang/laser-sintering-3dprinter.git
   
   # 查看状态
   git status
   
   # 添加文件到暂存区
   git add 文件名
   
   # 提交更改
   git commit -m "提交说明"
   
   # 推送到远程
   git push origin main
   ```

3. [ ] **VSCode Git 图形界面**
   - 认识源代码管理面板
   - 练习：修改文件 → 暂存 → 提交 → 推送
   - 查看提交历史

#### 检查点
- [ ] 能独立完成 clone/add/commit/push 操作
- [ ] 知道如何查看修改历史
- [ ] 理解 `.gitignore` 的作用

---

### Day 3-4: PlatformIO 核心概念

#### 学习目标
- 理解 PlatformIO 是什么
- 掌握项目结构
- 学会使用 PlatformIO 工具

#### PlatformIO 是什么？
```
PlatformIO = 跨平台嵌入式开发环境

传统开发:          PlatformIO:
Keil/MDK  ----→    统一的 VSCode 界面
Arduino IDE ----→  智能代码补全
STM32CubeIDE ----→ 一键编译烧录
```

#### 核心概念

**1. 平台(Platform)**
```ini
# platformio.ini
platform = ststm32    # STM32 平台
platform = atmelavr   # AVR 平台
```

**2. 框架(Framework)**
```ini
framework = arduino      # Arduino 框架
framework = stm32cube    # HAL 库框架
```

**3. 板子(Board)**
```ini
board = genericSTM32F407VET6    # 我们的主板
board = megaatmega2560          # Mega 2560
```

**4. 环境(Environment)**
```ini
[env:my_env]
platform = ststm32
board = genericSTM32F407VET6
framework = arduino
```

#### 实践任务

**Day 3: 创建第一个 PlatformIO 项目**

1. [ ] **创建新项目**
   - VSCode → PlatformIO 图标 → "Create New Project"
   - Name: `test_project`
   - Board: `Generic STM32F4 series`
   - Framework: `Arduino`

2. [ ] **认识项目结构**
   ```
   test_project/
   ├── include/          # 头文件
   ├── lib/              # 库文件
   ├── src/              # 源代码
   │   └── main.cpp      # 主程序
   ├── test/             # 测试代码
   └── platformio.ini    # 项目配置
   ```

3. [ ] **编写第一个程序**
   ```cpp
   // src/main.cpp
   #include <Arduino.h>
   
   void setup() {
     Serial.begin(115200);
     pinMode(LED_BUILTIN, OUTPUT);
   }
   
   void loop() {
     Serial.println("Hello PlatformIO!");
     digitalWrite(LED_BUILTIN, HIGH);
     delay(500);
     digitalWrite(LED_BUILTIN, LOW);
     delay(500);
   }
   ```

**Day 4: PlatformIO 工具使用**

1. [ ] **底部工具栏功能**
   - 勾选图标：Build (编译)
   - 箭头图标：Upload (上传/烧录)
   - 插头图标：Serial Monitor (串口监视器)
   - 垃圾桶：Clean (清理)

2. [ ] **platformio.ini 详解**
   ```ini
   [env:genericSTM32F407VET6]
   platform = ststm32
   board = genericSTM32F407VET6
   framework = arduino
   
   ; 上传方式
   upload_protocol = stlink    ; 使用 ST-Link
   ; upload_protocol = dfu     ; 使用 USB DFU
   
   ; 调试配置
   debug_tool = stlink
   
   ; 编译选项
   build_flags = 
       -D DEBUG
       -D LED_BUILTIN=PC13
   
   ; 库依赖
   lib_deps = 
       adafruit/Adafruit SSD1306 @ ^2.5.0
   ```

3. [ ] **串口监视器使用**
   - 波特率设置
   - 发送命令
   - 过滤输出

#### 检查点
- [ ] 能独立创建 PlatformIO 项目
- [ ] 理解 platformio.ini 每个配置项
- [ ] 能使用串口监视器查看输出

---

### Day 5-7: 第一个编译项目

#### 学习目标
- 下载 Marlin 源码
- 完成第一次成功编译
- 理解编译输出

#### Day 5: 下载和准备

1. [ ] **克隆 Marlin 仓库**
   ```bash
   # 进入项目目录
   cd D:\mySource\project\AI_Word\laser-sintering-3dprinter\firmware
   
   # 克隆 Marlin (如果还没有)
   git clone https://github.com/MarlinFirmware/Marlin.git Marlin-2.1.2.1-src
   cd Marlin-2.1.2.1-src
   git checkout 2.1.2.1
   ```

2. [ ] **在 VSCode 中打开**
   - File → Open Folder
   - 选择 `Marlin-2.1.2.1-src`
   - 等待 PlatformIO 初始化

3. [ ] **认识 Marlin 项目结构**
   ```
   Marlin-2.1.2.1-src/
   ├── Marlin/
   │   ├── Marlin.ino          # Arduino 入口
   │   ├── Configuration.h     # 主配置
   │   ├── Configuration_adv.h # 高级配置
   │   └── src/                # 源代码
   ├── platformio.ini          # PlatformIO 配置
   └── ...
   ```

#### Day 6: 配置和编译

1. [ ] **选择编译环境**
   ```ini
   # 编辑 platformio.ini
   # 找到 default_envs，改为：
   default_envs = mks_robin_nano_v3_usb_flash_drive
   ```

2. [ ] **复制配置文件**
   ```bash
   # 复制我们的 MKS SLS 配置
   cp ../marlin-config/Configuration_MKS_SLS.h Marlin/Configuration.h
   cp ../marlin-config/Configuration_adv_MKS_SLS.h Marlin/Configuration_adv.h
   ```

3. [ ] **第一次编译**
   - 点击底部工具栏的 ✅ Build
   - 观察编译输出
   - 预计时间：5-15 分钟（首次）

#### Day 7: 理解编译结果

1. [ ] **分析编译输出**
   ```
   RAM:   [==        ]  15.4% (used 20124 bytes from 131072 bytes)
   Flash: [=====     ]  45.2% (used 237312 bytes from 524288 bytes)
   ```
   - RAM: 程序运行内存占用
   - Flash: 固件大小

2. [ ] **找到生成的固件**
   ```
   .pio/build/mks_robin_nano_v3_usb_flash_drive/
   └── Robin_nano_v3.bin    # 这就是要烧录的固件
   ```

3. [ ] **常见编译错误排查**
   | 错误 | 解决方案 |
   |-----|---------|
   | `No such file or directory` | 检查文件路径 |
   | `undefined reference` | 缺少库依赖 |
   | `region RAM overflowed` | 内存不足，禁用一些功能 |
   | `multiple definition` | 重复定义，检查头文件保护 |

#### 检查点
- [ ] 能独立完成 Marlin 编译
- [ ] 能找到生成的 `.bin` 文件
- [ ] 能识别并解决常见编译错误

---

## Phase 2: 嵌入式基础 (Week 2)

### Day 8-9: STM32 架构认知

#### 学习目标
- 理解 STM32F407 基本架构
- 掌握内存映射
- 了解时钟系统

#### STM32F407 核心参数
```
型号: STM32F407VET6
核心: ARM Cortex-M4
频率: 168 MHz
Flash: 512 KB
RAM: 128 KB
GPIO: 82 个
定时器: 14 个
ADC: 3 个 12-bit
```

#### 实践任务
1. [ ] **阅读数据手册**
   - 下载 STM32F407 Reference Manual
   - 重点阅读：
     - 第 2 章：系统架构
     - 第 3 章：存储器映射
     - 第 6 章：时钟系统

2. [ ] **认识 GPIO 端口**
   ```
   STM32F407 端口:
   ├── GPIOA (PA0-PA15)
   ├── GPIOB (PB0-PB15)
   ├── GPIOC (PC0-PC15)
   ├── GPIOD (PD0-PD15)
   ├── GPIOE (PE0-PE15)
   └── ...
   ```

3. [ ] **时钟树理解**
   ```
   HSE (8MHz) → PLL → SYSCLK (168MHz)
                      ├── AHB (168MHz)
                      ├── APB1 (42MHz)
                      └── APB2 (84MHz)
   ```

#### 检查点
- [ ] 能说出 STM32F407 的主要参数
- [ ] 知道 GPIO 命名规则
- [ ] 理解时钟分频概念

---

### Day 10-11: 硬件抽象层(HAL)理解

#### 学习目标
- 理解 HAL 的作用
- 掌握 HAL 基本 API
- 学会查阅 HAL 文档

#### 什么是 HAL？
```
硬件抽象层 (Hardware Abstraction Layer)

应用层代码
    ↓
HAL API (通用接口)
    ↓
寄存器操作 (硬件相关)
    ↓
硬件

好处: 代码可移植，不同芯片只需换 HAL
```

#### 常用 HAL 函数
```cpp
// GPIO 操作
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);    // 置高
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // 置低
HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);                   // 读取
HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);                 // 翻转

// 延时
HAL_Delay(1000);  // 延时 1000ms

// 获取时钟
uint32_t tick = HAL_GetTick();  // 获取系统 tick
```

#### 实践任务
1. [ ] **阅读 HAL 源码**
   - 找到 `stm32f4xx_hal_gpio.c`
   - 理解 `HAL_GPIO_Init()` 函数

2. [ ] **编写 GPIO 测试程序**
   ```cpp
   // 初始化 LED 引脚
   void LED_Init() {
       GPIO_InitTypeDef GPIO_InitStruct = {0};
       __HAL_RCC_GPIOC_CLK_ENABLE();
       
       GPIO_InitStruct.Pin = GPIO_PIN_13;
       GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
       GPIO_InitStruct.Pull = GPIO_NOPULL;
       GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
       HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
   }
   ```

#### 检查点
- [ ] 能解释 HAL 的好处
- [ ] 知道如何初始化 GPIO
- [ ] 能使用基本 HAL 函数

---

### Day 12-13: 引脚与GPIO

#### 学习目标
- 深入理解引脚复用
- 掌握 PWM 输出
- 学会使用定时器

#### 引脚复用功能
```
每个引脚可以有多个功能:
PA6: GPIO / TIM3_CH1 / SPI1_MISO / ...
     ↓         ↓           ↓
   通用IO    PWM输出     SPI通信
```

#### PWM 原理
```
PWM (脉冲宽度调制)

周期: 1ms (频率 1kHz)
占空比: 30%

     ┌──┐     ┌──┐     ┌──
     │  │     │  │     │
─────┘  └─────┘  └─────┘
 0.3ms 0.7ms
 
占空比 = 高电平时间 / 周期
```

#### 实践任务
1. [ ] **配置 PWM 输出**
   ```cpp
   // TIM3 CH1 (PA6) PWM 配置
   void PWM_Init() {
       TIM_HandleTypeDef htim3;
       TIM_OC_InitTypeDef sConfigOC = {0};
       
       // 初始化 TIM3
       htim3.Instance = TIM3;
       htim3.Init.Prescaler = 84-1;      // 84MHz/84 = 1MHz
       htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
       htim3.Init.Period = 1000-1;       // 1MHz/1000 = 1kHz
       HAL_TIM_PWM_Init(&htim3);
       
       // 配置 PWM 通道
       sConfigOC.OCMode = TIM_OCMODE_PWM1;
       sConfigOC.Pulse = 500;            // 50% 占空比
       HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
       HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
   }
   ```

2. [ ] **使用示波器验证 PWM**
   - 连接 PA6 到示波器
   - 观察波形
   - 修改占空比，观察变化

#### 检查点
- [ ] 能解释 PWM 原理
- [ ] 知道如何配置定时器 PWM
- [ ] 能计算 PWM 频率和占空比

---

### Day 14: 调试技巧入门

#### 学习目标
- 掌握串口调试
- 学会使用 ST-Link 调试
- 了解断点和单步执行

#### 调试方法

**1. 串口打印调试**
```cpp
#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
  #define DEBUG_PRINT(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

void setup() {
  Serial.begin(115200);
  DEBUG_PRINT("System started");
}
```

**2. ST-Link 硬件调试**
```
ST-Link 连接:
├── SWDIO → PA13
├── SWCLK → PA14
├── GND   → GND
└── 3.3V  → 3.3V (可选)
```

#### 实践任务
1. [ ] **配置调试环境**
   ```ini
   # platformio.ini
   debug_tool = stlink
   debug_init_break = tbreak setup
   ```

2. [ ] **使用断点调试**
   - 在代码中设置断点（点击行号左侧）
   - 启动调试（F5）
   - 单步执行（F10/F11）
   - 查看变量值

3. [ ] **观察变量和寄存器**
   - 添加监视表达式
   - 查看 GPIO 寄存器状态
   - 查看定时器寄存器

#### 检查点
- [ ] 能使用串口打印调试信息
- [ ] 知道如何连接 ST-Link
- [ ] 能使用断点进行单步调试

---

## Phase 3: Marlin 框架 (Week 3)

### Day 15-17: Marlin 代码结构

#### 学习目标
- 理解 Marlin 整体架构
- 掌握核心模块功能
- 学会代码导航

#### Marlin 架构图
```
Marlin/
├── Marlin.ino              # 入口
├── src/
│   ├── core/               # 核心功能
│   │   ├── serial.cpp      # 串口通信
│   │   ├── utility.cpp     # 工具函数
│   │   └── types.h         # 类型定义
│   ├── gcode/              # G-code 解析
│   │   ├── gcode.cpp       # 主解析器
│   │   ├── queue.cpp       # 指令队列
│   │   └── gcode.d/        # 各 G-code 实现
│   ├── module/             # 功能模块
│   │   ├── motion.cpp      # 运动控制
│   │   ├── planner.cpp     # 路径规划
│   │   ├── stepper.cpp     # 步进控制
│   │   └── temperature.cpp # 温度控制
│   ├── lcd/                # 显示系统
│   │   ├── marlinui.cpp    # UI 核心
│   │   └── extui/          # 扩展 UI
│   │       └── mks_ui/     # MKS UI
│   └── HAL/                # 硬件抽象层
│       └── STM32/          # STM32 实现
```

#### 实践任务
1. [ ] **代码导航练习**
   - 从 `Marlin.ino` 开始，跟踪程序启动流程
   - 找到 `setup()` 和 `loop()` 函数
   - 跟踪一个 G-code 指令的处理流程

2. [ ] **阅读核心代码**
   - `src/module/stepper.cpp` - 理解步进中断
   - `src/module/planner.cpp` - 理解路径规划
   - `src/gcode/gcode.cpp` - 理解指令解析

3. [ ] **绘制流程图**
   - 画出 G1 指令的处理流程
   - 画出温度控制流程

#### 检查点
- [ ] 能说出 Marlin 的主要模块
- [ ] 能找到任意功能的实现代码
- [ ] 理解 G-code 处理流程

---

### Day 18-19: 配置文件详解

#### 学习目标
- 深入理解 Configuration.h
- 掌握 Configuration_adv.h
- 学会配置验证

#### Configuration.h 核心章节
```cpp
// 1. 基本信息
#define STRING_CONFIG_H_AUTHOR "(Your Name)"

// 2. 串口设置
#define SERIAL_PORT 3
#define BAUDRATE 115200

// 3. 主板选择
#define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3

// 4. 温度设置
#define TEMP_SENSOR_BED 1
#define HEATER_BED_PIN PA0

// 5. 运动设置
#define DEFAULT_AXIS_STEPS_PER_UNIT {80,80,400,400}
#define DEFAULT_MAX_FEEDRATE {300,300,5,50}

// 6. 步进驱动
#define X_DRIVER_TYPE TMC2209
#define X_CURRENT 800

// 7. LCD 设置
#define MKS_TS35_V2_0
#define TFT_LVGL_UI
```

#### 实践任务
1. [ ] **逐行阅读配置文件**
   - 阅读 Configuration.h 前 500 行
   - 每行添加注释说明

2. [ ] **修改配置并验证**
   - 修改 `BAUDRATE` 为 250000
   - 修改 `X_CURRENT` 为 600
   - 编译验证

3. [ ] **配置依赖关系**
   - 理解为什么修改 A 会影响 B
   - 例如：`TFT_LVGL_UI` 依赖 `MKS_TS35_V2_0`

#### 检查点
- [ ] 能解释每个主要配置项的作用
- [ ] 知道配置项之间的依赖关系
- [ ] 能独立修改配置并验证

---

### Day 20-21: 编译与烧录流程

#### 学习目标
- 掌握完整编译流程
- 学会多种烧录方式
- 理解固件更新机制

#### 烧录方式对比
| 方式 | 优点 | 缺点 | 适用场景 |
|-----|------|------|---------|
| SD 卡 | 简单，无需额外硬件 | 需要 SD 卡 | 日常更新 |
| ST-Link | 可靠，可调试 | 需要硬件 | 开发调试 |
| USB DFU | 直接通过 USB | 需要进入 DFU 模式 | 紧急恢复 |
| 串口 | 通用 | 速度慢 | 无其他方式时 |

#### MKS 固件更新流程
```
1. 编译生成 Robin_nano_v3.bin
2. 复制到 SD 卡根目录
3. 插入 SD 卡到主板
4. 上电，自动检测并更新
5. 等待更新完成，重启
```

#### 实践任务
1. [ ] **SD 卡更新**
   - 准备 FAT32 格式的 SD 卡
   - 复制固件到 SD 卡
   - 观察更新过程

2. [ ] **ST-Link 烧录**
   - 连接 ST-Link
   - 配置 platformio.ini
   - 使用 Upload 按钮烧录

3. [ ] **验证固件版本**
   - 连接串口
   - 发送 `M115` 命令
   - 查看版本信息

#### 检查点
- [ ] 能使用至少两种方式烧录固件
- [ ] 知道如何验证固件是否更新成功
- [ ] 理解 MKS 的 SD 卡更新机制

---

### Day 22-23: 第一次点亮主板

#### 学习目标
- 完成第一次硬件测试
- 验证基础功能
- 建立调试环境

#### 测试清单
```
基础功能测试:
├── 电源指示
├── 屏幕显示
├── 触摸响应
├── 蜂鸣器
├── SD 卡读取
└── 串口通信
```

#### 实践任务
1. [ ] **硬件连接**
   - 连接 12/24V 电源
   - 连接 USB 线到电脑
   - 连接屏幕

2. [ ] **上电测试**
   - 观察电源指示灯
   - 观察屏幕是否显示
   - 记录任何问题

3. [ ] **基础功能验证**
   - 触摸屏幕，观察响应
   - 插入 SD 卡，检查识别
   - 打开串口监视器，观察输出

4. [ ] **发送测试命令**
   ```gcode
   M115      ; 查看版本信息
   M119      ; 查看限位开关状态
   M122      ; 查看 TMC 驱动状态
   M140 S60  ; 设置床温 60°C
   ```

#### 检查点
- [ ] 主板能正常上电
- [ ] 屏幕能正常显示
- [ ] 能通过串口通信

---

## Phase 4-6: 后续阶段

后续阶段（MKS 生态、SLS 专项、项目实战）与之前计划类似，但增加了更多基础解释和练习。

详见完整计划文档...

---

## 🛠️ 开发环境检查清单

### 软件安装
- [ ] VSCode 安装完成
- [ ] PlatformIO IDE 扩展安装
- [ ] C/C++ 扩展安装
- [ ] Git 安装并配置
- [ ] STM32CubeProgrammer 安装（可选）

### 硬件准备
- [ ] MKS Robin Nano V3 主板
- [ ] MKS TS35 V2.0 屏幕
- [ ] ST-Link V2 调试器
- [ ] USB 转串口模块（如需要）
- [ ] 12/24V 电源

### 知识储备
- [ ] C/C++ 基础语法
- [ ] 基本的电子电路知识
- [ ] 3D 打印机工作原理

---

## 📚 推荐学习资源

### 官方文档
- [PlatformIO 文档](https://docs.platformio.org/)
- [Marlin 官方文档](https://marlinfw.org/)
- [STM32 HAL 库文档](https://www.st.com/)

### 视频教程
- PlatformIO 官方 YouTube 频道
- Marlin 配置教程（YouTube/B站）
- STM32 入门教程

### 社区论坛
- Marlin GitHub Issues
- PlatformIO Community
- RepRap Forums

---

## 💡 学习建议

1. **不要跳步** - 每个阶段都掌握后再进入下一阶段
2. **多动手** - 看十遍不如做一遍
3. **做好笔记** - 记录遇到的问题和解决方法
4. **善用搜索** - 遇到问题先搜索，再提问
5. **安全第一** - 通电操作注意安全

---

## 🆘 求助指南

遇到问题时的解决步骤：
1. 检查是否按照步骤操作
2. 查看错误信息，尝试理解
3. 搜索错误信息（Google/百度）
4. 查看官方文档
5. 询问 Claw (我)

---

## ✅ 阶段验收标准

### Phase 1 验收
- [ ] 能独立创建 PlatformIO 项目
- [ ] 能使用 Git 管理代码
- [ ] 能成功编译 Marlin

### Phase 2 验收
- [ ] 理解 STM32 架构
- [ ] 能使用 HAL 库编程
- [ ] 能使用调试工具

### Phase 3 验收
- [ ] 理解 Marlin 代码结构
- [ ] 能修改配置文件
- [ ] 能烧录并运行固件

---

**准备好开始了吗？我们从 Day 1 开始！**

— Claw (老师傅)
