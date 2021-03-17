#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <raylib.h>
#include <deque>

Graph::Graph(int width, int height, int nodeSize, int nodeSpacing)
{
	m_width = width;
	m_height = height;
	createGraph(nodeSize, nodeSpacing);
}

void Graph::update(float deltaTime)
{
	Actor::update(deltaTime);

	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->update(deltaTime);
	}
}

void Graph::draw()
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->draw();
	}
}

void Graph::BFS(int startX, int startY, int goalX, int goalY)
{
	// Get a reference to the start and end nodes
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	// If either is null, return
	if (!start || !goal)
		return;

	// Set the color to start and mark it as visited
	start->color = ColorToInt(GREEN);
	start->visited = true;
	
	// Set an iterator to start
	Node* currentNode = start;

	// Create a queue and add start to it
	std::deque<Node*> queue;
	queue.push_front(start);

	// So long as there is something in the queue, search for the goal
	while (!queue.empty())
	{
		// Set the iterator to the first thing in the queue and then pop it
		currentNode = queue[0];
		queue.pop_front();

		// If we've reached the goal, set its color and return
		if (currentNode == goal)
		{
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		// If we haven't reached the goal, get all neighbors
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			// Store the node at the other end of the edge
			Node* currentEdgeEnd = nullptr;

			// Set the node to be the opposite end of the edge
			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			// If the opposite node hasn't been visited, mark it and add it to the queue	
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_front(currentEdgeEnd);
			}
		}
	}
}

Node* Graph::getNode(int xPos, int yPos)
{
	// Ensure valid positions
	if (xPos > m_width || 
		yPos > m_height ||
		xPos < 0 ||
		yPos < 0)
		return nullptr;

	// Loop through all nodes
	for (int i = 0; i < m_nodes.size(); i++)
	{
		// If the current node is at the given position, return it
		if (m_nodes[i]->graphPosition == MathLibrary::Vector2(xPos, yPos))
			return m_nodes[i];
	}

	// If no node was found, return nullptr
	return nullptr;
}

void Graph::createGraph(int nodeSize, int nodeSpacing)
{
	float xPos = 0;
	float yPos = 0;

	// Loops for the amount of nodes in the graph
	for (int i = 0; i < m_width * m_height; i++)
	{
		// Create a new node with the current graph position and size
		Node* currentNode = new Node(xPos, yPos, nodeSize);
		
		// Set the local offset for spacing
		MathLibrary::Vector2 nodeLocalPosition = { xPos * nodeSpacing, yPos * nodeSpacing };
		currentNode->setLocalPosition(nodeLocalPosition);

		// Add the node as a chile of the grid and update the list
		addChild(currentNode);
		m_nodes.push_back(currentNode);

		// Connect the node to all nodes in range
		for (int j = 0; j < m_nodes.size(); j++)
		{
			// Find the displacement between the current node being added and the node being evaluated
			MathLibrary::Vector2 displacement = m_nodes[j]->graphPosition - currentNode->graphPosition;

			// Check if the magnitude of the displacement is farther than the maximum
			if (displacement.getMagnitude() <= 1.42 && displacement.getMagnitude() > 0)
			{
				// Create a new edge that connects the two nodes
				Edge* currentEdge = new Edge(m_nodes[j], currentNode);
				currentNode->edges.push_back(currentEdge);
				m_nodes[j]->edges.push_back(currentEdge);
			}
		}

		// Increment x
		xPos++;

		// If the xposition is greater than the width, reset it and increase the y
		if (xPos >= m_width)
		{
			xPos = 0;
			yPos++;
		}
	}
}