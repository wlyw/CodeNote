#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <functional>
#define MAXNUM 500    //������������������
#define NODE 1        //VO�е�ǩ���ڵ�������

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

//////////////////////ȫ�ֱ���/////////////////////////

int num;            //ԭʼ���ݸ���
trnode tr[MAXNUM];     //����������
int sj,xj;          //��ѯ�����½�
rode_path lpath,rpath;   //����·��
///////////////////////////////////////////////////////

//���ź���
int comp(const void * a,const void * b)
{
    return *(int *)a - *(int *)b;
}

//hash����
unsigned int APHash(char *str)
{
    unsigned int hash = 0;
    int i;

    for(i=0;*str;i++)
    {
        if((i & 1) == 0)
        {
            hash^=((hash << 7)^(*str++)^(hash >> 3));
        }
        else
        {
            hash^=(~((hash << 11)^(*str++)^(hash >> 5)));
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
    }
    crtree(n/2);
}

//������ѯ�����ݽ���
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
        if(tr[i].data>down)
        {
            printf("%d ",tr[i].data);
            if(!flag)
            {
                xj=i;
                flag=true;
            }
        }
    }
    return;
}

//���߽���·��
void leftbr(int x_xj)
{
    if(x_xj==NODE)
        return;
    if(x_xj%2!=0)
    {
        lpath.index[lpath.nowcount]=x_xj;
        lpath.data_hash[lpath.nowcount]=tr[x_xj].data_hash;
        lpath.nowcount++;
        leftbr((x_xj-1)/2);
    }
    else leftbr(x_xj/2);
    return;
}

//�ұ߽���·��
void rightbr(int x_xj)
{
    if(x_xj==NODE)
        return;
    if(x_xj%2==0)
    {
        rpath.index[rpath.nowcount]=x_xj;
        rpath.data_hash[rpath.nowcount]=tr[x_xj].data_hash;
        rpath.nowcount++;
        rightbr(x_xj/2);
    }
    else leftbr((x_xj-1)/2);
    return;
}

//����VO
void printvo()
{
    int i=0;
    //�������½�
    printf("���½�Ϊ:%d %d",xj,sj);

    //��������·��
    printf("��·��Ϊ:\n");
    for(i=0;i<lpath.nowcount;i++)
    {
        printf("%d.%d %s\n",i,lpath.index[i],lpath.data_hash[i].c_str());
    }
    printf("��·��Ϊ:\n");
    for(i=0;i<rpath.nowcount;i++)
    {
        printf("%d.%d %s\n",i,rpath.index[i],rpath.data_hash[i].c_str());
    }
}

//��ѯ����
void findnode()
{
    int up,down; //��ѯ������
    //�������ݽ���
    printf("����Ҫ��ѯ�ķ�Χ:\n");
    scanf("%d%d",&down,&up);
    print(down,up);

    //����VO

    //��ʼ��·��
    lpath.nowcount=0;
    rpath.nowcount=0;
    //��������·��
    leftbr(xj);
    rightbr(sj);

    //����VO
    printvo();
}

int main(void)
{
    //����ԭʼ���ݲ���������
	int original[100];

	scanf("%d",&num);
	for(int i=0;i<num;i++)
        scanf("%d",&original[i]);
    qsort(original,num,sizeof(original[0]),comp);

    //������N��Ҷ�ӽڵ�����������

    //Ҷ�ӽڵ�
    for(int i=num;i<num*2;i++)
    {
        tr[i].data=original[i-num];
        tr[i].data_hash=hashdata(tr[i].data);
    }
    //����������
    crtree(num/2);

    int a;
    do
    {
        printf("��������Ҫִ�еĲ�����\n");
        printf("0���˳�\n");
        printf("1����ѯ\n");
        scanf("%d",&a);
        if(a==1)
            findnode();
    }while(a!=0);
    return 0;
}
