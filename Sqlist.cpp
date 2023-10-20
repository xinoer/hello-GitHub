#include <stdio.h>
#include <stdlib.h>

#define TRUR 1
#define FNLSE 0
#define OK 1
# define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2
typedef int Status;

#define MAXSIZE 100
#define ElemType int

typedef struct 
{
	ElemType *elem;
	int length;
}SqList;

Status InitList(SqList &L){
	//构造一个空的顺序表
	L.elem=new ElemType [MAXSIZE];
	if(!L.elem)
		exit (OVERFLOW);
	L.length=0;
	return OK;
}

Status GetElem(SqList &L,int i,ElemType &e){
	//顺序表取第i个位置的值
	if(i<1||i>L.length)//判断i值是否合理
		return ERROR;
	e=L.elem[i-1];//第i-1个单元存储i值
	return OK;
}

int LocateElem(SqList L,ElemType e){
	//在顺序表L中查找值为e的元素，返回其序号
	for(int i=0;i<L.length;i++)
		if(L.elem[i]==e)
			return i+1;//查找成功，返回序号i+1
	return 0;
}

Status ListInert(SqList &L,int i,ElemType e){
	//在顺序表L中第i个位置之前插入新的元素e，i值合法范围是1-L.length-1
	if((i<1)||(i>L.length+1))
		return ERROR;//i小于1或者i大于表长，则返回错误
	if(L.length==MAXSIZE)
		return ERROR;//如果L的长度等于最大值，则返回错误
	int j=L.length-1;
	for(j;j>=1;j--)
		L.elem[j+1]=L.elem[j];//插入位置之后的元素，倒序开始，往后移动一个位置
	L.elem[i-1]=e;//将新的元素放入i位置
	L.length=L.length+1;//表长+1
	return OK;
}

int main(){
	SqList L[MAXSIZE];
	InitList(*L);//初始化L

}