#include <bits/stdc++.h>
using namespace std;
#define MaxSize 100
#define ElemType int
#define Status int
#define LIST_INIT_SIZE 100 
#define LISTINCREMENT 10 
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define TRUE 1
#define FALSE 0
typedef struct LNode
{
	ElemType data; // data为抽象元素类型
	struct LNode *next; // next为指针类型
}LNode, *LinkList;

void visit(ElemType c) /* ListTraverse()调用的函数(类型要一致) */
{
   printf("%d ",c);
}

Status CmpGreater(ElemType data, ElemType e) 
{
    return data > e ? TRUE : FALSE;
}

Status DestoryList(LinkList &L)
{
	// 销毁链表
	LinkList p;
	if (NULL == L) // 确保链表存在
		return ERROR;
	p = L;
	while (p != NULL)
	{
		p = L->next;
		free(L);
		L = p;
	}
	L = NULL;
	return OK;
}

Status CleaeList(LinkList &L)
{
	// 链表置空
	LinkList p, q;
	if (NULL == L)
		return ERROR;
	p = L->next;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	L->next = NULL;
	return OK;
}

Status ListEmpty(LinkList L)
{
	// 判断链表是否为空
	bool flag = (NULL == L->next && NULL != L) ?  true : false;
	if (flag) return TRUE;
	return FALSE;
}

int ListLength(LinkList L)
{
	// 返回链表元素个数
	if (NULL == L || NULL == L->next)
		return 0;
	int count = 0;
	LinkList p = L->next;
	while (p)
	{
		count ++;
		p = p->next;
	}
	return count;
}

int LocateElem(LinkList L, ElemType e, Status(Compare)(ElemType, ElemType))
{
	// 返回首个与e满足Compare关系的元素位序
 	if (NULL == L || NULL == L->next)
 		return 0;
 	int i = 1;
 	LinkList p = L->next;
 	if (p != NULL && !Compare(p->data, e))
 	{
 		i++;
 		p = p->next;
 	}
 	if (p != NULL) return i;
 	return 0;
}

Status PriorElem(LinkList L, ElemType cur, ElemType &pre)
{
	// 返回前驱
	if (NULL == L || NULL == L->next)
		return ERROR;
	LinkList p = L->next;
	if (p->data == cur) // 无前驱
		return ERROR;
	LinkList q = p->next;
	if (q != NULL && q->data != cur)
	{
		p = q;
		q = q->next;
	}
	if (NULL == q)
		return ERROR;
	pre = p->data;
	return OK;
}

Status NextElem(LinkList L, ElemType cur, ElemType &nex)
{
	// 返回后继
	if (NULL == L || NULL == L->next)
		return ERROR;
	LinkList p = L->next;
	if (p->next != NULL && p->data != cur)
		p = p->next;
	if (NULL == p->next)
		return ERROR;
	nex = p->next->data;
	return OK;
}

void ListTraverse(LinkList L, void(visit)(ElemType))
{
	// 遍历
	if (NULL == L || NULL == L->next)
		return;
	LinkList p = L->next;
	while (p != NULL)
	{
		visit(p->data);
		p = p->next;
	}
	putchar('\n');
}

LinkList creatNode01()
{
	// 生成先进先出单链表（链式队列）
	LinkList head, tail, p;
	head = (LinkList)malloc(sizeof(LNode));
	ElemType e;
	tail = head;
	scanf("%d", &e);
	while (e != 0)
	{
		p = (LinkList)malloc(sizeof(LNode));
		p->data = e;
		tail->next = p;
		tail = p;
		scanf("%d", &e);
	}
	tail->next = NULL;
	return head;
}

LinkList creatNode02()
{
	// 生成后进先出单链表（链式栈）
	LinkList head, p;
	ElemType e;
	head = (LinkList)malloc(sizeof(LNode));
	head->next = NULL;
	scanf("%d", &e);
	while(e != 0)
	{
		p = (LinkList)malloc(sizeof(LNode));
		p->data = e;
		p->next = head->next;
		head->next = p;
		scanf("%d", &e);
	}
	return head;
}

void creatNode03(LinkList &head, ElemType e)
{
	// 生成不带表头递增有序单链表算法
	LinkList q = NULL, p = head, f; // p,q扫描，查找插入位置
	while (p != NULL && e > p->data)
	{
		q = p;
		p = p->next;
	}
	f = (LinkList)malloc(sizeof(LNode));
	f->data = e;
	if (NULL == p)
	{
		f->next = NULL;
		if (NULL == q)
			head = f; // 对空表的插入
		else
			q->next = f; // 作为最后一个结点插入
	}
	else if (NULL == q) // 作为第一个结点插入
	{
		f->next = p;
		head = f;
	}
	else  // 一般情况插入新结点
	{
		f->next = p;
		q->next = f;
	}
}

void creatNode04(LinkList head, ElemType e)
{
	// 生成带表头递增有序单链表算法
	LinkList q = head, p = head->next, f;
	while (p && e > p->data)
	{
		q = p;
		p = p->next;
	}
	f = (LinkList)malloc(sizeof(LNode));
	f->data = e;
	f->next = p;
	q->next = f;
}

Status IninList(LinkList &L)
{
	// 构建一个空的线性单链表
	L = (LinkList)malloc(sizeof(LNode));
	if (NULL == L) exit(OVERFLOW);
	L->next = NULL;
	return OK;
}

Status GetElem(LinkList L, int i, ElemType &e)
{
	// L为带头结点的单链表的头指针
	// 当第i个元素存在时，其值赋给e并返回OK,否则返回error
	LinkList p = L->next;
	int j = 1;
	while (p && j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
}

Status ListDelete(LinkList &L, int i, ElemType &e)
{
	// 在带头结点的单链表L中，删除第i个元素，并由e返回其值
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1) return ERROR; // 删除位置不合理
	LinkList q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

Status NodeDelete(LinkList head, ElemType e)
{
	// 在带表头结点的单链表中删除值为e的结点
	LinkList q = head, p = head->next;
	while (p && p->data != e)
	{
		q = p;
		p = p->next;
	}
	if (p)
	{
		q->next = p->next;
		free(p);
		return OK;
	}
	else
		return ERROR;
}

Status ListInsert(LinkList &L, int i, ElemType e)
{
	// 在带头结点的单链表L中第i个位置之前插入元素e
	LinkList p = L;
	int j = 0;
	while (p && j < i - 1) // 寻找第i-1个节点
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1) return ERROR;
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

void MergeList(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	// 归并La,Lb得到Lc
	LinkList pa = La->next, pb = Lb->next, pc;
	La = pc = La; // 用La的头结点作为Lc的头结点
	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb; // 插入剩余段
	free(Lb);
	La = NULL;
	Lb = NULL;
}

int main(int argc, char const *argv[])
{
	cout << "creatNode01" << endl;
	LinkList L1 = creatNode01();
	ListTraverse(L1, visit);
	cout << "creatNode02" << endl;
	LinkList L2 = creatNode02();
	ListTraverse(L2, visit);
	cout << "creatNode03" << endl;
	LinkList head1 = NULL;
	ElemType e;
	cin >> e;
	while (e != 0)
	{
		creatNode03(head1, e);
		cin >> e;
	}
	cout << "creatNode04" << endl;
	LinkList head2 = (LinkList)malloc(sizeof(LNode));
	head2->next = NULL;
	cin >> e;
	while (e != 0)
	{
		creatNode04(head2, e);
		cin >> e;
	}
	cout << "IninList" << endl;
	LinkList L;
	IninList(L);
	cout << "ListEmpty" << endl;
	ListEmpty(L) ? cout << "Yes" : cout << "No";
	cout << endl;
	cout << "ListInsert" << endl;
	for (int i = 1; i <= 8; i++)
		ListInsert(L, i, 2 * i);
	cout << "ListTraverse" << endl;
	ListTraverse(L, visit);
	cout << "ListLength" << endl;
	cout << ListLength(L) << endl;
	cout << "ListDelete" << endl;
	OK == ListDelete(L, 6, e) ? cout << e : cout << "ERROR";
	cout << endl;
	ListTraverse(L, visit);
	cout << "GetElem" << endl;
	cout << GetElem(L, 4, e);
	cout << "LocateElem" << endl;
	int i = LocateElem(L, 7, CmpGreater);
	GetElem(L, i, e);
	cout << e << endl;
	cout << "PriorElem" << endl;
	ElemType cur = 6;
	if (OK == PriorElem(L, cur, e))
		cout << e << endl;
	else
		cout << "ERROR" << endl;
	cout << "NextElem" << endl;
	if (OK == NextElem(L, cur, e))
		cout << e << endl;
	else
		cout << "ERROR" << endl;
	cout << "CleaeList" << endl;
	cout << "Before" << endl;
	ListEmpty(L) ? cout << "Yes" << endl : cout << "No" << endl;
	cout << "After" << endl;
	CleaeList(L);
	ListEmpty(L) ? cout << "Yes" << endl : cout << "No" << endl;
	cout << "DestoryList" << endl;
	cout << "Before" << endl;
	L ? cout << "Yes" << endl : cout << "No" << endl;
	DestoryList(L);
	cout << "After" << endl;
	L ? cout << "Yes" << endl : cout << "No" << endl;
	cout << "MergeList" << endl;
	LinkList Lc;
	MergeList(L1, L2, Lc);
	ListTraverse(Lc, visit);
	return 0;
}
