#include"CMap.h"
#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
CMap::CMap(int capacity) 
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];
	m_pMatrix = new int[m_iCapacity * m_iCapacity];
	//memset(m_pMatrix,0,m_iCapacity*m_iCapacity*sizeof(int)); //初始化矩阵每个元素赋值0，设置矩阵空间
	for (int i = 0; i < m_iCapacity * m_iCapacity;i++) 
	{
		m_pMatrix[i] = 0;
	 }

}
CMap::~CMap() 
{
	delete[]m_pNodeArray;
	delete[]m_pMatrix;

}
bool CMap::addNode(Node* pNode) 
{
	if (pNode == NULL) 
	{
		return false;
	}
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;
	m_iNodeCount++;
	return true;
}
void CMap::resetNode() 
{
	for (int i = 0; i < m_iNodeCount; i++) 
	{
		m_pNodeArray[i].m_bIsVisited = false;
	}
}
bool CMap::setValueToMatrixForDirectedGraph(int row,int col,int val)
{
	if (row < 0 || row >= m_iCapacity) 
	{
		return false;
	}
	if (col < 0 || col >= m_iCapacity) 
	{
		return false;
	}

	m_pMatrix[row * m_iCapacity + col] = val;
	//cout << "direction:" << row * m_iCapacity + col << endl;
	return true;
}
bool CMap::setValueToMatrixForUndirectedGraph(int row, int col, int val) 
{
	if (row < 0 || row >= m_iCapacity) 
	{
		return false;
	}
	if (col < 0 || col >= m_iCapacity) 
	{
		return false;
	}
	m_pMatrix[row * m_iCapacity + col] = val;
	m_pMatrix[col * m_iCapacity + row] = val;
	return true;
}
bool CMap::getValueFromMatrix(int row, int col, int& val) 
{
	if (row < 0 || row >= m_iCapacity) 
	{
		return false;
	}
	if (col < 0 || col >= m_iCapacity) 
	{
		return false;
	}
	val = m_pMatrix[row*m_iCapacity+col];
	return true;
}
void CMap::printMatrix() 
{
	for (int i = 0; i < m_iCapacity; i++) 
	{
		for (int k = 0; k < m_iCapacity; k++) 
		{
			cout << m_pMatrix[i * m_iCapacity + k] << " ";
		}
		cout << endl;
	}
}
//深度优先搜索
void CMap::depthFirstTraverse(int nodeIndex)
{
	int value = 0;
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	//通过邻接矩阵判断是否与其他顶点有连接
	for (int i = 0; i < m_iCapacity; i++)
	{
		getValueFromMatrix(nodeIndex, i, value);
		if (value == 1)   //判断有弧连接其他顶点
		{
			//再判断该点是否被访问过
			if (m_pNodeArray[i].m_bIsVisited) 
			{
				continue;
			}
			else 
			{
				depthFirstTraverse(i);
			}
		}
		else  //如果没有去向索引为i的顶点的弧，则循环继续
		{
			continue;
		}
	} 
}
//广度优先遍历
void CMap::breadthFirstTraverse(int nodeIndex) 
{
	cout << m_pNodeArray[nodeIndex].m_cData <<" ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	vector<int>curVec;
	curVec.push_back(nodeIndex);
	breadthFirstTraverseImpl(curVec);
	


}

void CMap::breadthFirstTraverseImpl(vector<int> preVec) 
{
	int value = 0;
	vector<int> curVec;
	
	for (int j = 0; j < (int)preVec.size(); j++) 
	{
		
		for(int i=0;i<m_iCapacity;i++)
		{
			//抓取上一个结点的值
			getValueFromMatrix(preVec[j],i,value);
			if (value != 0) 
			{
				//判断是否访问过结点
				if (m_pNodeArray[i].m_bIsVisited) 
				{
					continue;
				}
				//输出顶点值,结点致1,存入curVec
				else 
				{
					cout << m_pNodeArray[i].m_cData << " ";
					m_pNodeArray[i].m_bIsVisited = true;
					curVec.push_back(i);
				}
			}
		}
	}
	//如果curVec没有结点,程序终止
	if (curVec.size() == 0) 
	{
		return ;
	}
	//如果curVec还有结点,执行递归
	else 
	{
		breadthFirstTraverseImpl(curVec);
	}
	
}