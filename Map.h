#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include "Console.h"

struct MapTile {
  int x;
  int y;
  char symbol;
  int foreColour;
  int backColour;
  float cost = 0.0f; //Cost this tile has when moving over it.
  int team = 0;
  bool isGoal = false;
  bool hasBlood = false;
  float bloodLife = 0.0f;
  bool hasActor = false;
};

class WorldMap {
public:
  
  WorldMap();
  
  void LoadMap(const std::string &file);
  
  void DrawMap(Console * con);
  
  MapTile * GetMapTile(const int &x, const int &y);
  
  void UpdateMap();
  
  bool GetSpawn(int & x, int & y, const int &team);
  bool GetGoal(int * x, int * y, const int &team);
  
private:
  std::vector<MapTile*> m_data;
  std::vector<MapTile*> m_upDateData;
  std::vector<MapTile*> m_spawn;
  std::vector<MapTile*> m_goal;
};

#endif //MAP_H