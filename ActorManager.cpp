#include "ActorManager.h"


ActorManager::ActorManager(const int &total, WorldMap * map) {
  m_maxTeamSize = total / 2;
  m_team1count = 0;
  m_team2count = 0;
  m_lastspawn = 5;
  m_actorList.resize(total);
  m_map = map;
  for(size_t i = 0; i < m_actorList.size(); i++) {
    m_actorList[i] = nullptr;
  }
}
  
void ActorManager::SpawnActor() {
  //We want to spawn a Actor for each team at the same time.
  if(m_lastspawn == 5) {
    if(m_team1count < m_maxTeamSize) {
      for(size_t i = 0; i < m_actorList.size(); i++) {
	if(m_actorList[i] == nullptr) {
	  Actor * newActor = new Actor();  
	  newActor->InitActor(1, m_map);
	  newActor->SetID(i);
	  m_actorList[i] = newActor;
	  m_team1count++;
	  break;
	}
      }
    }
    if(m_team2count < m_maxTeamSize) {
      for(size_t i = 0; i < m_actorList.size(); i++) {
	if(m_actorList[i] == nullptr) {
	  Actor * newActor = new Actor();  
	  newActor->InitActor(2, m_map);
	  newActor->SetID(i);
	  m_actorList[i] = newActor;
	  m_team2count++;
	  break;
	}
      }
    }
    m_lastspawn = 0;
  }
  else if(m_lastspawn < 5) {
    m_lastspawn++;
  }
}
  
void ActorManager::TickActors(Console * con) {
  for(size_t i = 0; i < m_actorList.size(); i++) {
    if(m_actorList[i] != nullptr) {
      m_actorList[i]->TickActor(con, *this);
    }
  }
}
  
void ActorManager::CleanUp() {
  for(size_t i = 0; i < m_actorList.size(); i++) {
    if(m_actorList[i] != nullptr) {
      if(m_actorList[i]->GetHealth() <= 0.00f) {
	m_map->GetMapTile(m_actorList[i]->GetXPos(), m_actorList[i]->GetYPos())->hasActor = false;
	if(m_actorList[i]->GetTeam() == 1) {
	  m_team1count--;
	}
	else {
	  m_team2count--;
	}
	delete m_actorList[i];
	m_actorList[i] = nullptr;
	
      }
    }
  }
}

void ActorManager::DrawActors(Console * con) {
  for(size_t i = 0; i < m_actorList.size(); i++) {
    if(m_actorList[i] != nullptr) {
      m_actorList[i]->DrawActor(con);
    }
  }
}

Actor * ActorManager::GetActor(const int &index) {
  return m_actorList[index];
}