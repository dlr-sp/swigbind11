
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <array>

class Mesh {
public:
    using Node = std::array<double, 3>;
    using Element = std::array<int, 4>;

    void addNode(double x, double y, double z);
    void addElement(int n1, int n2, int n3, int n4);

    int numNodes() const;
    int numElemensts() const;

    void printInfo() const;

    const Node& getNode(int idx) const;
    const Element& getElement(int idx) const;

private:
    std::vector<Node> nodes;
    std::vector<Element> elements;
};

#endif
