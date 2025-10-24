#include "mesh.hpp"
#include <iostream>

void Mesh::addNode(double x, double y, double z) {
    nodes.push_back({x, y, z});
}

void Mesh::addElement(int n1, int n2, int n3, int n4){
    elements.push_back({n1, n2, n3, n4});
}

int Mesh::numNodes() const {
    return static_cast<int>(nodes.size());
}
int Mesh::numElemensts() const {
    return static_cast<int>(elements.size());
}

void Mesh::printInfo() const {
    std::cout << "Mesh info:\n";
    std::cout << "Nodes: " << numNodes() << "\n";
    std::cout << "Elements: " << numElemensts() <<"\n";
}

const Mesh::Node& Mesh::getNode(int idx) const {
    return nodes.at(idx);
}
const Mesh::Element& Mesh::getElement(int idx) const {
    return elements.at(idx);
}
