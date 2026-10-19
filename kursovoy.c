#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>   
#include <windows.h>  
#define N 70
#define UCL 61.93
#define MIN_X 0
#define MAX_X 100
#define NORM_MIN 30
#define NORM_MAX 55
double calculate_Q(double x) {
    if (x < 30) {
        return 3.0 * (x - 30.0) + 10.0;
    }
    else if (x >= 30 && x <= 55) {
        double inside_sqrt = x - 42.5 + 12.0;
        if (inside_sqrt < 0) return 0;
        return 2.0 * sqrt(inside_sqrt) + 45.0;
    }
    else {
        return (pow(x - 55.0, 2) / 6.0) + 55.0;
    }
}
int compare_doubles(const void* a, const void* b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}
double calculate_median(double arr[], int n) {
    double* sorted_arr = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) sorted_arr[i] = arr[i];
    qsort(sorted_arr, n, sizeof(double), compare_doubles);
    double median;
    if (n % 2 == 0) {
        median = (sorted_arr[n / 2 - 1] + sorted_arr[n / 2]) / 2.0;
    }
    else {
        median = sorted_arr[n / 2];
    }
    free(sorted_arr);
    return median;
}
double calculate_mean(double arr[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    printf("=== ВАРИАНТ 15: Мониторинг реактора ===\n\n");
    printf("--- 5. Контрольный пример ---\n");
    double control_x = 52.50;
    double control_q = calculate_Q(control_x);
    printf("X = %.2f%% -> Q = %.2f (Ожидается: 54.38)\n", control_x, control_q);
    if (fabs(control_q - 54.38) < 0.01) {
        printf("Тест ПРОЙДЕН.\n\n");
    }
    else {
        printf("Тест НЕ ПРОЙДЕН (проверьте формулы)!\n\n");
    }
    double X[N];
    double Q[N];
    printf("--- Генерация данных (N=%d) и расчёт Q ---\n", N);
    for (int i = 0; i < N; i++) {
        X[i] = (double)(rand() % 1001) / 10.0;
        Q[i] = calculate_Q(X[i]);
    }
    printf("\n--- 2. Оперативный контроль (UCL = %.2f) ---\n", UCL);
    int deviations_count = 0;
    for (int i = 0; i < N; i++) {
        if (Q[i] > UCL) {
            printf("ВНИМАНИЕ! Отклонение: X=%.2f, Q=%.2f > UCL\n", X[i], Q[i]);
            deviations_count++;
        }
    }
    if (deviations_count == 0) {
        printf("Отклонений не обнаружено. Система в норме.\n");
    }
    else {
        printf("Обнаружено отклонений: %d\n", deviations_count);
    }
    int start_idx = 6;
    int end_idx = 36;
    int count_stat = end_idx - start_idx + 1;
    double* subset = (double*)malloc(count_stat * sizeof(double));
    for (int i = 0; i < count_stat; i++) {
        subset[i] = Q[start_idx + i];
    }
    printf("\n--- 3. Статистический анализ Q[%d...%d] ---\n", start_idx, end_idx);
    double mean_val = calculate_mean(subset, count_stat);
    double median_val = calculate_median(subset, count_stat);
    printf("Среднее значение: %.4f\n", mean_val);
    printf("Медиана:          %.4f\n", median_val);
    free(subset);
    printf("\n--- 4. Дополнительное задание ---\n");
    printf("(Задание не указано в варианте, вывод пропущен)\n");

    return 0;
}