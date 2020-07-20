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
    printf("******日程管理******\n");
    printf("1.增添日程\n");
    printf("2.删除日程\n");
    printf("3.修改日程\n");

    printf("4.查找日程\n");
    printf("5.日程一览\n");
    printf("6.临期提醒\n");
    printf("7.显示\n");
    printf("your choice:\n");

    scanf("%d", &choice);
    fflush(stdin);
    while (choice < 0 || choice > 7) {
        if (choice < 0 || choice > 7) {
            printf("请输入有效值!\n");
            goto schedule_list;
        }
    }
    switch (choice) {//**跳转问题
        case 1:
            printf("请输入增添的日程名、紧急程度（0-4，4为最紧急）、年、月、日、时、分、秒：\n");
            scanf("%s%d%d%d%d%d%d%d", data.thing, &data.degree,
                  &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.second);
            while (data.degree < 0 || data.degree > 4 || data.year < 0 || data.month < 0 || data.month > 12 ||
                   data.day < 0 || data.day > a[data.month - 1] || data.hour < 0 || data.hour > 24 ||
                   data.minute < 0 || data.minute > 60 || data.second < 0 || data.second > 60) {
                printf("请输入有效值！\n");
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
            printf("请输入想要删除的日程名：\n");
            scanf("%s", thing);
            del_data(user_id, thing);
            goto schedule_list;
        case 3:
            printf("请输入你想要改变的日程名：\n");
            scanf("%s", thing);
            printf("请输入修改后的日程名、紧急程度（0-4，4为最紧急）、年、月、日、时、分、秒：\n");
            scanf("%s%d%d%d%d%d%d%d", data.thing, &data.degree,
                  &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.second);
            while (data.degree < 0 || data.degree > 4 || data.year < 0 || data.month < 0 || data.month > 12 ||
                   data.day < 0 || data.day > a[data.month - 1] || data.hour < 0 || data.hour > 24 ||
                   data.minute < 0 || data.minute > 60 || data.second < 0 || data.second > 60) {
                printf("请输入有效值！\n");
                fflush(stdin);
                goto schedule_list;
            }
            update_data(user_id, thing, &data);
            goto schedule_list;
        case 4:
            printf("请输入你想要查找的日程名：\n");
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
            printf("请输入有效值！\n");
            goto schedule_list;
    }
    }







