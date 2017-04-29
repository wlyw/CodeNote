#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <functional>
#define MAXNUM 500    //�����������������
#define NODE 1        //VO�е�ǩ���ڵ������

using namespace std;

typedef struct trnode_s      //�������ڵ����ݽṹ
{
    int data;
	string data_hash;
}trnode;

typedef struct rode_path     //·�����ݽṹ
{
    int nowcount;
    int index[100];
    string data_hash[100];
}rode_path;

typedef struct VO           //VO���ݽṹ
{
	int nowcount;
	trnode vd[MAXNUM];
}vo;

//////////////////////ȫ�ֱ���/////////////////////////

int num;            //ԭʼ���ݸ���
trnode tr[MAXNUM];     //����������
int sj,xj;          //��ѯ�����½�
rode_path lpath,rpath;   //����·��
vo vonode;          //vo���
///////////////////////////////////////////////////////

//���ź���
int comp(const void * a,const void * b)
{
    return *(int *)a - *(int *)b;
}

//hash����
unsigned int APHash(string str)
{
    unsigned int hash = 0;
    int i;

    for(i=0;str[i];i++)
    {
        if((i & 1) == 0)
        {
            hash^=((hash << 7)^(str[i])^(hash >> 3));
        }
        else
        {
            hash^=(~((hash << 11)^(str[i])^(hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF);
}

//hash����
string hashdata(int data)
{
    char b[100];
    itoa(data,b,10);
    int n=APHash(b);
    char re[100];
    itoa(n,re,10);
    return re;
}

//create bitree
void crtree(int n)
{
    if(n==0)
        return;
    for(int i=n;i<n*2;i++)
    {
        tr[i].data_hash=tr[i*2].data_hash;
        tr[i].data_hash += tr[i*2+1].data_hash;
		int n=APHash(tr[i].data_hash.c_str());
		char re[100];
		itoa(n,re,10);
		tr[i].data_hash=re;
    }
    crtree(n/2);
}

//�����ѯ�����ݽ��
void print(int down,int up)
{
    bool flag=false;
    for(int i=num;i<num*2;i++)
    {
        if(tr[i].data>up)
        {
            sj=i-1;
            return;
        }
		if(tr[i].data==up)
        {
            sj=i;
            return;
        }
        if(tr[i].data>down)
        {
            printf("%d ",tr[i].data);
			//���vonode
			vonode.vd[vonode.nowcount].data=i;    //vonode�е�data�����Ϊ����ֵ
			vonode.vd[vonode.nowcount].data_hash=tr[i].data_hash;
			vonode.nowcount++;

            if(!flag)
            {
                xj=i;
                flag=true;
            }
        }
		if(tr[i].data==down)
        {
            if(!flag)
            {
                xj=i;
                flag=true;
            }
        }
    }
	if(sj==0)
		sj=num*2-1;
    return;
}

//��߽��·��
void leftbr(int x_xj)
{
    if(x_xj==NODE)
        return;
    if(x_xj%2!=0)
    {
        lpath.index[lpath.nowcount]=x_xj-1;
        lpath.data_hash[lpath.nowcount]=tr[x_xj-1].data_hash;
        lpath.nowcount++;

		//���vonode
		vonode.vd[vonode.nowcount].data=x_xj-1;    
		vonode.vd[vonode.nowcount].data_hash=tr[x_xj-1].data_hash;
		vonode.nowcount++;

        leftbr((x_xj-1)/2);
    }
    else leftbr(x_xj/2);
    return;
}

//�ұ߽��·��
void rightbr(int x_xj)
{
    if(x_xj==NODE)
        return;
    if(x_xj%2==0)
    {
        rpath.index[rpath.nowcount]=x_xj+1;
        rpath.data_hash[rpath.nowcount]=tr[x_xj+1].data_hash;
        rpath.nowcount++;

		//���vonode
		vonode.vd[vonode.nowcount].data=x_xj+1;    
		vonode.vd[vonode.nowcount].data_hash=tr[x_xj+1].data_hash;
		vonode.nowcount++;

        rightbr(x_xj/2);
    }
    else rightbr((x_xj-1)/2);
    return;
}

//���VO
void printvo()
{
    int i=0;
    //������½�
	printf("\n���½�Ϊ:%d %d\n",tr[xj].data,tr[sj].data);
	//���vonode
	vonode.vd[vonode.nowcount].data=xj;    
	vonode.vd[vonode.nowcount].data_hash=tr[xj].data_hash;
	vonode.nowcount++;
	vonode.vd[vonode.nowcount].data=sj;    
	vonode.vd[vonode.nowcount].data_hash=tr[sj].data_hash;
	vonode.nowcount++;

    //�������·��
    printf("��·��Ϊ:\n");
    for(i=0;i<lpath.nowcount;i++)
    {
        printf("%d.%d %s\n",i+1,lpath.index[i],lpath.data_hash[i].c_str());
    }
    printf("��·��Ϊ:\n");
    for(i=0;i<rpath.nowcount;i++)
    {
        printf("%d.%d %s\n",i+1,rpath.index[i],rpath.data_hash[i].c_str());
    }
}

//��ѯ����
void findnode()
{
    int up,down; //��ѯ������

	//��ʼ��VO���
	vonode.nowcount=0;

    //������ݽ��
    printf("����Ҫ��ѯ�ķ�Χ:\n");
    scanf("%d%d",&down,&up);
    print(down,up);

    //���VO

    //��ʼ��·��
    lpath.nowcount=0;
    rpath.nowcount=0;
    //�������·��
    leftbr(xj);
    rightbr(sj);

    //���VO
    printvo();
}

//�ؽ�����
//������֪��ѯ�����hashֵ���߽�hashֵ�Լ�·��hashֵ�ع���NODE��hashֵ
string reconstructor(int needpath)
{
	for(int i=0;i<vonode.nowcount;i++)
		if(needpath==vonode.vd[i].data)
			return vonode.vd[i].data_hash;

	string temp=reconstructor(needpath*2)+reconstructor((needpath*2)+1);

	int n=APHash(temp);
	char re[100];
	itoa(n,re,10);
	temp=re;
	return temp;
}

int main(void)
{
    //����ԭʼ���ݲ���������
	int original[100];

	scanf("%d",&num);
	for(int i=0;i<num;i++)
        scanf("%d",&original[i]);
    qsort(original,num,sizeof(original[0]),comp);

    //������N��Ҷ�ӽڵ����������

    //Ҷ�ӽڵ�
    for(int i=num;i<num*2;i++)
    {
        tr[i].data=original[i-num];
        tr[i].data_hash=hashdata(tr[i].data);
    }
    //��������
    crtree(num/2);

    int a;
    do
    {
        printf("��������Ҫִ�еĲ�����\n");
        printf("0���˳�\n");
        printf("1����ѯ\n");
		printf("2���ؽ�\n");
        scanf("%d",&a);
        if(a==1)
            findnode();
		if(a==2)
		{
			string temp=reconstructor(NODE);
			printf("ǩ���ڵ�hashֵΪ��%s\n",temp.c_str());
		}
    }while(a!=0);
    return 0;
}
