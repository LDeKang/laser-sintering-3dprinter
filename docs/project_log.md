# SLS激光烧结3D打印机项目日志

> 记录开发过程中遇到的问题、解决方案和重要决策

---

## 2026-03-24

### 问题：编译错误 - HEATER_0_PIN not defined

**时间：** 23:23  
**现象：**
```
Marlin\src\HAL\STM32\../../inc/SanityCheck.h:2127:4: error: #error "HEATER_0_PIN not defined for this board."
```

**原因分析：**
- `EXTRUDERS = 1` 配置了一个热端（E0）
- Marlin的SanityCheck需要 `HEATER_0_PIN` 和 `TEMP_SENSOR_0` 来定义这个热端
- 虽然配置了虚拟温度传感器（998），但pins文件中没有定义 `HEATER_0_PIN`
- 原来的pins文件把 `HEATER_0_PIN` 完全删除了，只定义了激光控制引脚

**解决方案：**
在 `pins_MKS_ROBIN_NANO_V3_common.h` 中添加虚拟定义：
```cpp
#define HEATER_0_PIN                        PE5   // SLS: 虚拟定义，实际用于激光控制
```

**影响：**
- Marlin的SanityCheck通过
- 实际加热控制不会生效（TEMP_SENSOR_0是虚拟传感器998）
- 激光控制仍然使用PE5引脚

**文件修改：**
- `firmware/marlin-sls/Marlin/src/pins/stm32f4/pins_MKS_ROBIN_NANO_V3_common.h`

---

## 日志模板

### 问题：[问题标题]

**时间：** YYYY-MM-DD HH:MM  
**现象：** [描述错误现象]

**原因分析：** [分析根本原因]

**解决方案：** [具体的解决步骤]

**影响：** [对项目的影响]

**文件修改：** [修改的文件列表]

---

*最后更新：2026-03-24*
