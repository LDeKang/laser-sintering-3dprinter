#!/usr/bin/env python3
"""
SLS to FDM 配置转换脚本
将 Marlin SLS 激光烧结配置改回标准 FDM 3D 打印机配置
"""

import re
import shutil
from datetime import datetime

# 文件路径
CONFIG_H = "Marlin/Configuration.h"
CONFIG_ADV_H = "Marlin/Configuration_adv.h"

def backup_files():
    """备份原始配置文件"""
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    shutil.copy(CONFIG_H, f"{CONFIG_H}.sls.{timestamp}.backup")
    shutil.copy(CONFIG_ADV_H, f"{CONFIG_ADV_H}.sls.{timestamp}.backup")
    print(f"✓ 已备份原配置文件")

def modify_config_h():
    """修改 Configuration.h - SLS 改回 FDM"""
    
    with open(CONFIG_H, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 1. 修改机器名称
    content = re.sub(
        r'#define STRING_CONFIG_H_AUTHOR ".*?"',
        '#define STRING_CONFIG_H_AUTHOR "(MKS Robin Nano V3, FDM Printer)"',
        content
    )
    
    # 2. 修改温度传感器（热端改回真实传感器）
    # SLS: #define TEMP_SENSOR_0 998 (虚拟传感器)
    # FDM: #define TEMP_SENSOR_0 1 (100k EPCOS热敏电阻)
    content = re.sub(
        r'#define TEMP_SENSOR_0 998.*?\n',
        '#define TEMP_SENSOR_0 1  // 100kΩ EPCOS热敏电阻\n',
        content
    )
    
    # 3. 启用热端加热（删除或注释掉禁用热端的配置）
    # 查找并移除 SLS 的虚拟温度设置
    content = re.sub(
        r'#define DUMMY_THERMISTOR_998_VALUE 25\n',
        '',
        content
    )
    
    # 4. 禁用激光功能
    # SLS: #define LASER_FEATURE
    # FDM: //#define LASER_FEATURE
    content = re.sub(
        r'(#define LASER_FEATURE)',
        r'//\1  // 禁用激光功能（FDM打印机）',
        content
    )
    
    # 5. 禁用 SPINDLE 功能（如果启用）
    content = re.sub(
        r'(#define SPINDLE_FEATURE)',
        r'//\1  // 禁用主轴功能',
        content
    )
    
    # 6. 修改挤出头名称
    content = re.sub(
        r'// #define HOTEND_OFFSET_X \{0\.0, 20\.00\}',
        '// #define HOTEND_OFFSET_X {0.0, 20.00}  // 多挤出机偏移',
        content
    )
    
    # 7. 启用热端 PID 控制
    content = re.sub(
        r'//#define PIDTEMP',
        '#define PIDTEMP  // 启用热端PID温度控制',
        content
    )
    
    # 8. 启用热端热保护
    content = re.sub(
        r'//#define THERMAL_PROTECTION_HOTENDS',
        '#define THERMAL_PROTECTION_HOTENDS  // 启用热端热保护',
        content
    )
    
    # 9. 修改默认步进值（E轴从铺料改回挤出机）
    # SLS: E轴用于铺料，步数较大
    # FDM: E轴用于挤出，标准值
    content = re.sub(
        r'#define DEFAULT_AXIS_STEPS_PER_UNIT \{ 80, 80, 400, 1600 \}',
        '#define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400, 93 }  // 标准挤出机步数',
        content
    )
    
    # 10. 修改最大温度限制
    content = re.sub(
        r'#define HEATER_0_MAXTEMP 275',
        '#define HEATER_0_MAXTEMP 275  // 热端最高温度',
        content
    )
    
    with open(CONFIG_H, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("✓ 已修改 Configuration.h")

def modify_config_adv_h():
    """修改 Configuration_adv.h - 高级设置"""
    
    with open(CONFIG_ADV_H, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 1. 禁用激光相关的高级功能
    content = re.sub(
        r'(#define LASER_POWER_INLINE)',
        r'//\1',
        content
    )
    
    content = re.sub(
        r'(#define LASER_MOVE_POWER)',
        r'//\1',
        content
    )
    
    # 2. 启用标准挤出机功能
    content = re.sub(
        r'//#define LIN_ADVANCE',
        '#define LIN_ADVANCE  // 启用线性推进',
        content
    )
    
    # 3. 启用回抽功能
    content = re.sub(
        r'//#define FWRETRACT',
        '#define FWRETRACT  // 启用固件回抽',
        content
    )
    
    with open(CONFIG_ADV_H, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print("✓ 已修改 Configuration_adv.h")

def print_summary():
    """打印修改摘要"""
    print("\n" + "="*60)
    print("配置转换完成！")
    print("="*60)
    print("\n主要修改：")
    print("  1. ✓ 机器名称改为 FDM 打印机")
    print("  2. ✓ 热端传感器改回真实热敏电阻 (类型 1)")
    print("  3. ✓ 禁用激光功能")
    print("  4. ✓ 启用热端 PID 控制")
    print("  5. ✓ 启用热端热保护")
    print("  6. ✓ E轴步数改回标准挤出机值")
    print("  7. ✓ 启用线性推进 (LIN_ADVANCE)")
    print("  8. ✓ 启用固件回抽 (FWRETRACT)")
    print("\n下一步：")
    print("  1. 检查并确认你的具体硬件配置：")
    print("     - 驱动类型 (A4988/TMC2208/TMC2209)")
    print("     - 热端传感器型号")
    print("     - 是否有热床")
    print("  2. 使用 PlatformIO 编译固件")
    print("  3. 刷入主板测试")
    print("\n编译命令：")
    print("  pio run -e mks_robin_nano_v3_usb_flash_drive")
    print("="*60)

if __name__ == "__main__":
    print("SLS → FDM 配置转换工具")
    print("="*60)
    
    try:
        backup_files()
        modify_config_h()
        modify_config_adv_h()
        print_summary()
    except Exception as e:
        print(f"\n✗ 错误: {e}")
        print("请检查文件路径和权限")
