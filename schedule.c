#include <stdio.h>
#include "schedule_functions.h"

void function(int user_id);
int main() {
    function(1);
    return 0;
}
void function(int user_id){
    u_thing data;
    char thing[200];

    int choice = 7;
    int choice2 = 1;
    int a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char filename[20];
    sprintf(filename, "%d%s", user_id, "_schedule.txt");

    schedule_list:
    printf("******�ճ̹���******\n");
    printf("1.�����ճ�\n");
    printf("2.ɾ���ճ�\n");
    printf("3.�޸��ճ�\n");

    printf("4.�����ճ�\n");
    printf("5.�ճ�һ��\n");
    printf("6.��������\n");
    printf("7.��ʾ\n");
    printf("your choice:\n");

    scanf("%d", &choice);
    fflush(stdin);
    while (choice < 0 || choice > 7) {
        if (choice < 0 || choice > 7) {
            printf("��������Чֵ!\n");
            goto schedule_list;
        }
    }
    switch (choice) {//**��ת����
        case 1:
            printf("������������ճ����������̶ȣ�0-4��4Ϊ����������ꡢ�¡��ա�ʱ���֡��룺\n");
            scanf("%s%d%d%d%d%d%d%d", data.thing, &data.degree,
                  &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.second);
            while (data.degree < 0 || data.degree > 4 || data.year < 0 || data.month < 0 || data.month > 12 ||
                   data.day < 0 || data.day > a[data.month - 1] || data.hour < 0 || data.hour > 24 ||
                   data.minute < 0 || data.minute > 60 || data.second < 0 || data.second > 60) {
                printf("��������Чֵ��\n");
                fflush(stdin);
                break;
            }
            if(!(data.degree < 0 || data.degree > 4 || data.year < 0 || data.month < 0 || data.month > 12 ||
               data.day < 0 || data.day > a[data.month - 1] || data.hour < 0 || data.hour > 24 ||
               data.minute < 0 || data.minute > 60 || data.second < 0 || data.second > 60)){
                insert_data(user_id, &data);
            }
            goto schedule_list;
        case 2:
            printf("��������Ҫɾ�����ճ�����\n");
            scanf("%s", thing);
            del_data(user_id, thing);
            goto schedule_list;
        case 3:
            printf("����������Ҫ�ı���ճ�����\n");
            scanf("%s", thing);
            printf("�������޸ĺ���ճ����������̶ȣ�0-4��4Ϊ����������ꡢ�¡��ա�ʱ���֡��룺\n");
            scanf("%s%d%d%d%d%d%d%d", data.thing, &data.degree,
                  &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.second);
            while (data.degree < 0 || data.degree > 4 || data.year < 0 || data.month < 0 || data.month > 12 ||
                   data.day < 0 || data.day > a[data.month - 1] || data.hour < 0 || data.hour > 24 ||
                   data.minute < 0 || data.minute > 60 || data.second < 0 || data.second > 60) {
                printf("��������Чֵ��\n");
                fflush(stdin);
                goto schedule_list;
            }
            update_data(user_id, thing, &data);
            goto schedule_list;
        case 4:
            printf("����������Ҫ���ҵ��ճ�����\n");
            scanf("%s", thing);
            lookup_data(user_id, thing);
            goto schedule_list;
        case 5:
            handle_show(user_id);
            goto schedule_list;
        case 6:
            remind_system(user_id);
            goto schedule_list;
        case 7:
            print_schedule(user_id);
            break;
        default:
            printf("��������Чֵ��\n");
            goto schedule_list;
    }
    }







