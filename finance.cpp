#include <stdio.h>
#include "finance_functions.h"

extern const char* const CATEGORY[];
extern const int kind;
extern finance_node* finance_head;
extern int lenth_node;

const char* const CATEGORY[] = {"����", "����", "ˮ��", "��ʳ", "����", "��ͨ", "��ױ", "����"};
const int kind = sizeof(CATEGORY)/sizeof(char*);
finance_node* finance_head = NULL;
int lenth_node = 0;

int main(){
    finance_function(1234);
    return 0;
}

void finance_function(int user_id){

    //���û������ݣ������ļ��еģ���ʼ����������ȥ
    initialize_linklist(user_id);

    //�˵��б�
    main_list:
    printf("1. ����µ�����/֧����¼��\n");
    printf("2. �޸�����/֧����¼��\n");
    printf("3. ɾ������/֧����¼��\n");
    printf("4. �鿴��/��/�ղ���ͳ����Ϣ��\n");
    printf("5. ���������档\n");
    printf("������ѡ��ǰ���Ӧ�����֡�\n");

    int choice = 0;
    if( (scanf("%d", &choice)) != 1){
        fflush(stdin);
        printf("�����������������롣\n");
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
        default : printf("�����������������롣\n");goto main_list;break;
    }

}
//
//ͳ�ƹ��ܣ��ּ��ȡ��¡���ͳ�����롢֧����
// �Լ������棨��ʳס�еȣ�ռ�ȣ�������ռ�ȸ����ʵ����飻�����������˰���û������·ݵ���Ϣ�������ָ�������ݣ�Ԥ������滮����Ԥ�㣬ÿ�ճ��������Լ��ܽ������ѣ��򳬹�80%��