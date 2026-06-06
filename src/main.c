#include "student.h"
#include <stdlib.h>

int main(void)
{
    system("chcp 65001 >nul");

    char names[MAX_STU_NUM][NAME_LEN];
    int scores[MAX_STU_NUM];
    int sum = 0, max, min;
    float avg;

    int n = input_student_count();
    input_student_info(names, scores, n);
    calculate_stats(scores, n, &sum, &avg, &max, &min);
    sort_students(names, scores, n);
    print_results(names, scores, n, avg, max, min);

    return 0;
}