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
	printf("请输入你的ID\nID:");
	scanf("%d",&userID);
	printf("回答密保问题:\n你的小学班主任名字是:");
	scanf("%s",pProtect);
	while(ite){
		if(userID==ite->ID){
			if((strcmp(input_password_protect,ite->password_protect))==1){
				printf("请输入你的新密码：");
				scanf("%s",pPassword);
				strcpy(ite->password,newPassword);
				printf("密码修改成功！");
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
	printf("请选择你所想进入的功能界面:\n");
	printf("0-exit\n");
	printf("1-日程管理\n");
	printf("2-财务管理\n");
	printf("3-饮食管理\n");
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
			//调用其它各模块的删除功能
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
	
	printf("请分两行输入用户名及密码\n");
	scanf("%s",pName);
	scanf("%s",pPassword);
	
	new_user->ID=userID;
	strcpy(new_user->name,newName);
	strcpy(new_user->password,newPassword);
	
	printf("请回答密保问题并记住你的答案以便找回密码。\n你的小学班主任名字是：");
	scanf("%s",pPassword_protect);
	strcpy(new_user->password_protect,pPassword_protect);
	
	printf("你的唯一ID为%04d\n",userID);
	
	printf("请选择后续操作\n0-Exit\n1-login\n");
	
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
	printf("请输入ID及密码\n");

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
	printf("\n密码:");
	scanf("%s",pPassword);
	
	struct user *ite=head;
	
	while(ite){
		if(userID==ite->ID){
			while(1){
				if((strcmp(input_password,ite->password))==1){
					printf("密码正确！进入功能选择面板\n");
					function_choose(userID,ite->name);
					break;
				}else{
					printf("再试一次！或通过输入0返回上一级菜单找回密码");
					int choice=1;
					scanf("%d",&choice);
					if(choice==0){
						getChoice1();
						break;
					}else{
						pPassword=input_password;
						printf("\n密码:");
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
		printf("用户ID不存在");
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
