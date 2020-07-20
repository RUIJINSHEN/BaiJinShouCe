#include<stdio.h>
#include<cstring>
#include<stdlib.h>

int numOfUser=0;

struct user{
	int ID;
	char name[20];
	char password[20];
	char password_protect[20];
	
	struct user *next;
};

struct user *head=NULL;

void registerUser();
void login();
void getChoice1();
void find_password();
void function_choose(int,char[]);
void save_data();
void load_data();
void user_delete(int);


void find_password(){
	int userID;
	char newPassword[20];
	char input_password_protect[20];
	char *pPassword=newPassword;
	char *pProtect=input_password_protect;
	struct user *ite=head;
	printf("���������ID\nID:");
	scanf("%d",&userID);
	printf("�ش��ܱ�����:\n���Сѧ������������:");
	scanf("%s",pProtect);
	while(ite){
		if(userID==ite->ID){
			if((strcmp(input_password_protect,ite->password_protect))==1){
				printf("��������������룺");
				scanf("%s",pPassword);
				strcpy(ite->password,newPassword);
				printf("�����޸ĳɹ���");
				getChoice1(); 
			}
		}
		
	}
	
	
}

void load_data(){
	struct user *ite;
	struct user *new_user=(struct user *)malloc(sizeof(struct user));
	if(new_user == NULL){
        printf("malloc error!\n");
        return;
    }
    
    FILE *user_info,*user_num;
	user_info=fopen("userInfo.txt","rb");
	user_num=fopen("numOfUser.txt","rb");
	
	do{
		fwrite(new_user,sizeof(struct user),1,user_info);
		ite=new_user->next;
	}while(ite!=NULL);
	
	fread(&numOfUser,sizeof(int),1,user_num);
}

void save_data(){
	struct user *ite=head;
	if(ite==NULL){
		return;
	}
	
	FILE *user_info,*user_num;
	user_info=fopen("userInfo.txt","wb");
	user_num=fopen("numOfUser.txt","wb");
	
	while(ite){
		fwrite(ite,sizeof(struct user),1,user_info);
	}
	fprintf(user_num,"%d",numOfUser);
	
}

/*
void function_choose(int userID,char username[]){
	int choice=0;
	
	printf("Hello %s\n",username); 
	printf("��ѡ�����������Ĺ��ܽ���:\n");
	printf("0-exit\n");
	printf("1-�ճ̹���\n");
	printf("2-�������\n");
	printf("3-��ʳ����\n");
	scanf("%d",&choice);
	
	switch(choice){
		case 0:
			getChoice1();
			break;
		case 1:
			richeng(userID);
		case 2:
			fiance_functions(userID);
		case 3:
			food(userID);
		case 9:
			user_delete(userID); 
	}
}
*/


void user_delete(int userID){
	struct user *ite=head;
	if(head->ID==userID){
		head=head->next;
		return;
	}
	while(ite->next){
		if(ite->next->ID==userID){
			ite->next=ite->next->next;
			//����������ģ���ɾ������
			return;
		}
	}

}


void registerUser(){
	
	struct user *new_user=(struct user *)malloc(sizeof(struct user));
	if(new_user == NULL){
        printf("malloc error!\n");
        return;
    }
    
	new_user->next=head;
	head=new_user;
	
	char newName[20]; 
	char newPassword[20];
	char newPasswordProtect[20];
	
	char *pName=newName;
	char *pPassword=newPassword;
	char *pPassword_protect=newPasswordProtect;
	
	numOfUser++;
	int userID=numOfUser-1;
	
	printf("������������û���������\n");
	scanf("%s",pName);
	scanf("%s",pPassword);
	
	new_user->ID=userID;
	strcpy(new_user->name,newName);
	strcpy(new_user->password,newPassword);
	
	printf("��ش��ܱ����Ⲣ��ס��Ĵ��Ա��һ����롣\n���Сѧ�����������ǣ�");
	scanf("%s",pPassword_protect);
	strcpy(new_user->password_protect,pPassword_protect);
	
	printf("���ΨһIDΪ%04d\n",userID);
	
	printf("��ѡ���������\n0-Exit\n1-login\n");
	
	int choice=0;
	switch(choice){
		case 0:
			return;
		case 1:
			login();
	} 
	
	
}


void login() { 
	
	char input_password[20];
	char *pPassword=input_password;
	
	int userID;	
	printf("������ID������\n");

	printf("ID:");
	while(1){
		scanf("%d",&userID);
		if(userID>10000 && userID<0){
			printf("Invalid input,try again!\n");
		}
		else{
			break;
		}
	}
	printf("\n����:");
	scanf("%s",pPassword);
	
	struct user *ite=head;
	
	while(ite){
		if(userID==ite->ID){
			while(1){
				if((strcmp(input_password,ite->password))==1){
					printf("������ȷ�����빦��ѡ�����\n");
					function_choose(userID,ite->name);
					break;
				}else{
					printf("����һ�Σ���ͨ������0������һ���˵��һ�����");
					int choice=1;
					scanf("%d",&choice);
					if(choice==0){
						getChoice1();
						break;
					}else{
						pPassword=input_password;
						printf("\n����:");
						scanf("%s",pPassword);
					}
				}
			}
			break;	
		}else{
			ite=ite->next;
		}
	}	
	if(ite==NULL){
		printf("�û�ID������");
	}
		
	
}
	 


void getChoice1(){
	int choice;
	printf("Please input the number of your choice and press Enter\n");
	printf("0-Exit\n");
	printf("1-Login\n");
	printf("2-Register\n");
	printf("3-Forget your password\n");
	printf("4-")
	scanf("%d",&choice);
	
	switch(choice){
		case 0:
			return;
		case 1:
			login();
			break;
		case 2:
			registerUser();
			break;
		case 3:
			find_password();
			break;
	}
}

int main() {
	
	load_data();
	getChoice1(); 
	
	save_data();
}
