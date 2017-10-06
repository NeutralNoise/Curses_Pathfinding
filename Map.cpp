#include "Map.h"
#include <fstream>
#include <ncurses.h>
#include "Defines.h"
#include <fstream>
WorldMap::WorldMap() {
  m_data.resize(MAP_Y * MAP_X);
  for(size_t i = 0; i < m_data.size(); i++) {
    m_data[i] = nullptr;
  }
}
  
void WorldMap::LoadMap(const std::string &file) {
  std::vector<std::string> buffer;
  std::string linebuff;
  
  std::ifstream mfile;
  
  mfile.open(file);
  
  if(mfile.is_open()){
    while(std::getline(mfile, linebuff)) {
      buffer.push_back(linebuff);
    }
  }
  else {
    //Error Message please.
  }
  
  if(buffer.size() <= 0) {
    return;
  }
  
  for(size_t y = 0; y < buffer.size(); y++) {
    for(size_t x = 0; x < buffer[y].size();x++) {
      MapTile * tmp = new MapTile;
      switch(buffer[y][x]) {
	case '#':
	  tmp->x = x;
	  tmp->y = y;
	  tmp->symbol = '#';
	  tmp->foreColour = COLOR_BLACK;
	  tmp->backColour = COLOR_WHITE;
	  m_data[x+ y * MAP_X] = tmp;
	  break;
	 case '.':
	  tmp->x = x;
	  tmp->y = y;
	  tmp->symbol = '.';
	  tmp->foreColour = COLOR_WHITE;
	  tmp->backColour = COLOR_BLACK;
	  m_data[x+ y * MAP_X] = tmp;
	  break;
	 case '1':
	  tmp->x = x;
	  tmp->y = y;
	  tmp->symbol = 'S';
	  tmp->foreColour = COLOR_RED;
	  tmp->backColour = COLOR_GREEN;
	  tmp->team = 1;
	  m_data[x+ y * MAP_X] = tmp;
	  m_spawn.push_back(tmp);
	  break;
	 case '2':
	  tmp->x = x;
	  tmp->y = y;
	  tmp->symbol = 'S';
	  tmp->foreColour = COLOR_BLUE;
	  tmp->backColour = COLOR_GREEN;
	  tmp->team = 2;
	  m_data[x+ y * MAP_X] = tmp;
	  m_spawn.push_back(tmp);
	  break;
	 case '3':
	 case '4':
	  tmp->x = x;
	  tmp->y = y;
	  tmp->symbol = 'G';
	  tmp->foreColour = COLOR_GREEN;
	  tmp->backColour = COLOR_BLACK;
	  tmp->isGoal = true;
	  m_data[x+ y * MAP_X] = tmp;
	  m_goal.push_back(tmp);
	  break;
      }
    }
  }
}

void WorldMap::DrawMap(Console * con) {
  for(int y = 0; y < MAP_Y; y++) {
    for(int x = 0; x < MAP_X; x++) {
      if(m_data[x + y * MAP_X] != nullptr) {
        con->MoveCursor(x,y);
        MapTile *tmp =  m_data[x + y * MAP_X];
        con->PrintChar(tmp->symbol, tmp->foreColour, tmp->backColour);
      }
    }
  }
}

MapTile * WorldMap::GetMapTile(const int &x, const int &y) {
  if(x < 0 || y < 0) {
    return nullptr;
  }
  return m_data[x + y * MAP_X];
}

void WorldMap::UpdateMap() {
  std::ofstream file;
  file.open("debug.txt");
  for(int y = 0; y < MAP_Y; y++) {
    for(int x = 0; x < MAP_X; x++) {
      if(m_data[x+y*MAP_X] != nullptr) {
	file << m_data[x+y*MAP_X]->cost;
	file << "\n";
	//Update the color of the tile if it has blood and remove bloodLife;
	if(m_data[x+y*MAP_X]->hasBlood) {
	  m_data[x+y*MAP_X]->backColour = COLOR_RED;
	  if(m_data[x+y*MAP_X]->bloodLife > 0.00f) {
	    m_data[x+y*MAP_X]->bloodLife -= 0.10f;
	  }
	  else if(m_data[x+y*MAP_X]->bloodLife <= 0.00f) {
	    m_data[x+y*MAP_X]->hasBlood = false;
	    m_data[x+y*MAP_X]->bloodLife = 0.00f;
	    if(m_data[x+y*MAP_X]->symbol == '#') {
	      m_data[x+y*MAP_X]->backColour = COLOR_WHITE;
	    }
	    else if(m_data[x+y*MAP_X]->symbol == '.') {
	      m_data[x+y*MAP_X]->backColour = COLOR_BLACK;
	    }
	  }
	}
      
	//Update the goal team colours
	if(m_data[x+y*MAP_X]->team == 0 && m_data[x+y*MAP_X]->isGoal) {
	  m_data[x+y*MAP_X]->backColour = COLOR_BLACK;
	}
	else if(m_data[x+y*MAP_X]->team == 1) {
	  m_data[x+y*MAP_X]->backColour = COLOR_RED;
	}
	else if(m_data[x+y*MAP_X]->team == 2) {
	  m_data[x+y*MAP_X]->backColour = COLOR_BLUE;
	}
	  
	//Decrease move cost down untill it hits 0.
	if(m_data[x+y*MAP_X]->cost > 0.00f) {
	  m_data[x+y*MAP_X]->cost -= 0.01f;
	}
	else if(m_data[x+y*MAP_X]->cost < 0.00f) {
	  m_data[x+y*MAP_X]->cost = 0.00f;
	}
      }
    }
  }
}

bool WorldMap::GetSpawn(int & x, int &y, const int &team) {
  int jhhjgk = m_spawn.size();
  for(size_t i = 0; i < m_spawn.size(); i++) {
    int testTeam = m_spawn[i]->team;
    if(m_spawn[i]->team == team) {
      x = m_spawn[i]->x;
      y = m_spawn[i]->y;
      return true;
    }
  }
  return false;
}

bool WorldMap::GetGoal(int * x, int *y, const int &team) {
  for(size_t i = 0; i < m_goal.size(); i++) {
    if(m_goal[i]->team == team) {
      *x = m_goal[i]->x;
      *y = m_goal[i]->y;
      return true;
    }
  }
  return false;
}