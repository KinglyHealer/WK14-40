/*
 * ============================================================================
 *  说明: 以下为重构后的函数化代码，原始代码已封存于本文件末尾注释块中
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------- 函数声明 ---------- */
int  input_student_count(void);
void input_student_info(char names[][20], int scores[], int n);
void calculate_stats(int scores[], int n, int *sum, float *avg, int *max, int *min);
void sort_students(char names[][20], int scores[], int n);
void print_results(char names[][20], int scores[], int n, float avg, int max, int min);

/* ---------- 主函数（重构后） ---------- */
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


/*
 * ============================================================================
 *  【原始代码存档】以下为重构前未拆分的完整代码，全部逻辑堆砌在main中
 *  保留此注释块用于新旧代码对照，展示重构修改过程
 * ============================================================================
 *
 * #include <stdio.h>
 * #include <string.h>
 * #include <stdlib.h>
 *
 * int main() {
 *     system("chcp 65001"); // 将控制台代码页切换为 UTF-8
 *     // 1. 定义变量
 *     int n, i, j;
 *     char names[100][20];
 *     int scores[100];
 *     int sum = 0, max = 0, min = 100;
 *     float avg;
 *
 *     // 2. 输入学生人数
 *     printf("请输入学生人数: ");
 *     scanf("%d", &n);
 *     while (n <= 0 || n > 100) {
 *         printf("人数不合法，请重新输入(1-100): ");
 *         scanf("%d", &n);
 *     }
 *
 *     // 3. 输入每个学生的姓名和成绩
 *     for (i = 0; i < n; i++) {
 *         printf("请输入第%d个学生的姓名: ", i+1);
 *         scanf("%s", names[i]);
 *         printf("请输入第%d个学生的成绩: ", i+1);
 *         scanf("%d", &scores[i]);
 *         while (scores[i] < 0 || scores[i] > 100) {
 *             printf("成绩不合法，请重新输入(0-100): ");
 *             scanf("%d", &scores[i]);
 *         }
 *     }
 *
 *     // 4. 计算总分、平均分、最高分、最低分
 *     for (i = 0; i < n; i++) {
 *         sum += scores[i];
 *         if (scores[i] > max) max = scores[i];
 *         if (scores[i] < min) min = scores[i];
 *     }
 *     avg = (float)sum / n;
 *
 *     // 5. 按成绩从高到低排序
 *     for (i = 0; i < n-1; i++) {
 *         for (j = 0; j < n-1-i; j++) {
 *             if (scores[j] < scores[j+1]) {
 *                 int temp_score = scores[j];
 *                 scores[j] = scores[j+1];
 *                 scores[j+1] = temp_score;
 *
 *                 char temp_name[20];
 *                 strcpy(temp_name, names[j]);
 *                 strcpy(names[j], names[j+1]);
 *                 strcpy(names[j+1], temp_name);
 *             }
 *         }
 *     }
 *
 *     // 6. 输出结果
 *     printf("\n===== 成绩统计结果 =====\n");
 *     printf("平均分: %.2f\n", avg);
 *     printf("最高分: %d\n", max);
 *     printf("最低分: %d\n", min);
 *     printf("\n成绩排名:\n");
 *     for (i = 0; i < n; i++) {
 *         printf("%d. %s: %d分\n", i+1, names[i], scores[i]);
 *     }
 *
 *     return 0;
 * }
 *
 * ============================================================================
 */