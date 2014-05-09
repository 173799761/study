/*********************************************************************
*********************本算法使用广度优先搜索的算法*********************
*********************本算法参考编程之美连连看思路*********************
*********************************************************************/
#include<stdio.h>
#include<stdlib.h>
/********************************************************************
     XLEN 表示连连看矩形的行数
	 YLEN 表示连连看矩形的列数
	 MAXNUM 表示正无穷
*********************************************************************/
#define XLEN 4
#define YLEN 4 
#define MAXNUM 10000 

/********************************************************************
     Point 表示图形中坐标点0<=x<XLEN,0<=y<YLEN
	 Node 链表的节点结构
	 Matrix[XLEN][YLEN]存放连连看图片情况，若有图片设置为1，没有图片用
	 0表示
	 Path[XLEN][YLEN] 存放起始点到终点的路径，最后从终点反向查找给出路
	 径
	 ListPre  待搜索链表的链头
	 ListCur  用于区分到扩展节点的层数，指向倒数第二层的最后一个节点
	 Listtail 待搜索链表的链头

	 SListPre 已经搜索节点节点组成的链表的表头
	 SListTail 已经搜索节点节点组成的链表的表尾
*********************************************************************/
typedef struct Point
{
	int x;
	int y;
};

typedef struct Node
{
	Point point;
	Node * next;
};

int Matrix[XLEN][YLEN] = {{1,0,0,1},{1,1,0,1},{1,1,0,1},{1,0,0,1}};
Point Path[XLEN][YLEN];
int cost[XLEN][YLEN];
Node* listPre = NULL;
Node* ListTail = NULL;
Node* ListCur = NULL;

Node* SListPre = NULL;
Node* SListTail = NULL;

int crossNum = 0; //连线拐角的个数这里假设点a->b->a这样的路径也算进一个拐角
/********************************************************************
     creatNode() 创建一个节点，用于添加到待搜索链表，已搜索链表不用创
	 建节点，只需要改变链表指针即可把节点从带搜索链表删除，添加到已搜
	 索链表
	 AddSList()添加节点到已搜索链表
	 AddList() 添加节点到待搜索链表
	 findPre() 查找给出节点的父节点
	 DeleteFromList()将待搜索链表中的符合条件的节点删除，包括该坐标处
	 不为空切不是终点的节点，已经搜索过的节点
	 FindChild()从四个方向上查找符合条件的节点，加入待搜索链表
	 isInList() 查看重点是否已经搜索到了
	 findWay() 广度优先搜索算法实现
*********************************************************************/
Node* creatNode(Point point) 
{
	Node* node =(Node*)malloc(sizeof(Node));
	node->point.x = point.x;
	node->point.y = point.y;
	node->next = NULL;
	return node;
}
void AddSList(Node* node)
{   
	if(SListPre==NULL)
	{
		SListPre = node;
		SListTail = node;
		return;
	}
	//如果已搜索链表中已经存在这个节点，就不用添加了
	for(Node* ptr =SListPre;ptr!=SListTail->next;ptr=ptr->next)
	{
		if(ptr->point.x=node->point.x&&ptr->point.y==node->point.y)
			return;
	}
	SListTail->next = node;
	SListTail = SListTail->next;
	
}

void AddList(Point pointA)
{
	Node* node = creatNode(pointA);
	if(listPre==NULL)
	{
		listPre = node;
		ListTail = node;
		ListCur = node;
	}
	else
	{
		ListTail->next = node;
		ListTail = node;
	}
}

//Node* popNode()
//{   
//	if(listPre!=NULL)
//	{
//	  Node * temp = listPre;
//      listPre = listPre->next;
//	  return temp;
//	}
//	else 
//		return NULL;
//
//}

Node* findPre(Node* tlistPre,Node* node)
{   
	Node* ptr = tlistPre;
	if(node==ptr) return NULL;
	while(ptr->next!=node&&ptr!=NULL)
	{
		ptr=ptr->next;
	}
	return ptr;
}

void DeleteFromList()//S0从S1中删除
{  
	Node* ptr1 = listPre; 
	Node* ptr0;
	while(ptr1!=ListTail->next)
	{
		bool flag = false;
		//已搜索链表中已经出现的节点需要删除
		for(Node* ptr2 = SListPre;ptr2!=SListTail->next;ptr2=ptr2->next)
		{
			if(ptr1->point.x==ptr2->point.x&&ptr1->point.y==ptr2->point.y)
			{
				flag = true;
				break;
			}
		}
		//那些已经存放图片的位置对应的节点需要删除
		if(Matrix[ptr1->point.x][ptr1->point.y]==1)
		{   
			   flag = true;
		}
		if(flag)
		{
			ptr0 = findPre(listPre,ptr1);
			if(ptr0==NULL)//如果是头结点被删除，表头指针后移
			{
				listPre = listPre->next;
			}
			else
			{
			   if(ptr1==ListTail)//如果是尾结点被删除，表尾指针前移
			   {
				  ListTail = ptr0;
			   }
			   if(ptr1==ListCur)//分割指针所指结点被删除，指针指向前一个节点
			   {
				   ListCur = ptr0;
			   }
			   ptr0->next = ptr1->next;
			}
		}
		ptr1=ptr1->next;

	}
}


void FindChild(Point point,Point pointB)//像上下左右四个方向上查找可扩展节点
{   
	int xl = point.x-1;
	while(xl>=0)
	{   
		Point p;
		//扩展到第一个有图片的节点为止
		if(Matrix[xl][point.y]==1)
		{   
			p.x = xl;
		    p.y = point.y;
			if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))//未被扩展的节点或者是终点
			{
		      Node* node = creatNode(p);
		      ListTail->next = node;
		      ListTail = node;
			  if(cost[point.x][point.y]+point.x-xl<cost[xl][point.y])
		      {
			    Path[xl][point.y] = point;
			    cost[xl][point.y] = cost[point.x][point.y]+point.x-xl;
			    //printf("<%d %d>  (%d)\n" ,xl,point.y,cost[xl][point.y]);
		      }
			}
			 break;
		}
		p.x = xl;
		p.y = point.y;
		if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))
		{
	       Node* node = creatNode(p);
	       ListTail->next = node;
	       ListTail = node;	
		   printf("<%d---%d>\n" ,cost[point.x][point.y],cost[xl][point.y]);
		   if(cost[point.x][point.y]+point.x-xl<cost[xl][point.y])
		   {
			  Path[xl][point.y] = point;
			  cost[xl][point.y] = cost[point.x][point.y]+point.x-xl;
			 // printf("<%d %d>  (%d)\n" ,xl,point.y,cost[xl][point.y]);
		   }
		}
		
		
		//路径问题
		xl--;
	}

	int xr = point.x+1;
	while(xr<XLEN)
	{   
		Point p;
		if(Matrix[xr][point.y]==1)
		{
			p.x = xr;
		    p.y = point.y;
			if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))
			{
		    Node* node = creatNode(p);
		    ListTail->next = node;
		    ListTail = node;
			if(cost[point.x][point.y]+xr-point.x<cost[xr][point.y])
		    {
			   Path[xr][point.y] = point;
			   cost[xr][point.y] = cost[point.x][point.y]+xr-point.x;
			   //printf("<%d %d>  (%d)\n" ,xr,point.y,cost[xr][point.y]);
		    }
			}
			break;
		}
		

		p.x = xr;
		p.y = point.y;
		if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))
		{
		  Node* node = creatNode(p);
		  ListTail->next = node;
		  ListTail = node;
		

		  if(cost[point.x][point.y]+xr-point.x<cost[xr][point.y])
		  {
			Path[xr][point.y] = point;
			cost[xr][point.y] = cost[point.x][point.y]+xr-point.x;
			//printf("<%d %d>  (%d)\n" ,xr,point.y,cost[xr][point.y]);
		  }
		}
		//路径问题
		xr++;
	}

	int yt = point.y-1;
	while(yt>=0)
	{   
		Point p;
		if(Matrix[point.x][yt]==1)
		{
		    p.x = point.x;
		    p.y = yt;
			if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))
		    {
		       Node* node = creatNode(p);
		       ListTail->next = node;
		       ListTail = node;
		       if(cost[point.x][point.y]+point.y-yt<cost[point.x][yt])
		       {
			      Path[point.x][yt] = point;
			      cost[point.x][yt] = cost[point.x][point.y]+point.y-yt;
			      //printf("<%d %d>  (%d)\n" ,point.x,yt,cost[point.x][yt]);
		       }
			}
			break;
		}
		p.x = point.x;
		p.y = yt;
		if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))
		{
		   Node* node = creatNode(p);
		   ListTail->next = node;
		   ListTail = node;
		

		   if(cost[point.x][point.y]+point.y-yt<cost[point.x][yt])
		   {
			Path[point.x][yt] = point;
			cost[point.x][yt] = cost[point.x][point.y]+point.y-yt;
			//printf("<%d %d>  (%d)\n" ,point.x,yt,cost[point.x][yt]);
		   }
		}
		yt--;
		//路径问题

	}
	int yb = point.y+1;
	while(yb<YLEN)
	{   
		Point p;
		if(Matrix[point.x][yb]==1)
		{
			
		    p.x = point.x;
		    p.y = yb;
			if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))
		    {
		        Node* node = creatNode(p);
		        ListTail->next = node;
		        ListTail = node;
			    if(cost[point.x][point.y]+yb-point.y<cost[point.x][yb])
		        {
			        Path[point.x][yb] = point;
			        cost[point.x][yb] = cost[point.x][point.y]+yb-point.y;
		         	//printf("<%d %d>  (%d)\n" ,point.x,yb,cost[point.x][yb]);
		        }
			}
			break;	
		}
		p.x = point.x;
		p.y = yb;
		if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))
		{
	        Node* node = creatNode(p);
	        ListTail->next = node;
		    ListTail = ListTail->next;

		    if(cost[point.x][point.y]+yb-point.y<cost[point.x][yb])
		    {
			    Path[point.x][yb] = point;
		    	cost[point.x][yb] = cost[point.x][point.y]+yb-point.y;
		    	//printf("<%d %d>  (%d)\n" ,point.x,yb,cost[point.x][yb]);
	    	}
		}
		yb++;
		//路径问题
	}
	/*printf("----添加后的S1链表为:");
	for(Node* ptr = listPre;ptr!=ListTail->next;ptr=ptr->next)
	{
		printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	}
	printf("\n");*/
}

bool isInList(Point pointB)
{   
	bool flag = false;
	for(Node* ptr = listPre;ptr!=ListTail->next;ptr=ptr->next)
	{
		if(ptr->point.x==pointB.x&&ptr->point.y==pointB.y)
		{
			flag = true;
			break;
		}
	}
	return flag;
}

bool findWay(Point pointA,Point pointB)
{   
	cost[pointA.x][pointA.y] = 0;
	AddList(pointA);//初始化
	while(crossNum<3)
	{    
		crossNum++;
		printf("\n第%d轮:\n",crossNum);
		for(Node* ptr = listPre;ptr!=ListCur->next;ptr=ptr->next)
		{   
			
			FindChild(ptr->point,pointB);
			AddSList(ptr);  
		}
		if(isInList(pointB)) return true;
		listPre = ListCur->next;
		ListCur = ListTail;
		DeleteFromList();
		printf("<SL>链表为:");
	    for(Node* ptr = SListPre;ptr!=SListTail->next;ptr=ptr->next)
	    {
	     printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	    }
	    printf("\n");
		printf("<S>链表为:");
	    for(Node* ptr = listPre;ptr!=ListTail->next;ptr=ptr->next)
	    {
		    printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	    }
	    printf("\n");
		
	}
	if(cost[pointB.x][pointB.y]<MAXNUM)
	{   
		return true;
	}
	else
		return false;
}
int main()
{   
	//初始化矩阵
	for(int i=0;i<XLEN;i++)
	{
		for(int j=0;j<YLEN;j++)
		{
			cost[i][j] = MAXNUM;
		}
	}

	Point pointA,pointB;
	pointA.x=0;
	pointA.y=0;
	pointB.x=3;
	pointB.y=3;

	if(findWay(pointA,pointB))
	{   
		printf("SL链表为:");
	    for(Node* ptr = SListPre;ptr!=SListTail->next;ptr=ptr->next)
	    {
	     printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	    }
	    printf("\n");
		printf("<S>链表为:");
	    for(Node* ptr = listPre;ptr!=ListTail->next;ptr=ptr->next)
	    {
		    printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	    }
	    printf("\n");

		printf("最短路径长度为：%d\n",cost[pointB.x][pointB.y]);

		Point p = pointB;
		printf("(%d,%d)",p.x,p.y);
		while(p.x!=pointA.x||p.y!=pointA.y)
		{
			p = Path[p.x][p.y];
			printf("<--(%d,%d)",p.x,p.y);
		}
		printf("\n");
	}
	else
	{
		printf("没有这样的路径！");
	}

	system("PAUSE");
	return 0;
}