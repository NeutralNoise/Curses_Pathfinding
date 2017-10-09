#ifndef ACTOR_H
#define ACTOR_H
#include "PathFinding.h"
#include "Map.h"
#include "Console.h"
#include "ActorManager.h"

class ActorManager;

class Actor {
public:
  Actor();
  Actor(WorldMap *map);

  void InitActor(const int &team, WorldMap * map);

  void Move(ActorManager &aman);

  void DrawActor(Console * con);

  void TickActor(Console * con, ActorManager &aman);

  void CheckVision(ActorManager &aman);

  bool Attack(ActorManager &aman);

  float GetHealth();

  void SetID(const int &id);

  int GetTeam();

  void RemoveHealth(const float rh);

  int GetXPos();
  int GetYPos();

private:
  //position of the actor
  int m_x;
  int m_y;
  int m_lastx;
  int m_lasty;
  int m_goalX;
  int m_goalY;

  //The team the actor is on.
  int m_team;

  float m_health;

  PathFinder m_pather;
  WorldMap * m_map;

  bool m_pathed;
  bool m_seenOtherTeam;
  bool m_attacking;
  int m_campCount;

  int m_id;
  int m_killID; // The ID of the actor this actor is attacking.

};


#endif //ACTOR_H
