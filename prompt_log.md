# prompt_log.md

> **说明**：本文档已嵌入原版代码，直接全量保存。记录了学生成绩管理系统 V2.0 重构过程中与 AI 协作的完整 5 轮对话日志。

---

# AI代码协作日志 | 学生成绩管理系统V2.0重构

共 5 轮沟通，全程围绕原 V1 代码审查、拆分、优化、用例、版本对比，所有优化落地到项目源码。

## 第1轮：原代码逐行通俗解析

### 我的提问

请用初学者能看懂的大白话逐行解析这份C语言学生成绩管理源码，逐个解释头文件、变量、自定义函数、整体执行流程，源码如下：

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------- 函数声明 ---------- */
int  input_student_count(void);
void input_student_info(char names[][20], int scores[], int n);
void calculate_stats(int scores[], int n, int *sum, float *avg, int *max, int *min);
void sort_students(char names[][20], int scores[], int n);
void print_results(char names[][20], int scores[], int n, float avg, int max, int min);

/* ---------- 主函数（重构前原版） ---------- */
int main() {
    system("chcp 65001"); // 将控制台代码页切换为 UTF-8

    char names[100][20];
    int scores[100];
    int sum = 0, max = 0, min = 100;
    float avg;

    // 1. 输入并校验学生人数
    int n = input_student_count();

    // 2. 输入所有学生的姓名和成绩
    input_student_info(names, scores, n);

    // 3. 计算总分、平均分、最高分、最低分
    calculate_stats(scores, n, &sum, &avg, &max, &min);

    // 4. 按成绩从高到低排序
    sort_students(names, scores, n);

    // 5. 输出所有统计结果和排名
    print_results(names, scores, n, avg, max, min);

    return 0;
}

/* ---------- 函数定义 ---------- */

// 功能1: 输入并校验学生人数
int input_student_count(void) {
    int n;
    printf("请输入学生人数: ");
    scanf("%d", &n);
    while (n <= 0 || n > 100) {
        printf("人数不合法，请重新输入(1-100): ");
        scanf("%d", &n);
    }
    return n;
}

// 功能2: 输入所有学生的姓名和成绩
void input_student_info(char names[][20], int scores[], int n) {
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个学生的姓名: ", i + 1);
        scanf("%s", names[i]);
        printf("请输入第%d个学生的成绩: ", i + 1);
        scanf("%d", &scores[i]);
        while (scores[i] < 0 || scores[i] > 100) {
            printf("成绩不合法，请重新输入(0-100): ");
            scanf("%d", &scores[i]);
        }
    }
}

// 功能3: 计算总分、平均分、最高分、最低分
void calculate_stats(int scores[], int n, int *sum, float *avg, int *max, int *min) {
    *sum = 0;
    *max = 0;
    *min = 100;
    for (int i = 0; i < n; i++) {
        *sum += scores[i];
        if (scores[i] > *max) *max = scores[i];
        if (scores[i] < *min) *min = scores[i];
    }
    *avg = (float)(*sum) / n;
}

// 功能4: 按成绩从高到低排序（冒泡排序，同步交换姓名）
void sort_students(char names[][20], int scores[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (scores[j] < scores[j + 1]) {
                int temp_score = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp_score;

                char temp_name[20];
                strcpy(temp_name, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp_name);
            }
        }
    }
}

// 功能5: 输出所有统计结果和排名
void print_results(char names[][20], int scores[], int n, float avg, int max, int min) {
    printf("\n===== 成绩统计结果 =====\n");
    printf("平均分: %.2f\n", avg);
    printf("最高分: %d\n", max);
    printf("最低分: %d\n", min);
    printf("\n成绩排名:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s: %d分\n", i + 1, names[i], scores[i]);
    }
}
```

### AI回复

1.  **头文件**：`stdio.h` 负责输入输出；`string.h` 提供 `strcpy` 字符串复制；`stdlib.h` 用于 `system` 修改控制台编码。
2.  上方是 5 个自定义函数声明，提前告诉编译器后续有这 5 个方法。
3.  **main函数**：修改控制台为 UTF-8 编码，定义姓名二维数组、分数数组，依次执行：录入人数 → 录入学生信息 → 成绩统计 → 冒泡排序 → 打印结果。
4.  **input_student_count**：输入学生总数，限定范围 1~100，非法数值循环重输。
5.  **input_student_info**：循环逐个录入姓名和成绩，成绩强制限制 0~100，错误输入重复录入。
6.  **calculate_stats**：遍历分数数组，累加总分、筛选最高分与最低分，计算平均分。
7.  **sort_students**：冒泡降序排列分数，分数交换时同步拷贝交换对应学生姓名。
8.  **print_results**：输出平均分、极值、排名列表。

### 个人落地总结

梳理清楚原有完整业务流程，确定重构不能删减任何功能，所有原有输入校验、统计、排序逻辑全部保留，作为 V2 重构基准。

---

## 第2轮：重构初稿代码缺陷审查

### 我的提问

帮忙审查这份初步改造后的成绩代码，从代码冗余、魔法数字、工程规范、程序潜在隐患四个方向列出全部问题。

> 说明：初稿就是上方原版单文件代码

### AI回复

1.  代码全部在单个 `.c` 文件，函数声明和实现写在一起，不符合 C 工程多文件开发规范，无法复用函数。
2.  大量魔法数字：`100`、`20`、`0`、`100` 零散分布，修改容量或分数范围需要多处改动，极易出错。
3.  最高分初始 `0`、最低分初始 `100` 写死在代码中，没有统一常量，代码可读性差。
4.  成绩、人数校验的判断条件重复书写，冗余代码多。
5.  编译无警告参数，隐藏潜在语法、边界隐患。

### 个人落地总结

采纳全部优化建议：拆分 `.h` 头文件与 `.c` 源文件，所有固定数值改用宏定义集中管理，后续按照规范完成分文件改造。

---

## 第3轮：生成全套边界测试用例

### 我的提问

结合本成绩系统功能，设计全场景边界测试用例，包含人数临界、非法输入、分数临界、特殊同分场景，标注输入内容与预期运行结果。

### AI回复

1.  **人数边界**：`n=1` 最小合法、`n=100` 最大合法；输入 `0`、负数、`101` 均拦截重输。
2.  **分数边界**：`-5`、`105` 非法报错重输；`0`、`100` 为合法临界值正常入库。
3.  **全员同分**：多名学生分数完全一致，排序后原有顺序保持不变。
4.  **混合极值**：同时存在 `0` 分与 `100` 分，统计最高分、最低分、平均分计算无误。

### 个人落地总结

将用例整理成表格写入 `README.md`，开发完成后逐项手动测试，验证程序容错能力。

---

## 第4轮：标准化代码审查清单输出

### 我的提问

生成三列表格形式C代码审查清单：规范项、现存问题、优化方案，适配本项目。

### AI回复

| 规范项 | 现存问题 | 优化方案 |
| :--- | :--- | :--- |
| 常量管理 | 多处硬编码数字 | 头文件用 `#define` 统一宏定义 |
| 工程结构 | 单文件耦合 | 头文件放声明，源文件放实现，main 单独拆分 |
| 代码冗余 | 分数、人数区间重复书写 | 统一引用宏常量消除重复代码 |
| 编译规范 | 默认编译无警告 | 编译添加 `-Wall -Wextra`，排查隐患 |

### 个人落地总结

对照清单逐条整改代码，完成宏替换 + 多文件拆分，严格使用带警告参数编译。

---

## 第5轮：V1原版 & V2重构版对比分析

### 我的提问

对比V1原始单文件代码与V2模块化重构代码，从结构、代码冗余、可维护性、优缺点做详细对比。

### AI回复

#### V1旧版缺点

1.  所有代码耦合在单个文件，声明、实现、主函数混杂，不能单独引用函数。
2.  魔法数字遍布代码，修改参数需要全文档查找替换，维护成本高。
3.  重复常量代码多，拓展新功能困难。

#### V2新版优化

1.  **工程拆分**：`include/student.h`（宏+声明）、`src/student.c`（函数实现）、`src/main.c`（入口），原代码存入 `origin_main.c` 备份。
2.  全局常量宏定义，修改参数只改头文件一处。
3.  冗余代码清除，编译开启警告，代码健壮性提升。

#### 小弊端

文件数量增多，新手浏览代码需要切换多个文件。

### 个人落地总结

整体重构收益远大于缺点，功能与原版完全一致无改动，实现实质性工程化升级，满足课程 V2.0 重构要求。