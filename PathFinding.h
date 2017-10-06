#ifndef PATHFINDING_H
#define PATHFINDING_H
#include <vector>
#include <deque>
#include "SearchCell.h"
#include "Map.h"
#include "Vec2.h" //Only used to store the current path.

class PathFinder {
public:
  void FindPath(const int &x, const int &y, const int &x2, const int &y2, WorldMap &map);
  void ContinuePath(WorldMap &map);
  bool PathOpen(const int &x, const int &y, const float &cost, SearchCell * parent, WorldMap &map);
  
  void GetNextPathStep(int * x, int * y);
  bool FoundPath();
  
private:
  
  SearchCell * GetNextCell();
  
  std::vector<SearchCell*> m_open;
  std::vector<SearchCell*> m_closed;
  std::deque<Vec2> m_path;
  
  SearchCell * m_start;
  SearchCell * m_goal;
  
  bool m_initStartGoal = false;
  bool m_foundPath = false;
  
};

#endif //PATHFINDING_H