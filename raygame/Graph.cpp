#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <raylib.h>

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

std::vector<Node*> Graph::dijkstra(int startX, int startY, int goalX, int goalY)
{
	//Create a node pointer that points to the start node
	Node* start = getNode(startX, startY);
	//Create a node pointer that points to the goal node
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	if (!start || !goal)
		//return an empty list
		return std::vector<Node*>();
	//end if statement

	//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);

	//Create a node pointer that will be act as an iterator for the graph
	Node* iterator = nullptr;

	//Create an open list
	std::deque<Node*> openList;
	//Create a closed list
	std::deque<Node*> closedList;

	//Add start to the open list
	openList.push_front(start);

	//Loop while the open list is not empty
	while (openList.size() > 0)
	{
		//Sort the items in the open list by the g score
		openList = sortQueue(openList);

		//Set the iterator to be the first item in the open list
		iterator = openList[0];

		//Check if the iterator is pointing to the goal node
		if (iterator == goal)
		{
			//Mark the goal as being found by changing its color
			iterator->color = ColorToInt(YELLOW);
			//Return the new path found
			break;
		}
		//end if statement

		//Pop the first item off the open list
		openList.pop_front();

		//Add the first item to the closed list
		closedList.push_front(iterator);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < iterator->edges.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* other = nullptr;

			//Check if the iterator is on the second end of the node
			if (iterator == iterator->edges[i]->connectedNode2)
				//Set the edge end pointer to be the first end of the node
				other = iterator->edges[i]->connectedNode1;
			//Otherwise if the iterator is on the first end of the node...
			else
				//set the edge end pointer to be the second end of the node
				other = iterator->edges[i]->connectedNode2;
			// end if statement

			//Check if node at the end of the edge is in the closed list
			if (!isInQueue(closedList, other))
			{
				//Create an int and set it to be the g score of the iterator plus the cost of the edge
				int gScore = iterator->gScore + iterator->edges[i]->cost;

				//Check if the node at the end ofthe edge is in the open list
				if (!isInQueue(openList, other))
				{
					//Mark the node as visited by changing its color
					other->visited = true;
					other->color = ColorToInt(RED);

					//Set the nodes g score to be the g score calculated earlier
					other->gScore = gScore;

					//Set the nodes previous to be the iterator
					other->previous = iterator;

					//Add the node to the open list
					openList.push_front(other);
				}
				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else if (gScore < other->gScore)
				{
					//Mark the node as visited by changing its color
					other->visited = true;
					other->color = ColorToInt(RED);

					//Set its g score to be the g score calculated earlier
					other->gScore = gScore;

					//Set its previous to be the current node
					other->previous = iterator;
				}
			}
			//end if statement
		}
		//end loop
	}
	//end loop

	// Reverse through previous nodes and store them in a vector to find the path
	std::vector<Node*> path;
	while (iterator)
	{
		path.push_back(iterator);
		iterator = iterator->previous;
	}
	return path;
}

std::vector<Node*> Graph::aStar(int startX, int startY, int goalX, int goalY)
{
	//Create a node pointer that points to the start node
	Node* start = getNode(startX, startY);
	//Create a node pointer that points to the goal node
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	if (!start || !goal)
		//return an empty list
		return std::vector<Node*>();
	//end if statement

	//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);

	//Create a node pointer that will be act as an iterator for the graph
	Node* iterator = nullptr;

	//Create an open list
	std::deque<Node*> openList;
	//Create a closed list
	std::deque<Node*> closedList;

	//Add start to the open list
	openList.push_front(start);

	//Loop while the open list is not empty
	while (openList.size() > 0)
	{
		//Sort the items in the open list by the g score
		openList = sortQueue(openList);

		//Set the iterator to be the first item in the open list
		iterator = openList[0];

		//Check if the iterator is pointing to the goal node
		if (iterator == goal)
		{
			//Mark the goal as being found by changing its color
			iterator->color = ColorToInt(YELLOW);
			//Return the new path found
			break;
		}
		//end if statement

		//Pop the first item off the open list
		openList.pop_front();

		//Add the first item to the closed list
		closedList.push_front(iterator);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < iterator->edges.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* other = nullptr;

			//Check if the iterator is on the second end of the node
			if (iterator == iterator->edges[i]->connectedNode2)
				//Set the edge end pointer to be the first end of the node
				other = iterator->edges[i]->connectedNode1;
			//Otherwise if the iterator is on the first end of the node...
			else
				//set the edge end pointer to be the second end of the node
				other = iterator->edges[i]->connectedNode2;
			// end if statement

			//Check if node at the end of the edge is in the closed list
			if (!isInQueue(closedList, other))
			{
				//Create an int and set it to be the g score of the iterator plus the cost of the edge
				float gScore = iterator->gScore + iterator->edges[i]->cost;
				float hScore = (iterator->graphPosition - goal->graphPosition).getMagnitude();
				float fScore = gScore + hScore;
				//Check if the node at the end ofthe edge is in the open list
				if (!isInQueue(openList, other))
				{
					//Mark the node as visited by changing its color
					other->visited = true;
					other->color = ColorToInt(RED);

					//Set the nodes g score to be the g score calculated earlier
					other->gScore = gScore;
					other->hScore = hScore;

					//Set the nodes previous to be the iterator
					other->previous = iterator;

					//Add the node to the open list
					openList.push_front(other);
				}
				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else if (fScore < other->getFScore())
				{
					//Mark the node as visited by changing its color
					other->visited = true;
					other->color = ColorToInt(RED);

					//Set its g score to be the g score calculated earlier
					other->gScore = gScore;
					other->hScore = hScore;

					//Set its previous to be the current node
					other->previous = iterator;
				}
			}
			//end if statement
		}
		//end loop
	}
	//end loop

	// Reverse through previous nodes and store them in a vector to find the path
	std::vector<Node*> path;
	while (iterator)
	{
		path.push_back(iterator);
		iterator = iterator->previous;
	}
	return path;
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

std::deque<Node*> Graph::sortQueue(std::deque<Node*> queue)
{
	for (int i = 0; i < queue.size(); i++)
	{
		for (int j = queue.size(); j > i; j--)
		{
			if (queue[i]->getFScore() > queue[j - 1]->getFScore())
			{
				Node* temp = queue[i];
				queue[i] = queue[j - 1];
				queue[j - 1] = temp;
			}
		}
	}
	return queue;
}

std::deque<Node*> Graph::sortQueueAscending(std::deque<Node*> queue)
{
	for (int i = 0; i < queue.size(); i++)
	{
		for (int j = i; j < queue.size(); j++)
		{
			if (queue[i]->getFScore() > queue[j]->getFScore())
			{
				Node* temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	return queue;
}

bool Graph::isInQueue(std::deque<Node*> queue, Node* node)
{
	for (int i = 0; i < queue.size(); i++)
		if (queue[i] == node)
			return true;

	return false;
}
