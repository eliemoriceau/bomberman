//
// Created by marin on 20/06/2021.
//

#pragma once
#include <vector>
#include "MapManager.hpp"
#include <list>
#include "Vector3.hpp"
#include "VectorUtils.hpp"
#include <queue>

class Node
{
public:
    Node();
    Node(int _x, int _y, bool _walkable);
    ~Node() = default;

    int x;
    int y;
    bool walkable;
    int fcost;

    int getFcost() const;

    int gcost;
    int hcost;
    Node *parent;
};

class Pathfinding
{
public:
    ~Pathfinding() = default;

    static Pathfinding *getInstance();

    std::vector<Node*> getNeigtbours(Node node);
    bool nodeContains(Node node, std::deque<Node*> list);
    int nodePositon(Node node, std::deque<Node*> list);
    int getDistance(Node a, Node b);
    void drawNode(Node node, std::shared_ptr<Raylib::ColorRGB> color);
    Node *getNodeByPosition(std::shared_ptr<Raylib::Vector3> pos);
    void generateNode();
    void showParents();
    std::list<std::shared_ptr<Raylib::Vector3>> retacePath(Node *startNode, Node *current);
    std::list<std::shared_ptr<Raylib::Vector3>> FindPath(std::shared_ptr<Raylib::Vector3> start_pos, std::shared_ptr<Raylib::Vector3> end_pos);

private:
    Pathfinding() = default;
    std::vector<std::vector<Node*>> nodes;
    static Pathfinding *_instance;

};