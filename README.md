# DrawLang 课程设计项目

## 项目简介

本项目实现一个简化绘图语言 `DrawLang` 的解释器，用于完成编译原理课程设计。

根据任务书要求，项目包含两套实现：

1. Java 手工实现词法分析和递归下降语法分析
2. 基于 Flex/Bison 的自动生成词法和语法分析

两套实现共享统一的语义规则和 JSON IR，并最终由 Python 后端绘制图形。

## 关键文档

- `核心规则说明.md`：完整 EBNF、Token 表、语义规则、JSON IR 约束
- `工程设计与实现方案.md`：工程结构、平台依赖、模块划分、实施步骤

## 当前目录结构

```text
ks/
├── backend/
├── docs/
├── examples/
├── java_frontend/
├── scripts/
├── tests/
├── yacc_frontend/
├── README.md
├── 工程设计与实现方案.md
└── 核心规则说明.md
```

## 当前进度

已完成：

- 语言核心规则文档
- 工程设计方案文档
- 项目目录骨架
- Python 绘图后端初版
- 样例输入与预期 IR 初版

进行中：

- Java 手工前端

待完成：

- Flex/Bison 自动前端
- 双前端一致性测试
- 报告与答辩材料整理

## Windows 依赖

### 已确认具备

- `java`
- `javac`
- `python`
- `pip`

### 仍需安装

```powershell
python -m pip install matplotlib
```

若要完成自动前端，还需要：

- `win_flex`
- `win_bison`
- `gcc` 或 `MinGW-w64`

## 共享后端使用方式

后端程序：

```text
backend/draw_backend.py
```

运行方式：

```powershell
python backend\draw_backend.py tests\expected_ir\demo.json output.png
```

功能：

- 读取 JSON IR
- 校验基本语义
- 使用 matplotlib 绘制 PNG 图像

## 下一步

1. 完成 Java 词法分析器
2. 完成 Java 递归下降语法分析器
3. 生成 JSON IR
4. 联调 Python 后端
5. 安装并验证 `win_flex_bison` 后推进自动前端
