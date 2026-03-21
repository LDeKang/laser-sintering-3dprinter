# SLS 3D 打印机固件开发 - 学徒学习计划

> **适用对象**: 项目老板/技术负责人  
> **目标**: 彻底掌握 MKS Robin Nano V3 + Marlin 2.1.2.1 固件开发  
> **预计周期**: 4-6 周（每天 2-3 小时）  
> **编写**: Claw (AI 助手)  
> **日期**: 2026-03-21

---

## 📚 学习路线图

```
Week 1: 基础认知
├── Day 1-2: 硬件架构理解
├── Day 3-4: Marlin 固件结构
└── Day 5-7: 开发环境搭建

Week 2: 核心代码
├── Day 8-10: 引脚与硬件抽象层
├── Day 11-13: 步进电机控制
└── Day 14: 温度控制系统

Week 3: MKS 生态
├── Day 15-17: MKS LVGL UI 系统
├── Day 18-20: 屏幕与触摸驱动
└── Day 21: WiFi 模块集成

Week 4: SLS 专项
├── Day 22-24: 激光控制系统
├── Day 25-27: 铺料机构控制
└── Day 28: 安全系统与联锁

Week 5-6: 实战项目
├── 移植验证
├── 功能调试
└── 性能优化
```

---

## Week 1: 基础认知

### Day 1-2: 硬件架构理解

#### 学习目标
- 理解 MKS Robin Nano V3 硬件设计
- 掌握 STM32F407 核心资源
- 熟悉主板引脚分配

#### 学习资料
```
docs/
├── hardware/
│   ├── MKS_Robin_Nano_V3_Pinout.pdf (需下载)
│   └── STM32F407_Reference_Manual.pdf (需下载)
└── schematic/
    └── MKS_Robin_Nano_V3_Schematic.pdf (需下载)
```

#### 实践任务
1. [ ] 打印 MKS Robin Nano V3 引脚图，标注每个引脚功能
2. [ ] 对照原理图，找到以下模块的物理位置：
   - 5 个步进驱动插座
   - 3 个温度传感器接口
   - 2 个加热输出
   - TFT 屏幕接口
   - WiFi 模块接口
3. [ ] 制作引脚功能对照表

#### 检查点
- [ ] 能不看资料说出 X/Y/Z/E0/E1 步进引脚
- [ ] 知道 TMC2209 UART 通信使用的引脚
- [ ] 理解为什么激光 PWM 要避开某些引脚

---

### Day 3-4: Marlin 固件结构

#### 学习目标
- 理解 Marlin 代码组织架构
- 掌握配置文件的作用
- 了解编译构建流程

#### 核心目录结构
```
Marlin/
├── Marlin/
│   ├── src/
│   │   ├── HAL/           # 硬件抽象层
│   │   ├── core/          # 核心功能
│   │   ├── feature/       # 可选功能
│   │   ├── gcode/         # G-code 解析
│   │   ├── lcd/           # 显示系统
│   │   │   └── extui/
│   │   │       └── mks_ui/    # MKS UI
│   │   ├── module/        # 功能模块
│   │   │   ├── motion.cpp     # 运动控制
│   │   │   ├── planner.cpp    # 路径规划
│   │   │   ├── stepper.cpp    # 步进控制
│   │   │   └── temperature.cpp # 温度控制
│   │   └── pins/          # 引脚定义
│   ├── Configuration.h    # 主配置
│   └── Configuration_adv.h # 高级配置
└── platformio.ini         # 构建配置
```

#### 实践任务
1. [ ] 逐行阅读 `Configuration.h` 前 200 行，注释每个宏定义
2. [ ] 找到并阅读以下文件：
   - `src/module/stepper.cpp` - 理解步进电机如何驱动
   - `src/module/motion.cpp` - 理解 G-code 如何转化为运动
   - `src/gcode/gcode.cpp` - 理解 G-code 解析流程
3. [ ] 画出 Marlin 启动流程图

#### 检查点
- [ ] 能解释 `#define MOTHERBOARD` 的作用
- [ ] 知道 `Configuration.h` 和 `Configuration_adv.h` 的区别
- [ ] 理解 `platformio.ini` 中的 `default_envs`

---

### Day 5-7: 开发环境搭建

#### 学习目标
- 搭建完整的编译环境
- 掌握 PlatformIO 使用
- 完成第一次固件编译

#### 环境需求
```
软件清单:
├── VSCode
├── PlatformIO IDE 插件
├── Git
├── Python 3.8+
└── STM32CubeProgrammer (备用烧录)
```

#### 实践任务
1. [ ] 安装 VSCode + PlatformIO
2. [ ] 克隆 Marlin 2.1.2.1 仓库
3. [ ] 配置 `platformio.ini`：
   ```ini
   default_envs = mks_robin_nano_v3_usb_flash_drive
   ```
4. [ ] 复制我们的配置文件：
   ```bash
   cp firmware/marlin-config/Configuration_MKS_SLS.h Marlin/Configuration.h
   cp firmware/marlin-config/Configuration_adv_MKS_SLS.h Marlin/Configuration_adv.h
   ```
5. [ ] 执行编译：
   ```bash
   pio run -e mks_robin_nano_v3_usb_flash_drive
   ```

#### 常见问题排查
| 问题 | 解决方案 |
|-----|---------|
| 编译失败，找不到头文件 | 检查 `platformio.ini` 的 `include_dir` |
| 链接错误 | 清理 `.pio/build` 目录重新编译 |
| 内存不足 | 禁用不需要的功能 |

#### 检查点
- [ ] 能独立完成编译，生成 `.bin` 文件
- [ ] 理解编译错误信息
- [ ] 知道如何清理构建缓存

---

## Week 2: 核心代码

### Day 8-10: 引脚与硬件抽象层 (HAL)

#### 学习目标
- 理解 HAL 的作用
- 掌握引脚定义文件结构
- 学会添加自定义引脚

#### 核心文件
```
src/pins/stm32f4/
├── pins_MKS_ROBIN_NANO_V3.h          # V3 主定义
├── pins_MKS_ROBIN_NANO_V3_common.h   # V3 通用定义
└── pins_MKS_ROBIN_NANO_V1_3_F4.h     # V1.3 定义
```

#### 引脚定义示例解析
```cpp
// 步进电机引脚定义
#define X_STEP_PIN         PE3    // X轴步进脉冲
#define X_DIR_PIN          PE2    // X轴方向
#define X_ENABLE_PIN       PE4    // X轴使能（低电平有效）

// TMC2209 UART 通信
#define X_SERIAL_TX_PIN    PD5    // UART 发送
#define X_SERIAL_RX_PIN    X_SERIAL_TX_PIN  // 单线半双工
```

#### 实践任务
1. [ ] 逐行阅读 `pins_MKS_ROBIN_NANO_V3_common.h`
2. [ ] 制作引脚功能表（Excel），包含：
   - 引脚号
   - 功能名称
   - 对应 STM32 端口
   - 是否 PWM  capable
   - 备注
3. [ ] 修改引脚定义，添加激光控制引脚

#### 检查点
- [ ] 能解释 `#ifndef` 保护的作用
- [ ] 知道如何查找 STM32 引脚的 PWM 功能
- [ ] 理解 UART 单线半双工模式

---

### Day 11-13: 步进电机控制

#### 学习目标
- 理解步进电机控制原理
- 掌握 TMC2209 驱动配置
- 学会 UART 通信调试

#### 核心概念
```
步进控制链:
G-code (G1 X10) 
    ↓
G-code Parser (gcode.cpp)
    ↓
Planner (planner.cpp) - 路径规划、加速度计算
    ↓
Stepper ISR (stepper.cpp) - 中断服务程序，产生脉冲
    ↓
GPIO 输出 → 步进驱动器 → 电机转动
```

#### TMC2209 UART 配置
```cpp
// 电流设置
#define X_CURRENT       800    // mA
#define X_CURRENT_HOME  400    // 归零时电流

// 微步进设置
#define X_MICROSTEPS    16     // 16微步

// 静音模式
#define STEALTHCHOP_XY  // X/Y轴启用静音模式
```

#### 实践任务
1. [ ] 阅读 `src/module/stepper.cpp`，理解脉冲产生机制
2. [ ] 学习 TMC2209 数据手册（重点：UART 协议）
3. [ ] 使用串口助手测试 TMC2209 通信
4. [ ] 修改电流参数，观察电机声音变化

#### 调试技巧
```cpp
// 启用 TMC 调试信息
#define TMC_DEBUG
#define MONITOR_DRIVER_STATUS
```

连接串口后发送 `M122` 查看驱动状态。

#### 检查点
- [ ] 能解释 `DEFAULT_AXIS_STEPS_PER_UNIT` 的计算方法
- [ ] 知道如何读取 TMC2209 的 `SG_RESULT`（堵转检测）
- [ ] 理解 `HYBRID_THRESHOLD` 的作用

---

### Day 14: 温度控制系统

#### 学习目标
- 理解 PID 控制原理
- 掌握温度传感器类型
- 学会 PID 参数整定

#### 核心代码
```cpp
// src/module/temperature.cpp
// 温度控制 ISR，每 100ms 执行一次

// PID 参数
#define DEFAULT_Kp 22.2
#define DEFAULT_Ki 1.08
#define DEFAULT_Kd 114
```

#### SLS 特殊需求
```cpp
// 加热腔体（尼龙烧结需要 160-180°C）
#define HEATER_CHAMBER_PIN PA1
#define TEMP_SENSOR_CHAMBER 1
#define CHAMBER_MAXTEMP 180
```

#### 实践任务
1. [ ] 阅读 `temperature.cpp`，理解 PID 控制流程
2. [ ] 使用 `M303` 命令自动整定 PID 参数
3. [ ] 绘制温度响应曲线

#### 检查点
- [ ] 能解释 PID 三个参数的作用
- [ ] 知道如何读取温度传感器原始值
- [ ] 理解热失控保护机制

---

## Week 3: MKS 生态

### Day 15-17: MKS LVGL UI 系统

#### 学习目标
- 理解 LVGL 图形库
- 掌握 MKS UI 架构
- 学会修改 UI 界面

#### 核心目录
```
src/lcd/extui/mks_ui/
├── draw_ui.cpp/h          # UI 主框架
├── draw_*.cpp/h           # 各界面实现
│   ├── draw_home.cpp      # 主界面
│   ├── draw_printing.cpp  # 打印界面
│   ├── draw_set.cpp       # 设置界面
│   └── ...
├── tft_lvgl_configuration.cpp  # LVGL 配置
├── pic_manager.cpp        # 图片管理
└── wifi_module.cpp        # WiFi 模块
```

#### LVGL 基础
```cpp
// 创建按钮
lv_obj_t *btn = lv_btn_create(parent);
lv_obj_set_pos(btn, x, y);
lv_obj_set_size(btn, w, h);

// 设置事件回调
lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
```

#### 实践任务
1. [ ] 阅读 `draw_ui.cpp`，理解 UI 初始化流程
2. [ ] 修改 `draw_home.cpp`，添加自定义按钮
3. [ ] 学习使用 LVGL 在线图片转换工具
4. [ ] 替换一张 UI 图片资源

#### 检查点
- [ ] 能解释 `lv_obj_t` 是什么
- [ ] 知道如何添加新的 UI 界面
- [ ] 理解 `assets` 文件夹的作用

---

### Day 18-20: 屏幕与触摸驱动

#### 学习目标
- 理解 TFT 屏幕接口
- 掌握触摸校准
- 学会调试显示问题

#### 核心配置
```cpp
// 屏幕型号
#define MKS_TS35_V2_0

// 触摸校准参数
#define TOUCH_CALIBRATION_X -17253
#define TOUCH_CALIBRATION_Y 11579
#define TOUCH_OFFSET_X 514
#define TOUCH_OFFSET_Y -24
```

#### 实践任务
1. [ ] 阅读 `src/HAL/STM32/tft/` 目录下的驱动代码
2. [ ] 执行触摸校准程序
3. [ ] 修改屏幕旋转方向
4. [ ] 调整背光亮度控制

#### 检查点
- [ ] 能解释 SPI 和 FSMC 接口的区别
- [ ] 知道如何进行触摸校准
- [ ] 理解 `TFT_BUFFER_SIZE` 的作用

---

### Day 21: WiFi 模块集成

#### 学习目标
- 理解 MKS WiFi 模块协议
- 掌握网络配置
- 学会远程控制

#### 核心代码
```cpp
// WiFi 模块串口配置
#define WIFI_SERIAL 3
#define MKS_WIFI_MODULE_SERIAL 1

// ESP8266/ESP32 通信协议
// 参考: Marlin/src/lcd/extui/mks_ui/wifi_module.cpp
```

#### 实践任务
1. [ ] 配置 WiFi 模块连接路由器
2. [ ] 使用 MKS WiFi APP 连接打印机
3. [ ] 测试远程文件传输

#### 检查点
- [ ] 能解释 WiFi 模块的 AT 指令
- [ ] 知道如何更新 WiFi 模块固件
- [ ] 理解 ESP3D 协议

---

## Week 4: SLS 专项

### Day 22-24: 激光控制系统

#### 学习目标
- 理解激光 PWM 控制
- 掌握激光安全机制
- 学会激光功率标定

#### 核心配置
```cpp
// 激光功能启用
#define LASER_FEATURE

// PWM 引脚配置
#define SPINDLE_LASER_PWM_PIN PA6    // TIM3_CH1
#define SPINDLE_LASER_FREQUENCY 1000 // 1kHz

// 激光使能
#define SPINDLE_LASER_ENA_PIN PA7

// 安全超时
#define LASER_SAFETY_TIMEOUT_MS 1000
```

#### 激光控制 G-code
```
M3 S128      ; 激光开启，功率 50% (0-255)
M5           ; 激光关闭
M3 I         ; 激光立即模式（无延迟）
```

#### 实践任务
1. [ ] 阅读 `src/feature/spindle_laser.cpp`
2. [ ] 使用示波器测量 PWM 波形
3. [ ] 标定激光功率曲线（S值 vs 实际功率）
4. [ ] 测试激光安全超时功能

#### 安全要点
```cpp
// 必须实现的安全功能
#define SLS_SAFETY_DOOR_PIN PB0   // 门开关
#define SLS_ESTOP_PIN PB1         // 急停

// 激光冷却风扇
#define LASER_COOLING_FAN_PIN PC14
```

#### 检查点
- [ ] 能解释 PWM 频率对激光控制的影响
- [ ] 知道如何测试激光功率
- [ ] 理解激光安全联锁逻辑

---

### Day 25-27: 铺料机构控制

#### 学习目标
- 理解铺料系统机械结构
- 掌握 E 轴改造为铺料电机
- 学会铺料流程编程

#### 核心概念
```
铺料流程:
1. Z 轴下降一层厚度
2. E 轴（铺料电机）前进，推出粉末
3. 刮板平整粉末层
4. 激光扫描烧结
5. 重复
```

#### 配置修改
```cpp
// E0 改为铺料电机
#define E0_DRIVER_TYPE TMC2209
#define E0_CURRENT 600

// 铺料步数校准
#define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400, 400 }
// X, Y, Z, E0 (铺料)
```

#### 铺料 G-code 脚本
```gcode
; 铺料子程序
G91          ; 相对坐标
G1 Z0.1      ; Z 下降 0.1mm
G1 E10 F1000 ; 铺料电机推出粉末
G90          ; 绝对坐标
```

#### 实践任务
1. [ ] 修改配置，禁用热端温度检查
2. [ ] 编写铺料测试程序
3. [ ] 调试铺料量与 E 轴步数关系
4. [ ] 优化铺料速度曲线

#### 检查点
- [ ] 能解释为什么禁用 `EXTRUDERS`
- [ ] 知道如何校准铺料量
- [ ] 理解铺料速度与粉末密度的关系

---

### Day 28: 安全系统与联锁

#### 学习目标
- 设计完整的安全系统
- 掌握中断处理
- 学会故障诊断

#### 安全系统架构
```
硬件保护:
├── 安全门开关 (常闭)
├── 急停按钮 (常闭)
├── 激光冷却风扇监控
└── 温度监控

软件保护:
├── 激光超时自动关闭
├── 门打开自动关闭激光
├── 温度异常保护
└── 通信超时保护
```

#### 中断处理代码
```cpp
// 急停中断处理
void estop_isr() {
  // 立即停止所有运动
  stepper.quick_stop();
  // 关闭激光
  WRITE(SPINDLE_LASER_ENA_PIN, LOW);
  // 设置系统状态
  system_state = STATE_ESTOP;
}
```

#### 实践任务
1. [ ] 设计安全联锁逻辑图
2. [ ] 编写急停处理代码
3. [ ] 测试各种故障场景
4. [ ] 编写故障诊断程序

#### 检查点
- [ ] 能画出安全系统框图
- [ ] 知道如何编写中断服务程序
- [ ] 理解看门狗定时器的作用

---

## Week 5-6: 实战项目

### 阶段一: 移植验证 (Week 5)

#### 任务清单
- [ ] 应用 MKS SLS 配置
- [ ] 编译固件
- [ ] 烧录测试
- [ ] 验证基础功能
  - [ ] 屏幕显示
  - [ ] 触摸响应
  - [ ] 步进电机运动
  - [ ] 温度读取

#### 调试记录模板
```
日期: 2026-XX-XX
测试项目: 
预期结果: 
实际结果: 
问题分析: 
解决方案: 
```

---

### 阶段二: 功能调试 (Week 6 上半)

#### 任务清单
- [ ] 激光控制测试
- [ ] 铺料系统调试
- [ ] 安全系统验证
- [ ] WiFi 模块测试

#### 激光功率标定表
| S值 | PWM占空比 | 实测功率 | 备注 |
|-----|----------|---------|------|
| 0   | 0%       | 0W      | 关闭 |
| 64  | 25%      | ?W      | 低功率 |
| 128 | 50%      | ?W      | 中功率 |
| 192 | 75%      | ?W      | 高功率 |
| 255 | 100%     | ?W      | 最大功率 |

---

### 阶段三: 性能优化 (Week 6 下半)

#### 优化方向
1. **运动性能**
   - 加速度优化
   - 扫描速度优化
   - 拐角速度优化

2. **激光控制**
   - PWM 频率优化
   - 功率响应时间
   - 扫描路径规划

3. **铺料质量**
   - 铺料速度优化
   - 粉末密度控制
   - 层厚一致性

---

## 📖 参考资源

### 官方文档
- [Marlin 官方文档](https://marlinfw.org/)
- [MKS GitHub](https://github.com/makerbase-mks)
- [LVGL 文档](https://docs.lvgl.io/)

### 数据手册
- STM32F407 Reference Manual
- TMC2209 Datasheet
- MKS Robin Nano V3 Schematic

### 社区资源
- Marlin Discord
- MKS Facebook Group
- RepRap Forums

---

## 🛠️ 开发工具

### 必备工具
| 工具 | 用途 | 下载链接 |
|-----|------|---------|
| VSCode | 代码编辑 | https://code.visualstudio.com/ |
| PlatformIO | 编译构建 | VSCode 插件 |
| Git | 版本控制 | https://git-scm.com/ |
| STM32CubeProgrammer | 固件烧录 | ST 官网 |
| Putty/Serial Monitor | 串口调试 | - |

### 推荐工具
| 工具 | 用途 |
|-----|------|
| Logic Analyzer | 信号分析 |
| Oscilloscope | PWM 测量 |
| Thermal Camera | 温度分布 |
| Power Meter | 激光功率测量 |

---

## 📋 检查清单

### 基础掌握
- [ ] 能独立编译 Marlin 固件
- [ ] 能修改引脚定义
- [ ] 能配置 TMC2209 参数
- [ ] 能调试串口通信

### MKS 生态
- [ ] 能修改 LVGL UI
- [ ] 能替换 UI 图片资源
- [ ] 能配置 WiFi 模块
- [ ] 能进行触摸校准

### SLS 专项
- [ ] 能标定激光功率
- [ ] 能编写铺料程序
- [ ] 能实现安全联锁
- [ ] 能诊断系统故障

---

## 💡 学习建议

1. **理论与实践结合**: 每学一个概念，立即动手验证
2. **做好笔记**: 记录遇到的问题和解决方案
3. **版本控制**: 使用 Git 管理代码变更
4. **安全第一**: 激光测试时佩戴防护眼镜
5. **循序渐进**: 不要跳过基础，直接看高级内容

---

## 🆘 求助指南

遇到问题时：
1. 先查阅本计划中的相关章节
2. 查看 `docs/` 目录下的文档
3. 搜索 Marlin GitHub Issues
4. 询问 Claw (我)

---

## ✅ 结业标准

完成以下项目即视为掌握：
1. 独立编译并通过 MKS SLS 固件
2. 成功完成一次单层烧结测试
3. 能诊断并修复常见故障
4. 能添加自定义功能到 UI

---

**祝学习顺利！有任何问题随时问我。**

— Claw
