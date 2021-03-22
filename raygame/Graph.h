#pragma once
#include "Actor.h"
#include <vector>
#include <deque>

class Node;

class Graph : public Actor
{
public:
	Graph(int width, int height, int nodeSize, int nodeSpacing);

	void update(float deltaTime) override;
	void draw() override;

	void BFS(int startX, int startY, int goalX, int goalY);
	std::vector<Node*> dijkstra(int startX, int startY, int goalX, int goalY);
	std::vector<Node*> aStar(int startX, int startY, int goalX, int goalY);
	Node* getNode(int xPos, int yPos);


private:
	void createGraph(int nodeSize, int nodeSpacing);
	std::deque<Node*> sortQueue(std::deque<Node*> queue);
	std::deque<Node*> sortQueueAscending(std::deque<Node*> queue);
	bool isInQueue(std::deque<Node*> queue, Node* node);

private:
	int m_height;
	int m_width;
	std::vector<Node*> m_nodes;
};

