#ifndef SECOND_SCHEDULE_FUNCTIONS_H
#define SECOND_SCHEDULE_FUNCTIONS_H


typedef struct user_thing{
    char thing[200];
    int degree;//重要性（0-4），4代表最重要
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
}u_thing;

typedef struct schedule_thing{
    u_thing data;
    struct schedule_thing *next;
}*u_schedule;

u_schedule readFile(int user_id); //文件读取计划
void save_file(int user_id, u_schedule p); //文件存入
void del_file(int user_id);
void print_schedule(int user_id); //打印文件内容(用户内容）
void free_file(u_schedule p); //释放链表
void insert_data(int user_id,u_thing *thing_name); //链表：增事件
void del_data(int user_id,char *thing_name); //链表：删事件
void update_data(int user_id,char *thing_name, u_thing *thing); //链表：改事件
void lookup_data(int user_id,char *thing_name); //链表：查事件
void handle_show(int user_id);//展示形式的选择处理
void time_order(int user_id);//按时间顺序
void priority_order(int user_id);//优先顺序
void importance_order(int user_id);//重要性顺序
void exchange(u_schedule head , u_schedule p);
void remind_system(int user_id);
int calculate_interval(int year,int mon,int day);
int day_number(int year,int mon,int day);
int year_number(int year1,int year2);


#endif //SECOND_SCHEDULE_FUNCTIONS_H
