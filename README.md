# CS101A(H) Data Structures - Course Reference Repository

[![License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](LICENSE)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=cplusplus)]()
[![Build System](https://img.shields.io/badge/Build-Makefile%20%26%20CMake-C7A046?logo=gnu)]()

> 📚 **ShanghaiTech University | CS101A(H) Data Structures (Fall 2025)**
>
> **本仓库为课程参考资源库，非作业提交内容。**  
> 包含课程要求的**作业实现思路参考**与**期末项目要求文档**，请**独立完成作业**以遵守学术诚信规范。

---

## 📌 核心资源说明

| 资源类型             | 仓库路径                                                | 内容说明                                                    | 重要提示                                         |
| -------------------- | ------------------------------------------------------- | ----------------------------------------------------------- | ------------------------------------------------ |
| **作业参考代码**     | `CS101A25F_HW[1-8]`                                     | 课程作业的**C++实现思路参考**（含个人实现与TA参考答案对比） | ✅ 仅作**理解算法逻辑**使用<br>❌ **严禁直接提交** |
| **期末项目要求文档** | `Final_Project.pdf`                                     | **课程官方期末项目说明**（含任务描述/测试用例/评分标准）    | ✅ **这是唯一官方文档**<br>❌ 非我的报告/实现      |
| **课程项目参考**     | `CS101A25F_PROJ[1-3]`                                   | 课程项目实现思路（含CMake构建系统）                         | ✅ 仅作**工程实践参考**<br>❌ 需独立实现           |
| **期末大作业**       | [Maze-Awaken](https://github.com/rayor2020/Maze-Awaken) | 期末项目代码仓库（**独立仓库**，非本仓库内容）              | ✅ 仅作**最终效果参考**<br>❌ 不能作为作业提交     |

---

> 📝 **博客文章详解**：  
> 本仓库的详细使用指南已整理为博客文章，包含 **课程资源说明、构建工具差异、学术诚信提醒** 等：  
> 👉 [CS101A(H)数据结构课程资源指南：仓库使用说明与注意事项](https://ray-or.com/273.html)

---

## ⚙️ 构建工具使用指南（关键差异说明）

| 作业类型        | 构建方式     | 操作步骤                                                       | 适用范围                   |
| --------------- | ------------ | -------------------------------------------------------------- | -------------------------- |
| **HW1-HW4**     | `Makefile`   | `cd CS101A25F_HW1 && make && ./hw1`                            | 课程要求使用Makefile的作业 |
| **HW5-HW8**     | **手动编译** | `g++ -std=c++17 src/main.cpp -o hw5 && ./hw5`                  | 无构建文件，需手动编译     |
| **PROJ1-PROJ3** | `CMake`      | `cd CS101A25F_PROJ1 && cmake . && make && ./proj1`             | 课程项目（非作业）         |
| **PROJ4**       | **独立仓库** | 请访问 [Maze-Awaken](https://github.com/rayor2020/Maze-Awaken) | 期末大作业（非本仓库）     |

> 💡 **重要提示**：  
> 课程**教学语言为C++**（非C语言），所有代码均使用`-std=c++17`标准编译。

---

## 🛑 学术诚信警告（必须阅读！）

> ⚠️ **本仓库所有内容均为学习参考，严禁直接提交！**  
> ⚠️ **Final_Project.pdf是课程官方要求文档**，**不是**我的课程报告或实现  
> ⚠️ **TA参考答案仅用于理解思路**，提交需**独立完成**  
> ⚠️ 课程系统会检测代码相似度，直接提交本仓库内容将视为**学术不端**

> ✨ **正确使用方式**：  
> `理解算法逻辑 → 重写代码 → 用测试用例验证 → 提交独立实现`

---

## 📂 仓库结构快速导航

```text
.
├── CS101A25F_HW[1-8]       # 作业参考（HW1-HW4用Makefile，HW5-HW8需手动编译）
│   ├── src/                # C++源码（.cpp/.h）
│   └── README.md           # 作业说明（含构建提示）
├── CS101A25F_PROJ[1-3]     # 课程项目参考（使用CMake）
│   ├── src/
│   └── CMakeLists.txt      # 构建配置
├── Final_Project.pdf       # 🚨 期末项目官方要求文档（课程唯一指定文件）
├── LICENSE                 # GPL-3.0许可证
└── README.md               # 你正在阅读的文件
```

---

## 🚀 快速使用指引

### 步骤1：阅读官方文档
```bash
# 重点查看期末项目要求
open Final_Project.pdf  # 或在GitHub查看
```

### 步骤2：参考作业实现（以HW1为例）
```bash
# 进入作业目录
cd CS101A25F_HW1

# 查看参考代码
cat src/LinkedList.cpp

# 用Makefile构建（HW1-HW4适用）
make
./hw1
```

### 步骤3：独立实现作业
```bash
# 1. 理解算法逻辑（参考HW1的LinkedList实现）
# 2. 在自己的作业目录中重写代码
# 3. 用测试用例验证
g++ -std=c++17 src/main.cpp -o hw1 && ./hw1
```

---

> ✨ **本仓库已解归档，代码可正常访问**  
> **⚠️ 请严格遵守学术诚信要求，独立完成作业！**  
> **仓库地址**：[https://github.com/rayor2020/CS101A-H-HW-and-Proj](https://github.com/rayor2020/CS101A-H-HW-and-Proj)

---

<div align="center">
  <sub>本仓库为课程参考资源，非作业提交内容 | 课程：CS101A(H) Data Structures (2025 Fall)</sub>
</div>

> This README is AI-generated. 
> ⚠️ Possible factual errors exist. Please verify with course materials and report issues in the repository.