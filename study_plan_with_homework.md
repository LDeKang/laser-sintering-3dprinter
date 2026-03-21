# SLS 3D 打印机固件开发 - 带作业完整学习路线

> **适用对象**: 零 PlatformIO/Marlin 经验，要求彻底掌握  
> **教学方式**: 师傅带徒弟，每阶段布置作业  
> **验收标准**: 作业完成并检查通过才能进入下一阶段  
> **预计周期**: 8-10 周（每天 2-3 小时）  
> **编写**: Claw (老师傅)  
> **日期**: 2026-03-21

---

## 📋 学习规则

1. **按顺序学习** - 不能跳阶段
2. **完成作业** - 每阶段作业必须完成
3. **师傅检查** - 作业完成后发给我检查
4. **验收通过** - 检查通过才能进入下一阶段
5. **做好笔记** - 记录学习心得和问题

---

## Phase 1: 工具链基础 (Week 1-2)

### Day 1: VSCode 基础操作

#### 理论学习（30分钟）
阅读 VSCode 官方入门文档：https://code.visualstudio.com/docs

#### 实践作业
**作业 1.1: 界面熟悉**
- [ ] 打开 VSCode，截图显示完整界面
- [ ] 标注出：活动栏、资源管理器、编辑器、终端、状态栏
- [ ] 提交截图给我

**作业 1.2: 快捷键练习**
完成以下操作各 10 次，记录用时：
- [ ] `Ctrl+P` 打开文件
- [ ] `Ctrl+Shift+F` 全局搜索
- [ ] `Ctrl+\`` 打开终端
- [ ] `Ctrl+Shift+P` 命令面板
- [ ] `Ctrl+/` 注释/取消注释

**作业 1.3: 安装扩展**
- [ ] 安装 PlatformIO IDE
- [ ] 安装 C/C++ 扩展
- [ ] 安装 GitLens
- [ ] 截图显示已安装的扩展列表

#### 验收标准
- [ ] 能熟练使用 5 个以上快捷键
- [ ] 能在 5 秒内打开任意文件
- [ ] 所有必需扩展安装完成

---

### Day 2: Git 版本控制入门

#### 理论学习（30分钟）
阅读 Git 基础：https://git-scm.com/book/zh/v2/起步-Git-基础

#### 实践作业
**作业 2.1: Git 配置**
```bash
# 在终端中执行，截图显示结果
git config --global user.name "你的名字"
git config --global user.email "你的邮箱"
git config --list
```
- [ ] 截图显示配置结果

**作业 2.2: 克隆仓库**
```bash
# 执行以下命令
cd D:\mySource\project\AI_Word
git clone https://github.com/LDeKang/laser-sintering-3dprinter.git test-clone
```
- [ ] 截图显示克隆成功
- [ ] 查看克隆下来的文件夹结构

**作业 2.3: 基础操作练习**
```bash
cd test-clone
# 1. 创建一个新文件
echo "Hello Git" > test.txt

# 2. 查看状态
git status

# 3. 添加到暂存区
git add test.txt

# 4. 提交更改
git commit -m "Add test file"

# 5. 查看提交历史
git log --oneline
```
- [ ] 截图显示每一步的结果

**作业 2.4: VSCode Git 图形界面**
- [ ] 修改 test.txt 文件内容
- [ ] 使用 VSCode 的源代码管理面板查看更改
- [ ] 使用图形界面提交更改
- [ ] 截图显示提交历史

#### 验收标准
- [ ] 能独立完成 clone/add/commit 操作
- [ ] 能解释工作区、暂存区、仓库的区别
- [ ] 能使用命令行和图形界面两种方式操作

---

### Day 3: PlatformIO 核心概念（上）

#### 理论学习（45分钟）
阅读 PlatformIO 文档：https://docs.platformio.org/en/latest/what-is-platformio.html

#### 实践作业
**作业 3.1: 创建第一个项目**
1. [ ] VSCode → PlatformIO 图标 → "Create New Project"
2. [ ] Name: `hello_pio`
3. [ ] Board: `Generic STM32F4 series`
4. [ ] Framework: `Arduino`
5. [ ] 等待项目创建完成（可能需要下载工具链，耐心等待）
6. [ ] 截图显示创建成功的项目结构

**作业 3.2: 认识项目结构**
在 `hello_pio` 文件夹中找到以下文件/文件夹，截图标注：
- [ ] `platformio.ini` - 项目配置文件
- [ ] `src/main.cpp` - 主程序
- [ ] `include/` - 头文件夹
- [ ] `lib/` - 库文件夹
- [ ] `.pio/` - PlatformIO 工作目录

**作业 3.3: 理解 platformio.ini**
打开 `platformio.ini`，逐行注释说明：
```ini
; 这是 PlatformIO 项目配置文件
[env:genericSTM32F407VET6]
; 使用的平台
platform = ststm32
; 使用的板子
board = genericSTM32F407VET6
; 使用的框架
framework = arduino
; 监控波特率
monitor_speed = 115200
```
- [ ] 提交带注释的 platformio.ini 文件

#### 验收标准
- [ ] 能独立创建 PlatformIO 项目
- [ ] 知道每个文件夹的作用
- [ ] 能解释 platformio.ini 的主要配置项

---

### Day 4: PlatformIO 核心概念（下）

#### 实践作业
**作业 4.1: 编写第一个程序**
修改 `src/main.cpp`：
```cpp
#include <Arduino.h>

// 定义 LED 引脚（PC13 是大多数 STM32 板子的内置 LED）
#define LED_PIN PC13

void setup() {
  // 初始化串口
  Serial.begin(115200);
  
  // 初始化 LED 引脚
  pinMode(LED_PIN, OUTPUT);
  
  // 打印启动信息
  Serial.println("================================");
  Serial.println("Hello PlatformIO!");
  Serial.println("My first embedded program");
  Serial.println("================================");
}

void loop() {
  // LED 闪烁
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(1000);
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(1000);
}
```
- [ ] 逐行注释代码，解释每个函数的作用
- [ ] 提交带注释的代码

**作业 4.2: 编译项目**
1. [ ] 点击底部工具栏的 ✅ Build（或按 `Ctrl+Alt+B`）
2. [ ] 观察编译输出，记录编译时间
3. [ ] 截图显示编译成功信息
4. [ ] 找到生成的 `.bin` 或 `.elf` 文件位置

**作业 4.3: 理解编译输出**
编译成功后，终端会显示类似：
```
RAM:   [==        ]  15.4% (used 20124 bytes from 131072 bytes)
Flash: [=====     ]  45.2% (used 237312 bytes from 524288 bytes)
```
- [ ] 解释 RAM 和 Flash 的含义
- [ ] 计算实际使用的字节数
- [ ] 计算剩余可用空间

#### 验收标准
- [ ] 能独立编写简单的 Arduino 程序
- [ ] 能成功编译项目
- [ ] 理解编译输出的含义

---

### Day 5: PlatformIO 工具使用（上）

#### 实践作业
**作业 5.1: 底部工具栏功能测试**
依次点击底部工具栏的每个按钮，记录功能：
- [ ] ✅ Build - 编译项目
- [ ] → Upload - 上传/烧录固件
- [ ] 🔌 Serial Monitor - 串口监视器
- [ ] 🗑️ Clean - 清理构建文件
- [ ] 🔍 Test - 运行测试
- [ ] 🐛 Debug - 启动调试

截图标注每个按钮的功能。

**作业 5.2: 串口监视器使用**
1. [ ] 连接你的 STM32 开发板到电脑（如果有）
2. [ ] 点击 🔌 Serial Monitor
3. [ ] 观察输出（如果板子已有程序）
4. [ ] 尝试发送一些字符
5. [ ] 截图显示串口监视器界面

如果没有开发板，先学习界面功能：
- [ ] 波特率设置位置
- [ ] 发送输入框
- [ ] 清除输出按钮

**作业 5.3: platformio.ini 高级配置**
修改 `platformio.ini`，添加以下内容：
```ini
[env:genericSTM32F407VET6]
platform = ststm32
board = genericSTM32F407VET6
framework = arduino

; 上传方式配置
upload_protocol = stlink
; upload_protocol = dfu
; upload_protocol = serial

; 监控波特率
monitor_speed = 115200

; 构建标志
build_flags = 
    -D DEBUG_MODE
    -D LED_PIN=PC13

; 库依赖
lib_deps = 
    ; 这里可以添加外部库
```
- [ ] 逐行注释说明每个配置项
- [ ] 解释 upload_protocol 的三种方式区别

#### 验收标准
- [ ] 熟悉所有工具栏按钮功能
- [ ] 能使用串口监视器
- [ ] 能配置 platformio.ini 的高级选项

---

### Day 6: PlatformIO 工具使用（下）

#### 实践作业
**作业 6.1: 库管理**
1. [ ] 打开 PlatformIO Home（点击左侧 PlatformIO 图标 → Open）
2. [ ] 进入 Libraries
3. [ ] 搜索 "Adafruit SSD1306"
4. [ ] 查看库详情页
5. [ ] 截图显示如何安装库

**作业 6.2: 添加库到项目**
在 `platformio.ini` 中添加：
```ini
lib_deps = 
    adafruit/Adafruit SSD1306 @ ^2.5.7
    adafruit/Adafruit GFX Library @ ^1.11.9
```
- [ ] 保存文件，观察 PlatformIO 自动下载库
- [ ] 截图显示 `.pio/libdeps/` 目录下的库文件

**作业 6.3: 平台切换练习**
创建两个环境，分别用于不同板子：
```ini
[env:stm32f4]
platform = ststm32
board = genericSTM32F407VET6
framework = arduino

[env:arduino_uno]
platform = atmelavr
board = uno
framework = arduino
```
- [ ] 尝试切换环境编译（点击底部环境选择器）
- [ ] 记录两个环境的编译结果差异

#### 验收标准
- [ ] 能搜索和安装 PlatformIO 库
- [ ] 能在项目中使用外部库
- [ ] 理解多环境配置

---

### Day 7: Phase 1 阶段考核

#### 考核作业
**作业 7.1: 综合项目**
创建一个完整的 PlatformIO 项目，要求：

1. [ ] 项目名：`phase1_test`
2. [ ] 板子：`Generic STM32F4 series`
3. [ ] 功能：实现一个计数器，每秒钟：
   - LED 闪烁一次
   - 串口打印当前计数（0, 1, 2, 3...）
   - 计数到 10 后归零

4. [ ] 代码要求：
   - 每行都有注释
   - 使用宏定义 LED 引脚
   - 使用 millis() 代替 delay()（学习非阻塞编程）

参考代码框架：
```cpp
#include <Arduino.h>

#define LED_PIN PC13

unsigned long previousMillis = 0;
const long interval = 1000;
int counter = 0;

void setup() {
  // 你的代码
}

void loop() {
  // 使用 millis() 实现非阻塞延时
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // 你的代码
  }
}
```

**作业 7.2: 项目文档**
编写 README.md，包含：
- [ ] 项目介绍
- [ ] 硬件要求
- [ ] 编译说明
- [ ] 运行效果描述

**作业 7.3: Git 提交**
- [ ] 初始化 Git 仓库
- [ ] 提交所有文件
- [ ] 推送到你的 GitHub（可选）

#### 验收标准
- [ ] 代码编译无错误
- [ ] 代码注释完整
- [ ] 使用 millis() 非阻塞编程
- [ ] 有完整的项目文档
- [ ] 使用 Git 管理代码

#### 提交方式
将以下内容发给我：
1. 项目代码（main.cpp）
2. platformio.ini
3. README.md
4. 编译成功截图
5. 学习心得（遇到的问题和解决方法）

**Phase 1 通过后才能进入 Phase 2**

---

## Phase 2: 嵌入式基础 (Week 3-4)

### Day 8-9: STM32 架构认知

#### 理论学习
阅读 STM32F407 Reference Manual：
- 第 1 章：介绍
- 第 2 章：存储器映射
- 第 3 章：电源控制

#### 作业
**作业 8.1: STM32F407 参数整理**
制作一个表格，包含：
| 参数 | 数值 | 说明 |
|-----|------|------|
| 核心 | Cortex-M4 | ARM 32位处理器 |
| 主频 | 168 MHz | 最高运行频率 |
| Flash | ? | 程序存储空间 |
| RAM | ? | 运行内存 |
| GPIO | ? | 通用IO数量 |
| ADC | ? | 模数转换器 |
| 定时器 | ? | 定时器数量 |

- [ ] 填写完整表格
- [ ] 解释每个参数的意义

**作业 8.2: 内存映射图**
根据参考手册，画出 STM32F407 的内存映射：
```
0x0000 0000 - 0x0000 0000: ?
0x0800 0000 - 0x0800 0000: ? (Flash)
0x2000 0000 - 0x2000 0000: ? (SRAM)
...
```
- [ ] 画出主要内存区域
- [ ] 标注每个区域的用途

**作业 8.3: GPIO 端口整理**
列出 STM32F407VET6 的所有 GPIO 端口：
- [ ] GPIOA (PA0-PA15)
- [ ] GPIOB (PB0-PB15)
- [ ] ...
- [ ] 标注特殊功能引脚（如调试接口）

#### 验收标准
- [ ] 掌握 STM32F407 核心参数
- [ ] 理解内存映射概念
- [ ] 熟悉 GPIO 端口分布

---

### Day 10-11: 硬件抽象层(HAL)理解

#### 理论学习
阅读 STM32 HAL 库文档：
- HAL 概述
- GPIO HAL 函数
- 时钟配置

#### 作业
**作业 10.1: HAL 函数整理**
整理常用的 HAL 函数：
| 函数 | 功能 | 参数说明 |
|-----|------|---------|
| HAL_GPIO_Init() | 初始化 GPIO | GPIO_TypeDef, GPIO_InitTypeDef |
| HAL_GPIO_WritePin() | 写 GPIO | ... |
| HAL_GPIO_ReadPin() | 读 GPIO | ... |
| HAL_Delay() | 延时 | ... |
| HAL_GetTick() | 获取 tick | ... |

- [ ] 每个函数都要有参数说明和示例

**作业 10.2: GPIO 初始化代码**
编写 GPIO 初始化代码，初始化 PA5 为输出：
```cpp
void GPIO_PA5_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  // 1. 使能 GPIOA 时钟
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  // 2. 配置 GPIO 参数
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  
  // 3. 初始化 GPIO
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
```
- [ ] 逐行注释
- [ ] 解释每个参数的选择原因

**作业 10.3: 时钟系统理解**
根据时钟树，计算：
- [ ] 如果 HSE = 8MHz，PLL 倍频后 SYSCLK = ?
- [ ] AHB 分频后 HCLK = ?
- [ ] APB1 分频后 PCLK1 = ?
- [ ] APB2 分频后 PCLK2 = ?

#### 验收标准
- [ ] 能使用 HAL 函数编程
- [ ] 理解 GPIO 初始化流程
- [ ] 理解时钟系统

---

### Day 12-13: PWM 与定时器

#### 作业
**作业 12.1: PWM 原理总结**
用自己的话解释：
- [ ] 什么是 PWM
- [ ] 频率和占空比的关系
- [ ] PWM 有哪些应用场景

**作业 12.2: PWM 配置代码**
编写 TIM3 CH1 (PA6) 的 PWM 配置：
```cpp
void PWM_Init(void) {
  TIM_HandleTypeDef htim3;
  TIM_OC_InitTypeDef sConfigOC = {0};
  
  // 1. 使能时钟
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  // 2. 配置 GPIO
  // ...
  
  // 3. 配置定时器
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = ?;      // 计算分频值
  htim3.Init.Period = ?;          // 计算周期值
  // ...
  
  // 4. 配置 PWM 通道
  // ...
  
  // 5. 启动 PWM
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}
```
- [ ] 计算产生 1kHz PWM 的参数
- [ ] 实现 0%、25%、50%、75%、100% 占空比切换

**作业 12.3: PWM 应用**
使用 PWM 实现 LED 呼吸灯效果：
- [ ] 占空比从 0% 渐变到 100%
- [ ] 再从 100% 渐变到 0%
- [ ] 循环往复

#### 验收标准
- [ ] 理解 PWM 原理
- [ ] 能配置定时器 PWM
- [ ] 能实现呼吸灯效果

---

### Day 14: Phase 2 阶段考核

#### 考核作业
**综合项目：多功能控制器**

实现一个基于 STM32 的多功能控制器：

功能要求：
1. [ ] LED 控制
   - 按键 1：切换 LED 模式（闪烁/呼吸灯/常亮）
   - 每种模式用不同频率

2. [ ] PWM 输出
   - PA6 输出可调 PWM
   - 按键 2：增加占空比
   - 按键 3：减少占空比

3. [ ] 串口交互
   - 发送 's'：显示当前状态
   - 发送 '1'/'2'/'3'：模拟按键功能

代码要求：
- [ ] 使用 HAL 库
- [ ] 模块化设计（每个功能独立函数）
- [ ] 非阻塞编程（使用 millis()）
- [ ] 完整注释

提交内容：
1. 完整代码
2. 电路连接图（按键、LED 连接方式）
3. 使用说明
4. 演示视频（如果有硬件）或详细运行说明

**Phase 2 通过后才能进入 Phase 3**

---

## Phase 3: Marlin 框架 (Week 5-6)

### Day 15-17: Marlin 代码结构

#### 作业
**作业 15.1: 代码导航练习**
从 `Marlin.ino` 开始，跟踪以下流程：
- [ ] 程序启动流程（setup()）
- [ ] 主循环流程（loop()）
- [ ] 记录每个重要函数调用

**作业 15.2: G-code 流程图**
跟踪 `G1 X10 Y20 F1500` 的处理流程：
- [ ] 从串口接收
- [ ] 解析 G-code
- [ ] 路径规划
- [ ] 步进执行
- [ ] 画出完整流程图

**作业 15.3: 模块功能整理**
整理 Marlin 核心模块：
| 模块 | 文件 | 功能 | 关键函数 |
|-----|------|------|---------|
| 运动控制 | motion.cpp | 执行运动指令 | do_blocking_move_to |
| 路径规划 | planner.cpp | 计算运动轨迹 | buffer_line |
| 步进控制 | stepper.cpp | 产生步进脉冲 | isr |
| 温度控制 | temperature.cpp | 控制温度 | manage_heater |

- [ ] 每个模块阅读源码，理解原理
- [ ] 记录关键函数和数据结构

#### 验收标准
- [ ] 理解 Marlin 启动流程
- [ ] 能跟踪 G-code 处理流程
- [ ] 熟悉核心模块功能

---

### Day 18-19: 配置文件详解

#### 作业
**作业 18.1: 配置项分类整理**
将 `Configuration.h` 的配置项分类：
- [ ] 基本信息类
- [ ] 硬件配置类
- [ ] 运动参数类
- [ ] 温度控制类
- [ ] 显示配置类
- [ ] 安全保护类

**作业 18.2: 关键配置实验**
修改以下配置，观察编译结果变化：
- [ ] 修改 `BAUDRATE`（115200 → 250000）
- [ ] 修改 `DEFAULT_AXIS_STEPS_PER_UNIT`
- [ ] 启用/禁用 `TFT_LVGL_UI`
- [ ] 记录每次修改后的 Flash/RAM 占用

**作业 18.3: 配置依赖关系图**
画出以下配置的依赖关系：
```
TFT_LVGL_UI
    ↓ 依赖
MKS_TS35_V2_0
    ↓ 依赖
SDSUPPORT
```
- [ ] 找出 10 个有依赖关系的配置项

#### 验收标准
- [ ] 能分类整理配置项
- [ ] 理解配置项之间的依赖
- [ ] 能根据需求修改配置

---

### Day 20-21: 编译与烧录

#### 作业
**作业 20.1: Marlin 编译**
1. [ ] 克隆 Marlin 2.1.2.1
2. [ ] 配置 `platformio.ini`
3. [ ] 复制我们的 MKS SLS 配置
4. [ ] 编译并记录：
   - 编译时间
   - Flash 占用
   - RAM 占用
   - 警告信息数量

**作业 20.2: 烧录方式对比**
研究三种烧录方式：
| 方式 | 优点 | 缺点 | 适用场景 |
|-----|------|------|---------|
| SD 卡 | | | |
| ST-Link | | | |
| USB DFU | | | |

- [ ] 尝试至少一种方式（如果有硬件）

**作业 20.3: 编译错误排查**
故意制造 5 个编译错误，记录：
- [ ] 错误信息
- [ ] 错误原因
- [ ] 解决方法

#### 验收标准
- [ ] 能成功编译 Marlin
- [ ] 了解多种烧录方式
- [ ] 能排查常见编译错误

---

### Day 22-23: Phase 3 阶段考核

#### 考核作业
**Marlin 配置项目**

任务：为 MKS Robin Nano V3 配置一个完整的 Marlin 固件

要求：
1. [ ] 基础配置
   - 正确的板子选择
   - 正确的串口配置
   - TMC2209 驱动配置

2. [ ] 屏幕配置
   - MKS TS35 V2.0
   - TFT LVGL UI
   - 中文语言

3. [ ] 功能配置
   - 激光功能（模拟配置）
   - WiFi 模块
   - SD 卡支持

4. [ ] 编译验证
   - 编译无错误
   - 记录资源占用
   - 生成可用的 .bin 文件

提交内容：
1. 完整的 Configuration.h
2. 完整的 Configuration_adv.h
3. platformio.ini
4. 编译成功截图
5. 配置说明文档（每个关键配置的解释）

**Phase 3 通过后才能进入 Phase 4**

---

## Phase 4-6: 后续阶段

后续阶段（MKS 生态、SLS 专项、项目实战）将在前面阶段通过后再详细规划。

每个阶段都会有：
- 详细的理论学习
- 具体的实践作业
- 严格的阶段考核

---

## 📋 作业提交规范

### 提交格式
```
【Day X 作业提交】

1. 完成的作业列表：
   - [x] 作业 X.1
   - [x] 作业 X.2
   - [ ] 作业 X.3（未完成原因）

2. 代码/文件：
   - 见附件或直接粘贴

3. 截图：
   - [截图1说明]
   - [截图2说明]

4. 遇到的问题：
   - 问题1：...
   - 解决方法：...

5. 学习心得：
   - 今天学到了什么
   - 有什么疑问
```

### 提交方式
- 直接发给我（Claw）
- 或者提交到 GitHub，发链接给我

### 检查反馈
我会在 24 小时内：
1. 检查作业完成情况
2. 指出问题和改进建议
3. 确认是否通过
4. 给出下一阶段指导

---

## ✅ 总体验收标准

### Phase 1 通过标准
- [ ] 熟练使用 VSCode 和 Git
- [ ] 能独立创建 PlatformIO 项目
- [ ] 能编写、编译简单的嵌入式程序
- [ ] 代码规范，注释完整

### Phase 2 通过标准
- [ ] 理解 STM32 架构
- [ ] 能使用 HAL 库编程
- [ ] 能实现 GPIO、PWM、定时器功能
- [ ] 掌握调试技巧

### Phase 3 通过标准
- [ ] 理解 Marlin 代码结构
- [ ] 能独立配置 Marlin
- [ ] 能编译生成可用固件
- [ ] 能排查配置问题

---

**准备好了吗？从 Day 1 开始！**

**记住：不完成作业不能进入下一阶段，这是为你好。**

— Claw (老师傅)
