#include <stdio.h>
#include "finance_functions.h"

extern const char* const CATEGORY[];
extern const int kind;
extern finance_node* finance_head;
extern int lenth_node;

const char* const CATEGORY[] = {"收入", "餐饮", "水果", "零食", "日用", "交通", "化妆", "其他"};
const int kind = sizeof(CATEGORY)/sizeof(char*);
finance_node* finance_head = NULL;
int lenth_node = 0;

int main(){
    finance_function(1234);
    return 0;
}

void finance_function(int user_id){

    //将用户的数据（本地文件中的）初始化到链表中去
    initialize_linklist(user_id);

    //菜单列表
    main_list:
    printf("1. 添加新的收入/支出记录。\n");
    printf("2. 修改收入/支出记录。\n");
    printf("3. 删除收入/支出记录。\n");
    printf("4. 查看年/月/日财务统计信息。\n");
    printf("5. 返回主界面。\n");
    printf("请输入选项前面对应的数字。\n");

    int choice = 0;
    if( (scanf("%d", &choice)) != 1){
        fflush(stdin);
        printf("输入有误！请重新输入。\n");
        goto main_list;
    }

    switch(choice){
        case 1 : new_finance_record(user_id); fflush(stdin);goto main_list;
        case 2 : update_finance_record(user_id); fflush(stdin);goto main_list;
        case 3 : delete_finance_record(user_id);fflush(stdin);goto main_list;
        case 4 : finance_statistics();fflush(stdin);goto main_list;
        case 5 : return;
#ifdef LOCAL
        case 6 : show_all_finance_node();fflush(stdin);goto main_list;
#endif
        default : printf("输入有误！请重新输入。\n");goto main_list;break;
    }

}
//
//统计功能：分季度、月、日统计收入、支出，
// 以及各方面（衣食住行等）占比，并根据占比给出适当建议；计算个人所得税；用户根据月份等信息检索获得指定的数据；预算管理：规划当月预算，每日超额提醒以及总金额超额提醒（或超过80%）