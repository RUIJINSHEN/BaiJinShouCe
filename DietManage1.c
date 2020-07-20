#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include "DietManage.h"

typedef struct record{
	char time[11];  //用餐日期 
	char dtime[5];  //餐类别 
	char category[15];//食物类别
	char fname[10]; //食物名称
	int weight; //食物克数
	int qheat; //热量
	struct record *next; 
}record,*linklist;
void init(char filename[])
{
	FILE *fp=NULL;
	fp=fopen(filename,"w");
	fprintf(fp,"%s","用餐日期 餐类别 食物类别 食物名称 食物克数 热量");
	fclose(fp);
}
void insert(char filename[])
{
	char* stop_at = NULL;
	record nrecord;
	FILE *fp=NULL;
	int num,sum=0; //sum统计今天的总卡路里,psum统计新增的记录的食物类别的卡路里 
	char s[60],category[15];
	int year,month,day;
	int heat1=25,heat2=100,heat3=50,heat4=200,heat5=500,heat6=200,heat7=500;
	int psum1=0,psum2=0,psum3=0,psum4=0,psum5=0,psum6=0,psum7=0;
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	year = 1900 + p->tm_year;
	month = 1 + p->tm_mon;
	day = p->tm_mday;
	printf("输入用餐日期：");
	scanf("%s",nrecord.time);
	printf("选择餐类别\n");
	printf("1.早餐\n2.午餐\n3.晚餐\n");
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(nrecord.dtime,"早餐");
			break;
		case 2:
			strcpy(nrecord.dtime,"午餐");
			break;
		case 3:
			strcpy(nrecord.dtime,"晚餐");
			break;
		default:
			printf("请输入正确的数字\n");
			return ;	
	}
	printf("选择食物类别\n");
	printf("1.油脂类\n2.奶类\n3.豆类\n4.鱼、禽、肉、蛋\n5.蔬菜类\n6.水果类\n7.五谷类\n"); 
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(nrecord.category,"油脂类");
			strcpy(category,"油脂类");
			break;
		case 2:
			strcpy(nrecord.category,"奶类");
			strcpy(category,"奶类");
			break;
		case 3:
			strcpy(nrecord.category,"豆类");
			strcpy(category,"豆类");
			break;
		case 4:
			strcpy(nrecord.category,"鱼、禽、肉、蛋");
			strcpy(category,"鱼、禽、肉、蛋");
			break;
		case 5:
			strcpy(nrecord.category,"蔬菜类");
			strcpy(category,"蔬菜类");
			break;
		case 6:
			strcpy(nrecord.category,"水果类");
			strcpy(category,"水果类");
			break;	
		case 7:
			strcpy(nrecord.category,"五谷类");
			strcpy(category,"五谷类");
			break;
		default:
			printf("请输入正确的数字\n");
			return ;	
	}
	printf("输入食物名称\n");
	scanf("%s",nrecord.fname);
	printf("食物克数\n");
	scanf("%d",&nrecord.weight);
	printf("食物热量（大卡）\n");
	scanf("%d",&nrecord.qheat);
	fp=fopen(filename,"a");
	fprintf(fp,"\n%s %s %s %s %d %d",nrecord.time,nrecord.dtime,nrecord.category,nrecord.fname,nrecord.weight,nrecord.qheat);
	fclose(fp); 
	fp = fopen(filename, "r");
	fgets(s, 60, fp);
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %s %d %d", nrecord.time,nrecord.dtime,nrecord.category,nrecord.fname,&nrecord.weight,&nrecord.qheat);
		if(strtoul(strtok(nrecord.time,"."), &stop_at, 0)==year&&strtoul(strtok(NULL,"."), &stop_at, 0)==month&&strtoul(strtok(NULL,"."), &stop_at, 0)==day){
			sum+=nrecord.qheat;
			if(!strcmp(nrecord.category,"油脂类")){
				psum1+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"奶类")){
				psum2+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"豆类")){
				psum3+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"鱼、禽、肉、蛋")){
				psum4+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"蔬菜类")){
				psum5+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"水果类")){
				psum6+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"五谷类")){
				psum7+=nrecord.weight;
			}  
		}
	}
	if(sum>1900){
		printf("你今天已额外摄入，%d大卡，相当于吃了%.2f个冰淇淋，需要跳绳%.1f分钟\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
	}
	if(psum1>heat1){
		printf("你今天已额外摄入%s，%d克\n","油脂类",psum1-heat1);
	}
	if(psum2>heat2){
		printf("你今天已额外摄入%s，%d克\n","奶类",psum2-heat2);
	}
	if(psum3>heat3){
		printf("你今天已额外摄入%s，%d克\n","豆类",psum3-heat3);
	}
	if(psum4>heat4){
		printf("你今天已额外摄入%s，%d克\n","鱼、禽、肉、蛋",psum4-heat4);
	}
	if(psum5>heat5){
		printf("你今天已额外摄入%s，%d克\n","蔬菜类",psum5-heat5);
	}
	if(psum6>heat6){
		printf("你今天已额外摄入%s，%d克\n","水果类",psum6-heat6);
	}
	if(psum7>heat7){
		printf("你今天已额外摄入%s，%d克\n","五谷类",psum7-heat7);
	}
	fclose(fp);
}
void deleterecord(char filename[])
{
	char* stop_at = NULL;
	linklist L,p,q;
	record drecord; 
	FILE *fp=NULL;
	int num,option,sum=0;
	int year,month,day;
	int heat1=25,heat2=100,heat3=50,heat4=200,heat5=500,heat6=200,heat7=500;
	int psum1=0,psum2=0,psum3=0,psum4=0,psum5=0,psum6=0,psum7=0;
	char s[60],category[15];
	char ttime[11];
	time_t timep;
	struct tm *m;
	time(&timep);
	m = gmtime(&timep);
	year = 1900 + m->tm_year;
	month = 1 + m->tm_mon;
	day = m->tm_mday;
	L = (linklist)malloc(sizeof(record));
	L->next=NULL;
	q=L;
	printf("1.根据日期删除\n2.根据所有属性删除\n");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
			printf("输入日期\n");
			scanf("%s",drecord.time);
			fp = fopen(filename, "r");
			fgets(s, 60, fp);
			while (!feof(fp))
			{
				p = (linklist)malloc(sizeof(record));
				fscanf(fp, "%s %s %s %s %d %d", p->time,p->dtime,p->category,p->fname,&p->weight,&p->qheat);
				if(!strcmp(drecord.time,p->time)){
					continue;
				}
				q->next=p;
				p->next=NULL;
				q=p;
				strcpy(ttime,p->time);
				if(strtoul(strtok(ttime,"."), &stop_at, 0)==year&&strtoul(strtok(NULL,"."), &stop_at, 0)==month&&strtoul(strtok(NULL,"."), &stop_at, 0)==day){
					sum+=q->qheat;
					if(!strcmp(q->category,"油脂类")){
						psum1+=q->weight;
					}else if(!strcmp(q->category,"奶类")){
						psum2+=q->weight;
					}else if(!strcmp(q->category,"豆类")){
						psum3+=q->weight;
					}else if(!strcmp(q->category,"鱼、禽、肉、蛋")){
						psum4+=q->weight;
					}else if(!strcmp(q->category,"蔬菜类")){
						psum5+=q->weight;
					}else if(!strcmp(q->category,"水果类")){
						psum6+=q->weight;
					}else if(!strcmp(q->category,"五谷类")){
						psum7+=q->weight;
					}
				}
			}
			fclose(fp);
			if(sum>1900){
				printf("你今天已额外摄入，%d大卡，相当于吃了%.2f个冰淇淋，需要跳绳%.1f分钟\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
			}
			if(psum1>heat1){
				printf("你今天已额外摄入%s，%d克\n","油脂类",psum1-heat1);
			}
			if(psum2>heat2){
				printf("你今天已额外摄入%s，%d克\n","奶类",psum2-heat2);
			}
			if(psum3>heat3){
				printf("你今天已额外摄入%s，%d克\n","豆类",psum3-heat3);
			}
			if(psum4>heat4){
				printf("你今天已额外摄入%s，%d克\n","鱼、禽、肉、蛋",psum4-heat4);
			}
			if(psum5>heat5){
				printf("你今天已额外摄入%s，%d克\n","蔬菜类",psum5-heat5);
			}
			if(psum6>heat6){
				printf("你今天已额外摄入%s，%d克\n","水果类",psum6-heat6);
			}
			if(psum7>heat7){
				printf("你今天已额外摄入%s，%d克\n","五谷类",psum7-heat7);
			}
			q=L;
			fp = fopen(filename, "w");
			fputs("用餐日期 餐类别 食物类别 食物名称 食物克数 热量",fp);	
			while(q->next!=NULL){
				fprintf(fp,"\n%s %s %s %s %d %d",q->next->time,q->next->dtime,q->next->category,q->next->fname,q->next->weight,q->next->qheat);
				q=q->next;
			}
			fclose(fp);
			break;
		case 2:
			printf("输入要删除的日期\n");
			scanf("%s",drecord.time);
			printf("选择餐类别\n");
			printf("1.早餐\n2.午餐\n3.晚餐\n");
			scanf("%d",&num);
			switch(num)
			{
				case 1:
					strcpy(drecord.dtime,"早餐");
					break;
				case 2:
					strcpy(drecord.dtime,"午餐");
					break;
				case 3:
					strcpy(drecord.dtime,"晚餐");
					break;
				default:
					printf("请输入正确的数字\n");
					return ;	
			}
			printf("选择食物类别\n");
			printf("1.油脂类\n2.奶类\n3.豆类\n4.鱼、禽、肉、蛋\n5.蔬菜类\n6.水果类\n7.五谷类\n"); 
			scanf("%d",&num);
			switch(num)
			{
				case 1:
					strcpy(drecord.category,"油脂类");
					strcpy(category,"油脂类");
					break;
				case 2:
					strcpy(drecord.category,"奶类");
					strcpy(category,"奶类");
					break;
				case 3:
					strcpy(drecord.category,"豆类");
					strcpy(category,"豆类");
					break;
				case 4:
					strcpy(drecord.category,"鱼、禽、肉、蛋");
					strcpy(category,"鱼、禽、肉、蛋");
					break;
				case 5:
					strcpy(drecord.category,"蔬菜类");
					strcpy(category,"蔬菜类");
					break;
				case 6:
					strcpy(drecord.category,"水果类");
					strcpy(category,"水果类");
					break;	
				case 7:
					strcpy(drecord.category,"五谷类");
					strcpy(category,"五谷类");
					break;
				default:
					printf("请输入正确的数字\n");
					return ;	
			}
			printf("输入食物名称\n");
			scanf("%s",drecord.fname);
			printf("食物克数\n");
			scanf("%d",&drecord.weight);
			printf("食物热量（大卡）\n");
			scanf("%d",&drecord.qheat);
			fp = fopen(filename, "r");
			fgets(s, 60, fp);
			while (!feof(fp))
			{
				p = (linklist)malloc(sizeof(record));
				fscanf(fp, "%s %s %s %s %d %d", p->time,p->dtime,p->category,p->fname,&p->weight,&p->qheat);
				if(!strcmp(drecord.time,p->time)&&!strcmp(drecord.dtime,p->dtime)&&!strcmp(drecord.category,p->category)&&!strcmp(drecord.fname,p->fname)&&drecord.weight==p->weight&&drecord.qheat==p->qheat){
					continue;
				}
				q->next=p;
				p->next=NULL;
				q=p;
				strcpy(ttime,p->time);
				if(strtoul(strtok(ttime,"."), &stop_at, 0)==year&&strtoul(strtok(NULL,"."), &stop_at, 0)==month&&strtoul(strtok(NULL,"."), &stop_at, 0)==day){
					sum+=q->qheat;
					if(!strcmp(q->category,"油脂类")){
						psum1+=q->weight;
					}else if(!strcmp(q->category,"奶类")){
						psum2+=q->weight;
					}else if(!strcmp(q->category,"豆类")){
						psum3+=q->weight;
					}else if(!strcmp(q->category,"鱼、禽、肉、蛋")){
						psum4+=q->weight;
					}else if(!strcmp(q->category,"蔬菜类")){
						psum5+=q->weight;
					}else if(!strcmp(q->category,"水果类")){
						psum6+=q->weight;
					}else if(!strcmp(q->category,"五谷类")){
						psum7+=q->weight;
					} 
				}
			}
			fclose(fp);
			if(sum>1900){
				printf("你今天已额外摄入，%d大卡，相当于吃了%.2f个冰淇淋，需要跳绳%.1f分钟\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
			}
			if(psum1>heat1){
				printf("你今天已额外摄入%s，%d克\n","油脂类",psum1-heat1);
			}
			if(psum2>heat2){
				printf("你今天已额外摄入%s，%d克\n","奶类",psum2-heat2);
			}
			if(psum3>heat3){
				printf("你今天已额外摄入%s，%d克\n","豆类",psum3-heat3);
			}
			if(psum4>heat4){
				printf("你今天已额外摄入%s，%d克\n","鱼、禽、肉、蛋",psum4-heat4);
			}
			if(psum5>heat5){
				printf("你今天已额外摄入%s，%d克\n","蔬菜类",psum5-heat5);
			}
			if(psum6>heat6){
				printf("你今天已额外摄入%s，%d克\n","水果类",psum6-heat6);
			}
			if(psum7>heat7){
				printf("你今天已额外摄入%s，%d克\n","五谷类",psum7-heat7);
			}
			q=L;
			fp = fopen(filename, "w");
			fputs("用餐日期 餐类别 食物类别 食物名称 食物克数 热量",fp);	
			while(q->next!=NULL){
				fprintf(fp,"\n%s %s %s %s %d %d",q->next->time,q->next->dtime,q->next->category,q->next->fname,q->next->weight,q->next->qheat);
				q=q->next;
			}
			fclose(fp);
			break;
		default:
			printf("请输入正确的数字\n");
			return ;	
	}	
}
void modify(char filename[])
{
	char* stop_at = NULL;
	char s[60],category1[15],category2[15];
	char ttime[11];
	int num,sum=0;
	int heat1=25,heat2=100,heat3=50,heat4=200,heat5=500,heat6=200,heat7=500;
	int psum1=0,psum2=0,psum3=0,psum4=0,psum5=0,psum6=0,psum7=0; 
	int year,month,day;
	FILE *fp=NULL;
	record mrecord1,mrecord2;
	linklist L,p,q;
	time_t timep;
	struct tm *m;
	time(&timep);
	m = gmtime(&timep);
	year = 1900 + m->tm_year;
	month = 1 + m->tm_mon;
	day = m->tm_mday;
	L = (linklist)malloc(sizeof(record));
	L->next=NULL;
	q=L;
	printf("输入目标记录\n");
	printf("日期：");
	scanf("%s",mrecord1.time);
	printf("餐类别\n");
	printf("1.早餐\n2.午餐\n3.晚餐\n");
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord1.dtime,"早餐");
			break;
		case 2:
			strcpy(mrecord1.dtime,"午餐");
			break;
		case 3:
			strcpy(mrecord1.dtime,"晚餐");
			break;
		default:
			printf("请输入正确的数字\n");
			return ;	
	}
	printf("食物类别\n");
	printf("1.油脂类\n2.奶类\n3.豆类\n4.鱼、禽、肉、蛋\n5.蔬菜类\n6.水果类\n7.五谷类\n"); 
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord1.category,"油脂类");
			strcpy(category1,"油脂类");
			break;
		case 2:
			strcpy(mrecord1.category,"奶类");
			strcpy(category1,"奶类");
			heat1=100;
			break;
		case 3:
			strcpy(mrecord1.category,"豆类");
			strcpy(category1,"豆类");
			break;
		case 4:
			strcpy(mrecord1.category,"鱼、禽、肉、蛋");
			strcpy(category1,"鱼、禽、肉、蛋");
			break;
		case 5:
			strcpy(mrecord1.category,"蔬菜类");
			strcpy(category1,"蔬菜类");
			break;
		case 6:
			strcpy(mrecord1.category,"水果类");
			strcpy(category1,"水果类");
			break;	
		case 7:
			strcpy(mrecord1.category,"五谷类");
			strcpy(category1,"五谷类");
			break;
		default:
			printf("请输入正确的数字\n");
			return ;	
	}
	printf("食物名称：");
	scanf("%s",mrecord1.fname);
	printf("食物克数：");
	scanf("%d",&mrecord1.weight);
	printf("热量：");
	scanf("%d",&mrecord1.qheat); 
	printf("输入修改后的记录\n");
	printf("日期：");
	scanf("%s",mrecord2.time);
	printf("餐类别\n");
	printf("1.早餐\n2.午餐\n3.晚餐\n");
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord2.dtime,"早餐");
			break;
		case 2:
			strcpy(mrecord2.dtime,"午餐");
			break;
		case 3:
			strcpy(mrecord2.dtime,"晚餐");
			break;
		default:
			printf("请输入正确的数字\n");
			return ;	
	}
	printf("食物类别\n");
	printf("1.油脂类\n2.奶类\n3.豆类\n4.鱼、禽、肉、蛋\n5.蔬菜类\n6.水果类\n7.五谷类\n"); 
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord2.category,"油脂类");
			strcpy(category2,"油脂类");
			break;
		case 2:
			strcpy(mrecord2.category,"奶类");
			strcpy(category2,"奶类");
			break;
		case 3:
			strcpy(mrecord2.category,"豆类");
			strcpy(category2,"豆类");
			break;
		case 4:
			strcpy(mrecord2.category,"鱼、禽、肉、蛋");
			strcpy(category2,"鱼、禽、肉、蛋");
			break;
		case 5:
			strcpy(mrecord2.category,"蔬菜类");
			strcpy(category2,"蔬菜类");
			break;
		case 6:
			strcpy(mrecord2.category,"水果类");
			strcpy(category2,"水果类");
			break;	
		case 7:
			strcpy(mrecord2.category,"五谷类");
			strcpy(category2,"五谷类");
			break;
		default:
			printf("请输入正确的数字\n");
			return ;	
	}
	printf("食物名称：");
	scanf("%s",mrecord2.fname);
	printf("食物克数：");
	scanf("%d",&mrecord2.weight);
	printf("热量：");
	scanf("%d",&mrecord2.qheat); 
	fp = fopen(filename, "r");
	fgets(s, 60, fp);
	while (!feof(fp))
	{
		p = (linklist)malloc(sizeof(record));
		fscanf(fp, "%s %s %s %s %d %d", p->time,p->dtime,p->category,p->fname,&p->weight,&p->qheat);
		if(!strcmp(mrecord1.time,p->time)&&!strcmp(mrecord1.dtime,p->dtime)&&!strcmp(mrecord1.category,p->category)&&!strcmp(mrecord1.fname,p->fname)&&mrecord1.weight==p->weight&&mrecord1.qheat==p->qheat){
			strcpy(p->time,mrecord2.time);
			strcpy(p->dtime,mrecord2.dtime);
			strcpy(p->category,mrecord2.category);
			strcpy(p->fname,mrecord2.fname);
			p->weight=mrecord2.weight;
			p->qheat=mrecord2.qheat;
		}
		q->next=p;
		p->next=NULL;
		q=p;
		strcpy(ttime,p->time);
		if(strtoul(strtok(ttime,"."), &stop_at, 0)==year&&strtoul(strtok(NULL,"."), &stop_at, 0)==month&&strtoul(strtok(NULL,"."), &stop_at, 0)==day){
			sum+=q->qheat;
			if(!strcmp(q->category,"油脂类")){
				psum1+=q->weight;
			}else if(!strcmp(q->category,"奶类")){
				psum2+=q->weight;
			}else if(!strcmp(q->category,"豆类")){
				psum3+=q->weight;
			}else if(!strcmp(q->category,"鱼、禽、肉、蛋")){
				psum4+=q->weight;
			}else if(!strcmp(q->category,"蔬菜类")){
				psum5+=q->weight;
			}else if(!strcmp(q->category,"水果类")){
				psum6+=q->weight;
			}else if(!strcmp(q->category,"五谷类")){
				psum7+=q->weight;
			} 
		}
	}
	fclose(fp);
	if(sum>1900){
		printf("你今天已额外摄入，%d大卡，相当于吃了%.2f个冰淇淋，需要跳绳%.1f分钟\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
	}
	if(psum1>heat1){
		printf("你今天已额外摄入%s，%d克\n","油脂类",psum1-heat1);
	}
	if(psum2>heat2){
		printf("你今天已额外摄入%s，%d克\n","奶类",psum2-heat2);
	}
	if(psum3>heat3){
		printf("你今天已额外摄入%s，%d克\n","豆类",psum3-heat3);
	}
	if(psum4>heat4){
		printf("你今天已额外摄入%s，%d克\n","鱼、禽、肉、蛋",psum4-heat4);
	}
	if(psum5>heat5){
		printf("你今天已额外摄入%s，%d克\n","蔬菜类",psum5-heat5);
	}
	if(psum6>heat6){
		printf("你今天已额外摄入%s，%d克\n","水果类",psum6-heat6);
	}
	if(psum7>heat7){
		printf("你今天已额外摄入%s，%d克\n","五谷类",psum7-heat7);
	}
	q=L;
	fp = fopen(filename, "w");
	fputs("用餐日期 餐类别 食物类别 食物名称 食物克数 热量",fp);	
	while(q->next!=NULL){
		fprintf(fp,"\n%s %s %s %s %d %d",q->next->time,q->next->dtime,q->next->category,q->next->fname,q->next->weight,q->next->qheat);
		q=q->next;
	}
	fclose(fp);
}
void view(char filename[])
{
	char* stop_at = NULL;
	record vrecord;
	FILE *fp=NULL;
	char s[60],ptime[11];
	int sum=0;
	int year,month,day;
	int heat1=25,heat2=100,heat3=50,heat4=200,heat5=500,heat6=200,heat7=500;
	int psum1=0,psum2=0,psum3=0,psum4=0,psum5=0,psum6=0,psum7=0; 
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	year = 1900 + p->tm_year;
	month = 1 + p->tm_mon;
	day = p->tm_mday;
	printf("输入查询日期：");
	scanf("%s",ptime);
	fp = fopen(filename, "r");
	fgets(s, 60, fp);
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %s %d %d", vrecord.time,vrecord.dtime,vrecord.category,vrecord.fname,&vrecord.weight,&vrecord.qheat);
		if(!strcmp(ptime,vrecord.time))
			printf("%s %s %s %s %d %d\n",vrecord.time,vrecord.dtime,vrecord.category,vrecord.fname,vrecord.weight,vrecord.qheat);
		if(strtoul(strtok(vrecord.time,"."), &stop_at, 0)==year&&strtoul(strtok(NULL,"."), &stop_at, 0)==month&&strtoul(strtok(NULL,"."), &stop_at, 0)==day){
			sum+=vrecord.qheat;
			if(!strcmp(vrecord.category,"油脂类")){
				psum1+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"奶类")){
				psum2+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"豆类")){
				psum3+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"鱼、禽、肉、蛋")){
				psum4+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"蔬菜类")){
				psum5+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"水果类")){
				psum6+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"五谷类")){
				psum7+=vrecord.weight;
			}
		}
	}
	fclose(fp);
	if(sum>1900){
		printf("你今天已额外摄入，%d大卡，相当于吃了%.2f个冰淇淋，需要跳绳%.1f分钟\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
	}
	if(psum1>heat1){
		printf("你今天已额外摄入%s，%d克\n","油脂类",psum1-heat1);
	}
	if(psum2>heat2){
		printf("你今天已额外摄入%s，%d克\n","奶类",psum2-heat2);
	}
	if(psum3>heat3){
		printf("你今天已额外摄入%s，%d克\n","豆类",psum3-heat3);
	}
	if(psum4>heat4){
		printf("你今天已额外摄入%s，%d克\n","鱼、禽、肉、蛋",psum4-heat4);
	}
	if(psum5>heat5){
		printf("你今天已额外摄入%s，%d克\n","蔬菜类",psum5-heat5);
	}
	if(psum6>heat6){
		printf("你今天已额外摄入%s，%d克\n","水果类",psum6-heat6);
	}
	if(psum7>heat7){
		printf("你今天已额外摄入%s，%d克\n","五谷类",psum7-heat7);
	}
}
void submenu(char filename[])
{
	int exit=0;
	int num;
	while(exit!=-1)
	{
		printf("|---------------------------------|\n");
		printf("|             饮食管理            |\n");
		printf("|---------------------------------|\n");
		printf("|          1.新增饮食记录         |\n");
		printf("|          2.删除饮食记录         |\n");
		printf("|          3.修改饮食记录         |\n");
		printf("|          4.查看指定日期记录     |\n");
		printf("|          5.初始化               |\n");//第一次使用饮食管理时使用 
		printf("|          0.退出                 |\n");
		printf("|---------------------------------|\n");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
				insert(filename);
				break;
			case 2:
				deleterecord(filename);
				break;
			case 3:
				modify(filename);
				break;
			case 4:
				view(filename);
				break;
			case 5:
				init(filename); 
				break;
			case 0:
				exit=-1;
				break;
			default:
				printf("请输入正确的数字\n");	
		}
	}
}
void fdelete(char filename[])
{
	printf("%s\n",filename);
	if(remove(filename)==0)
		printf("成功删除\n");
	else
		perror("remove\n");
}
void menu(char user_ID[])
{
	char filename[21];
	char disk[]="D:\\";
	char user[]="user_";
	char diet[]="_Diet";
	char txt[]=".txt";
	strcpy(filename,disk);
	strcat(filename,user);
	strcat(filename,user_ID);
	strcat(filename,diet);
	strcat(filename,txt);
	int exit=0;
	int num;
	while(exit!=-1)
	{
		printf("|---------------------------------|\n");
		printf("|             饮食管理            |\n");
		printf("|---------------------------------|\n");
		printf("|          1.进入饮食管理         |\n");
		printf("|          2.删除饮食管理文件     |\n");
		printf("|          0.退出                 |\n");
		printf("|---------------------------------|\n");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
				submenu(filename); 
				break;
			case 2:
				fdelete(filename);
				break;
			case 0:
				exit=-1;
				break;
			default:
				printf("请输入正确的数字\n");	
		}
	}
}

int main(){
	char user_ID[] = "0001";
	menu(user_ID);
	return 0;
}
