//
// Created by marin on 18/06/2021.
//

#include "Pathfinding.hpp"
#include "EntityCreator.hpp"

Pathfinding *Pathfinding::_instance = nullptr;


Pathfinding *Pathfinding::getInstance()
{
    if (_instance == nullptr)
        _instance = new Pathfinding();
    return _instance;
}


Node::Node(int _x, int _y, bool _walkable) : x(_x), y(_y), walkable(_walkable)
{
    fcost = 0;
    gcost = 0;
    hcost = 0;
    parent = nullptr;
}

Node::Node()
{
    x = 0;
    y = 0;
    fcost = 0;
    gcost = 0;
    hcost = 0;
    parent = nullptr;
}

int Node::getFcost() const {
    return gcost + hcost;
}


void Pathfinding::generateNode()
{
    nodes.clear();

    std::vector<std::vector<char>> maps = MapManager::getInstance()->getMap2D();

    nodes.resize(MapManager::getInstance()->getHeight() + 1);
    for (int row = 0; row <= MapManager::getInstance()->getHeight(); row++)
    {
        nodes[row].resize(MapManager::getInstance()->getWidth());
        for (int col = 1; col <= MapManager::getInstance()->getWidth(); col++) {
            if (maps[row][col - 1] == 'U' || maps[row][col - 1] == 'B' || maps[row][col - 1] == 'X') {
                nodes[row][col - 1] = new Node(row, col - 1, false);
            }
            else {
                nodes[row][col - 1] = new Node(row, col - 1, true);
                //drawNode(*nodes[row][col - 1], std::make_shared<Raylib::ColorRGB>(255,255,255,255));
            }
        }
    }
}

Node *Pathfinding::getNodeByPosition(std::shared_ptr<Raylib::Vector3> pos) {
    auto coords = MapManager::getInstance()->getArrayCoords(pos);
    for (int row = 0; row <= MapManager::getInstance()->getHeight(); row++) {
        nodes.resize(MapManager::getInstance()->getHeight());
        for (int col = 1; col <= MapManager::getInstance()->getWidth(); col++) {
            if (nodes[row][col - 1]->x == coords.first && nodes[row][col - 1]->y == coords.second)
                return nodes[row][col - 1];
        }
    }
    return nullptr;
}

bool Pathfinding::nodeContains(Node node, std::deque<Node*> list)
{
    for (auto el : list) {
        if (el->x == node.x && el->y == node.y)
            return true;
    }
    return false;
}

int Pathfinding::nodePositon(Node node, std::deque<Node*> list)
{
    int index = 0;

    for (auto el : list) {
        if (el->x == node.x && el->y == node.y)
            return index;
        index++;
    }
    return -1;
}

void Pathfinding::drawNode(Node node, std::shared_ptr<Raylib::ColorRGB> color)
{
    auto texture_border = WALL_GRID;
    auto pos = newVector(-MapManager::getInstance()->getWidth()/2 + node.y,4,-MapManager::getInstance()->getHeight()/2 + node.x);
    EntityCreator::createCube(pos, newVector(1,1,1), color, WALL_GRID, node.y, node.x);
}

std::vector<Node*> Pathfinding::getNeigtbours(Node node)
{
    std::vector<Node*> neighbours = {};

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0)
                continue;
            if (x == -1 && y == -1)
                continue;
            if (y == 1 && x == -1)
                continue;
            if (y == -1 && x == 1)
                continue;
            if (y == 1 && x == 1)
                continue;

            int checkX =  node.x + x;
            int checkY = node.y + y;

            if (checkX >= 0 && checkX < MapManager::getInstance()->getWidth() && checkY >= 0 && checkY < MapManager::getInstance()->getHeight()) {
                neighbours.push_back(nodes[checkX][checkY]);
            }
        }
    }

    return neighbours;
}

int Pathfinding::getDistance(Node a, Node b) {
    int dstX = abs(a.x - b.x);
    int dstY = abs(a.y - b.y);

    if (dstX > dstY)
        return 14*dstY + 10* (dstX-dstY);
    return 14*dstX + 10 * (dstY-dstX);
}

std::list<std::shared_ptr<Raylib::Vector3>> Pathfinding::retacePath(Node *startNode, Node *current)
{
    std::list<std::shared_ptr<Raylib::Vector3>> path;

    while (current->x != startNode->x && current->y != startNode->y) {
        path.push_back(newVector(-MapManager::getInstance()->getWidth()/2 + current->y,1,-MapManager::getInstance()->getHeight()/2 + current->x));
        current = current->parent;
    }
    path.reverse();
    return path;
}
void Pathfinding::showParents()
{

}
std::list<std::shared_ptr<Raylib::Vector3>> Pathfinding::FindPath(std::shared_ptr<Raylib::Vector3> start_pos, std::shared_ptr<Raylib::Vector3> end_pos)
{
    generateNode();

    Node *start_node = getNodeByPosition(start_pos);
    Node *end_node = getNodeByPosition(end_pos);

    std::list<std::shared_ptr<Raylib::Vector3>> paths;
    std::deque<Node*> open_set;
    std::deque<Node*> close_set;

    open_set.push_back(start_node);


    //std::cout << start_node->walkable << " " << end_node->walkable << "\n";
    if (!end_node->walkable || !start_node->walkable) {
        return {};
    }

    while (open_set.size() > 0) {
        Node *current = open_set[0];
        for (int i = 1; i < open_set.size(); i++) {
            if (open_set[i]->getFcost() < current->getFcost() || open_set[i]->getFcost() == current->getFcost()) {
                if (open_set[i]->hcost < current->hcost)
                    current = open_set[i];
            }
        }
        if (nodePositon(*current, open_set) != -1) {
            open_set.erase(open_set.begin() + nodePositon(*current, open_set));
        }
        close_set.push_back(current);
        paths.push_back(newVector(-MapManager::getInstance()->getWidth()/2 + current->y,1,-MapManager::getInstance()->getHeight()/2 + current->x));

        if (current->x == end_node->x && current->y == end_node->y) {
            return paths;
        }
        for(auto neigh : getNeigtbours(*current)) {
            if (!neigh->walkable || nodeContains(*neigh, close_set)) {
                continue;
            }
            int newMovement = current->gcost + getDistance(*current, *neigh);
            if (newMovement < neigh->gcost || !nodeContains(*neigh, open_set)) {
                neigh->gcost = newMovement;
                neigh->hcost = getDistance(*neigh, *end_node);
                neigh->parent = nodes[current->x][current->y];
                if (!nodeContains(*neigh, open_set)) {
                    open_set.push_back(neigh);
                }
            }
        }
    }
    return {};
}