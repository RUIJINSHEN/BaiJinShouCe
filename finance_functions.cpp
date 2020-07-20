#include <stdio.h>
#include <stdlib.h>
#include "finance_functions.h"
#include <string.h>

extern const int kind;
extern const char* CATEGORY[];
extern finance_node* finance_head;
extern int lenth_node;

/**
 * 此函数是财务管理中的添加收入/支出记录的功能函数
 * @param user_id
 */
void new_finance_record(int user_id){

    //先打开user_id对应的存储数据的文件 对应的文件名为user_id_finance.txt
    char file_name[20];
    sprintf(file_name, "%d%s", user_id, "_finance.txt");
    FILE* fp = NULL;
    //此函数的功能只是添加记录，所以用ab+打开文件
    fp = fopen(file_name, "ab+");
    if(fp == NULL){
        printf("文件打开失败！\n");
        return;
    }

    struct finance_data new_data;

    printf("待添加的项目是支出还是收入？支出输入0，收入输入1。\n");
    int choice1 = 0;
    int choice2 = 0;
    while( (scanf("%d", &choice1)) != 1 || choice1<0 || choice1>1){
        printf("输入有误，请重新输入！\n");
        fflush(stdin);
    }

    switch(choice1){
        case 0 :
            //提示用户输入
            printf("请按照：“年.月.日 花费项目 金额”的格式输入。\n");
            while((scanf("%d.%d.%d %s %lf", &(new_data.year), &(new_data.month), &(new_data.day),
                    new_data.name,&(new_data.value))) != 5 || new_data.year<=0 || new_data.month>12
                    || new_data.month<=0 || new_data.day<=0 ||new_data.day>31 || new_data.value<0) {
                fflush(stdin);
                printf("输入有误，请重新输入！\n");
            }
            //因为是支出，所以将value反号变成负数
            new_data.value = -new_data.value;

            printf("请从下面的选项中选择消费的类型。\n");
            //第一个是收入，所以i的初始化值为1，跳过收入
            for(int i = 1; i<kind; i++){
                printf("%d.%-7s", i, CATEGORY[i]);
                if(i%5==0){
                    printf("\n");
                }
            }
            printf("\n");

            while((scanf("%d", &choice2)) !=1 || choice2<=0 || choice2>(kind-1)){
                printf("输入有误，请重新输入！\n");
                fflush(stdin);
            }
            strcpy(new_data.category, CATEGORY[choice2]);
            //确认用户输入
            printf("你输入了：\n消费时间：%d.%d.%d 消费项目：%s 金额：%.2lf 消费类型：%s\n", new_data.year, new_data.month,
                    new_data.day, new_data.name,-new_data.value, new_data.category);
            if(fwrite(&new_data, sizeof(struct finance_data), 1, fp) == 1){
                printf("添加成功！\n");
            }
            insert_head_finance_node(new_data);
            break;
        case 1 :
            printf("请按照：”年.月.日 收入金额“的格式进行输入。\n");
            while((scanf("%d.%d.%d %lf", &(new_data.year), &(new_data.month), &(new_data.day),
                    &(new_data.value))) != 4 || new_data.value<0 || new_data.year<=0||new_data.month>12 ||
                    new_data.month<=0 || new_data.day<=0 ||new_data.day>31){
                printf("输入有误，请重新输入！\n");
                fflush(stdin);
            }
            strcpy(new_data.name, "void");
            strcpy(new_data.category, CATEGORY[0]);
            printf("你输入了：\n%d.%d.%d 收入%.2lf\n", new_data.year, new_data.month, new_data.day, new_data.value);
            if(fwrite(&new_data,sizeof(struct finance_data), 1, fp) == 1){
                printf("添加成功！\n");
            }
            insert_head_finance_node(new_data);
            break;
        default:break;
    }
    fclose(fp);
    return;
}

/**
 * 此函数用于修改已经存在的记录。
 * @param user_id
 */
void update_finance_record(int user_id){

    char file_name[20];
    sprintf(file_name, "%d%s", user_id, "_finance.txt");
    FILE* fp = NULL;
    fp = fopen(file_name, "wb");
    if(fp == NULL){
        printf("文件打开失败！\n");
        return;
    }

    show_all_finance_node();
    printf("输入记录前的序号以修改记录。\n");
    int lable_in = 0;
    while(scanf("%d", &lable_in) !=1 || lable_in<1 || lable_in > lenth_node){
        printf("输入有误！请重新输入。\n");
        fflush(stdin);
    }

    update_finance_node_by_lable(lable_in);
    write_all_linkedlist_to_file(fp);
    fclose(fp);
}

void update_finance_node_by_lable(int lable){

    finance_node* search = NULL;
    for(finance_node* beginning = finance_head; beginning != NULL; beginning = beginning->next){
        if(beginning->lable == lable){
            search = beginning;
        }
    }

    if(search == NULL){
        printf("No such element found.\n");
        return;
    }

    if(strcmp(search->data.category, CATEGORY[0]) ==0 ){
        printf("你选择的是：\n");
        show_finance_node_by_pointer(search);
        printf("请输入要修改的金额。\n");
        double new_value = 0;
        while(scanf("%lf", &new_value) !=1 || new_value<=0){
            printf("输入有误！请重新输入。\n");
            fflush(stdin);
        }
        search->data.value = new_value;
    }else{
        int choice2 =0;
        finance_data new_data = search->data;
        printf("你选择的是：\n");
        show_finance_node_by_pointer(search);
        printf("请按照：“年.月.日 花费项目 金额”的格式输入。\n");
        while((scanf("%d.%d.%d %s %lf", &(new_data.year), &(new_data.month), &(new_data.day),
                     new_data.name,&(new_data.value))) != 5 || new_data.year<=0 || new_data.month>12
              || new_data.month<=0 || new_data.day<=0 ||new_data.day>31 || new_data.value<0) {
            fflush(stdin);
            printf("输入有误，请重新输入！\n");
        }
        //因为是支出，所以将value反号变成负数
        new_data.value = -new_data.value;

        printf("请从下面的选项中选择消费的类型。\n");
        //第一个是收入，所以i的初始化值为1，跳过收入
        for(int i = 1; i<kind; i++){
            printf("%d.%-7s", i, CATEGORY[i]);
            if(i%5==0){
                printf("\n");
            }
        }
        printf("\n");

        while((scanf("%d", &choice2)) !=1 || choice2<=0 || choice2>(kind-1)){
            printf("输入有误，请重新输入！\n");
            fflush(stdin);
        }
        strcpy(new_data.category, CATEGORY[choice2]);
        //确认用户输入
        printf("你输入了：\n消费时间：%d.%d.%d 消费项目：%s 金额：%.2lf 消费类型：%s\n", new_data.year, new_data.month,
               new_data.day, new_data.name,new_data.value, new_data.category);
        printf("修改成功！\n");
        search->data = new_data;
    }
    return;
}

/**
 * 此函数用于删除某一条记录
 * @param user_id
 */
void delete_finance_record(int user_id){

    show_all_finance_node();
    printf("输入记录前的序号以删除记录。\n");
    int lable_in = 0;
    while(scanf("%d", &lable_in) !=1 || lable_in<1 || lable_in > lenth_node){
        printf("输入有误！请重新输入。\n");
        fflush(stdin);
    }

    char file_name[20];
    FILE* fp = NULL;

    printf("你选择的是：\n");
    show_finance_node_by_lable(lable_in);
    printf("是否确认删除？确认[y] 取消[n]\n");
    char confirm = 'n';
    fflush(stdin);
    scanf("%c", &confirm);
    switch(confirm){
        case 'y' :
        case 'Y' :

            sprintf(file_name, "%d%s", user_id, "_finance.txt");
            fp = fopen(file_name, "wb");
            if(fp == NULL){
                printf("文件打开失败！\n");
                return;
            }
            delete_finance_node_by_lable(lable_in);
            write_all_linkedlist_to_file(fp);
            break;
        case 'n' : break;
        case 'N' : break;
        default: break;
    }
    fclose(fp);
}

void finance_statistics(){

    statistics_menu:
    printf("1. 按年查看记录以及统计信息。\n");
    printf("2. 按月查看记录以及统计信息。\n");
    printf("3. 按日查看记录以及统计信息。\n");
    printf("4. 按时间段查看记录以及统计信息。\n");
    printf("5. 返回。\n");
    printf("请输入选项前面对应的数字。\n");

    int choice1 = 0;
    while(scanf("%d", &choice1) != 1 ){
        printf("输入有误！请重新输入。\n");
        fflush(stdin);
    }
    switch(choice1){
        case 1 : finance_statistics_by_year(); fflush(stdin); goto statistics_menu;
        case 2 : finance_statistics_by_month();fflush(stdin); goto statistics_menu;
        case 3 : finance_statistics_by_date();fflush(stdin); goto statistics_menu;
        case 4 : finance_statistics_by_period();fflush(stdin); goto statistics_menu;
        case 5 : return;
        default : fflush(stdin); goto statistics_menu;
    }

}

void finance_statistics_by_year(){
    printf("输入想要查看的年份。\n");
    int year_in = 0;
    while(scanf("%d", &year_in) !=1 || year_in<=0){
        printf("输入有误！请重新输入。\n");
        fflush(stdin);
    }
    char arg[10];
    sprintf(arg, "%d%s", year_in, "年");
    calculate_and_show_data(arg, year_in, 1, 1, year_in, 12, 31);
    return;
}

void finance_statistics_by_month(){
    printf("输入想要查看的月份，格式：“年.月”。\n");
    int year_in = 0;
    int month_in = 0;
    while(scanf("%d.%d", &year_in, &month_in) !=2 || year_in<=0 || month_in<=0 ||month_in>12){
        printf("输入有误！请重新输入。\n");
        fflush(stdin);
    }
    char arg[10];
    sprintf(arg, "%d.%d", year_in, month_in);
    calculate_and_show_data(arg, year_in, month_in, 1, year_in, month_in, 31);
    return;
}

void finance_statistics_by_date(){

    printf("输入想要查看的日期，格式：“年.月.日”。\n");
    int year_in = 0;
    int month_in = 0;
    int day_in = 0;
    while(scanf("%d.%d.%d", &year_in, &month_in, &day_in) !=3 || year_in<=0 || month_in<=0 ||
        month_in>12 || day_in<=0 || day_in>31){
        printf("输入有误！请重新输入。\n");
        fflush(stdin);
    }
    char arg[10];
    sprintf(arg, "%d.%d.%d", year_in, month_in, day_in);
    calculate_and_show_data(arg, year_in, month_in, day_in, year_in, month_in, day_in);
    return;
}

void finance_statistics_by_period(){
    printf("输入想要查看的时间段，格式：“起始年.起始月.起始日 终止年.终止月.终止日”。\n");
    int year_in1 = 0;
    int month_in1 = 0;
    int day_in1 = 0;
    int year_in2 = 0;
    int month_in2 = 0;
    int day_in2 = 0;
    while(scanf("%d.%d.%d %d.%d.%d", &year_in1, &month_in1, &day_in1, &year_in2, &month_in2, &day_in2) !=6 ||
        year_in1<=0 || month_in1<=0 || month_in1>12 || day_in1<=0 || day_in1>31
        || year_in2<=0 || month_in2<=0 || month_in2>12 || day_in2<=0 || day_in2>31){
        printf("输入有误！请重新输入。\n");
        fflush(stdin);
    }
    char arg[25];
    sprintf(arg, "%d.%d.%d~%d.%d.%d", year_in1, month_in1, day_in1, year_in2, month_in2, day_in2);
    calculate_and_show_data(arg, year_in1, month_in1, day_in1, year_in2, month_in2, day_in2);
    return;
}


/**
 * 此函数用于统计并显示符合条件的记录，两边的端点是包括在内的。
 * 默认输入的日期是合法的 且 start与end是同一天，或者start在end之前
 */
void calculate_and_show_data(char* argu, int start_year, int start_month, int start_day, int end_year, int end_month, int end_day){
    //遍历链表中所有的元素，找出符合条件的记录，输出并统计
    value_and_kind all_statistics[kind-1];
    double total_value = 0;
    double income = 0;
    int counter = 0;

    for(int i = 0; i<kind-1; i++){
        all_statistics[i].category = CATEGORY[i+1];
    }

    for(finance_node* beginning = finance_head; beginning != NULL; beginning = beginning->next){

        if(date_cmp(beginning->data.year, beginning->data.month, beginning->data.day,
                start_year, start_month, start_day) >=0 && date_cmp(beginning->data.year,
                beginning->data.month, beginning->data.day, end_year, end_month, end_day) <=0){
            counter++;
            if(counter == 1){
                printf("%-5s %-10s %-20s %-12s %-6s\n","序号","日期", "项目", "金额", "类型");
            }
            show_finance_node_by_pointer(beginning);
            for(int i = 1; i<kind; i++){
                if(strcmp(beginning->data.category, CATEGORY[i]) == 0){
                    (all_statistics[i-1]).value += (-beginning->data.value);
                    total_value += (-beginning->data.value);
                    break;
                }
            }
            if(strcmp(beginning->data.category, CATEGORY[0]) == 0){
                income += beginning->data.value;
            }
        }

    }

    for(int i = 0; i<kind-1; i++){
        (all_statistics[i]).percentage = (all_statistics[i]).value/total_value;
    }

    //排序并输出统计结果
    printf("\n在%s：\n", argu);
    printf("收入：%.2lf\n", income);
    printf("支出：%.2lf\n", total_value);
    printf("其中各项占比：\n");

    sort_statistics(all_statistics, kind-1);
    show_statistics(all_statistics, kind-1);

}

void show_statistics(value_and_kind* all_statistics, int len){
    printf("%-6s%-15s%s","类别", "金额","占总支出百分比\n");
    for(int i = 0; i<len; i++){
        printf("%-6s%-10.2lf%.2lf%c\n", all_statistics[i].category, all_statistics[i].value, all_statistics[i].percentage*100, '%');
    }
    printf("\n");
}

/**
 * 以降序排序
 * @param ori
 */
void sort_statistics(struct value_and_kind* ori, int len){
    for(int i = 0; i<len-1; i++){
        value_and_kind* tem = &(ori[i]);
        for(int j = i; j<len; j++){
            if(ori[j].value>tem->value){
                tem = &(ori[j]);
            }
        }
        //交换ori[i]与tem
        value_and_kind swap = ori[i];
        ori[i] = *tem;
        *tem = swap;
    }
}

/**
 *
 * @return 如果日期1在日期2之前，返回-1，日期1与日期2是同一天返回0，日期1在日期2之后返回1；
 */
int date_cmp(int year1, int month1, int day1, int year2, int month2, int day2){
    if(year1<year2){
        return -1;
    }else if(year1 == year2 && month1<month2){
        return -1;
    }else if(year1 == year2 && month1 == month2 && day1<day2){
        return -1;
    }else if(year1 == year2 && month1 == month2 && day1 == day2) {
        return 0;
    }else{
        return 1;
    }
}

//从本地文件中读取用户的收入/支出记录
void initialize_linklist(int user_id){

    char file_name[20];
    sprintf(file_name, "%d%s", user_id, "_finance.txt");
    FILE* fp = NULL;
    //此函数的功能只是读取记录，所以用rb打开文件
    fp = fopen(file_name, "rb");
    if(fp == NULL){
        fp = fopen(file_name, "wb+");
        if(fp == NULL){
            printf("文件打开失败！\n");
        }
        return;
    }

    struct finance_data data_in;
    while(fread(&data_in, sizeof(struct finance_data), 1, fp) == 1){
        insert_head_finance_node(data_in);
    }

    fclose(fp);

    return;
}

void insert_head_finance_node(struct finance_data data){
    finance_node* newNode = (finance_node*)malloc(sizeof(finance_node));
    if(newNode == NULL){
        printf("Malloc fail.\n");
        return;
    }
    newNode->data = data;

    newNode->lable = 1;
    newNode->next = finance_head;
    finance_head = newNode;

    int counter = 1;
    for(finance_node* beginning = finance_head; beginning != NULL; counter++){
        beginning->lable = counter;
        beginning = beginning->next;
    }
    lenth_node++;
}

void delete_finance_node_by_lable(int lable){
    finance_node* beginning = finance_head;
    if(beginning == NULL){
        printf("The list is empty.");
        return;
        }

    if(finance_head->lable == lable){
        finance_node* tem = finance_head;
        finance_head = finance_head->next;
        free(tem);
        }

    while(beginning->next != NULL){
        if(beginning->next->lable == lable){
            finance_node* temp = beginning->next;
            beginning->next = beginning->next->next;
            free(temp);
            break;
        }
        beginning = beginning->next;
    }
    return;
}

void write_all_linkedlist_to_file(FILE* fp){
    for(finance_node* beginning = finance_head; beginning != NULL; beginning = beginning->next){
        fwrite(&(beginning->data), sizeof(struct finance_data), 1, fp);
    }
}

void show_all_finance_node(){
    printf("%-5s %-10s %-20s %-12s %-6s\n","序号","日期", "项目", "金额", "类型");
    for(finance_node* beginning = finance_head; beginning != NULL; beginning = beginning->next){
        char date[10];
        sprintf(date,"%d.%d.%d", beginning->data.year, beginning->data.month, beginning->data.day);

        if( (strcmp(beginning->data.category, CATEGORY[0])) == 0){
            printf("%-5d %-10s %-20s %-10.2lf\n", beginning->lable, date, "收入", beginning->data.value);
        }else{
            printf("%-5d %-10s %-20s %-10.2lf %-6s\n", beginning->lable, date, beginning->data.name, beginning->data.value, beginning->data.category);
        }
    }
}
void show_finance_node_by_lable(int lable){
    finance_node* beginning = finance_head;
    for(;beginning !=NULL; beginning = beginning->next) {
        if(beginning->lable == lable){
            show_finance_node_by_pointer(beginning);
        }
    }
    return;
}
void show_finance_node_by_pointer(finance_node* node){
    char date[10];
    sprintf(date,"%d.%d.%d", node->data.year, node->data.month, node->data.day);

    if( (strcmp(node->data.category, CATEGORY[0])) == 0){
        printf("%-5d %-10s %-20s %-10.2lf\n", node->lable, date, "收入", node->data.value);
    }else{
        printf("%-5d %-10s %-20s %-10.2lf %-6s\n", node->lable, date, node->data.name,
                node->data.value, node->data.category);
    }
}

