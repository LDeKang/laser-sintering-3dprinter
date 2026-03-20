const fs = require('fs');
const path = require('path');

// 改进的 DOCX 生成器 - 统一宋体，使用表格

function createStyledDocx(outputPath) {
    // [Content_Types].xml
    const contentTypes = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
    <Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>
    <Default Extension="xml" ContentType="application/xml"/>
    <Override PartName="/word/document.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml"/>
    <Override PartName="/word/styles.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml"/>
</Types>`;

    // _rels/.rels
    const rels = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
    <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument" Target="word/document.xml"/>
</Relationships>`;

    // word/_rels/document.xml.rels
    const docRels = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
    <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles" Target="styles.xml"/>
</Relationships>`;

    // word/styles.xml - 统一使用宋体
    const styles = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:styles xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
    <w:style w:type="paragraph" w:default="1" w:styleId="Normal">
        <w:name w:val="Normal"/>
        <w:rPr>
            <w:rFonts w:ascii="宋体" w:eastAsia="宋体" w:hAnsi="宋体" w:cs="宋体"/>
            <w:sz w:val="24"/>
            <w:szCs w:val="24"/>
        </w:rPr>
    </w:style>
    <w:style w:type="paragraph" w:styleId="Title">
        <w:name w:val="Title"/>
        <w:basedOn w:val="Normal"/>
        <w:pPr>
            <w:spacing w:before="0" w:after="300"/>
            <w:jc w:val="center"/>
        </w:pPr>
        <w:rPr>
            <w:rFonts w:ascii="宋体" w:eastAsia="宋体"/>
            <w:b/>
            <w:sz w:val="44"/>
            <w:szCs w:val="44"/>
        </w:rPr>
    </w:style>
    <w:style w:type="paragraph" w:styleId="Heading1">
        <w:name w:val="heading 1"/>
        <w:basedOn w:val="Normal"/>
        <w:pPr>
            <w:spacing w:before="300" w:after="200"/>
        </w:pPr>
        <w:rPr>
            <w:rFonts w:ascii="宋体" w:eastAsia="宋体"/>
            <w:b/>
            <w:sz w:val="32"/>
            <w:szCs w:val="32"/>
        </w:rPr>
    </w:style>
    <w:style w:type="paragraph" w:styleId="Heading2">
        <w:name w:val="heading 2"/>
        <w:basedOn w:val="Normal"/>
        <w:pPr>
            <w:spacing w:before="200" w:after="150"/>
        </w:pPr>
        <w:rPr>
            <w:rFonts w:ascii="宋体" w:eastAsia="宋体"/>
            <w:b/>
            <w:sz w:val="28"/>
            <w:szCs w:val="28"/>
        </w:rPr>
    </w:style>
    <w:style w:type="paragraph" w:styleId="Heading3">
        <w:name w:val="heading 3"/>
        <w:basedOn w:val="Normal"/>
        <w:pPr>
            <w:spacing w:before="150" w:after="100"/>
        </w:pPr>
        <w:rPr>
            <w:rFonts w:ascii="宋体" w:eastAsia="宋体"/>
            <w:b/>
            <w:sz w:val="24"/>
            <w:szCs w:val="24"/>
        </w:rPr>
    </w:style>
    <w:style w:type="table" w:styleId="TableNormal">
        <w:name w:val="Normal Table"/>
        <w:tblPr>
            <w:tblInd w:w="0" w:type="dxa"/>
            <w:tblCellMar>
                <w:top w:w="100" w:type="dxa"/>
                <w:left w:w="100" w:type="dxa"/>
                <w:bottom w:w="100" w:type="dxa"/>
                <w:right w:w="100" w:type="dxa"/>
            </w:tblCellMar>
        </w:tblPr>
    </w:style>
</w:styles>`;

    // 转义 XML 特殊字符
    function escapeXml(text) {
        return text.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
    }

    // 创建段落
    function createParagraph(text, style = 'Normal') {
        return `<w:p><w:pPr><w:pStyle w:val="${style}"/></w:pPr><w:r><w:rPr><w:rFonts w:ascii="宋体" w:eastAsia="宋体"/></w:rPr><w:t>${escapeXml(text)}</w:t></w:r></w:p>`;
    }

    // 创建表格
    function createTable(headers, rows) {
        const colCount = headers.length;
        const tblW = 9638; // 表格总宽度
        const colW = Math.floor(tblW / colCount);
        
        let gridCols = '';
        for (let i = 0; i < colCount; i++) {
            gridCols += `<w:gridCol w:w="${colW}"/>`;
        }
        
        // 表头行
        let headerRow = '<w:tr>';
        headers.forEach(h => {
            headerRow += `<w:tc><w:tcPr><w:tcW w:w="${colW}" w:type="dxa"/><w:shd w:val="clear" w:fill="D9E2F3"/></w:tcPr><w:p><w:pPr><w:jc w:val="center"/></w:pPr><w:r><w:rPr><w:rFonts w:ascii="宋体" w:eastAsia="宋体"/><w:b/></w:rPr><w:t>${escapeXml(h)}</w:t></w:r></w:p></w:tc>`;
        });
        headerRow += '</w:tr>';
        
        // 数据行
        let dataRows = '';
        rows.forEach(row => {
            dataRows += '<w:tr>';
            row.forEach(cell => {
                dataRows += `<w:tc><w:tcPr><w:tcW w:w="${colW}" w:type="dxa"/></w:tcPr><w:p><w:r><w:rPr><w:rFonts w:ascii="宋体" w:eastAsia="宋体"/></w:rPr><w:t>${escapeXml(cell)}</w:t></w:r></w:p></w:tc>`;
            });
            dataRows += '</w:tr>';
        });
        
        return `<w:tbl><w:tblPr><w:tblW w:w="${tblW}" w:type="dxa"/><w:jc w:val="center"/><w:tblBorders><w:top w:val="single" w:sz="4" w:space="0" w:color="000000"/><w:left w:val="single" w:sz="4" w:space="0" w:color="000000"/><w:bottom w:val="single" w:sz="4" w:space="0" w:color="000000"/><w:right w:val="single" w:sz="4" w:space="0" w:color="000000"/><w:insideH w:val="single" w:sz="4" w:space="0" w:color="000000"/><w:insideV w:val="single" w:sz="4" w:space="0" w:color="000000"/></w:tblBorders></w:tblPr><w:tblGrid>${gridCols}</w:tblGrid>${headerRow}${dataRows}</w:tbl>`;
    }

    // 构建文档内容
    let body = '';
    
    // 标题
    body += createParagraph('SLM金属3D打印机详细设计规格书', 'Title');
    body += '<w:p><w:pPr><w:jc w:val="center"/></w:pPr><w:r><w:rPr><w:rFonts w:ascii="宋体" w:eastAsia="宋体"/></w:rPr><w:t>版本: v1.0 | 日期: 2026-03-15</w:t></w:r></w:p>';
    
    // 1. 项目概述
    body += createParagraph('1. 项目概述', 'Heading1');
    body += createParagraph('1.1 项目目标', 'Heading2');
    body += createParagraph('构建一台基于机械XY点烧结方案的入门级SLM（选择性激光熔化）金属3D打印机，预算¥15000，能够打印316L不锈钢零件。', 'Normal');
    
    body += createParagraph('1.2 技术路线选择', 'Heading2');
    body += createTable(
        ['方案', '优点', '缺点', '选择'],
        [
            ['振镜扫描', '速度快(1-2m/s)、精度高', '成本高(¥3500+)、复杂', '❌'],
            ['机械XY点烧结', '成本低、结构简单', '极慢(50mm/s)、精度一般', '✅']
        ]
    );
    
    body += createParagraph('1.3 核心参数', 'Heading2');
    body += createTable(
        ['参数', '规格', '备注'],
        [
            ['成型尺寸', '100×100×80mm', 'X×Y×Z'],
            ['激光功率', '200W', '光纤激光器 1064nm'],
            ['扫描方式', '机械XY点烧结', '无振镜'],
            ['层厚范围', '50-100μm', '可调'],
            ['光斑直径', '~100μm', '聚焦后'],
            ['XY分辨率', '10μm', '步进电机+滚珠丝杆'],
            ['Z轴分辨率', '2.5μm', '减速后'],
            ['扫描速度', '50mm/s', '点烧结模式'],
            ['单层时间', '5-10分钟', '取决于填充率'],
            ['材料', '316L不锈钢', '球形粉末 15-45μm'],
            ['预算', '¥15000', '-']
        ]
    );
    
    // 2. 机械系统设计
    body += createParagraph('2. 机械系统设计', 'Heading1');
    body += createParagraph('2.1 X轴（激光头横向）', 'Heading2');
    body += createParagraph('功能：携带激光头横向移动，实现X方向扫描', 'Normal');
    body += createTable(
        ['参数', '规格'],
        [
            ['行程', '120mm'],
            ['驱动', '57闭环步进电机'],
            ['减速比', '1:5'],
            ['传动', '1610滚珠丝杆（导程10mm）'],
            ['导轨', 'MGN12直线导轨×2'],
            ['分辨率', '10μm/步'],
            ['最大速度', '50mm/s'],
            ['定位精度', '±0.05mm']
        ]
    );
    
    body += createParagraph('选型理由：57电机+1:5减速提供足够扭矩，闭环防止丢步；1610丝杆平衡速度和精度；MGN12导轨承载激光头稳定运行。', 'Normal');
    
    body += createParagraph('2.2 Y轴（激光头纵向）', 'Heading2');
    body += createTable(
        ['参数', '规格'],
        [
            ['行程', '120mm'],
            ['驱动', '57闭环步进电机'],
            ['减速比', '1:5'],
            ['传动', '1610滚珠丝杆（导程10mm）'],
            ['导轨', 'MGN12直线导轨×2'],
            ['负载', 'X轴组件+激光头（约5kg）']
        ]
    );
    body += createParagraph('注意：Y轴负载较大，需要更强的电机或更大减速比', 'Normal');
    
    body += createParagraph('2.3 Z1轴（成型缸）', 'Heading2');
    body += createParagraph('功能：成型平台逐层下降', 'Normal');
    body += createTable(
        ['参数', '规格'],
        [
            ['行程', '100mm'],
            ['驱动', '57步进电机'],
            ['减速比', '1:10行星减速器'],
            ['传动', '1605滚珠丝杆（导程5mm）'],
            ['分辨率', '2.5μm/步'],
            ['负载', '平台+粉末（约5kg）']
        ]
    );
    body += createParagraph('选型理由：1:10减速提供大扭矩支撑粉末重量；1605丝杆5mm导程提高分辨率；高精度要求层厚控制关键。', 'Normal');
    
    body += createParagraph('2.4 Z2轴（送粉缸）', 'Heading2');
    body += createTable(
        ['参数', '规格'],
        [
            ['行程', '100mm'],
            ['驱动', '42步进电机'],
            ['传动', '1605滚珠丝杆（导程5mm）'],
            ['分辨率', '25μm/步（无减速）']
        ]
    );
    body += createParagraph('注意：送粉精度要求较低，42电机足够', 'Normal');
    
    body += createParagraph('2.5 铺粉系统', 'Heading2');
    body += createParagraph('功能：将粉末从送粉缸推到成型区域并刮平', 'Normal');
    body += createTable(
        ['参数', '规格'],
        [
            ['驱动', '42步进电机'],
            ['传动', 'GT2同步带，20齿皮带轮'],
            ['行程', '150mm'],
            ['刮刀', '硬质合金，厚度0.3mm'],
            ['安装', '磁吸快换'],
            ['铺粉速度', '100mm/s']
        ]
    );
    body += createParagraph('工作流程：1)刮刀在送粉缸上方待命 → 2)Z2上升送粉 → 3)刮刀移动铺粉 → 4)刮刀返回 → 5)Z1下降一层', 'Normal');
    
    // 3. 激光系统
    body += createParagraph('3. 激光系统', 'Heading1');
    body += createParagraph('3.1 激光器', 'Heading2');
    body += createTable(
        ['参数', '规格'],
        [
            ['类型', '光纤激光器'],
            ['功率', '200W'],
            ['波长', '1064nm'],
            ['光束质量', 'M² < 1.5'],
            ['调制方式', 'TTL/PWM'],
            ['调制频率', '1-50kHz'],
            ['冷却', '风冷/水冷'],
            ['光纤芯径', '20μm']
        ]
    );
    body += createParagraph('采购建议：国产锐科/创鑫二手设备；要求带保修（至少3个月）；确认光纤接口类型（QBH或QCS）', 'Normal');
    
    body += createParagraph('3.2 光路系统', 'Heading2');
    body += createParagraph('激光器光纤输出 → 准直镜 → 聚焦镜 → 保护镜片 → 工件表面', 'Normal');
    body += createTable(
        ['部件', '规格'],
        [
            ['准直镜', 'F=50mm'],
            ['聚焦镜', 'F=100mm'],
            ['工作距离', '约80mm'],
            ['保护镜片', '石英玻璃，镀1064nm增透膜']
        ]
    );
    body += createParagraph('光斑计算：光纤芯径20μm，NA≈0.1 → 准直后光束直径≈10mm → 聚焦后光斑直径≈100μm', 'Normal');
    
    body += createParagraph('3.3 激光控制', 'Heading2');
    body += createTable(
        ['控制方式', '信号类型', '说明'],
        [
            ['使能', 'TTL高电平', '激光器准备就绪'],
            ['调制', 'PWM', '功率调节 0-100%'],
            ['急停', '开关量', '安全联锁']
        ]
    );
    body += createParagraph('PWM参数：频率1-10kHz；占空比0-100%对应功率0-200W；建议工作功率100-150W（留余量）', 'Normal');
    
    // 4. 保护舱设计
    body += createParagraph('4. 保护舱设计', 'Heading1');
    body += createParagraph('4.1 功能要求', 'Heading2');
    body += createParagraph('1) 惰性气氛：氧含量<500ppm，防止金属氧化；2) 安全防护：防止激光泄漏、粉末飞溅；3) 观察窗口：便于监控打印过程；4) 操作接口：手套口或快开门', 'Normal');
    
    body += createParagraph('4.2 材料与加工', 'Heading2');
    body += createTable(
        ['部件', '材料', '厚度', '加工方式'],
        [
            ['箱体', '304不锈钢', '2mm', '焊接'],
            ['框架', '4040铝型材', '-', '组装'],
            ['观察窗', '激光防护玻璃', '5mm', '镶嵌'],
            ['手套口', '标准手套法兰', '-', '安装'],
            ['密封条', '硅胶条', '-', '粘贴']
        ]
    );
    
    body += createParagraph('4.3 气体系统', 'Heading2');
    body += createParagraph('气体流程：氩气瓶 → 减压阀 → 流量计 → 保护舱底部进气 → 氧含量传感器监测 → 顶部出气', 'Normal');
    body += createTable(
        ['部件', '规格'],
        [
            ['氩气瓶', '40L工业瓶'],
            ['减压阀', '0-0.6MPa可调'],
            ['流量计', '0-50L/min'],
            ['氧分析仪', '0-1000ppm，电化学传感器']
        ]
    );
    body += createParagraph('操作参数：充气流量10-20L/min；目标氧含量<500ppm；换气次数建议5-10次舱体积', 'Normal');
    
    // 5. 控制系统
    body += createParagraph('5. 控制系统', 'Heading1');
    body += createParagraph('5.1 控制架构', 'Heading2');
    body += createParagraph('PC (上位机) → USB/串口 → MKS Robin Nano V3 (主控板)', 'Normal');
    body += createTable(
        ['输出', '连接'],
        [
            ['X轴驱动', '57闭环步进'],
            ['Y轴驱动', '57闭环步进'],
            ['Z1驱动', '57步进(成型缸)'],
            ['Z2驱动', '42步进(送粉缸)'],
            ['E轴驱动', '42步进(刮刀)'],
            ['PWM输出', '激光器调制'],
            ['TTL输出', '激光器使能']
        ]
    );
    
    body += createParagraph('5.2 主控板选型：MKS Robin Nano V3', 'Heading2');
    body += createTable(
        ['规格项', '参数'],
        [
            ['MCU', 'STM32F407VGT6 (168MHz)'],
            ['步进驱动', '5路 (TMC2209或A4988)'],
            ['输入', '限位开关×6，温度×2'],
            ['输出', 'PWM×2，风扇×2，加热×2'],
            ['接口', 'USB, TF卡, WiFi(可选)'],
            ['价格', '~¥300']
        ]
    );
    body += createParagraph('选型理由：32位MCU性能足够；5路步进刚好满足需求；开源Marlin固件支持；性价比高', 'Normal');
    
    body += createParagraph('5.3 安全联锁', 'Heading2');
    body += createTable(
        ['联锁项目', '传感器', '动作'],
        [
            ['舱门开启', '门磁开关', '激光器关闭'],
            ['急停按钮', '急停开关', '全系统断电'],
            ['氧含量过高', '氧分析仪', '报警+暂停打印'],
            ['激光器故障', '激光器反馈', '暂停打印']
        ]
    );
    
    // 6. BOM预算
    body += createParagraph('6. BOM预算', 'Heading1');
    body += createTable(
        ['类别', '预算'],
        [
            ['激光系统', '¥7300'],
            ['机械系统', '¥4615'],
            ['控制系统', '¥500'],
            ['保护舱/气体', '¥2400'],
            ['杂项', '¥900'],
            ['总计', '¥15715']
        ]
    );
    body += createParagraph('注：超预算¥715，建议优化激光器或保护舱成本', 'Normal');
    
    // 7. 里程碑与验收标准
    body += createParagraph('7. 里程碑与验收标准', 'Heading1');
    
    body += createParagraph('Phase 1: 机械装配 (Week 1-2)', 'Heading2');
    body += createParagraph('任务：铝型材框架搭建完成；XY轴安装手动推动顺畅；Z轴安装升降平稳；铺粉系统安装刮刀运动正常', 'Normal');
    body += createParagraph('验收标准：各轴手动操作顺畅，无明显间隙', 'Normal');
    
    body += createParagraph('Phase 2: 光路搭建 (Week 2-3)', 'Heading2');
    body += createParagraph('任务：激光器安装固定；准直聚焦镜组安装；光路对准焦点清晰；保护舱焊接组装', 'Normal');
    body += createParagraph('验收标准：激光能在不锈钢板上烧出清晰痕迹', 'Normal');
    
    body += createParagraph('Phase 3: 控制系统 (Week 3-4)', 'Heading2');
    body += createParagraph('任务：控制板接线完成；Marlin固件烧录；各轴电机调试；激光控制测试；安全联锁测试', 'Normal');
    body += createParagraph('验收标准：能用G代码控制各轴运动和激光开关', 'Normal');
    
    body += createParagraph('Phase 4: 工艺调试 (Week 4-8)', 'Heading2');
    body += createParagraph('任务：单层烧结测试（10×10mm方块）；铺粉质量优化；层间结合测试（5层堆叠）；10mm立方体打印；工艺参数固化', 'Normal');
    body += createParagraph('验收标准：成功打印10mm不锈钢立方体，无明显缺陷', 'Normal');
    
    // 页脚
    body += '<w:sectPr><w:pgSz w:w="11906" w:h="16838"/><w:pgMar w:top="1440" w:right="1440" w:bottom="1440" w:left="1440"/></w:sectPr>';

    // word/document.xml
    const document = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:document xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
    <w:body>${body}</w:body>
</w:document>`;

    // 创建临时目录
    const tempDir = fs.mkdtempSync(path.join(require('os').tmpdir(), 'docx-'));
    
    // 写入文件
    fs.writeFileSync(path.join(tempDir, '[Content_Types].xml'), contentTypes);
    fs.mkdirSync(path.join(tempDir, '_rels'));
    fs.writeFileSync(path.join(tempDir, '_rels', '.rels'), rels);
    fs.mkdirSync(path.join(tempDir, 'word'));
    fs.mkdirSync(path.join(tempDir, 'word', '_rels'));
    fs.writeFileSync(path.join(tempDir, 'word', '_rels', 'document.xml.rels'), docRels);
    fs.writeFileSync(path.join(tempDir, 'word', 'styles.xml'), styles);
    fs.writeFileSync(path.join(tempDir, 'word', 'document.xml'), document);

    // 创建 ZIP
    const zipPath = outputPath.replace('.docx', '.zip');
    const psCommand = `powershell -Command "Compress-Archive -Path '${tempDir}\\*' -DestinationPath '${zipPath}' -Force"`;
    require('child_process').execSync(psCommand, { stdio: 'inherit' });
    
    // 重命名为 .docx
    fs.renameSync(zipPath, outputPath);
    
    // 清理临时目录
    fs.rmSync(tempDir, { recursive: true });
    
    console.log(`DOCX created: ${outputPath}`);
}

// 创建 Word 文档
createStyledDocx('SLM金属3D打印机设计规格书_v1.0.docx');