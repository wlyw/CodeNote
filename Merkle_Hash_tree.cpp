#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <functional>
#define MAXNUM 500    //二叉树数组最大容量
#define NODE 1        //VO中的签名节点的索引

using namespace std;

typedef struct trnode_s      //二叉树节点数据结构
{
    int data;
	string data_hash;
}trnode;

typedef struct rode_path     //路径数据结构
{
    int nowcount;
    int index[100];
    string data_hash[100];
}rode_path;

typedef struct VO           //VO数据结构
{
	int nowcount;
	trnode vd[MAXNUM];
}vo;

//////////////////////全局变量/////////////////////////

int num;            //原始数据个数
trnode tr[MAXNUM];     //二叉树数组
int sj,xj;          //查询的上下界
rode_path lpath,rpath;   //左右路径
vo vonode;          //vo结果
///////////////////////////////////////////////////////

//快排函数
int comp(const void * a,const void * b)
{
    return *(int *)a - *(int *)b;
}

//hash函数
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

//hash函数
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

//输出查询的数据结果
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
			//填充vonode
			vonode.vd[vonode.nowcount].data=i;    //vonode中的data保存的为索引值
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

//左边界的路径
void leftbr(int x_xj)
{
    if(x_xj==NODE)
        return;
    if(x_xj%2!=0)
    {
        lpath.index[lpath.nowcount]=x_xj-1;
        lpath.data_hash[lpath.nowcount]=tr[x_xj-1].data_hash;
        lpath.nowcount++;

		//填充vonode
		vonode.vd[vonode.nowcount].data=x_xj-1;    
		vonode.vd[vonode.nowcount].data_hash=tr[x_xj-1].data_hash;
		vonode.nowcount++;

        leftbr((x_xj-1)/2);
    }
    else leftbr(x_xj/2);
    return;
}

//右边界的路径
void rightbr(int x_xj)
{
    if(x_xj==NODE)
        return;
    if(x_xj%2==0)
    {
        rpath.index[rpath.nowcount]=x_xj+1;
        rpath.data_hash[rpath.nowcount]=tr[x_xj+1].data_hash;
        rpath.nowcount++;

		//填充vonode
		vonode.vd[vonode.nowcount].data=x_xj+1;    
		vonode.vd[vonode.nowcount].data_hash=tr[x_xj+1].data_hash;
		vonode.nowcount++;

        rightbr(x_xj/2);
    }
    else rightbr((x_xj-1)/2);
    return;
}

//输出VO
void printvo()
{
    int i=0;
    //输出上下界
	printf("\n上下界为:%d %d\n",tr[xj].data,tr[sj].data);
	//填充vonode
	vonode.vd[vonode.nowcount].data=xj;    
	vonode.vd[vonode.nowcount].data_hash=tr[xj].data_hash;
	vonode.nowcount++;
	vonode.vd[vonode.nowcount].data=sj;    
	vonode.vd[vonode.nowcount].data_hash=tr[sj].data_hash;
	vonode.nowcount++;

    //输出左右路径
    printf("左路径为:\n");
    for(i=0;i<lpath.nowcount;i++)
    {
        printf("%d.%d %s\n",i+1,lpath.index[i],lpath.data_hash[i].c_str());
    }
    printf("右路径为:\n");
    for(i=0;i<rpath.nowcount;i++)
    {
        printf("%d.%d %s\n",i+1,rpath.index[i],rpath.data_hash[i].c_str());
    }
}

//查询操作
void findnode()
{
    int up,down; //查询上下限

	//初始化VO结果
	vonode.nowcount=0;

    //输出数据结果
    printf("输入要查询的范围:\n");
    scanf("%d%d",&down,&up);
    print(down,up);

    //输出VO

    //初始化路径
    lpath.nowcount=0;
    rpath.nowcount=0;
    //求出左右路径
    leftbr(xj);
    rightbr(sj);

    //输出VO
    printvo();
}

//重建函数
//根据已知查询结果的hash值、边界hash值以及路径hash值重构出NODE的hash值
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
    //输入原始数据并进行排序
	int original[100];

	scanf("%d",&num);
	for(int i=0;i<num;i++)
        scanf("%d",&original[i]);
    qsort(original,num,sizeof(original[0]),comp);

    //构建有N个叶子节点的满二叉树

    //叶子节点
    for(int i=num;i<num*2;i++)
    {
        tr[i].data=original[i-num];
        tr[i].data_hash=hashdata(tr[i].data);
    }
    //填充二叉树
    crtree(num/2);

    int a;
    do
    {
        printf("请输入你要执行的操作：\n");
        printf("0、退出\n");
        printf("1、查询\n");
		printf("2、重建\n");
        scanf("%d",&a);
        if(a==1)
            findnode();
		if(a==2)
		{
			string temp=reconstructor(NODE);
			printf("签名节点hash值为：%s\n",temp.c_str());
		}
    }while(a!=0);
    return 0;
}
