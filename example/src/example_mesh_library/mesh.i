
%module mesh
%{
#include "mesh.hpp"
%}

%include <std_vector.i>
%include <std_array.i>

namespace std {
    %template(Double3) array<double,3>;
    %template(Int4) array<int,4>;
    %template(NodeVector) vector<array<double,3>>;
    %template(ElementVector) vector<array<int,4>>;
}

%include "mesh.hpp"
