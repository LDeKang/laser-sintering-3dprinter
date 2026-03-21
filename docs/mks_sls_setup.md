# MKS 兼容 SLS 固件配置完成

## ✅ 已完成的工作

### 1. MKS UI 移植
- MKS LVGL UI 代码已存在于 Marlin 2.1.2.1 中
- 位于: `Marlin/src/lcd/extui/mks_ui/`
- 包含 134 个文件，完整的彩色触摸界面

### 2. MKS 引脚定义
- 已复制 MKS 官方引脚定义:
  - `pins_MKS_ROBIN_NANO_V3.h`
  - `pins_MKS_ROBIN_NANO_V3_common.h`

### 3. 构建脚本
- `mks_robin_nano35.py` - 固件打包脚本
- `download_mks_assets.py` - 资源下载脚本

### 4. SLS 配置文件
- `Configuration_MKS_SLS.h` - 主配置
- `Configuration_adv_MKS_SLS.h` - 高级配置

---

## 📋 关键配置说明

### 主板选择
```cpp
#define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3
```

### 屏幕配置
```cpp
#define MKS_TS35_V2_0      // MKS TS35 V2.0 3.5寸屏幕
#define TFT_LVGL_UI        // MKS 彩色触摸界面
#define TOUCH_SCREEN       // 启用触摸
```

### 激光配置
```cpp
#define LASER_FEATURE
#define SPINDLE_LASER_PWM_PIN PA6    // 激光功率控制
#define SPINDLE_LASER_ENA_PIN PA7    // 激光使能
```

### 步进驱动
```cpp
#define X_DRIVER_TYPE TMC2209
#define Y_DRIVER_TYPE TMC2209
#define Z_DRIVER_TYPE TMC2209
#define E0_DRIVER_TYPE TMC2209  // 铺料电机
#define E1_DRIVER_TYPE TMC2209
```

### WiFi 模块
```cpp
#define MKS_WIFI_MODULE    // MKS WiFi 模块支持
```

---

## 🔧 使用方法

### 1. 应用配置
```bash
# 复制配置文件到 Marlin 目录
cp firmware/marlin-config/Configuration_MKS_SLS.h Marlin-2.1.2.1-src/Marlin/Configuration.h
cp firmware/marlin-config/Configuration_adv_MKS_SLS.h Marlin-2.1.2.1-src/Marlin/Configuration_adv.h
```

### 2. 配置 platformio.ini
```ini
default_envs = mks_robin_nano_v3_usb_flash_drive
```

### 3. 下载资源文件
```bash
cd Marlin-2.1.2.1-src
python buildroot/share/PlatformIO/scripts/download_mks_assets.py
```

### 4. 编译固件
```bash
pio run -e mks_robin_nano_v3_usb_flash_drive
```

### 5. 更新固件
1. 复制 `.pio/build/mks_robin_nano_v3_usb_flash_drive/Robin_nano_v3.bin` 到 SD 卡
2. 复制 `assets` 文件夹到 SD 卡
3. 插入 SD 卡到主板，上电自动更新

---

## 📁 文件结构

```
firmware/
├── Marlin-2.1.2.1-src/           # Marlin 2.1.2.1 源码
│   ├── Marlin/
│   │   ├── src/
│   │   │   ├── lcd/extui/mks_ui/  # MKS LVGL UI (134文件)
│   │   │   └── pins/stm32f4/      # MKS 引脚定义
│   │   ├── Configuration.h        # 主配置
│   │   └── Configuration_adv.h    # 高级配置
│   └── buildroot/share/PlatformIO/scripts/  # 构建脚本
├── marlin-config/                 # 我们的 SLS 配置
│   ├── Configuration_MKS_SLS.h
│   └── Configuration_adv_MKS_SLS.h
└── mks-import/                    # MKS 官方文件备份
```

---

## ⚠️ 注意事项

1. **引脚定义**: 使用 MKS 官方引脚定义，不要修改
2. **资源文件**: 必须复制 `assets` 文件夹到 SD 卡
3. **屏幕校准**: 首次使用需要触摸校准
4. **激光安全**: 已配置安全门和急停引脚

---

## 🔜 下一步

1. 测试编译是否通过
2. 验证 MKS UI 功能
3. 添加 SLS 激光控制界面
4. 测试硬件兼容性
