# MKS Robin Nano V3 标准3D打印机配置说明

## 当前状态

此文件夹包含 Marlin 2.0.9.2 固件，之前配置为 SLS 激光烧结打印机。

## 恢复标准3D打印机的步骤

### 1. 备份当前SLS配置
```bash
cd firmware/marlin-sls/Marlin
cp Configuration.h Configuration.h.sls.backup
cp Configuration_adv.h Configuration_adv.h.sls.backup
```

### 2. 下载官方配置示例
从 Marlin 官方配置库下载 MKS Robin Nano V3 的标准配置：
https://github.com/MarlinFirmware/Configurations/tree/release-2.0.9.2/config/examples/Mks/Robin

### 3. 替换配置文件
将下载的官方配置文件替换到当前目录：
- `Configuration.h`
- `Configuration_adv.h`
- `_Bootscreen.h` (如果有)
- `_Statusscreen.h` (如果有)

### 4. 关键修改点（从SLS改回FDM）

#### 主板配置（保持不变）
```cpp
#define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3
```

#### 温度传感器（改回真实传感器）
```cpp
// SLS配置（虚拟传感器）
#define TEMP_SENSOR_0 998

// 标准FDM配置（例如100k热敏电阻）
#define TEMP_SENSOR_0 1
```

#### 挤出机配置（启用挤出机）
```cpp
// SLS配置（禁用挤出机）
//#define EXTRUDERS 1

// 标准FDM配置
#define EXTRUDERS 1
```

#### 激光功能（禁用）
```cpp
// SLS配置（启用激光）
#define LASER_FEATURE

// 标准FDM配置（禁用激光）
//#define LASER_FEATURE
```

#### 热端加热（启用）
```cpp
// SLS配置（禁用热端加热）
//#define HEATER_0_PIN

// 标准FDM配置（启用热端）
#define HEATER_0_PIN PA_1  // 根据实际引脚定义
```

### 5. 编译测试
```bash
platformio run -e mks_robin_nano_v3_usb_flash_drive
```

## 快速恢复脚本

需要我帮你写一个自动化脚本来完成这些修改吗？

## 注意事项

1. **引脚定义**：MKS Robin Nano V3 的引脚定义在 `pins_MKS_ROBIN_NANO_V3.h`
2. **驱动类型**：确认你的驱动是 A4988、TMC2208 还是 TMC2209
3. **屏幕**：如果使用的是 MKS TS35，需要启用 TFT 支持
4. **热床**：确认是否有热床，以及热床传感器类型

## 下一步

请告诉我：
1. 你的打印机具体配置（驱动类型、是否有热床、挤出机数量等）
2. 是否需要我直接帮你修改配置文件
3. 是否需要保留 SLS 配置作为备份
