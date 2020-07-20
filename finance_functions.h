#ifndef BAIJINSHOUCE_FINANCE_FUNCTIONS_H
#define BAIJINSHOUCE_FINANCE_FUNCTIONS_H

#include <stdio.h>

struct finance_data{
    int year;
    int month;
    int day;
    char name[40];
    double value;
    char category[7];
};
typedef struct finance_node{
    struct finance_data data;
    int lable;
    struct finance_node* next;
}finance_node;

typedef struct value_and_kind{
    double value = 0;
    double percentage = 0;
    const char* category = NULL;
}value_and_kind;

void finance_function(int user_id);
void new_finance_record(int user_id);
void update_finance_record(int user_id);
void delete_finance_record(int user_id);
void finance_statistics();

void initialize_linklist(int user_id);
void write_all_linkedlist_to_file(FILE* fp);
void finance_statistics_by_year();
void finance_statistics_by_month();
void finance_statistics_by_date();
void finance_statistics_by_period();
void calculate_and_show_data(char* argu, int start_year, int start_month, int start_day, int end_year, int end_month, int end_day);
int date_cmp(int year1, int month1, int day1, int year2, int month2, int day2);
void sort_statistics(struct value_and_kind* ori, int len);
void show_statistics(value_and_kind* all_statistics, int len);

void insert_head_finance_node(struct finance_data data);
void delete_finance_node_by_lable(int lable);
void show_all_finance_node();
void show_finance_node_by_pointer(finance_node* node);
void show_finance_node_by_lable(int lable);
void update_finance_node_by_lable(int lable);


#endif //BAIJINSHOUCE_FINANCE_FUNCTIONS_H
