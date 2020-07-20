#include <stdio.h>
#include <stdlib.h>
#include "finance_functions.h"
#include <string.h>

extern const int kind;
extern const char* CATEGORY[];
extern finance_node* finance_head;
extern int lenth_node;

/**
 * �˺����ǲ�������е��������/֧����¼�Ĺ��ܺ���
 * @param user_id
 */
void new_finance_record(int user_id){

    //�ȴ�user_id��Ӧ�Ĵ洢���ݵ��ļ� ��Ӧ���ļ���Ϊuser_id_finance.txt
    char file_name[20];
    sprintf(file_name, "%d%s", user_id, "_finance.txt");
    FILE* fp = NULL;
    //�˺����Ĺ���ֻ����Ӽ�¼��������ab+���ļ�
    fp = fopen(file_name, "ab+");
    if(fp == NULL){
        printf("�ļ���ʧ�ܣ�\n");
        return;
    }

    struct finance_data new_data;

    printf("����ӵ���Ŀ��֧���������룿֧������0����������1��\n");
    int choice1 = 0;
    int choice2 = 0;
    while( (scanf("%d", &choice1)) != 1 || choice1<0 || choice1>1){
        printf("�����������������룡\n");
        fflush(stdin);
    }

    switch(choice1){
        case 0 :
            //��ʾ�û�����
            printf("�밴�գ�����.��.�� ������Ŀ ���ĸ�ʽ���롣\n");
            while((scanf("%d.%d.%d %s %lf", &(new_data.year), &(new_data.month), &(new_data.day),
                    new_data.name,&(new_data.value))) != 5 || new_data.year<=0 || new_data.month>12
                    || new_data.month<=0 || new_data.day<=0 ||new_data.day>31 || new_data.value<0) {
                fflush(stdin);
                printf("�����������������룡\n");
            }
            //��Ϊ��֧�������Խ�value���ű�ɸ���
            new_data.value = -new_data.value;

            printf("��������ѡ����ѡ�����ѵ����͡�\n");
            //��һ�������룬����i�ĳ�ʼ��ֵΪ1����������
            for(int i = 1; i<kind; i++){
                printf("%d.%-7s", i, CATEGORY[i]);
                if(i%5==0){
                    printf("\n");
                }
            }
            printf("\n");

            while((scanf("%d", &choice2)) !=1 || choice2<=0 || choice2>(kind-1)){
                printf("�����������������룡\n");
                fflush(stdin);
            }
            strcpy(new_data.category, CATEGORY[choice2]);
            //ȷ���û�����
            printf("�������ˣ�\n����ʱ�䣺%d.%d.%d ������Ŀ��%s ��%.2lf �������ͣ�%s\n", new_data.year, new_data.month,
                    new_data.day, new_data.name,-new_data.value, new_data.category);
            if(fwrite(&new_data, sizeof(struct finance_data), 1, fp) == 1){
                printf("��ӳɹ���\n");
            }
            insert_head_finance_node(new_data);
            break;
        case 1 :
            printf("�밴�գ�����.��.�� ������ĸ�ʽ�������롣\n");
            while((scanf("%d.%d.%d %lf", &(new_data.year), &(new_data.month), &(new_data.day),
                    &(new_data.value))) != 4 || new_data.value<0 || new_data.year<=0||new_data.month>12 ||
                    new_data.month<=0 || new_data.day<=0 ||new_data.day>31){
                printf("�����������������룡\n");
                fflush(stdin);
            }
            strcpy(new_data.name, "void");
            strcpy(new_data.category, CATEGORY[0]);
            printf("�������ˣ�\n%d.%d.%d ����%.2lf\n", new_data.year, new_data.month, new_data.day, new_data.value);
            if(fwrite(&new_data,sizeof(struct finance_data), 1, fp) == 1){
                printf("��ӳɹ���\n");
            }
            insert_head_finance_node(new_data);
            break;
        default:break;
    }
    fclose(fp);
    return;
}

/**
 * �˺��������޸��Ѿ����ڵļ�¼��
 * @param user_id
 */
void update_finance_record(int user_id){

    char file_name[20];
    sprintf(file_name, "%d%s", user_id, "_finance.txt");
    FILE* fp = NULL;
    fp = fopen(file_name, "wb");
    if(fp == NULL){
        printf("�ļ���ʧ�ܣ�\n");
        return;
    }

    show_all_finance_node();
    printf("�����¼ǰ��������޸ļ�¼��\n");
    int lable_in = 0;
    while(scanf("%d", &lable_in) !=1 || lable_in<1 || lable_in > lenth_node){
        printf("�����������������롣\n");
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
        printf("��ѡ����ǣ�\n");
        show_finance_node_by_pointer(search);
        printf("������Ҫ�޸ĵĽ�\n");
        double new_value = 0;
        while(scanf("%lf", &new_value) !=1 || new_value<=0){
            printf("�����������������롣\n");
            fflush(stdin);
        }
        search->data.value = new_value;
    }else{
        int choice2 =0;
        finance_data new_data = search->data;
        printf("��ѡ����ǣ�\n");
        show_finance_node_by_pointer(search);
        printf("�밴�գ�����.��.�� ������Ŀ ���ĸ�ʽ���롣\n");
        while((scanf("%d.%d.%d %s %lf", &(new_data.year), &(new_data.month), &(new_data.day),
                     new_data.name,&(new_data.value))) != 5 || new_data.year<=0 || new_data.month>12
              || new_data.month<=0 || new_data.day<=0 ||new_data.day>31 || new_data.value<0) {
            fflush(stdin);
            printf("�����������������룡\n");
        }
        //��Ϊ��֧�������Խ�value���ű�ɸ���
        new_data.value = -new_data.value;

        printf("��������ѡ����ѡ�����ѵ����͡�\n");
        //��һ�������룬����i�ĳ�ʼ��ֵΪ1����������
        for(int i = 1; i<kind; i++){
            printf("%d.%-7s", i, CATEGORY[i]);
            if(i%5==0){
                printf("\n");
            }
        }
        printf("\n");

        while((scanf("%d", &choice2)) !=1 || choice2<=0 || choice2>(kind-1)){
            printf("�����������������룡\n");
            fflush(stdin);
        }
        strcpy(new_data.category, CATEGORY[choice2]);
        //ȷ���û�����
        printf("�������ˣ�\n����ʱ�䣺%d.%d.%d ������Ŀ��%s ��%.2lf �������ͣ�%s\n", new_data.year, new_data.month,
               new_data.day, new_data.name,new_data.value, new_data.category);
        printf("�޸ĳɹ���\n");
        search->data = new_data;
    }
    return;
}

/**
 * �˺�������ɾ��ĳһ����¼
 * @param user_id
 */
void delete_finance_record(int user_id){

    show_all_finance_node();
    printf("�����¼ǰ�������ɾ����¼��\n");
    int lable_in = 0;
    while(scanf("%d", &lable_in) !=1 || lable_in<1 || lable_in > lenth_node){
        printf("�����������������롣\n");
        fflush(stdin);
    }

    char file_name[20];
    FILE* fp = NULL;

    printf("��ѡ����ǣ�\n");
    show_finance_node_by_lable(lable_in);
    printf("�Ƿ�ȷ��ɾ����ȷ��[y] ȡ��[n]\n");
    char confirm = 'n';
    fflush(stdin);
    scanf("%c", &confirm);
    switch(confirm){
        case 'y' :
        case 'Y' :

            sprintf(file_name, "%d%s", user_id, "_finance.txt");
            fp = fopen(file_name, "wb");
            if(fp == NULL){
                printf("�ļ���ʧ�ܣ�\n");
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
    printf("1. ����鿴��¼�Լ�ͳ����Ϣ��\n");
    printf("2. ���²鿴��¼�Լ�ͳ����Ϣ��\n");
    printf("3. ���ղ鿴��¼�Լ�ͳ����Ϣ��\n");
    printf("4. ��ʱ��β鿴��¼�Լ�ͳ����Ϣ��\n");
    printf("5. ���ء�\n");
    printf("������ѡ��ǰ���Ӧ�����֡�\n");

    int choice1 = 0;
    while(scanf("%d", &choice1) != 1 ){
        printf("�����������������롣\n");
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
    printf("������Ҫ�鿴����ݡ�\n");
    int year_in = 0;
    while(scanf("%d", &year_in) !=1 || year_in<=0){
        printf("�����������������롣\n");
        fflush(stdin);
    }
    char arg[10];
    sprintf(arg, "%d%s", year_in, "��");
    calculate_and_show_data(arg, year_in, 1, 1, year_in, 12, 31);
    return;
}

void finance_statistics_by_month(){
    printf("������Ҫ�鿴���·ݣ���ʽ������.�¡���\n");
    int year_in = 0;
    int month_in = 0;
    while(scanf("%d.%d", &year_in, &month_in) !=2 || year_in<=0 || month_in<=0 ||month_in>12){
        printf("�����������������롣\n");
        fflush(stdin);
    }
    char arg[10];
    sprintf(arg, "%d.%d", year_in, month_in);
    calculate_and_show_data(arg, year_in, month_in, 1, year_in, month_in, 31);
    return;
}

void finance_statistics_by_date(){

    printf("������Ҫ�鿴�����ڣ���ʽ������.��.�ա���\n");
    int year_in = 0;
    int month_in = 0;
    int day_in = 0;
    while(scanf("%d.%d.%d", &year_in, &month_in, &day_in) !=3 || year_in<=0 || month_in<=0 ||
        month_in>12 || day_in<=0 || day_in>31){
        printf("�����������������롣\n");
        fflush(stdin);
    }
    char arg[10];
    sprintf(arg, "%d.%d.%d", year_in, month_in, day_in);
    calculate_and_show_data(arg, year_in, month_in, day_in, year_in, month_in, day_in);
    return;
}

void finance_statistics_by_period(){
    printf("������Ҫ�鿴��ʱ��Σ���ʽ������ʼ��.��ʼ��.��ʼ�� ��ֹ��.��ֹ��.��ֹ�ա���\n");
    int year_in1 = 0;
    int month_in1 = 0;
    int day_in1 = 0;
    int year_in2 = 0;
    int month_in2 = 0;
    int day_in2 = 0;
    while(scanf("%d.%d.%d %d.%d.%d", &year_in1, &month_in1, &day_in1, &year_in2, &month_in2, &day_in2) !=6 ||
        year_in1<=0 || month_in1<=0 || month_in1>12 || day_in1<=0 || day_in1>31
        || year_in2<=0 || month_in2<=0 || month_in2>12 || day_in2<=0 || day_in2>31){
        printf("�����������������롣\n");
        fflush(stdin);
    }
    char arg[25];
    sprintf(arg, "%d.%d.%d~%d.%d.%d", year_in1, month_in1, day_in1, year_in2, month_in2, day_in2);
    calculate_and_show_data(arg, year_in1, month_in1, day_in1, year_in2, month_in2, day_in2);
    return;
}


/**
 * �˺�������ͳ�Ʋ���ʾ���������ļ�¼�����ߵĶ˵��ǰ������ڵġ�
 * Ĭ������������ǺϷ��� �� start��end��ͬһ�죬����start��end֮ǰ
 */
void calculate_and_show_data(char* argu, int start_year, int start_month, int start_day, int end_year, int end_month, int end_day){
    //�������������е�Ԫ�أ��ҳ����������ļ�¼�������ͳ��
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
                printf("%-5s %-10s %-20s %-12s %-6s\n","���","����", "��Ŀ", "���", "����");
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

    //�������ͳ�ƽ��
    printf("\n��%s��\n", argu);
    printf("���룺%.2lf\n", income);
    printf("֧����%.2lf\n", total_value);
    printf("���и���ռ�ȣ�\n");

    sort_statistics(all_statistics, kind-1);
    show_statistics(all_statistics, kind-1);

}

void show_statistics(value_and_kind* all_statistics, int len){
    printf("%-6s%-15s%s","���", "���","ռ��֧���ٷֱ�\n");
    for(int i = 0; i<len; i++){
        printf("%-6s%-10.2lf%.2lf%c\n", all_statistics[i].category, all_statistics[i].value, all_statistics[i].percentage*100, '%');
    }
    printf("\n");
}

/**
 * �Խ�������
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
        //����ori[i]��tem
        value_and_kind swap = ori[i];
        ori[i] = *tem;
        *tem = swap;
    }
}

/**
 *
 * @return �������1������2֮ǰ������-1������1������2��ͬһ�췵��0������1������2֮�󷵻�1��
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

//�ӱ����ļ��ж�ȡ�û�������/֧����¼
void initialize_linklist(int user_id){

    char file_name[20];
    sprintf(file_name, "%d%s", user_id, "_finance.txt");
    FILE* fp = NULL;
    //�˺����Ĺ���ֻ�Ƕ�ȡ��¼��������rb���ļ�
    fp = fopen(file_name, "rb");
    if(fp == NULL){
        fp = fopen(file_name, "wb+");
        if(fp == NULL){
            printf("�ļ���ʧ�ܣ�\n");
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
    printf("%-5s %-10s %-20s %-12s %-6s\n","���","����", "��Ŀ", "���", "����");
    for(finance_node* beginning = finance_head; beginning != NULL; beginning = beginning->next){
        char date[10];
        sprintf(date,"%d.%d.%d", beginning->data.year, beginning->data.month, beginning->data.day);

        if( (strcmp(beginning->data.category, CATEGORY[0])) == 0){
            printf("%-5d %-10s %-20s %-10.2lf\n", beginning->lable, date, "����", beginning->data.value);
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
        printf("%-5d %-10s %-20s %-10.2lf\n", node->lable, date, "����", node->data.value);
    }else{
        printf("%-5d %-10s %-20s %-10.2lf %-6s\n", node->lable, date, node->data.name,
                node->data.value, node->data.category);
    }
}

