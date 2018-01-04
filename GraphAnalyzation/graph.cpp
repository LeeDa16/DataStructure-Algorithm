#include <stack>
#include "graph.h"

Graph::Graph(int v) :vertex_num(v), edge_num(0)
{
	for (int i = 0; i < vertex_num; ++i)
	{
		nodes.push_back(GraphNode());
	}
	graphMatrix = new int*[vertex_num];
	for (int i = 0; i < vertex_num; ++i)
	{
		graphMatrix[i] = new int[vertex_num];
		for (int j = 0; j < vertex_num; ++j)
		{
			graphMatrix[i][j] = MAX_DIST;
		}
	}
	for (int i = 0; i < vertex_num; ++i)
	{
		graphMatrix[i][i] = 0;
	}
	distMatrix = pathMatrix = nullptr;
}

Graph::~Graph()
{
	if (graphMatrix != nullptr)
	{
		for (int i = 0; i < vertex_num; ++i)
		{
			delete[] graphMatrix[i];
		}
	}
	if (distMatrix != nullptr)
	{
		for (int i = 0; i < vertex_num; ++i)
		{
			delete[] distMatrix[i];
		}
	}
	if (pathMatrix != nullptr)
	{
		for (int i = 0; i < vertex_num; ++i)
		{
			delete[] pathMatrix[i];
		}
	}
}

void Graph::addEdge(int begin, int end, int weight)
{
	graphMatrix[begin][end] = weight; //���ڽӾ�������ӱ�
}

void Graph::floyd()
{
	if (distMatrix == nullptr) //��ʼ��·�̾����·������
	{
		distMatrix = new int*[vertex_num];
		pathMatrix = new int*[vertex_num];
		for (int i = 0; i < vertex_num; ++i)
		{
			distMatrix[i] = new int[vertex_num];
			pathMatrix[i] = new int[vertex_num];
			for (int j = 0; j < vertex_num; ++j)
			{
				distMatrix[i][j] = graphMatrix[i][j];
				pathMatrix[i][j] = i;
			}
		}
	}
	else
	{
		for (int i = 0; i < vertex_num; ++i)
		{
			for (int j = 0; j < vertex_num; ++j)
			{
				distMatrix[i][j] = graphMatrix[i][j];
				pathMatrix[i][j] = i;
			}
		}
	}

	//floyd�㷨
	for (int k = 0; k < vertex_num; ++k)
	{
		for (int i = 0; i < vertex_num; ++i)
		{
			if (distMatrix[i][k] == MAX_DIST)
				continue;
			for (int j = 0; j < vertex_num; ++j)
			{
				if (distMatrix[i][j] > distMatrix[i][k] + distMatrix[k][j])
				{
					distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
					pathMatrix[i][j] = pathMatrix[k][j];
				}
			}
		}
	}
} 

int Graph::shortestPath(int begin, int end)
{
	if (distMatrix == nullptr)
	{
		floyd();
	}

	//ͨ��·�����������··��
	if (distMatrix[begin][end] != MAX_DIST && distMatrix[begin][end] != 0)
	{
		cout << distMatrix[begin][end] << "\t";
		int p = end;
		stack<int> path;
		path.push(p);
		do
		{
			p = pathMatrix[begin][p];
			path.push(p);
		} while (p != begin);
		int s = path.size();
		for (int i = 0; i < s; ++i)
		{
			cout << path.top();
			path.pop();
			if (i != s - 1)
				cout << " -> ";
		}
		cout << endl;
	}
	else
	{
		cout << " No Path" << endl;
	}
	return distMatrix[begin][end]; //������̾���
}

void Graph::centrality()
{
	if (distMatrix == nullptr)
	{
		floyd();
	}

	for (int i = 0; i < vertex_num; ++i)
	{
		for (int j = 0; j < vertex_num; ++j)
		{
			if (i != j && distMatrix[i][j] != MAX_DIST)
			{
				nodes[i].closeness += distMatrix[i][j]; //��ӽ����Ķ�
			}
			if (i != j && graphMatrix[i][j] != MAX_DIST)
			{
				++nodes[i].degree; //�������Ķ�
			}
		}
	}
	for (int k = 0; k < vertex_num; ++k)
	{
		for (int i = 0; i < vertex_num; ++i)
		{
			if (distMatrix[i][k] == MAX_DIST || i == k)
				continue;
			for (int j = 0; j < vertex_num; ++j)
			{
				//���ĳ�ڵ㵽�������ڵ�ľ���֮�͵��ڸ������ڵ����̾��룬˵�������������ڵ�����·����
				if (j != k && distMatrix[i][j] == distMatrix[i][k] + distMatrix[k][j])
				{
					++nodes[k].betweenness;
				}
			}
		}
	}

	//��������ͼ���ڽӾ���Ϊ�Գƾ������ÿ����Ľ������Ķȱ�����������
	for (int i = 0; i < vertex_num; ++i)
	{
		nodes[i].betweenness /= 2;
	}
}

void Graph::showCtrlty(ostream& out) const
{
	out << "�ڵ�" << "," << "������Ķ�" << "," << "�ӽ����Ķ�" << "," << "�������Ķ�" << endl;
	for (int i = 0; i < vertex_num; ++i)
	{
		out << i << ",";
		out << nodes[i].degree << ",";
		out << "1/" << nodes[i].closeness << ",";
		out << nodes[i].betweenness << endl;
	}
}

void Graph::prim()
{

}