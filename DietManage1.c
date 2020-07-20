#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include "DietManage.h"

typedef struct record{
	char time[11];  //�ò����� 
	char dtime[5];  //����� 
	char category[15];//ʳ�����
	char fname[10]; //ʳ������
	int weight; //ʳ�����
	int qheat; //����
	struct record *next; 
}record,*linklist;
void init(char filename[])
{
	FILE *fp=NULL;
	fp=fopen(filename,"w");
	fprintf(fp,"%s","�ò����� ����� ʳ����� ʳ������ ʳ����� ����");
	fclose(fp);
}
void insert(char filename[])
{
	char* stop_at = NULL;
	record nrecord;
	FILE *fp=NULL;
	int num,sum=0; //sumͳ�ƽ�����ܿ�·��,psumͳ�������ļ�¼��ʳ�����Ŀ�·�� 
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
	printf("�����ò����ڣ�");
	scanf("%s",nrecord.time);
	printf("ѡ������\n");
	printf("1.���\n2.���\n3.���\n");
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(nrecord.dtime,"���");
			break;
		case 2:
			strcpy(nrecord.dtime,"���");
			break;
		case 3:
			strcpy(nrecord.dtime,"���");
			break;
		default:
			printf("��������ȷ������\n");
			return ;	
	}
	printf("ѡ��ʳ�����\n");
	printf("1.��֬��\n2.����\n3.����\n4.�㡢�ݡ��⡢��\n5.�߲���\n6.ˮ����\n7.�����\n"); 
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(nrecord.category,"��֬��");
			strcpy(category,"��֬��");
			break;
		case 2:
			strcpy(nrecord.category,"����");
			strcpy(category,"����");
			break;
		case 3:
			strcpy(nrecord.category,"����");
			strcpy(category,"����");
			break;
		case 4:
			strcpy(nrecord.category,"�㡢�ݡ��⡢��");
			strcpy(category,"�㡢�ݡ��⡢��");
			break;
		case 5:
			strcpy(nrecord.category,"�߲���");
			strcpy(category,"�߲���");
			break;
		case 6:
			strcpy(nrecord.category,"ˮ����");
			strcpy(category,"ˮ����");
			break;	
		case 7:
			strcpy(nrecord.category,"�����");
			strcpy(category,"�����");
			break;
		default:
			printf("��������ȷ������\n");
			return ;	
	}
	printf("����ʳ������\n");
	scanf("%s",nrecord.fname);
	printf("ʳ�����\n");
	scanf("%d",&nrecord.weight);
	printf("ʳ���������󿨣�\n");
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
			if(!strcmp(nrecord.category,"��֬��")){
				psum1+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"����")){
				psum2+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"����")){
				psum3+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"�㡢�ݡ��⡢��")){
				psum4+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"�߲���")){
				psum5+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"ˮ����")){
				psum6+=nrecord.weight;
			}else if(!strcmp(nrecord.category,"�����")){
				psum7+=nrecord.weight;
			}  
		}
	}
	if(sum>1900){
		printf("������Ѷ������룬%d�󿨣��൱�ڳ���%.2f������ܣ���Ҫ����%.1f����\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
	}
	if(psum1>heat1){
		printf("������Ѷ�������%s��%d��\n","��֬��",psum1-heat1);
	}
	if(psum2>heat2){
		printf("������Ѷ�������%s��%d��\n","����",psum2-heat2);
	}
	if(psum3>heat3){
		printf("������Ѷ�������%s��%d��\n","����",psum3-heat3);
	}
	if(psum4>heat4){
		printf("������Ѷ�������%s��%d��\n","�㡢�ݡ��⡢��",psum4-heat4);
	}
	if(psum5>heat5){
		printf("������Ѷ�������%s��%d��\n","�߲���",psum5-heat5);
	}
	if(psum6>heat6){
		printf("������Ѷ�������%s��%d��\n","ˮ����",psum6-heat6);
	}
	if(psum7>heat7){
		printf("������Ѷ�������%s��%d��\n","�����",psum7-heat7);
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
	printf("1.��������ɾ��\n2.������������ɾ��\n");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
			printf("��������\n");
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
					if(!strcmp(q->category,"��֬��")){
						psum1+=q->weight;
					}else if(!strcmp(q->category,"����")){
						psum2+=q->weight;
					}else if(!strcmp(q->category,"����")){
						psum3+=q->weight;
					}else if(!strcmp(q->category,"�㡢�ݡ��⡢��")){
						psum4+=q->weight;
					}else if(!strcmp(q->category,"�߲���")){
						psum5+=q->weight;
					}else if(!strcmp(q->category,"ˮ����")){
						psum6+=q->weight;
					}else if(!strcmp(q->category,"�����")){
						psum7+=q->weight;
					}
				}
			}
			fclose(fp);
			if(sum>1900){
				printf("������Ѷ������룬%d�󿨣��൱�ڳ���%.2f������ܣ���Ҫ����%.1f����\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
			}
			if(psum1>heat1){
				printf("������Ѷ�������%s��%d��\n","��֬��",psum1-heat1);
			}
			if(psum2>heat2){
				printf("������Ѷ�������%s��%d��\n","����",psum2-heat2);
			}
			if(psum3>heat3){
				printf("������Ѷ�������%s��%d��\n","����",psum3-heat3);
			}
			if(psum4>heat4){
				printf("������Ѷ�������%s��%d��\n","�㡢�ݡ��⡢��",psum4-heat4);
			}
			if(psum5>heat5){
				printf("������Ѷ�������%s��%d��\n","�߲���",psum5-heat5);
			}
			if(psum6>heat6){
				printf("������Ѷ�������%s��%d��\n","ˮ����",psum6-heat6);
			}
			if(psum7>heat7){
				printf("������Ѷ�������%s��%d��\n","�����",psum7-heat7);
			}
			q=L;
			fp = fopen(filename, "w");
			fputs("�ò����� ����� ʳ����� ʳ������ ʳ����� ����",fp);	
			while(q->next!=NULL){
				fprintf(fp,"\n%s %s %s %s %d %d",q->next->time,q->next->dtime,q->next->category,q->next->fname,q->next->weight,q->next->qheat);
				q=q->next;
			}
			fclose(fp);
			break;
		case 2:
			printf("����Ҫɾ��������\n");
			scanf("%s",drecord.time);
			printf("ѡ������\n");
			printf("1.���\n2.���\n3.���\n");
			scanf("%d",&num);
			switch(num)
			{
				case 1:
					strcpy(drecord.dtime,"���");
					break;
				case 2:
					strcpy(drecord.dtime,"���");
					break;
				case 3:
					strcpy(drecord.dtime,"���");
					break;
				default:
					printf("��������ȷ������\n");
					return ;	
			}
			printf("ѡ��ʳ�����\n");
			printf("1.��֬��\n2.����\n3.����\n4.�㡢�ݡ��⡢��\n5.�߲���\n6.ˮ����\n7.�����\n"); 
			scanf("%d",&num);
			switch(num)
			{
				case 1:
					strcpy(drecord.category,"��֬��");
					strcpy(category,"��֬��");
					break;
				case 2:
					strcpy(drecord.category,"����");
					strcpy(category,"����");
					break;
				case 3:
					strcpy(drecord.category,"����");
					strcpy(category,"����");
					break;
				case 4:
					strcpy(drecord.category,"�㡢�ݡ��⡢��");
					strcpy(category,"�㡢�ݡ��⡢��");
					break;
				case 5:
					strcpy(drecord.category,"�߲���");
					strcpy(category,"�߲���");
					break;
				case 6:
					strcpy(drecord.category,"ˮ����");
					strcpy(category,"ˮ����");
					break;	
				case 7:
					strcpy(drecord.category,"�����");
					strcpy(category,"�����");
					break;
				default:
					printf("��������ȷ������\n");
					return ;	
			}
			printf("����ʳ������\n");
			scanf("%s",drecord.fname);
			printf("ʳ�����\n");
			scanf("%d",&drecord.weight);
			printf("ʳ���������󿨣�\n");
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
					if(!strcmp(q->category,"��֬��")){
						psum1+=q->weight;
					}else if(!strcmp(q->category,"����")){
						psum2+=q->weight;
					}else if(!strcmp(q->category,"����")){
						psum3+=q->weight;
					}else if(!strcmp(q->category,"�㡢�ݡ��⡢��")){
						psum4+=q->weight;
					}else if(!strcmp(q->category,"�߲���")){
						psum5+=q->weight;
					}else if(!strcmp(q->category,"ˮ����")){
						psum6+=q->weight;
					}else if(!strcmp(q->category,"�����")){
						psum7+=q->weight;
					} 
				}
			}
			fclose(fp);
			if(sum>1900){
				printf("������Ѷ������룬%d�󿨣��൱�ڳ���%.2f������ܣ���Ҫ����%.1f����\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
			}
			if(psum1>heat1){
				printf("������Ѷ�������%s��%d��\n","��֬��",psum1-heat1);
			}
			if(psum2>heat2){
				printf("������Ѷ�������%s��%d��\n","����",psum2-heat2);
			}
			if(psum3>heat3){
				printf("������Ѷ�������%s��%d��\n","����",psum3-heat3);
			}
			if(psum4>heat4){
				printf("������Ѷ�������%s��%d��\n","�㡢�ݡ��⡢��",psum4-heat4);
			}
			if(psum5>heat5){
				printf("������Ѷ�������%s��%d��\n","�߲���",psum5-heat5);
			}
			if(psum6>heat6){
				printf("������Ѷ�������%s��%d��\n","ˮ����",psum6-heat6);
			}
			if(psum7>heat7){
				printf("������Ѷ�������%s��%d��\n","�����",psum7-heat7);
			}
			q=L;
			fp = fopen(filename, "w");
			fputs("�ò����� ����� ʳ����� ʳ������ ʳ����� ����",fp);	
			while(q->next!=NULL){
				fprintf(fp,"\n%s %s %s %s %d %d",q->next->time,q->next->dtime,q->next->category,q->next->fname,q->next->weight,q->next->qheat);
				q=q->next;
			}
			fclose(fp);
			break;
		default:
			printf("��������ȷ������\n");
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
	printf("����Ŀ���¼\n");
	printf("���ڣ�");
	scanf("%s",mrecord1.time);
	printf("�����\n");
	printf("1.���\n2.���\n3.���\n");
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord1.dtime,"���");
			break;
		case 2:
			strcpy(mrecord1.dtime,"���");
			break;
		case 3:
			strcpy(mrecord1.dtime,"���");
			break;
		default:
			printf("��������ȷ������\n");
			return ;	
	}
	printf("ʳ�����\n");
	printf("1.��֬��\n2.����\n3.����\n4.�㡢�ݡ��⡢��\n5.�߲���\n6.ˮ����\n7.�����\n"); 
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord1.category,"��֬��");
			strcpy(category1,"��֬��");
			break;
		case 2:
			strcpy(mrecord1.category,"����");
			strcpy(category1,"����");
			heat1=100;
			break;
		case 3:
			strcpy(mrecord1.category,"����");
			strcpy(category1,"����");
			break;
		case 4:
			strcpy(mrecord1.category,"�㡢�ݡ��⡢��");
			strcpy(category1,"�㡢�ݡ��⡢��");
			break;
		case 5:
			strcpy(mrecord1.category,"�߲���");
			strcpy(category1,"�߲���");
			break;
		case 6:
			strcpy(mrecord1.category,"ˮ����");
			strcpy(category1,"ˮ����");
			break;	
		case 7:
			strcpy(mrecord1.category,"�����");
			strcpy(category1,"�����");
			break;
		default:
			printf("��������ȷ������\n");
			return ;	
	}
	printf("ʳ�����ƣ�");
	scanf("%s",mrecord1.fname);
	printf("ʳ�������");
	scanf("%d",&mrecord1.weight);
	printf("������");
	scanf("%d",&mrecord1.qheat); 
	printf("�����޸ĺ�ļ�¼\n");
	printf("���ڣ�");
	scanf("%s",mrecord2.time);
	printf("�����\n");
	printf("1.���\n2.���\n3.���\n");
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord2.dtime,"���");
			break;
		case 2:
			strcpy(mrecord2.dtime,"���");
			break;
		case 3:
			strcpy(mrecord2.dtime,"���");
			break;
		default:
			printf("��������ȷ������\n");
			return ;	
	}
	printf("ʳ�����\n");
	printf("1.��֬��\n2.����\n3.����\n4.�㡢�ݡ��⡢��\n5.�߲���\n6.ˮ����\n7.�����\n"); 
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			strcpy(mrecord2.category,"��֬��");
			strcpy(category2,"��֬��");
			break;
		case 2:
			strcpy(mrecord2.category,"����");
			strcpy(category2,"����");
			break;
		case 3:
			strcpy(mrecord2.category,"����");
			strcpy(category2,"����");
			break;
		case 4:
			strcpy(mrecord2.category,"�㡢�ݡ��⡢��");
			strcpy(category2,"�㡢�ݡ��⡢��");
			break;
		case 5:
			strcpy(mrecord2.category,"�߲���");
			strcpy(category2,"�߲���");
			break;
		case 6:
			strcpy(mrecord2.category,"ˮ����");
			strcpy(category2,"ˮ����");
			break;	
		case 7:
			strcpy(mrecord2.category,"�����");
			strcpy(category2,"�����");
			break;
		default:
			printf("��������ȷ������\n");
			return ;	
	}
	printf("ʳ�����ƣ�");
	scanf("%s",mrecord2.fname);
	printf("ʳ�������");
	scanf("%d",&mrecord2.weight);
	printf("������");
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
			if(!strcmp(q->category,"��֬��")){
				psum1+=q->weight;
			}else if(!strcmp(q->category,"����")){
				psum2+=q->weight;
			}else if(!strcmp(q->category,"����")){
				psum3+=q->weight;
			}else if(!strcmp(q->category,"�㡢�ݡ��⡢��")){
				psum4+=q->weight;
			}else if(!strcmp(q->category,"�߲���")){
				psum5+=q->weight;
			}else if(!strcmp(q->category,"ˮ����")){
				psum6+=q->weight;
			}else if(!strcmp(q->category,"�����")){
				psum7+=q->weight;
			} 
		}
	}
	fclose(fp);
	if(sum>1900){
		printf("������Ѷ������룬%d�󿨣��൱�ڳ���%.2f������ܣ���Ҫ����%.1f����\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
	}
	if(psum1>heat1){
		printf("������Ѷ�������%s��%d��\n","��֬��",psum1-heat1);
	}
	if(psum2>heat2){
		printf("������Ѷ�������%s��%d��\n","����",psum2-heat2);
	}
	if(psum3>heat3){
		printf("������Ѷ�������%s��%d��\n","����",psum3-heat3);
	}
	if(psum4>heat4){
		printf("������Ѷ�������%s��%d��\n","�㡢�ݡ��⡢��",psum4-heat4);
	}
	if(psum5>heat5){
		printf("������Ѷ�������%s��%d��\n","�߲���",psum5-heat5);
	}
	if(psum6>heat6){
		printf("������Ѷ�������%s��%d��\n","ˮ����",psum6-heat6);
	}
	if(psum7>heat7){
		printf("������Ѷ�������%s��%d��\n","�����",psum7-heat7);
	}
	q=L;
	fp = fopen(filename, "w");
	fputs("�ò����� ����� ʳ����� ʳ������ ʳ����� ����",fp);	
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
	printf("�����ѯ���ڣ�");
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
			if(!strcmp(vrecord.category,"��֬��")){
				psum1+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"����")){
				psum2+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"����")){
				psum3+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"�㡢�ݡ��⡢��")){
				psum4+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"�߲���")){
				psum5+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"ˮ����")){
				psum6+=vrecord.weight;
			}else if(!strcmp(vrecord.category,"�����")){
				psum7+=vrecord.weight;
			}
		}
	}
	fclose(fp);
	if(sum>1900){
		printf("������Ѷ������룬%d�󿨣��൱�ڳ���%.2f������ܣ���Ҫ����%.1f����\n",sum-1900,(sum-1)/150.0,(sum-1)/13.0);
	}
	if(psum1>heat1){
		printf("������Ѷ�������%s��%d��\n","��֬��",psum1-heat1);
	}
	if(psum2>heat2){
		printf("������Ѷ�������%s��%d��\n","����",psum2-heat2);
	}
	if(psum3>heat3){
		printf("������Ѷ�������%s��%d��\n","����",psum3-heat3);
	}
	if(psum4>heat4){
		printf("������Ѷ�������%s��%d��\n","�㡢�ݡ��⡢��",psum4-heat4);
	}
	if(psum5>heat5){
		printf("������Ѷ�������%s��%d��\n","�߲���",psum5-heat5);
	}
	if(psum6>heat6){
		printf("������Ѷ�������%s��%d��\n","ˮ����",psum6-heat6);
	}
	if(psum7>heat7){
		printf("������Ѷ�������%s��%d��\n","�����",psum7-heat7);
	}
}
void submenu(char filename[])
{
	int exit=0;
	int num;
	while(exit!=-1)
	{
		printf("|---------------------------------|\n");
		printf("|             ��ʳ����            |\n");
		printf("|---------------------------------|\n");
		printf("|          1.������ʳ��¼         |\n");
		printf("|          2.ɾ����ʳ��¼         |\n");
		printf("|          3.�޸���ʳ��¼         |\n");
		printf("|          4.�鿴ָ�����ڼ�¼     |\n");
		printf("|          5.��ʼ��               |\n");//��һ��ʹ����ʳ����ʱʹ�� 
		printf("|          0.�˳�                 |\n");
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
				printf("��������ȷ������\n");	
		}
	}
}
void fdelete(char filename[])
{
	printf("%s\n",filename);
	if(remove(filename)==0)
		printf("�ɹ�ɾ��\n");
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
		printf("|             ��ʳ����            |\n");
		printf("|---------------------------------|\n");
		printf("|          1.������ʳ����         |\n");
		printf("|          2.ɾ����ʳ�����ļ�     |\n");
		printf("|          0.�˳�                 |\n");
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
				printf("��������ȷ������\n");	
		}
	}
}

int main(){
	char user_ID[] = "0001";
	menu(user_ID);
	return 0;
}
