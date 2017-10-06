#ifndef ACTOR_MANAGER_H
#define ACTOR_MANAGER_H
#include <vector>
#include "Actor.h"
#include "Map.h"

class Actor;

class ActorManager {
  
public:
  
  ActorManager(const int &total, WorldMap * map);
  
  void SpawnActor();
  
  void TickActors(Console * con);
  
  void CleanUp();
  
  void DrawActors(Console * con);
  
  Actor * GetActor(const int &index);
  
private:
  
  std::vector<Actor*> m_actorList;
  int m_maxTeamSize;
  int m_team1count;
  int m_team2count;
  int m_lastspawn;
  WorldMap * m_map;
};

#endif //ACTOR_MANAGER_H