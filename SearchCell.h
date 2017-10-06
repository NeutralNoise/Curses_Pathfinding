#ifndef SEARCHCELL_H
#define SEARCHCELL_H
#include <math.h>
#include "Defines.h"

struct SearchCell {
 int x;
 int y;
 int id; //The index in the map array;
 SearchCell * parent;
 float g; //Distance from the start cell;
 float h; //Estimated distance to the end cell;
 
 SearchCell() {
    parent = nullptr;
 }
 
 SearchCell(const int &x, const int &y, SearchCell * parent) {
    this->parent = parent;
    this->x = x;
    this->y = y;
    id = x + y * MAP_X;
 }
  float GetF() {
    return g + h;
  }
  
  float EuclidenDistance(SearchCell * endCell) {
    float dx = this->x - endCell->x;
    float dy = this->y - endCell->y;
    
    float dist = pow(dx, 2) + pow(dy, 2);
    dist = sqrt(dist);
    
    return dist;
  }
  
};

#endif //SEARCHCELL_H