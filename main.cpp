#include <ncurses.h>
#include <string>
#include "Console.h"
#include "Map.h"
#include "ActorManager.h"
#include "Defines.h"

int main() {
  
  Console cTemp;
  WorldMap * wmap = new WorldMap;
  ActorManager amanager(TOTAL_ACTORS, wmap);
  
  cTemp.Init();
  cTemp.PrintString("Loading Map!");
  wmap->LoadMap("/home/pi/Documents/SourceCode/PathFinding/TestMap.txt");
  cTemp.PrintString("Creating Actor!");
  wmap->DrawMap(&cTemp);
  cTemp.RefreshScreen();
  //cTemp.GetChar();
  
  char c;
  while(c != 't') {
    amanager.SpawnActor();
    amanager.TickActors(&cTemp);
    amanager.CleanUp();
    wmap->UpdateMap();
    wmap->DrawMap(&cTemp);
    amanager.DrawActors(&cTemp);
    cTemp.RefreshScreen();
    
    c = cTemp.GetChar();
  }
  cTemp.Clean();
  delete wmap;
  return 0;
}