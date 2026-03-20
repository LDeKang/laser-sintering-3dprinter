# SLS 3D打印机项目 - 工程分析报告

**分析时间**: 2026-03-20  
**分析人**: Claw (嵌入式工程师)  
**项目**: laser-sintering-3dprinter  
**GitHub**: https://github.com/LDeKang/laser-sintering-3dprinter

---

## 一、项目演进历史

### 版本迭代

```
2026-03-14  36293c9  Initial project: Marlin config for Laser Sintering (SKR Mini E3 V3.0)
                 └─→ 最初方案: SKR Mini E3 V3.0 + 10W激光

2026-03-15  e70cc6c  Update to SLM metal printer project - mechanical XY scheme  
                 └─→ 升级为SLM金属打印方案
                 └─→ 200W光纤激光 + 316L不锈钢
                 └─→ 预算¥15000

2026-03-15  e66f2c8  Add detailed design spec and BOM v1.0
                 └─→ 添加详细设计规格书和BOM清单

2026-03-15  96d9af8  Add MiniClaw DNA chromosome system for project memory management
                 └─→ 添加项目记忆管理系统

2026-03-20  4c3ffab  Update: SLS Nylon printer project with MKS Robin Nano V3.1
                 └─→ 方案变更: SLS尼龙打印
                 └─→ 主板更换为MKS Robin Nano V3.1
                 └─→ 激光改为40W半导体激光

2026-03-20  eb66479  Add SLS Marlin firmware config for MKS Robin Nano V3.1
                 └─→ 添加Marlin固件配置
                 └─→ 激光PWM配置
                 └─→ TMC2209 UART配置
```

### 方案演变

| 阶段 | 技术路线 | 主板 | 激光 | 材料 | 预算 |
|------|---------|------|------|------|------|
| v0.1 | SLS基础 | SKR Mini E3 V3.0 | 10W | 尼龙 | - |
| v1.0 | SLM金属 | SKR Mini E3 V3.0 | 200W光纤 | 316L不锈钢 | ¥15000 |
| v2.0 | SLS尼龙 | **MKS Robin Nano V3.1** | **40W半导体** | **PA12/PA6** | 待评估 |

**关键决策**: 从SLM金属退回SLS尼龙，原因可能是成本和复杂度。

---

## 二、目录结构分析

```
laser-sintering-3dprinter/
├── README.md                    # 项目总览 (已更新为SLS方案)
├── LICENSE                      # 开源协议
├── 
├── cad/                         # CAD设计文件 (空)
│   └── (待添加机械设计)
│
├── docs/                        # 文档目录
│   ├── architecture.md          # [新增] 系统架构分析
│   ├── assembly/                # 装配指南 (待创建)
│   ├── operation/               # 操作手册 (待创建)
│   └── calibration/             # 校准指南 (待创建)
│
├── firmware/                    # 固件目录 [核心]
│   ├── marlin-config/           # [新增] SLS专用配置
│   │   ├── Configuration.h      # Marlin主配置
│   │   ├── Configuration_adv.h  # Marlin高级配置
│   │   └── README.md            # 配置说明
│   │
│   ├── Marlin-2.1.2.1-src/      # Marlin源码 (完整)
│   │   ├── Marlin/
│   │   │   ├── Configuration.h  # 默认配置
│   │   │   ├── Configuration_adv.h
│   │   │   └── src/             # 源码目录
│   │   │       ├── HAL/         # 硬件抽象层
│   │   │       ├── gcode/       # G-code解析
│   │   │       ├── lcd/         # 显示驱动
│   │   │       ├── module/      # 功能模块
│   │   │       └── feature/     # 特性实现
│   │   └── platformio.ini       # 编译配置
│   │
│   └── config/                  # 旧配置备份
│
├── gcode/                       # G-code脚本 (待创建)
│   └── (切片配置、测试脚本)
│
├── hardware/                    # 硬件资料 (待完善)
│   ├── schematic/               # 原理图
│   ├── bom/                     # 采购清单
│   └── drawings/                # 工程图纸
│
└── tests/                       # 测试记录 (待创建)
    └── (测试数据、问题记录)
```

---

## 三、技术栈分析

### 1. 硬件层

| 组件 | 型号 | 关键参数 | 用途 |
|------|------|----------|------|
| MCU | STM32F407VET6 | 168MHz, Cortex-M4F | 主控制器 |
| 驱动 | TMC2209 x5 | 2A RMS, UART模式 | XYZ+E步进 |
| 屏幕 | MKS TS35 V2.0 | 3.5寸 TFT, 480x320 | 本地UI |
| WiFi | ESP8266/ESP32 | 串口透传 | 无线控制 |
| 激光 | 40W 450nm | PWM控制 | 烧结光源 |

### 2. 软件层

```
┌─────────────────────────────────────────┐
│  应用层: G-code / 触摸屏UI / WiFi接口    │
├─────────────────────────────────────────┤
│  系统层: Marlin 2.1.2.1                 │
│  ├── G-code解析器 (parser.cpp)          │
│  ├── 运动规划 (planner.cpp)             │
│  ├── 步进控制 (stepper.cpp)             │
│  ├── 激光控制 (cutter.cpp)              │
│  └── 温度控制 (temperature.cpp)         │
├─────────────────────────────────────────┤
│  HAL层: STM32F4 Arduino Core            │
│  ├── GPIO (digitalWrite/Read)           │
│  ├── PWM (analogWrite)                  │
│  ├── UART (Serial)                      │
│  └── SPI (SD卡/屏幕)                    │
├─────────────────────────────────────────┤
│  底层: STM32 HAL库 (ST官方)             │
│  ├── stm32f4xx_hal_gpio.c               │
│  ├── stm32f4xx_hal_tim.c                │
│  └── stm32f4xx_hal_uart.c               │
└─────────────────────────────────────────┘
```

### 3. 开发工具链

| 工具 | 用途 | 版本 |
|------|------|------|
| PlatformIO | 编译/烧录 | Core 6.x |
| VSCode | 代码编辑 | - |
| Git | 版本控制 | - |
| ST-Link | 调试器 | V2/V3 |

---

## 四、核心代码分析

### 1. Marlin配置关键项

**Configuration.h**:
```cpp
// 主板选择
#define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3_1  // ID: 5229

// 激光功能
#define LASER_FEATURE                          // 启用激光控制
#define SPINDLE_LASER_PWM_PIN PC6              // PWM输出引脚
#define SPINDLE_LASER_FREQUENCY 1000           // 1kHz PWM

// 步进驱动
#define X_DRIVER_TYPE TMC2209                  // UART模式
#define X_CURRENT 800                          // 800mA电流
```

**关键问题**: `PC6`引脚是否正确？需要查MKS Robin Nano V3.1原理图确认。

### 2. 激光控制流程

```
用户发送: M3 S128
    ↓
G-code解析: parser.parse()
    ↓
调用: gcode_M3()
    ↓
设置功率: cutter.set_power(128)
    ↓
HAL层: analogWrite(PC6, 128)
    ↓
寄存器: TIM3->CCR1 = 128
    ↓
硬件: PC6输出PWM波形
```

### 3. TMC2209 UART通信

```cpp
// UART单线模式 (SW_UART)
#define X_SERIAL_TX_PIN PA9
#define X_SERIAL_RX_PIN PA9   // 同一引脚

// 通信流程
Marlin → UART → TMC2209
  - 设置电流: rms_current(800)
  - 设置微步: microsteps(16)
  - 读取状态: DRV_STATUS()
```

---

## 五、当前状态评估

### 已完成 ✅

1. **项目文档**
   - README.md (项目总览)
   - architecture.md (架构分析)
   - 固件配置文档

2. **固件配置**
   - Marlin基础配置
   - 激光功能配置
   - TMC2209配置

3. **版本管理**
   - Git仓库初始化
   - 6次提交记录

### 待完成 ⏳

1. **硬件验证**
   - [ ] 激光PWM引脚确认
   - [ ] 步进电机接线图
   - [ ] 限位开关配置
   - [ ] 温度传感器类型

2. **固件开发**
   - [ ] 编译测试
   - [ ] 烧录验证
   - [ ] 功能测试 (激光/步进/屏幕)

3. **机械设计**
   - [ ] 框架结构
   - [ ] 铺粉机构
   - [ ] 激光光路

4. **工艺开发**
   - [ ] 切片参数
   - [ ] 烧结工艺
   - [ ] 测试模型

---

## 六、学习路径建议

### 阶段1: 理解架构 (1-2天)
1. 阅读 `docs/architecture.md`
2. 理解Marlin三层架构
3. 熟悉STM32 HAL库概念

### 阶段2: 硬件基础 (2-3天)
1. 跑通Blink程序
2. 测试PWM输出
3. 控制步进电机
4. 读取TMC2209状态

### 阶段3: Marlin深入 (3-5天)
1. 阅读Marlin源码结构
2. 理解G-code解析流程
3. 跟踪激光控制代码
4. 修改配置并编译

### 阶段4: 系统集成 (持续)
1. 硬件接线
2. 固件烧录
3. 功能调试
4. 工艺优化

---

## 七、关键学习资源

### 代码阅读顺序

```
1. Marlin/Configuration.h          ← 从这里开始
2. Marlin/src/MarlinCore.cpp       ← 主循环
3. Marlin/src/gcode/gcode.cpp      ← G-code入口
4. Marlin/src/feature/cutter.cpp   ← 激光控制
5. Marlin/src/module/stepper.cpp   ← 步进控制
6. Marlin/src/HAL/STM32/*.cpp      ← HAL实现
```

### 文档资源

- [Marlin官方文档](https://marlinfw.org/)
- [STM32F4 HAL手册](https://www.st.com/resource/en/user_manual/dm00105879.pdf)
- [TMC2209 datasheet](https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC2209_Datasheet_V103.pdf)

---

## 八、风险评估

| 风险 | 概率 | 影响 | 应对 |
|------|------|------|------|
| 激光引脚错误 | 中 | 高 | 查原理图确认 |
| TMC2209通信失败 | 中 | 中 | 检查UART接线 |
| 屏幕不显示 | 低 | 中 | 检查SPI接线 |
| 编译失败 | 低 | 低 | PlatformIO环境 |
| 烧结效果差 | 高 | 高 | 大量工艺实验 |

---

**总结**: 项目已完成基础配置，处于"等待硬件验证"阶段。核心学习价值在于理解Marlin架构和STM32开发流程。

**下一步**: 等板子到了，按`docs/architecture.md`中的测试程序逐个验证。
