#include "PathFinding.h"
#include <algorithm>    // std::reverse

void PathFinder::FindPath(const int &x, const int &y, const int &x2, const int &y2, WorldMap &map) {
  if(!m_initStartGoal) {
    //Make sure our open and close cell vectors are clear.
    for(size_t i = 0; i < m_open.size(); i++) {
      delete m_open[i];
    }
    m_open.clear();
    for(size_t i = 0; i < m_closed.size(); i++) {
      delete m_closed[i];
    }
    m_closed.clear();
    //We don't need the old path still
    m_path.clear();
    
    //Set the start and goal cells;
    m_start = new SearchCell(x,y, nullptr);
    m_goal = new SearchCell(x2,y2, nullptr);
    m_start->g = 0;
    m_start->h = m_start->EuclidenDistance(m_goal);
    m_open.push_back(m_start);
    m_initStartGoal = true;
    m_foundPath = false;
  }
  
  if(m_initStartGoal) {
    ContinuePath(map);
  }
  else {
    return;
  }
  
}

void PathFinder::ContinuePath(WorldMap &map) {
  //Keep finding the path until there are no more oepn cells;
  if(m_open.empty()) {
    return;
  }
  //Get the cell in the open list with the lowest f score;
  SearchCell * current = GetNextCell();
  
  //Check if the current cell is the same as the goal cell.
  if(current->id == m_goal->id) {
    m_goal->parent = current;
    
    //Build the shortest path to goal.
    SearchCell * getPath = nullptr;
    //Work Backwards from the goal to the start cell.
    for(getPath = m_goal; getPath != nullptr; getPath = getPath->parent) {
      //Store the Path for some access :D
      m_path.push_back(Vec2(getPath->x, getPath->y));
    }
    
    //Reverse the path vector other wise its all Backwards
    std::reverse(m_path.begin(), m_path.end());
    
    m_foundPath = true;
    
    return;
  }
  //Check current neighbor cells.
  //Right Cell
  if(map.GetMapTile(current->x + 1, current->y)) {
    PathOpen(current->x + 1, current->y, current->g + 1.0 + map.GetMapTile(current->x + 1, current->y)->cost, current, map);
  }
  //Left Cell
  if(map.GetMapTile(current->x - 1, current->y)) {
    PathOpen(current->x - 1, current->y, current->g + 1.0 + map.GetMapTile(current->x - 1, current->y)->cost, current, map);
  }
  //Bottom Cell
  if(map.GetMapTile(current->x, current->y + 1)) {
    PathOpen(current->x, current->y + 1, current->g + 1.0 + map.GetMapTile(current->x, current->y + 1)->cost, current, map);
  }
  //Top Cell
  if(map.GetMapTile(current->x, current->y - 1)) {
    PathOpen(current->x, current->y - 1, current->g + 1.0 + map.GetMapTile(current->x, current->y - 1)->cost, current, map);
  }
  
  
  //1.414 squre root of 2
  //Cause when you move diag you are passing though 2 squares and some other math reason.
  //Left-up diagonal
  if(map.GetMapTile(current->x - 1, current->y - 1)) {
    PathOpen(current->x - 1, current->y - 1, current->g + 1.414 + map.GetMapTile(current->x - 1, current->y - 1)->cost, current, map);
  }
  //Right-up diagonal
  if(map.GetMapTile(current->x + 1, current->y - 1)) {
    PathOpen(current->x + 1, current->y - 1, current->g + 1.414 + map.GetMapTile(current->x + 1, current->y - 1)->cost, current, map);
  }
  //Left-down diagonal
  if(map.GetMapTile(current->x - 1, current->y + 1)) {
    PathOpen(current->x - 1, current->y + 1, current->g + 1.414 + map.GetMapTile(current->x - 1, current->y + 1)->cost, current, map);
  }
  //Right-down diagonal
  if(map.GetMapTile(current->x + 1, current->y + 1)) {
    PathOpen(current->x + 1, current->y + 1, current->g + 1.414 + map.GetMapTile(current->x + 1, current->y + 1)->cost, current, map);
  }

  
  ContinuePath(map);
  
  m_initStartGoal = false;
}

SearchCell * PathFinder::GetNextCell() {
  float bestF = 99999.0f;
  int index;
  //Find the cell with the lowest F in the open vector.
  for(size_t i = 0; i < m_open.size(); i++) {
    if(m_open[i]->GetF() < bestF) {
      bestF = m_open[i]->GetF();
      index = i;
    }
  }
  SearchCell * nextCell = m_open[index];
  //Remove the current cell from open list and add it to the closed list.
  m_open.erase(m_open.begin() + index);
  m_closed.push_back(nextCell);
  return nextCell;
}

bool PathFinder::PathOpen(const int &x, const int &y, const float &cost, SearchCell * parent, WorldMap &map) {
  //Check to make sure we are with in map bounds.
  if(x < 0) {
    return false;
  }
  if(y < 0) {
    return false;
  }
  if(x > MAP_X) {
    return false;
  }
  if(y > MAP_Y) {
    return false;
  }
  
  MapTile * tempTile = map.GetMapTile(x,y);
  
  //Check to see if this is a valid tile.
  if(tempTile == nullptr) {
   return false; 
  }
  
  //Check to see if this is a wall;
  if(tempTile->symbol == '#') {
    return false; 
  }
  
  int id = x + y * MAP_X;
  //Check if the cell is in the closed list.
  for(size_t i = 0; i < m_closed.size(); i++) {
    if(m_closed[i]->id == id) {
      return false;
    }
  }
  
  //Create a new search cell and add it to the open list.
  SearchCell * newCell = new SearchCell(x,y, parent);
  newCell->g = cost;
  newCell->h = newCell->EuclidenDistance(m_goal);
  
  //Check to see if this cell is already in the open list and then update if the f score is better.
  for(size_t i = 0; i < m_open.size(); i++) {
    if(id == m_open[i]->id) {
      float newf = newCell->g + cost + m_open[i]->h;
      
      if(m_open[i]->GetF() > newf) {
	m_open[i]->g = newCell->g + cost;
	m_open[i]->parent = parent;
	delete newCell;
	return true;
      }
      else {
	delete newCell;
	return false;
      }
      
    }
  }
  
  m_open.push_back(newCell);
  return true;
}


void PathFinder::GetNextPathStep(int * x, int * y) {
  if(!m_path.empty()) {
    //We only ever want the first element.
    Vec2 pos(m_path.front());
    *x = pos.x;
    *y = pos.y;
    m_path.pop_front();
  }
  else {
    *x = -1;
    *y = -1;
    m_foundPath = false;
  }
}

bool PathFinder::FoundPath() {
  return m_foundPath;
}




