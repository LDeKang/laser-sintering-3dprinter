# SLS激光烧结3D打印机 - 固件目录说明

## 目录结构（已整理）

```
firmware/
├── marlin-sls/              ← 【主工程】完整的Marlin固件（SLS修改版）
│   ├── Marlin/
│   │   ├── Configuration.h       # SLS配置文件
│   │   ├── Configuration_adv.h   # SLS高级配置
│   │   └── src/
│   ├── platformio.ini
│   └── ...
├── config-backup/           ← 原始配置文件备份（可删除）
├── sls_config_notes.md      ← SLS配置说明文档
└── mks_pins_analysis.txt    ← MKS引脚分析（参考）
```

## 使用说明

### 编译固件
```bash
cd firmware/marlin-sls
pio run -e STM32F103RC_btt
```

### 主要修改文件
- `Marlin/Configuration.h` - 主板、激光、E轴配置
- `Marlin/Configuration_adv.h` - 激光功能启用
- `Marlin/src/pins/stm32f1/pins_BTT_SKR_MINI_E3_common.h` - 激光引脚定义

## 历史记录
- 2026-03-22: 整理目录结构，删除重复文件夹
- 2026-03-22: 将Marlin从子模块转为普通文件夹
- 2026-03-22: 完成Week 1固件配置
