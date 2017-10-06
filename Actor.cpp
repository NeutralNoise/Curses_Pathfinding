#include "Actor.h"
#include <ncurses.h>
#include <sstream>
#include <fstream>
#include "LOS.h"
#include "Defines.h"

Actor::Actor() {
  m_x = 21;
  m_y = 21;
  m_lastx = 0;
  m_lasty = 0;
  m_goalX = 0;
  m_goalY = 0;
  m_health = 100.0f;
  m_team = 0;
  m_map = nullptr;
  m_pathed = false;
  m_seenOtherTeam = false;
  m_killID = -1;
  m_attacking = false;
}

Actor::Actor(WorldMap *map) {
  m_x = 21;
  m_y = 21;
  m_goalX = 0;
  m_goalY = 0;
  m_health = 100.0f;
  m_team = 0;
  m_map = map;
  m_pathed = false;
  m_seenOtherTeam = false;
  m_killID = -1;
  m_attacking = false;
}

void Actor::InitActor(const int &team, WorldMap * map) {
  
  if(map != nullptr) {
    m_map = map;
  }
  if(m_map != nullptr) {
    m_map->GetSpawn(m_x, m_y, team);
    m_lastx = m_x;
    m_lasty = m_y;
    m_map->GetMapTile(m_x, m_y)->hasActor = true;
  }
  
  m_team = team;
  
}

void Actor::DrawActor(Console * con) {
  MapTile * t = m_map->GetMapTile(m_lastx, m_lasty);
  t->hasActor = false;
  con->MoveCursor(m_lastx, m_lasty);
  con->PrintChar(t->symbol, t->foreColour, t->backColour);
  t = m_map->GetMapTile(m_x, m_y);
  t->hasActor = true;
  con->MoveCursor(m_x, m_y);
  if(m_team == 1) {
    con->SetColour(COLOR_RED, COLOR_GREEN);
  }
  else {
    con->SetColour(COLOR_BLUE, COLOR_GREEN);
  }
  con->PrintChar('@');
  con->ResetColour();
}

void Actor::TickActor(Console * con, ActorManager &aman) {
  if(m_health > 0.00f) {
    CheckVision(aman);
    if(m_attacking) {
      if(!Attack(aman)) {
	Move(aman);
      }
    }
    else {
      Move(aman);  
    }
  }
  else {
    m_map->GetMapTile(m_x, m_y)->hasBlood = true;
    m_map->GetMapTile(m_x, m_y)->bloodLife += 10.0f;
    m_map->GetMapTile(m_x, m_y)->cost += 0.50f;
  }
}

void Actor::CheckVision(ActorManager &aman) {
  //We only want to check for more things to attack if we aren't already attacking.
  if(!m_attacking) {
    //Loop though all the actors and check if we have LOS
    for(int i = 0; i < TOTAL_ACTORS; i++) {
      //Why would the actor want to attack it self.
      if(i != m_id) {
	Actor * a = aman.GetActor(i);
	if(a != nullptr) {
	  if(los(m_x, m_y, a->GetXPos(), a->GetYPos(), m_map) && a->GetTeam() != m_team) {
	    m_seenOtherTeam = true;
	    m_killID = i;
	    m_goalX = a->GetXPos();
	    m_goalY = a->GetYPos();
	  }
	}
      }
    }
  }
}

bool Actor::Attack(ActorManager &aman) {
  //Check if the actor is next to its target and then attack it.
  //Left Means the attacker is to the letf of the target.
  //Left
  Actor * a = aman.GetActor(m_killID);
  if(a == nullptr) {
    return false;
  }
  
  if(m_x == m_goalX - 1 && m_y == m_goalY ) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  //Right
  else if(m_x == m_goalX + 1 && m_y == m_goalY ) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  //Up
  else if(m_x == m_goalX && m_y == m_goalY + 1) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  //Down
  else if(m_x == m_goalX && m_y == m_goalY - 1) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  //Up-Left
  else if(m_x == m_goalX - 1 && m_y == m_goalY - 1) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  //Up-Right
  else if(m_x == m_goalX + 1 && m_y == m_goalY - 1) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  //Down-Left
  else if(m_x == m_goalX - 1 && m_y == m_goalY + 1) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  //Down-Right
  else if(m_x == m_goalX + 1 && m_y == m_goalY + 1) {
    a->RemoveHealth(100.0f);
    if(a->GetHealth() <= 0.00f) {
      m_seenOtherTeam = false;
      m_attacking = false;
      m_killID = -1;
    }
    return true;
  }
  
  
  
  return false;
}

void Actor::Move(ActorManager &aman) {
  
  //If the Actor is dead do nothing.
  if(m_health <= 0.00f) {
    return;
  }
  
  if(m_seenOtherTeam && !m_attacking) {
    m_pather.FindPath(m_x, m_y, m_goalX, m_goalY, *m_map);
    m_attacking = true;
    m_pathed = false;
  }
  else if(m_attacking){
    //We need to check to see if the actor hsa moved... Which it more then likely has. 
    //bye bye CPU
    Actor *a = aman.GetActor(m_killID);
    if(a != nullptr) {
      if(a->GetXPos() != m_goalX || a->GetYPos() != m_goalY) {
	m_goalX = a->GetXPos();
	m_goalY = a->GetYPos();
	m_pather.FindPath(m_x, m_y, m_goalX, m_goalY, *m_map);
	m_pathed = false;
      }
    }
    else {
      //It seems the actor has died.
      m_attacking = false;
      //Seeing as there is no actor there any more we can just find a new path.
      m_pathed = true;
    }
  }
  else if(!m_pather.FoundPath() || m_pathed == true) {
    //Find the goal the actor needs to path too.
    int goalx;
    int goaly;
    bool has_goal = false;
    //Check for a goal that hasn't been taken yet.
    if(!m_map->GetGoal(&goalx, &goaly, 0)) {
      //If all goals are taken get a goal taken by the other team.
      if(m_team == 1) {
	if(m_map->GetGoal(&goalx, &goaly, 2)) {
	  has_goal = true; 
	}
      }
      else {
	if(m_map->GetGoal(&goalx, &goaly, 1)) {
	  has_goal = true;  
	}
      }
    }
    else {
      has_goal = true;
    }

    //If the actor doesn't have a goal send them over to the other teams spawn.
    if(!has_goal) {
      if(m_team == 1) {
	m_map->GetSpawn(goalx, goaly, 2);
      }
      else {
	m_map->GetSpawn(goalx, goaly, 1);
      }
    }
    
    //Set our goal;
    m_goalX = goalx;
    m_goalY = goaly;
    
    m_pather.FindPath(m_x, m_y, m_goalX, m_goalY, *m_map);
    m_pathed = false;
  }
  
  
  //Move the Actor
  int x,y;
  m_pather.GetNextPathStep(&x,&y);
  
  //Check if we have a valid next step;
  if(x == -1 || y == -1) {
    //Do something next turn.
    return;
  }
  if(m_pathed == false){
    m_lastx = m_x;
    m_lasty = m_y;
    m_x = x;
    m_y = y;
  }
  if(m_x == m_goalX && m_y == m_goalY) {
    m_pathed = true;
  }
  
  //check if the map tile the actor is on is set to there team. If it isn't change it over to there team.
  MapTile * t = m_map->GetMapTile(m_x, m_y);
  if(t != nullptr) {
    if(t->isGoal) {
      t->team = m_team;
    }
  }
}


float Actor::GetHealth() {
  return m_health;
}

void Actor::SetID(const int &id) {
  m_id = id;
}

int Actor::GetTeam() {
  return m_team;
}

void Actor::RemoveHealth(const float rh) {
  m_health -= rh;
}

int Actor::GetXPos() {
  return m_x;
}

int Actor::GetYPos() {
  return m_y;
}












