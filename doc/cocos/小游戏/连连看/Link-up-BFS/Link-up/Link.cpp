/*********************************************************************
*********************���㷨ʹ�ù�������������㷨*********************
*********************���㷨�ο����֮��������˼·*********************
*********************************************************************/
#include<stdio.h>
#include<stdlib.h>
/********************************************************************
     XLEN ��ʾ���������ε�����
	 YLEN ��ʾ���������ε�����
	 MAXNUM ��ʾ������
*********************************************************************/
#define XLEN 4
#define YLEN 4 
#define MAXNUM 10000 

/********************************************************************
     Point ��ʾͼ���������0<=x<XLEN,0<=y<YLEN
	 Node ����Ľڵ�ṹ
	 Matrix[XLEN][YLEN]���������ͼƬ���������ͼƬ����Ϊ1��û��ͼƬ��
	 0��ʾ
	 Path[XLEN][YLEN] �����ʼ�㵽�յ��·���������յ㷴����Ҹ���·
	 ��
	 ListPre  �������������ͷ
	 ListCur  �������ֵ���չ�ڵ�Ĳ�����ָ�����ڶ�������һ���ڵ�
	 Listtail �������������ͷ

	 SListPre �Ѿ������ڵ�ڵ���ɵ�����ı�ͷ
	 SListTail �Ѿ������ڵ�ڵ���ɵ�����ı�β
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

int crossNum = 0; //���߹սǵĸ�����������a->b->a������·��Ҳ���һ���ս�
/********************************************************************
     creatNode() ����һ���ڵ㣬������ӵ����������������������ô�
	 ���ڵ㣬ֻ��Ҫ�ı�����ָ�뼴�ɰѽڵ�Ӵ���������ɾ������ӵ�����
	 ������
	 AddSList()��ӽڵ㵽����������
	 AddList() ��ӽڵ㵽����������
	 findPre() ���Ҹ����ڵ�ĸ��ڵ�
	 DeleteFromList()�������������еķ��������Ľڵ�ɾ�������������괦
	 ��Ϊ���в����յ�Ľڵ㣬�Ѿ��������Ľڵ�
	 FindChild()���ĸ������ϲ��ҷ��������Ľڵ㣬�������������
	 isInList() �鿴�ص��Ƿ��Ѿ���������
	 findWay() ������������㷨ʵ��
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
	//����������������Ѿ���������ڵ㣬�Ͳ��������
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

void DeleteFromList()//S0��S1��ɾ��
{  
	Node* ptr1 = listPre; 
	Node* ptr0;
	while(ptr1!=ListTail->next)
	{
		bool flag = false;
		//�������������Ѿ����ֵĽڵ���Ҫɾ��
		for(Node* ptr2 = SListPre;ptr2!=SListTail->next;ptr2=ptr2->next)
		{
			if(ptr1->point.x==ptr2->point.x&&ptr1->point.y==ptr2->point.y)
			{
				flag = true;
				break;
			}
		}
		//��Щ�Ѿ����ͼƬ��λ�ö�Ӧ�Ľڵ���Ҫɾ��
		if(Matrix[ptr1->point.x][ptr1->point.y]==1)
		{   
			   flag = true;
		}
		if(flag)
		{
			ptr0 = findPre(listPre,ptr1);
			if(ptr0==NULL)//�����ͷ��㱻ɾ������ͷָ�����
			{
				listPre = listPre->next;
			}
			else
			{
			   if(ptr1==ListTail)//�����β��㱻ɾ������βָ��ǰ��
			   {
				  ListTail = ptr0;
			   }
			   if(ptr1==ListCur)//�ָ�ָ����ָ��㱻ɾ����ָ��ָ��ǰһ���ڵ�
			   {
				   ListCur = ptr0;
			   }
			   ptr0->next = ptr1->next;
			}
		}
		ptr1=ptr1->next;

	}
}


void FindChild(Point point,Point pointB)//�����������ĸ������ϲ��ҿ���չ�ڵ�
{   
	int xl = point.x-1;
	while(xl>=0)
	{   
		Point p;
		//��չ����һ����ͼƬ�Ľڵ�Ϊֹ
		if(Matrix[xl][point.y]==1)
		{   
			p.x = xl;
		    p.y = point.y;
			if(cost[p.x][p.y]==MAXNUM||(p.x==pointB.x&&p.y==pointB.y))//δ����չ�Ľڵ�������յ�
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
		
		
		//·������
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
		//·������
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
		//·������

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
		//·������
	}
	/*printf("----��Ӻ��S1����Ϊ:");
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
	AddList(pointA);//��ʼ��
	while(crossNum<3)
	{    
		crossNum++;
		printf("\n��%d��:\n",crossNum);
		for(Node* ptr = listPre;ptr!=ListCur->next;ptr=ptr->next)
		{   
			
			FindChild(ptr->point,pointB);
			AddSList(ptr);  
		}
		if(isInList(pointB)) return true;
		listPre = ListCur->next;
		ListCur = ListTail;
		DeleteFromList();
		printf("<SL>����Ϊ:");
	    for(Node* ptr = SListPre;ptr!=SListTail->next;ptr=ptr->next)
	    {
	     printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	    }
	    printf("\n");
		printf("<S>����Ϊ:");
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
	//��ʼ������
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
		printf("SL����Ϊ:");
	    for(Node* ptr = SListPre;ptr!=SListTail->next;ptr=ptr->next)
	    {
	     printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	    }
	    printf("\n");
		printf("<S>����Ϊ:");
	    for(Node* ptr = listPre;ptr!=ListTail->next;ptr=ptr->next)
	    {
		    printf("<%d,%d> ",ptr->point.x,ptr->point.y);
	    }
	    printf("\n");

		printf("���·������Ϊ��%d\n",cost[pointB.x][pointB.y]);

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
		printf("û��������·����");
	}

	system("PAUSE");
	return 0;
}