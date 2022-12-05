#include <stdio.h>
#include <time.h>

int main() {
    // Переменная для системного времени
    long int s_time;
    // Указатель на структуру с локальным временем
    struct tm *m_time;
    // Строка для сохранения преобразованного времени
    char str_t[128] = "";

    // Считываем системное время
    s_time = time(NULL);
    // Преобразуем системное время в локальное
    m_time = localtime(&s_time);

    // Преобразуем локальное время в текстовую строку
    strftime(str_t, 128, "Date:  %X", m_time);

    // Выводим строку в консоль
    printf("%s\n",str_t);
    return 0;
}
