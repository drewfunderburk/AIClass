#pragma once
#include "Actor.h"
#include <vector>

class Edge;

class Node : public Actor
{
public:
	Node(int x, int y, int nodeSize);

	void update(float deltaTime) override;
	void draw() override;

	std::vector<Edge*> edges;
	MathLibrary::Vector2 graphPosition;
	int color = 0xFFFFFFFF;
	int size = 1;
	bool visited;
};

