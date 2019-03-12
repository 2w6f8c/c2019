#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* DB_PATH = "data.db";

typedef struct good {
    unsigned long id;  // ��1��ʼ��0��ʾ�����ݱ�ɾ��
    char name[20];     // ����
    int size;          // �ͺ� 0��small��1��medium��2��large
    int count;         // ���
} good;

good* goods = NULL;
unsigned long dataCount = 0L;  // ��������
unsigned long goodsLen = 0L;   // goods����
unsigned long lastIndex = 0L;  // ���һ�����ݵ����� + 1
unsigned long maxId = 0L;

void initConsole();          // ���ÿ���̨��ʽ
void readData();             // ���ļ��ж�ȡ����
void showMenu();             // �˵�
void printGood(good* good);  // ��ӡ����
void list();                 // ��ʾ�����б�
void input();                // ���Ԫ��
void output();               // ɾ��������Ԫ��
void dumpExit();             // �־û����ݲ��˳�����
void expandList();           // ����

int main() {
    initConsole();
    readData();
    showMenu();
    return 0;
}

void initConsole() { system("color 2"); }

void readData() {
    FILE* fp;
    if (!(fp = fopen(DB_PATH, "r"))) {
        printf("error open file %s\n", DB_PATH);
        return;
    }
    fscanf(fp, "%d", &dataCount);
    // ���������Ŀռ䣬Ϊ���Ԫ����׼��
    if (!(goods = (good*)malloc(2 * dataCount * sizeof(good)))) {
        printf("�����ڴ�ռ�ʧ�ܣ������˳���");
        return;
    }
    goodsLen = 2 * dataCount;
    lastIndex = dataCount;
    for (int i = 0; i < dataCount; i++) {
        fscanf(fp, "%d%s%d%d", &goods[i].id, goods[i].name, &goods[i].size,
               &goods[i].count);
    }
    maxId = goods[dataCount - 1].id;
    fclose(fp);
}

void printGood(good* good) {
    char size[10];
    switch (good->size) {
        case 0:
            strcpy(size, "small");
            break;
        case 1:
            strcpy(size, "medium");
            break;
        case 2:
            strcpy(size, "large");
            break;
        default:
            break;
    }
    printf("| %-6d| %-20s| %-10s| %-8d|\n", good->id, good->name, size,
           good->count);
}

void list() {
    system("cls");
    printf("+-------+---------------------+-----------+---------+\n");
    printf("| id    | name                | size      | count   |\n");
    printf("+-------+---------------------+-----------+---------+\n");
    for (int i = 0; i < lastIndex; i++) {
        if (goods[i].id) printGood(&goods[i]);
    }
    printf("+-------+---------------------+-----------+---------+\n");
    printf("press [m] to return to menu\n");
    char ch;
    while (ch = getch()) {
        if (ch == 'm') {
            showMenu();
            return;
        }
    }
}

void input() {
    system("cls");
    char name[20];
    int size = 0;
    int count = 0;
    good* tg;
    printf("����������:\n");
    printf("1.�������ƣ�");
    scanf("%s", name);
    do {
        printf("�������ͺţ�0��ʾС��1��ʾ�У�2��ʾ�󣩣�");
        scanf("%d", &size);
    } while (!(size == 0 || size == 1 || size == 2));
    do {
        printf("������������");
        scanf("%d", &count);
    } while (count < 0);
    if (goodsLen == lastIndex) expandList();
    tg = &goods[lastIndex++];
    tg->id = ++maxId;
    strcpy(tg->name, name);
    tg->size = size;
    tg->count = count;
    dataCount++;
    printf("��ӳɹ���\n");
    printf("press [m] to return to menu\n");
    printf("press [c] to continue");
    char ch;
    while (ch = getch()) {
        if (ch == 'm') showMenu();
        if (ch == 'c') input();
    }
}

void output() {
    system("cls");
    int success = 0;
    unsigned long id;
    do {
        printf("������Ҫ����Ļ����id��");
        scanf("%d", &id);
    } while (id < 0);
    for (int i = 0; i < lastIndex; i++) {
        if (id == goods[i].id) {
            success = 1;
            char size[10];
            switch (goods[i].size) {
                case 0:
                    strcpy(size, "small");
                    break;
                case 1:
                    strcpy(size, "medium");
                    break;
                case 2:
                    strcpy(size, "large");
                    break;
                default:
                    break;
            }
            goods[i].id = 0;
            dataCount--;
            printf("����ɹ�!���������ϢΪ��\n");
            printf("name: %s\t size: %s\t count: %d\n", goods[i].name, size,
                   goods[i].count);
        }
    }
    if (!success) printf("δ�ҵ�idΪ%d�Ļ���\n", id);
    printf("press [m] to return to menu\n");
    printf("press [c] to continue");
    char ch;
    while (ch = getch()) {
        if (ch == 'm') showMenu();
        if (ch == 'c') output();
    }
}

void dumpExit() {
    // dump
    FILE* fp;
    if (!(fp = fopen(DB_PATH, "w+"))) {
        printf("error open file %s\n", DB_PATH);
        return;
    }
    fprintf(fp, "%d\n", dataCount);
    for (int i = 0; i < lastIndex; i++) {
        // id��Ϊ0˵���ü�¼û�б�ɾ��
        if (goods[i].id) {
            fprintf(fp, "%d %s %d %d\n", goods[i].id, goods[i].name,
                    goods[i].size, goods[i].count);
        }
    }
    fclose(fp);

    // exit
    if (goods) free(goods);
    goods = NULL;
    exit(0);
}

void showMenu() {
    system("cls");
    char ch;
    printf("[1] ��ʾ����б�\n");
    printf("[2] ���\n");
    printf("[3] ����\n");
    printf("[q] �˳�����\n");

    while (ch = getch()) {
        switch (ch) {
            case '1':
                list();
                break;
            case '2':
                input();
                break;
            case '3':
                output();
                break;
            case 'q':
                dumpExit();
                break;
            default:
                break;
        }
    }
}

void expandList() {
    good* newGoods;
    if (!(newGoods = (good*)malloc(2 * goodsLen * sizeof(good)))) {
        printf("����ʱ�����ڴ�ռ�ʧ�ܣ������˳���");
        return;
    }
    for (int i = 0; i < dataCount; i++) {
        newGoods[i].id = goods[i].count;
        strcpy(newGoods[i].name, goods[i].name);
        newGoods[i].size = goods[i].size;
        newGoods[i].count = goods[i].count;
    }
    free(goods);
    goods = newGoods;
    newGoods = NULL;
    goodsLen = 2 * goodsLen;
}
