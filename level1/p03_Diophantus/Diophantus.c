#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int age;
    //��Ȼ������12*7�ı�������ʵ����12*7�꣬�ٶ�ʹ��������¼��
    const int step = 12 * 7;

    for (i = 1;; i++) {
        age = i * step;
        if (age / 6 + age / 12 + age / 7 + 5 + age / 2 + 4 == age) {
            printf("age: %d\n", age);
            break;
        }
    }

    system("pause");
    return 0;
}
