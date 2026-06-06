#include "student.h"
#include <string.h>

// 输入校验学生人数
int input_student_count(void)
{
    int n;
    printf("请输入学生人数: ");
    scanf("%d", &n);
    while (n <= 0 || n > MAX_STU_NUM)
    {
        printf("人数不合法，请重新输入(1-%d): ", MAX_STU_NUM);
        scanf("%d", &n);
    }
    return n;
}

// 批量录入学生姓名+成绩并校验分数
void input_student_info(char names[][NAME_LEN], int scores[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("请输入第%d个学生的姓名: ", i + 1);
        scanf("%s", names[i]);
        printf("请输入第%d个学生的成绩: ", i + 1);
        scanf("%d", &scores[i]);
        while (scores[i] < SCORE_MIN || scores[i] > SCORE_MAX)
        {
            printf("成绩不合法，请重新输入(%d-%d): ", SCORE_MIN, SCORE_MAX);
            scanf("%d", &scores[i]);
        }
    }
}

// 统计总分、平均分、最高最低分
void calculate_stats(int scores[], int n, int *sum, float *avg, int *max, int *min)
{
    *sum = 0;
    *max = SCORE_MIN;
    *min = SCORE_MAX;
    for (int i = 0; i < n; i++)
    {
        *sum += scores[i];
        if (scores[i] > *max)
            *max = scores[i];
        if (scores[i] < *min)
            *min = scores[i];
    }
    *avg = (float)(*sum) / n;
}

// 冒泡降序排序，同步交换姓名与分数
void sort_students(char names[][NAME_LEN], int scores[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (scores[j] < scores[j + 1])
            {
                // 交换分数
                int tmp_sc = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tmp_sc;

                // 交换姓名
                char tmp_name[NAME_LEN];
                strcpy(tmp_name, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tmp_name);
            }
        }
    }
}

// 打印统计数据+排名
void print_results(char names[][NAME_LEN], int scores[], int n, float avg, int max, int min)
{
    printf("\n===== 成绩统计结果 =====\n");
    printf("平均分: %.2f\n", avg);
    printf("最高分: %d\n", max);
    printf("最低分: %d\n", min);
    printf("\n成绩排名:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s: %d分\n", i + 1, names[i], scores[i]);
    }
}