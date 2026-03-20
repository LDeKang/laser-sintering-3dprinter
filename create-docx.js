const fs = require('fs');
const path = require('path');

// 简单的 DOCX 生成器
// DOCX 是一个 ZIP 文件，包含多个 XML 文件

function createDocx(content, outputPath) {
    // 创建 [Content_Types].xml
    const contentTypes = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
    <Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>
    <Default Extension="xml" ContentType="application/xml"/>
    <Override PartName="/word/document.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml"/>
    <Override PartName="/word/styles.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml"/>
</Types>`;

    // 创建 _rels/.rels
    const rels = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
    <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument" Target="word/document.xml"/>
</Relationships>`;

    // 创建 word/_rels/document.xml.rels
    const docRels = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
    <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles" Target="styles.xml"/>
</Relationships>`;

    // 创建 word/styles.xml
    const styles = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:styles xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
    <w:style w:type="paragraph" w:default="1" w:styleId="Normal">
        <w:name w:val="Normal"/>
        <w:rPr>
            <w:rFonts w:ascii="Calibri" w:eastAsia="宋体"/>
            <w:sz w:val="22"/>
            <w:szCs w:val="22"/>
        </w:rPr>
    </w:style>
    <w:style w:type="paragraph" w:styleId="Heading1">
        <w:name w:val="heading 1"/>
        <w:basedOn w:val="Normal"/>
        <w:pPr>
            <w:pStyle w:val="Heading1"/>
            <w:spacing w:before="240" w:after="120"/>
        </w:pPr>
        <w:rPr>
            <w:b/>
            <w:sz w:val="32"/>
            <w:szCs w:val="32"/>
        </w:rPr>
    </w:style>
    <w:style w:type="paragraph" w:styleId="Heading2">
        <w:name w:val="heading 2"/>
        <w:basedOn w:val="Normal"/>
        <w:pPr>
            <w:pStyle w:val="Heading2"/>
            <w:spacing w:before="200" w:after="100"/>
        </w:pPr>
        <w:rPr>
            <w:b/>
            <w:sz w:val="26"/>
            <w:szCs w:val="26"/>
        </w:rPr>
    </w:style>
</w:styles>`;

    // 转换内容为 Word XML
    const paragraphs = content.split('\n\n').map(para => {
        const trimmed = para.trim();
        if (!trimmed) return '';
        
        // 标题检测
        if (trimmed.startsWith('# ')) {
            const text = trimmed.substring(2).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
            return `<w:p><w:pPr><w:pStyle w:val="Heading1"/></w:pPr><w:r><w:t>${text}</w:t></w:r></w:p>`;
        }
        if (trimmed.startsWith('## ')) {
            const text = trimmed.substring(3).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
            return `<w:p><w:pPr><w:pStyle w:val="Heading2"/></w:pPr><w:r><w:t>${text}</w:t></w:r></w:p>`;
        }
        if (trimmed.startsWith('### ')) {
            const text = trimmed.substring(4).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
            return `<w:p><w:pPr><w:pStyle w:val="Heading3"/></w:pPr><w:r><w:t>${text}</w:t></w:r></w:p>`;
        }
        
        // 普通段落
        const text = trimmed.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
        return `<w:p><w:r><w:t>${text}</w:t></w:r></w:p>`;
    }).filter(p => p).join('\n');

    // 创建 word/document.xml
    const document = `<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:document xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
    <w:body>
        ${paragraphs}
        <w:sectPr>
            <w:pgSz w:w="11906" w:h="16838"/>
            <w:pgMar w:top="1440" w:right="1440" w:bottom="1440" w:left="1440"/>
        </w:sectPr>
    </w:body>
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

    // 使用 PowerShell 创建 ZIP
    const zipPath = outputPath.replace('.docx', '.zip');
    const psCommand = `powershell -Command "Compress-Archive -Path '${tempDir}\\*' -DestinationPath '${zipPath}' -Force"`;
    require('child_process').execSync(psCommand, { stdio: 'inherit' });
    
    // 重命名为 .docx
    fs.renameSync(zipPath, outputPath);
    
    // 清理临时目录
    fs.rmSync(tempDir, { recursive: true });
    
    console.log(`DOCX created: ${outputPath}`);
}

// 读取设计规格书内容
const content = fs.readFileSync('docs/design-spec-v1.0.md', 'utf8');

// 创建 Word 文档
createDocx(content, 'SLM金属3D打印机设计规格书.docx');