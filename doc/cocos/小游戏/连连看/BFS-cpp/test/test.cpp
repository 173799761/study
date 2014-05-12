// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "Node.h"
#include "Map.h"
#include "Point.h"
using namespace std;

typedef list<Node*> ListNode;
ListNode m_listNode1;
ListNode m_listNode2;





int _tmain(int argc, _TCHAR* argv[])
{

	Node * _node1 =  new Node(Point(0,0));
	Node * _node2 =  new Node(Point(3,3));
	Map _map;
	_map.init(_node1);


		_map.find(_node1,_node2);
		_map.checkDup();
		_map.pushBack();

	
		Map::NodeVecPtr _pVec;
		bool _flag(false);


		while (_flag == false)
		{
			_map.getCachVec(_pVec);

			for (auto itr : _pVec)
			{
				_map.find(itr,_node2);
				_flag = _map.isFindTarget();
				if (_flag == true)
				{
					break;
				}
				_map.checkDup();
				_map.pushBack();
			}

			if (_flag == true)
			{
				break;
			}
		}

		//while (_node2->isEqual(_node1) == false)
		//{

		//}
		cout << "·��Ϊ : " << _map.getPath(_node1->getPoint(),_node2->getPoint()) << endl;
		cout << "���·������Ϊ :" << _map.getCost() << endl;
		system("PAUSE");

	return 0;
}

