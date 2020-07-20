#include "schedule_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>


/*���ļ��ж�ȡ���ݣ�����������������ͷ���*/
u_schedule readFile(int user_id){
    char filename[20];
    sprintf(filename, "%d%s", user_id, "_schedule.txt");
    FILE* fp = NULL;//����ָ���ļ��ṹ���ָ�����fp
    u_schedule head = NULL; //��������ͷ���ָ��head������ֵΪ��
    u_schedule p,p1; //��������ڵ�ָ��p,p1��p���ڴ洢���ļ���ȡ�ĵ�ǰ�ڵ㣬p1���ڱ�ʶ����������̵�β�ڵ㣩
    unsigned int ret; //�����޷������ͱ���ret�����ڴ洢fread����ʵ�ʶ�ȡ�����ַ���
    int count = 0;  //�������ͱ���count�����ڴ洢����ڵ����

    fp = fopen(filename,"a+"); //��׷�Ӷ�д�ķ�ʽ���ļ������ļ�������ʱ�����ļ������ѷ���ֵ��ֵ��ָ�����fp
    if(fp == NULL){  //��ʧ�ܣ�������
        perror("read open");
        exit(1);
    }
    p = (u_schedule)malloc(sizeof(struct schedule_thing)); //����һ���ڵ�ṹ���Ŀռ䣬��������ڵ�ָ��pָ������ռ�
    memset(p, 0, sizeof(struct schedule_thing)); //��ʼ������Ŀռ䣨��0��䣩
    ret = fread(p, sizeof(u_thing), 1, fp);	//��ȡ�ļ��е��������ݽṹ���С�����ݣ�һ���û�data��Ϣ��������Ľڵ�ṹ����
    if(!ret){  //�ж϶�ȡ�����ַ����Ƿ�Ϊ0���ж��ļ��Ƿ�Ϊ�գ�Ϊ��Ϊ�棩��
        return head; //��������ͷ���ָ��head��headδ����ռ䣬ΪNULL��
    }
    while(ret){  //�ж϶�ȡ�����ַ����Ƿ�Ϊ1���ж��ļ��Ƿ�Ϊ�գ��ǿ�Ϊ�棩��
        count++;  //�ڵ������1
        if(count == 1){	//�ж��Ƿ�Ϊ��һ���ڵ㣨ͷ��㣩
            head = p; //����ǰ��ȡ���Ľڵ�p��ֵ��ͷ���
            p1 = p; //����ǰ��ȡ���Ľڵ���Ϊβ���
        }
        p1->next = p; //����ǰ��ȡ���Ľڵ�p��ֵ���ϴβ�����β���
        p1 = p; //����ǰ��ȡ���Ľڵ���Ϊβ�ڵ㣨β�ڵ�����ƶ�һ�Σ�
        p = (u_schedule)malloc(sizeof(struct schedule_thing)); //����һ���ڵ�ṹ���Ŀռ䣬��������ڵ�ָ��pָ������ռ�
        memset(p, 0, sizeof(struct schedule_thing)); //��ʼ������Ŀռ䣨��0��䣩
        ret = fread(p, sizeof(u_thing), 1, fp); //��ȡ�ļ��е��������ݽṹ���С�����ݣ�һ���û�data��Ϣ��������Ľڵ�ṹ����
    }
    p1->next = NULL; //��β�ڵ��next��ֵΪ��
    free(p);
    fclose(fp); //�ر��ļ�
    return head; //��������ͷ���ָ��head��headΪһ���ǿ������ͷ��㣩
}
/*�����ݴ����ļ����������Ϊ����ͷ���*/
void save_file(int user_id, u_schedule p){
    char filename[20];
    sprintf(filename, "%d%s", user_id, "_schedule.txt");
    FILE *fp; //����ָ���ļ��ṹ���ָ�����fp
    fp = fopen(filename, "w+"); //��ÿ�δ�����ļ����ݵķ�ʽ�򿪿ɶ�д�ļ������ļ�������ʱ�����ļ������ѷ���ֵ��ֵ��ָ�����fp
    if(fp == NULL){ //��ʧ�ܣ�������
        perror("save open");
        exit(1);
    }
    while(p){ //ѭ������������û���Ϣ����
        fwrite(p, sizeof(u_thing), 1, fp); //����ǰ���������û���Ϣ�ڵ��������д���ļ�
        p = p->next; //��ǰ�����ڵ�����ƶ�
    }
    fclose(fp); //�ر��ļ�
}
/*ɾ���ļ�*/
void del_file(int user_id){
    char filename[20];
    sprintf(filename, "%d%s", user_id, "_schedule.txt");
    if(remove(filename)==0){
        printf("�û��ճ���Ϣע���ɹ���\n");
    }else{
        perror("remove");
    }
}

/*��ӡ�ļ��е�����*/
void print_schedule(int user_id){
    u_schedule head = readFile(user_id); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
    u_schedule *p = &head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩
    /*while(p){
        //�����ճ̵�ɾ��
        int interval;
        interval = calculate_interval(p->data.year,p->data.month,p->data.day);
        if(interval==0){
            del_data(user_id,p->data.thing);
        }
    }*/
    while(*p){ //ѭ����������ÿһ���ڵ�
        printf("thing:%s\t degree:%d\t date:%d.%d.%d\t time:%d:%d:%d\n",(*p)->data.thing,(*p)->data.degree,
               (*p)->data.year,(*p)->data.month,(*p)->data.day,(*p)->data.hour,(*p)->data.minute,(*p)->data.second); //��ӡ��ǰ�����ڵ���������Ϣ
        (*p) = (*p)->next; //��ǰ�����ڵ�����ƶ�
    }
    free_file(head); //�ͷ�����
}
//�ͷ�����
void free_file(u_schedule p){
    u_schedule p1; //��������ڵ�ָ��p1��p1���ڴ洢Ҫ�ͷŵĵ�ǰ�ڵ㣩
    while(p){ //ѭ�����봫�������
        p1 = p; //����ǰ�����ڵ㸳ֵ��p1
        p = p->next; //��ǰ�����ڵ�����ƶ�
        free(p1); //�ͷ�p1�ڵ㣨���ͷ�����ƶ�ǰ�Ľڵ㣩
    }
}
//������β�ڵ��������
void insert_data(int user_id,u_thing *thing_name){
    u_schedule head = readFile(user_id); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
    u_schedule p; //��������ڵ�ָ��p��p���ڴ洢������û����ݣ�
    u_schedule p1 = head; //��������ڵ�ָ��p1��p1���ڴ洢��ǰ�ڵ㣩
    if(!p1){ //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棨Ϊ�漴Ϊ�ļ�Ϊ�գ���ͷ���δ����ռ䣩
        head = (u_schedule)malloc(sizeof(struct schedule_thing)); //����һ���ڵ�ṹ���Ŀռ䣬��������ͷ�ڵ�ָ��headָ������ռ�
        memset(head, 0, sizeof(struct schedule_thing)); //��ʼ������Ŀռ䣨��0��䣩
        head->data = *thing_name; //��������û����ݸ�ֵ��ͷ����������
        head->next = NULL; //��ͷ���ָ����ֵΪNULL
        printf("�����¼��ɹ���\n");
    }else{ //ͷ��㲻Ϊ�գ��ļ��д����û���Ϣ��
        while(p1->next){ //ѭ�����������ҵ�ָ����Ϊ�յĽڵ㣬������β�ڵ�
            p1 = p1->next;
        }
        p = (u_schedule)malloc(sizeof(struct schedule_thing)); //������һ���ڵ�ṹ���С�Ŀռ䣬��������ڵ�ָ��pָ������ռ�
        memset(p, 0, sizeof(struct schedule_thing)); //��ʼ������Ŀռ䣨��0��䣩
        p->data = *thing_name; //��������û����ݸ�ֵ������ڵ�p��������
        p->next = p1->next; //��β�ڵ��next��ֵ��p�ڵ��next�򣨽�NULL��ֵ��β����next��
        p1->next = p; //����β����next��ָ��ǰp�ڵ㣨β����Ϊp�ڵ㣬����p���뵽�����β����
        printf("�����¼��ɹ���\n");
    }
    save_file(user_id,head); //����������������ļ�
    print_schedule(user_id);
    free_file(head); //�ͷ�����
}
/*ɾ�����ݽڵ㣬�������ΪҪɾ�����û���*/
void del_data(int user_id,char *thing_name){
    u_schedule head = readFile(user_id); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
    u_schedule p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
    u_schedule pdel; //��������ڵ�ָ��pdel��pdel���ڴ洢Ҫɾ���Ľڵ㣩
    if(!head){ //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
        printf("û���ҵ�Ҫɾ�����¼�!\n");
    }else if(!strcmp(p->data.thing, thing_name)){ //�ж�ͷ����Ƿ�ΪҪɾ���Ľڵ㣨��Ϊ�棩
        pdel = p; //����ǰ�ڵ�p��ͷ���head����ֵ��pdel
        head = head->next; //��ͷ������һ���ڵ㸳ֵ��ͷ���
        free(pdel); //�ͷ�Ҫɾ���Ľڵ�
        printf("ɾ���¼��ɹ���\n");
    }else{ //ͷ��㲻Ϊ�գ���Ҫɾ���Ľڵ㲻��ͷ���
        while(p->next && strcmp(p->next->data.thing, thing_name)){ //ѭ�����������ҵ�Ҫɾ���ڵ����һ���ڵ�
            p = p->next;
        }
        if(p->next){ //�ж�Ҫɾ���Ľڵ��Ƿ�Ϊ�գ���Ϊ�ռ�Ϊ�ҵ���Ϊ�棩��Ϊ�ռ�Ϊδ�ҵ�����������Ҫɾ���Ľڵ㣩��
            pdel = p->next; //��Ҫɾ���Ľڵ㣨��ǰ�ڵ����һ���ڵ㣩��ֵ��pdel
            p->next = pdel->next; //��Ҫɾ���ڵ����һ���ڵ㸳ֵ��Ҫɾ���ڵ����һ���ڵ㣨����ǰһ���ڵ�ͺ�һ���ڵ�������
            free(pdel); //�ͷ�Ҫɾ���Ľڵ�
            printf("ɾ���¼��ɹ���\n");
        }else{ //��������Ҫɾ���Ľڵ�
            printf("û���ҵ�Ҫɾ�����¼�!\n");
        }
    }
    save_file(user_id,head); //��ɾ�������������ļ�
    free_file(head); //�ͷ�����
    print_schedule(user_id);
}
/*�������ݽڵ㣬�������ΪҪ���µ��û��͸��º���û���Ϣ�ṹ��*/
void update_data(int user_id,char *thing_name, u_thing *thing){
    u_schedule head = readFile(user_id); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
    u_schedule p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
    if(!head){ //�ж�ͷ����Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
        printf("û���ҵ�Ҫ�޸ĵ��¼�!\n");
    }else{ //ͷ��㲻Ϊ��
        while(p && strcmp(p->data.thing,thing_name)){ //ѭ�����������ҵ�Ҫ���µĽڵ�
            p = p->next;
        }
        if(p){ //�ж�Ҫ���µĽڵ��Ƿ�Ϊ�գ���Ϊ�ռ�Ϊ�ҵ���Ϊ�棩��Ϊ�ռ�Ϊδ�ҵ�����������Ҫ���µĽڵ㣩��
            p->data = *thing; //��������û����ݸ�ֵ��Ҫ���µĽڵ�p��������
            printf("�޸ĵ��¼��ɹ�!\n");
        }else{ //��������Ҫ���µĽڵ�
            printf("û���ҵ�Ҫ�޸ĵ��¼�!\n");
        }
    }
    save_file(user_id,head); //�����º����������ļ�
    print_schedule(user_id);
    free_file(head); //�ͷ�����
}
/*�������ݽڵ�,�������ΪҪ���ҵ��¼���������Ӧ��Ϣ*/
void lookup_data(int user_id,char *thing_name){
    u_schedule head = readFile(user_id); //��ȡ�ļ��е����ݲ�����Ϊ������ͷ���ָ�봫�ݸ�head
    u_schedule p = head; //��������ڵ�ָ��p��p���ڴ洢��ǰ�ڵ㣩������head��ֵ��p
    if(!p){ //�жϵ�ǰ��㣨ͷ��㣩�Ƿ�Ϊ�գ�Ϊ��Ϊ�棬���ļ�Ϊ�գ�
        printf("û���ҵ����¼�!\n");
    }
    while(p && strcmp(p->data.thing,thing_name)){
        p = p->next;
    }
    if(p) {
        printf("thing:%s\t degree:%d\t date:%d.%d.%d\t time:%d:%d:%d\n",
               p->data.thing, p->data.degree, p->data.year, p->data.month, p->data.day,
               p->data.hour, p->data.minute, p->data.second);

    }else{
        printf("û���ҵ����¼�!\n");
}
    free_file(head); //�ͷ�����
}
void handle_show(int user_id) {
    int choice2;

        list:
        printf("1.��ʱ��˳��\n");
        printf("2.�ۺϿ��ǵ�˳��\n");
        printf("3.��Ҫ�Ե�˳��\n");
        printf("4.����\n");
        printf("your choice:");

        scanf("%d", &choice2);
        fflush(stdin);
        while(choice2 < 1 || choice2 > 4){
            printf("��������Чֵ��");
            goto list;
        }

    switch (choice2) {
        case 1:
            time_order(user_id);
            printf("US");
            print_schedule(user_id);
            goto list;
        case 2:
            priority_order(user_id);
            print_schedule(user_id);
            goto list;
        case 3:
            importance_order(user_id);
            print_schedule(user_id);
            goto list;
        case 4:
            return;
        default:
            printf("��������Чֵ��\n");
            goto list;
    }


}

void time_order(int user_id){
    u_schedule head = readFile(user_id);

    u_schedule pre,p;
    int count = 0;
    pre = head;
    while (pre != NULL){
        pre = pre->next;
        count ++;
    }

   // if(head){

   for(int i = 0;i<count+1;i++){
        p=head;
        while(p->next){
            if(p->data.year > p->next->data.year)
            {
                exchange(head ,p);
            }
            else if(p->data.year == p->next->data.year)
            {
                if(p->data.month > p->next->data.month)
                {
                    exchange(head ,p);
                }
                else if(p->data.month == p->next->data.month)
                {
                    if(p->data.day > p->next->data.day)
                    {
                        exchange(head ,p);
                    }
                    else if(p->data.day == p->next->data.day)
                    {
                        if(p->data.hour > p->next->data.hour)
                        {
                            exchange(head ,p);
                        }
                        else if(p->data.hour == p->next->data.hour)
                        {
                            if(p->data.minute > p->next->data.minute)
                            {
                                exchange(head ,p);
                            }
                            else if(p->data.minute == p->next->data.minute)
                            {
                                if(p->data.second > p->next->data.second)
                                {
                                    exchange(head ,p);
                                }
                                else{
                                    p = p->next;
                                }
                            }
                            else{
                                p = p->next;
                            }
                        }
                        else{
                            p = p->next;
                        }
                    }
                    else{
                        p = p->next;
                    }
                }
                else{
                    p = p->next;
                }
            }
            else{
                p = p->next;
            }
        }
    }

    save_file(user_id,head);
   // }
}

void priority_order(int user_id) {
    u_schedule head = readFile(user_id);
    u_schedule pre, p;
    pre = head;
    int p_interval,p_next_interval;
    int count = 0;
    double p_priority_value,p_next_priority_value;//������ֵ��Խ����Խ����

    while (pre != NULL){
        pre = pre->next;
        count ++;
    }

    for(int i = 0;i<count+1;i++){
        p=head;
        while(p->next){

            p_interval = calculate_interval(p->data.year,p->data.month,p->data.day);
            p_next_interval = calculate_interval(p->next->data.year,p->next->data.month,p->next->data.day);
            p_priority_value=(double)(p->data.degree)/p_interval;
            p_next_priority_value=(double)(p->next->data.degree)/p_next_interval;
            if (p_priority_value < p_next_priority_value) {
                exchange(head ,p);
            }else{
                p = p->next;
            }
        }
    }
    save_file(user_id,head);
}

void importance_order(int user_id){
    u_schedule head = readFile(user_id);
    u_schedule pre, p;
    pre = head;
    int count = 0;

    while (pre != NULL){
        pre = pre->next;
        count ++;
    }

    for(int i = 0;i<count+1;i++){
        p=head;
        while(p->next){
            if (p->data.degree < p->next->data.degree) {
                exchange(head ,p);
            }else{
                p = p->next;
            }
        }
    }
    save_file(user_id,head);
}

void exchange(u_schedule head , u_schedule p)
{
    u_schedule pr;

    if(head == p){//������
        u_schedule second = head->next;
        p->next=second->next;
        head = second;
        second->next=p;

        /*u_schedule pp = p->next;
        p = pp->next;
        pp->next = p;*/
        /*if(p->next->next){
            u_schedule pb;
            pb = p->next;
            p->next = pb->next;
            pb->next = p;
        }else{
            u_schedule  pb;
            pb = p->next;
            p->next = NULL;
            pb->next = p;
        }*/

    }else{
        pr = head;
        while (pr){
            if(pr->next == p)
                break;
//            printf("pr=%p\n",pr);
//            printf("p=%p\n",p);
//            printf("%p\n",pr->next);
//            printf("\n");
            pr = pr->next;
            //printf(pr->next != p);

        }
        if(p->next->next){
            u_schedule pb;
            pb = p->next;
            pr->next = pb;
            p->next = pb->next;
            pb->next = p;
        }else{
            u_schedule  pb;
            pb = p->next;
            pr->next = pb;
            p->next = NULL;
            pb->next = p;
        }
    }

}


void remind_system(int user_id){

    u_schedule head = readFile(user_id);
    u_schedule p;
    p = head;
    //if(head){//�ļ���Ϊ��
        time_order(user_id);
        while(p){
            //�����ճ̵�ɾ��
            int interval;
            interval = calculate_interval(p->data.year,p->data.month,p->data.day);
            /*if(interval==0){
                del_data(user_id,p->data.thing);
            }*/

            if(interval<=3){//ʱ����<3����ɫ����������,��������
                printf("�����ճ̣�thing:%s\t degree:%d\t date:%d.%d.%d\t time:%d:%d:%d\n ",p->data.thing,p->data.degree,
                       p->data.year,p->data.month,p->data.day,p->data.hour,p->data.minute,p->data.second);
            }else{
                printf("1thing:%s\t degree:%d\t date:%d.%d.%d\t time:%d:%d:%d\n",p->data.thing,p->data.degree,
                       p->data.year,p->data.month,p->data.day,p->data.hour,p->data.minute,p->data.second);
            }
            p = p->next;
        }
        save_file(user_id,head);

}

int calculate_interval(int year,int mon,int day){

    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);

    int n_year,n_mon,n_day;
    //int n_hour,n_min,n_sec;

    n_year = 1900+p->tm_year;
    n_mon = 1+p->tm_mon;
    n_day = p->tm_mday;
    /*n_hour = p->tm_hour+8;
    n_min = p->tm_min;
    n_sec = p->tm_sec;*/

    int dist;
    /*while(fflush(stdin),//Ĭ��year1<year2
            scanf("%d%d%d%d%d%d",&year1,&mon1,&day1,&year2,&mon2,&day2)!=EOF)
    {*/
        if(n_year==year)
        {
            dist=day_number(year,mon,day)-day_number(n_year,n_mon,n_day);
        }else if(n_year<year){
            dist=
                    day_number(year,mon,day)
                    +year_number(n_year,year)
                    -day_number(n_year,n_mon,n_day);
        }else{
            dist=0;
        }
        return dist;
}

int day_number(int year,int mon,int day){//���������ڵ����ǵڼ���
    int a[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int i,total=0;
    for(i=0; i<mon-1; i++)
    {
        total+=a[i];
    }
    if(mon>2){
        if(year%4==0&&year%100!=0 || year%400==0){//�ж��Ƿ�Ϊ����
            total+=1;
        }
    }
    total+=day;
//printf("%04d-%02d-%02d is %dth days\n",year,mon,day,total);
    return total;
}

int year_number(int year1,int year2){
    int total=0,year;
    for(year=year1; year<year2; year++)
    {
        total+=365;
        if(year%4==0&&year%100!=0 || year%400==0){
            total+=1;
        }
    }
    return total;
}
