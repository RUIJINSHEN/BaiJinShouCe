#include "schedule_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>


/*从文件中读取数据，并创建链表返回链表头结点*/
u_schedule readFile(int user_id){
    char filename[20];
    sprintf(filename, "%d%s", user_id, "_schedule.txt");
    FILE* fp = NULL;//声明指向文件结构体的指针变量fp
    u_schedule head = NULL; //声明链表头结点指针head，并赋值为空
    u_schedule p,p1; //声明链表节点指针p,p1（p用于存储从文件读取的当前节点，p1用于标识创建链表过程的尾节点）
    unsigned int ret; //声明无符号整型变量ret，用于存储fread函数实际读取到的字符数
    int count = 0;  //定义整型变量count，用于存储链表节点个数

    fp = fopen(filename,"a+"); //以追加读写的方式打开文件，在文件不存在时创建文件，并把返回值赋值给指针变量fp
    if(fp == NULL){  //打开失败，错误处理
        perror("read open");
        exit(1);
    }
    p = (u_schedule)malloc(sizeof(struct schedule_thing)); //申请一个节点结构体大的空间，并用链表节点指针p指向这个空间
    memset(p, 0, sizeof(struct schedule_thing)); //初始化申请的空间（用0填充）
    ret = fread(p, sizeof(u_thing), 1, fp);	//读取文件中的链表数据结构体大小的数据（一个用户data信息）到申请的节点结构体中
    if(!ret){  //判断读取到的字符数是否为0（判断文件是否为空（为空为真））
        return head; //返回链表头结点指针head（head未申请空间，为NULL）
    }
    while(ret){  //判断读取到的字符数是否为1（判断文件是否为空（非空为真））
        count++;  //节点个数加1
        if(count == 1){	//判断是否为第一个节点（头结点）
            head = p; //将当前读取到的节点p赋值给头结点
            p1 = p; //将当前读取到的节点作为尾结点
        }
        p1->next = p; //将当前读取到的节点p赋值给上次操作的尾结点
        p1 = p; //将当前读取到的节点作为尾节点（尾节点向后移动一次）
        p = (u_schedule)malloc(sizeof(struct schedule_thing)); //申请一个节点结构体大的空间，并用链表节点指针p指向这个空间
        memset(p, 0, sizeof(struct schedule_thing)); //初始化申请的空间（用0填充）
        ret = fread(p, sizeof(u_thing), 1, fp); //读取文件中的链表数据结构体大小的数据（一个用户data信息）到申请的节点结构体中
    }
    p1->next = NULL; //将尾节点的next域赋值为空
    free(p);
    fclose(fp); //关闭文件
    return head; //返回链表头结点指针head（head为一个非空链表的头结点）
}
/*将数据存入文件，输入参数为链表头结点*/
void save_file(int user_id, u_schedule p){
    char filename[20];
    sprintf(filename, "%d%s", user_id, "_schedule.txt");
    FILE *fp; //声明指向文件结构体的指针变量fp
    fp = fopen(filename, "w+"); //以每次打开清空文件内容的方式打开可读写文件，在文件不存在时创建文件，并把返回值赋值给指针变量fp
    if(fp == NULL){ //打开失败，错误处理
        perror("save open");
        exit(1);
    }
    while(p){ //循环遍历传入的用户信息链表
        fwrite(p, sizeof(u_thing), 1, fp); //将当前遍历到的用户信息节点的数据域写入文件
        p = p->next; //当前遍历节点向后移动
    }
    fclose(fp); //关闭文件
}
/*删除文件*/
void del_file(int user_id){
    char filename[20];
    sprintf(filename, "%d%s", user_id, "_schedule.txt");
    if(remove(filename)==0){
        printf("用户日程信息注销成功！\n");
    }else{
        perror("remove");
    }
}

/*打印文件中的数据*/
void print_schedule(int user_id){
    u_schedule head = readFile(user_id); //读取文件中的数据并整合为链表，将头结点指针传递给head
    u_schedule *p = &head; //声明链表节点指针p（p用于存储当前节点）
    /*while(p){
        //过期日程的删除
        int interval;
        interval = calculate_interval(p->data.year,p->data.month,p->data.day);
        if(interval==0){
            del_data(user_id,p->data.thing);
        }
    }*/
    while(*p){ //循环遍历链表每一个节点
        printf("thing:%s\t degree:%d\t date:%d.%d.%d\t time:%d:%d:%d\n",(*p)->data.thing,(*p)->data.degree,
               (*p)->data.year,(*p)->data.month,(*p)->data.day,(*p)->data.hour,(*p)->data.minute,(*p)->data.second); //打印当前遍历节点数据域信息
        (*p) = (*p)->next; //当前遍历节点向后移动
    }
    free_file(head); //释放链表
}
//释放链表
void free_file(u_schedule p){
    u_schedule p1; //声明链表节点指针p1（p1用于存储要释放的当前节点）
    while(p){ //循环编译传入的链表
        p1 = p; //将当前遍历节点赋值于p1
        p = p->next; //当前遍历节点向后移动
        free(p1); //释放p1节点（即释放向后移动前的节点）
    }
}
//在链表尾节点插入数据
void insert_data(int user_id,u_thing *thing_name){
    u_schedule head = readFile(user_id); //读取文件中的数据并整合为链表，将头结点指针传递给head
    u_schedule p; //声明链表节点指针p（p用于存储传入的用户数据）
    u_schedule p1 = head; //声明链表节点指针p1（p1用于存储当前节点）
    if(!p1){ //判断头结点是否为空（为空为真（为真即为文件为空），头结点未申请空间）
        head = (u_schedule)malloc(sizeof(struct schedule_thing)); //申请一个节点结构体大的空间，并用链表头节点指针head指向这个空间
        memset(head, 0, sizeof(struct schedule_thing)); //初始化申请的空间（用0填充）
        head->data = *thing_name; //将传入的用户数据赋值给头结点的数据域
        head->next = NULL; //将头结点指针域赋值为NULL
        printf("增添事件成功！\n");
    }else{ //头结点不为空（文件中存在用户信息）
        while(p1->next){ //循环遍历链表找到指针域为空的节点，即链表尾节点
            p1 = p1->next;
        }
        p = (u_schedule)malloc(sizeof(struct schedule_thing)); //并申请一个节点结构体大小的空间，并用链表节点指针p指向这个空间
        memset(p, 0, sizeof(struct schedule_thing)); //初始化申请的空间（用0填充）
        p->data = *thing_name; //将传入的用户数据赋值给链表节点p的数据域
        p->next = p1->next; //将尾节点的next域赋值给p节点的next域（将NULL赋值给尾结点的next域）
        p1->next = p; //曾经尾结点的next域指向当前p节点（尾结点变为p节点，即将p插入到链表的尾部）
        printf("增添事件成功！\n");
    }
    save_file(user_id,head); //将插入后的链表存入文件
    print_schedule(user_id);
    free_file(head); //释放链表
}
/*删除数据节点，输入参数为要删除的用户名*/
void del_data(int user_id,char *thing_name){
    u_schedule head = readFile(user_id); //读取文件中的数据并整合为链表，将头结点指针传递给head
    u_schedule p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
    u_schedule pdel; //声明链表节点指针pdel（pdel用于存储要删除的节点）
    if(!head){ //判断头结点是否为空（为空为真，即文件为空）
        printf("没有找到要删除的事件!\n");
    }else if(!strcmp(p->data.thing, thing_name)){ //判断头结点是否为要删除的节点（是为真）
        pdel = p; //将当前节点p（头结点head）赋值给pdel
        head = head->next; //将头结点的下一个节点赋值给头结点
        free(pdel); //释放要删除的节点
        printf("删除事件成功！\n");
    }else{ //头结点不为空，且要删除的节点不是头结点
        while(p->next && strcmp(p->next->data.thing, thing_name)){ //循环遍历链表，找到要删除节点的上一个节点
            p = p->next;
        }
        if(p->next){ //判断要删除的节点是否为空（不为空即为找到（为真），为空即为未找到（链表中无要删除的节点））
            pdel = p->next; //将要删除的节点（当前节点的下一个节点）赋值给pdel
            p->next = pdel->next; //将要删除节点的下一个节点赋值给要删除节点的上一个节点（将其前一个节点和后一个节点相连）
            free(pdel); //释放要删除的节点
            printf("删除事件成功！\n");
        }else{ //链表中无要删除的节点
            printf("没有找到要删除的事件!\n");
        }
    }
    save_file(user_id,head); //将删除后的链表存入文件
    free_file(head); //释放链表
    print_schedule(user_id);
}
/*更新数据节点，输入参数为要更新的用户和更新后的用户信息结构体*/
void update_data(int user_id,char *thing_name, u_thing *thing){
    u_schedule head = readFile(user_id); //读取文件中的数据并整合为链表，将头结点指针传递给head
    u_schedule p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
    if(!head){ //判断头结点是否为空（为空为真，即文件为空）
        printf("没有找到要修改的事件!\n");
    }else{ //头结点不为空
        while(p && strcmp(p->data.thing,thing_name)){ //循环遍历链表，找到要更新的节点
            p = p->next;
        }
        if(p){ //判断要更新的节点是否为空（不为空即为找到（为真），为空即为未找到（链表中无要更新的节点））
            p->data = *thing; //将传入的用户数据赋值给要更新的节点p的数据域
            printf("修改的事件成功!\n");
        }else{ //链表中无要更新的节点
            printf("没有找到要修改的事件!\n");
        }
    }
    save_file(user_id,head); //将更新后的链表存入文件
    print_schedule(user_id);
    free_file(head); //释放链表
}
/*查找数据节点,输入参数为要查找的事件，返回相应信息*/
void lookup_data(int user_id,char *thing_name){
    u_schedule head = readFile(user_id); //读取文件中的数据并整合为链表，将头结点指针传递给head
    u_schedule p = head; //声明链表节点指针p（p用于存储当前节点），并将head赋值给p
    if(!p){ //判断当前结点（头结点）是否为空（为空为真，即文件为空）
        printf("没有找到该事件!\n");
    }
    while(p && strcmp(p->data.thing,thing_name)){
        p = p->next;
    }
    if(p) {
        printf("thing:%s\t degree:%d\t date:%d.%d.%d\t time:%d:%d:%d\n",
               p->data.thing, p->data.degree, p->data.year, p->data.month, p->data.day,
               p->data.hour, p->data.minute, p->data.second);

    }else{
        printf("没有找到该事件!\n");
}
    free_file(head); //释放链表
}
void handle_show(int user_id) {
    int choice2;

        list:
        printf("1.按时间顺序\n");
        printf("2.综合考虑的顺序\n");
        printf("3.重要性的顺序\n");
        printf("4.返回\n");
        printf("your choice:");

        scanf("%d", &choice2);
        fflush(stdin);
        while(choice2 < 1 || choice2 > 4){
            printf("请输入有效值！");
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
            printf("请输入有效值！\n");
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
    double p_priority_value,p_next_priority_value;//优先数值，越大则越优先

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

    if(head == p){//有问题
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
    //if(head){//文件不为空
        time_order(user_id);
        while(p){
            //过期日程的删除
            int interval;
            interval = calculate_interval(p->data.year,p->data.month,p->data.day);
            /*if(interval==0){
                del_data(user_id,p->data.thing);
            }*/

            if(interval<=3){//时间间隔<3，红色字体标红提醒,存在问题
                printf("临期日程：thing:%s\t degree:%d\t date:%d.%d.%d\t time:%d:%d:%d\n ",p->data.thing,p->data.degree,
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
    /*while(fflush(stdin),//默认year1<year2
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

int day_number(int year,int mon,int day){//返回日期在当年是第几天
    int a[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int i,total=0;
    for(i=0; i<mon-1; i++)
    {
        total+=a[i];
    }
    if(mon>2){
        if(year%4==0&&year%100!=0 || year%400==0){//判断是否为闰年
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
