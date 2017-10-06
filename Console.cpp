#include "Console.h"
#include <ncurses.h>

  void Console::Init() {
    /* Start curses mode*/
    initscr();
    
    //Check if we have a colour terminal.
    if(has_colors()) {
      m_hasColour = true;
      start_color();
      printw("Your teminal supports colour!");
    }
    else {
      m_hasColour = false;
      printw("Your teminal doesn't support colour!");
    }
    
    m_lastColour = 0;
    if(m_hasColour) {
      InitColourPairs();
    }
    
  }
  
  bool Console::HasColour() {
    return m_hasColour;
  }
  
  void Console::InitColourPairs() {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    
    init_pair(9, COLOR_WHITE, COLOR_WHITE);
    init_pair(10, COLOR_BLACK, COLOR_WHITE);
    init_pair(11, COLOR_RED, COLOR_WHITE);
    init_pair(12, COLOR_GREEN, COLOR_WHITE);
    init_pair(13, COLOR_YELLOW, COLOR_WHITE);
    init_pair(14, COLOR_BLUE, COLOR_WHITE);
    init_pair(15, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(16, COLOR_CYAN, COLOR_WHITE);
    
    init_pair(17, COLOR_WHITE, COLOR_RED);
    init_pair(18, COLOR_BLACK, COLOR_RED);
    init_pair(19, COLOR_RED, COLOR_RED);
    init_pair(20, COLOR_GREEN, COLOR_RED);
    init_pair(21, COLOR_YELLOW, COLOR_RED);
    init_pair(22, COLOR_BLUE, COLOR_RED);
    init_pair(23, COLOR_MAGENTA, COLOR_RED);
    init_pair(24, COLOR_CYAN, COLOR_RED);
    
    init_pair(25, COLOR_WHITE, COLOR_GREEN);
    init_pair(26, COLOR_BLACK, COLOR_GREEN);
    init_pair(27, COLOR_RED, COLOR_GREEN);
    init_pair(28, COLOR_GREEN, COLOR_GREEN);
    init_pair(29, COLOR_YELLOW, COLOR_GREEN);
    init_pair(30, COLOR_BLUE, COLOR_GREEN);
    init_pair(31, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(32, COLOR_CYAN, COLOR_GREEN);
    
    init_pair(33, COLOR_WHITE, COLOR_YELLOW);
    init_pair(34, COLOR_BLACK, COLOR_YELLOW);
    init_pair(35, COLOR_RED, COLOR_YELLOW);
    init_pair(36, COLOR_GREEN, COLOR_YELLOW);
    init_pair(37, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(38, COLOR_BLUE, COLOR_YELLOW);
    init_pair(39, COLOR_MAGENTA, COLOR_YELLOW);
    init_pair(40, COLOR_CYAN, COLOR_YELLOW);
    
    init_pair(41, COLOR_WHITE, COLOR_BLUE);
    init_pair(42, COLOR_BLACK, COLOR_BLUE);
    init_pair(43, COLOR_RED, COLOR_BLUE);
    init_pair(44, COLOR_GREEN, COLOR_BLUE);
    init_pair(45, COLOR_YELLOW, COLOR_BLUE);
    init_pair(46, COLOR_BLUE, COLOR_BLUE);
    init_pair(47, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(48, COLOR_CYAN, COLOR_BLUE);
    
    init_pair(49, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(50, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(51, COLOR_RED, COLOR_MAGENTA);
    init_pair(52, COLOR_GREEN, COLOR_MAGENTA);
    init_pair(53, COLOR_YELLOW, COLOR_MAGENTA);
    init_pair(54, COLOR_BLUE, COLOR_MAGENTA);
    init_pair(55, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(56, COLOR_CYAN, COLOR_MAGENTA);
    
    init_pair(57, COLOR_WHITE, COLOR_CYAN);
    init_pair(58, COLOR_BLACK, COLOR_CYAN);
    init_pair(59, COLOR_RED, COLOR_CYAN);
    init_pair(60, COLOR_GREEN, COLOR_CYAN);
    init_pair(61, COLOR_YELLOW, COLOR_CYAN);
    init_pair(62, COLOR_BLUE, COLOR_CYAN);
    init_pair(64, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(65, COLOR_CYAN, COLOR_CYAN);
  }
  
  void Console::SetColour(const int &fore, const int &back) {
    
    if(!m_hasColour) {
      return;
    }
    
    int index = GetColourPairIndex(fore, back);
    
    //Check to see if we have valid colours.
    if(index == 0) {
      return;
    }
    
    attron(COLOR_PAIR(index));
    
    m_lastColour = index;
    
  }
  
  void Console::ResetColour() {
    if(!m_hasColour || m_lastColour == 0) {
      return;
    }
    
    attroff(COLOR_PAIR(m_lastColour));
    m_lastColour = 0;
  }
  
  void Console::PrintChar(char c) {
    addch(c);
  }
  
  void Console::PrintChar(char c, const int &fore, const int &back) {
    SetColour(fore, back);
    addch(c);
    ResetColour();
  }
  
  void Console::PrintString(const std::string &str) {
    printw(str.c_str());
  }
  
  void Console::PrintString(const std::string &str, const int &fore, const int &back) {
    SetColour(fore, back);
    printw(str.c_str());
    ResetColour();
  }
  
  void Console::MoveCursor(const int &x, const int &y) {
    move(y,x);
  }
  
  int Console::GetColourPairIndex(const int &fore, const int &back) {
    switch(back){
      case COLOR_BLACK:
	switch(fore) {
	  case COLOR_WHITE:
	    return 1;
	    break;
	  case COLOR_BLACK:
	    return 2;
	    break;
	  case COLOR_RED:
	    return 3;
	    break;
	  case COLOR_GREEN:
	    return 4;
	    break;
	  case COLOR_YELLOW:
	    return 5;
	    break;
	  case COLOR_BLUE:
	    return 6;
	    break;
	  case COLOR_MAGENTA:
	    return 7;
	    break;
	  case COLOR_CYAN:
	    return 8;
	    break;
	}
	break;
      case COLOR_WHITE:
	switch(fore) {
	  case COLOR_WHITE:
	    return 9;
	    break;
	  case COLOR_BLACK:
	    return 10;
	    break;
	  case COLOR_RED:
	    return 11;
	    break;
	  case COLOR_GREEN:
	    return 12;
	    break;
	  case COLOR_YELLOW:
	    return 13;
	    break;
	  case COLOR_BLUE:
	    return 14;
	    break;
	  case COLOR_MAGENTA:
	    return 15;
	    break;
	  case COLOR_CYAN:
	    return 16;
	    break;
	  }
	  break;
	case COLOR_RED:
	  switch(fore) {
	    case COLOR_WHITE:
	      return 17;
	      break;
	    case COLOR_BLACK:
	      return 18;
	      break;
	    case COLOR_RED:
	      return 19;
	      break;
	    case COLOR_GREEN:
	      return 20;
	      break;
	    case COLOR_YELLOW:
	      return 21;
	      break;
	    case COLOR_BLUE:
	      return 22;
	      break;
	    case COLOR_MAGENTA:
	      return 23;
	      break;
	    case COLOR_CYAN:
	      return 24;
	      break;
	    }
	  break;
	case COLOR_GREEN:
	  switch(fore) {
	    case COLOR_WHITE:
	      return 25;
	      break;
	    case COLOR_BLACK:
	      return 26;
	      break;
	    case COLOR_RED:
	      return 27;
	      break;
	    case COLOR_GREEN:
	      return 28;
	      break;
	    case COLOR_YELLOW:
	      return 29;
	      break;
	    case COLOR_BLUE:
	      return 30;
	      break;
	    case COLOR_MAGENTA:
	      return 31;
	      break;
	    case COLOR_CYAN:
	      return 32;
	      break;
	    }
	  break;
	case COLOR_YELLOW:
	  switch(fore) {
	    case COLOR_WHITE:
	      return 33;
	      break;
	    case COLOR_BLACK:
	      return 34;
	      break;
	    case COLOR_RED:
	      return 35;
	      break;
	    case COLOR_GREEN:
	      return 36;
	      break;
	    case COLOR_YELLOW:
	      return 37;
	      break;
	    case COLOR_BLUE:
	      return 38;
	      break;
	    case COLOR_MAGENTA:
	      return 39;
	      break;
	    case COLOR_CYAN:
	      return 40;
	      break;
	    }
	  break;
	case COLOR_BLUE:
	  switch(fore) {
	    case COLOR_WHITE:
	      return 41;
	      break;
	    case COLOR_BLACK:
	      return 42;
	      break;
	    case COLOR_RED:
	      return 43;
	      break;
	    case COLOR_GREEN:
	      return 44;
	      break;
	    case COLOR_YELLOW:
	      return 45;
	      break;
	    case COLOR_BLUE:
	      return 46;
	      break;
	    case COLOR_MAGENTA:
	      return 47;
	      break;
	    case COLOR_CYAN:
	      return 48;
	      break;
	    }
	  break;
	case COLOR_MAGENTA:
	  switch(fore) {
	    case COLOR_WHITE:
	      return 49;
	      break;
	    case COLOR_BLACK:
	      return 50;
	      break;
	    case COLOR_RED:
	      return 51;
	      break;
	    case COLOR_GREEN:
	      return 52;
	      break;
	    case COLOR_YELLOW:
	      return 53;
	      break;
	    case COLOR_BLUE:
	      return 54;
	      break;
	    case COLOR_MAGENTA:
	      return 55;
	      break;
	    case COLOR_CYAN:
	      return 56;
	      break;
	    }
	  break;
	case COLOR_CYAN:
	  switch(fore) {
	    case COLOR_WHITE:
	      return 57;
	      break;
	    case COLOR_BLACK:
	      return 58;
	      break;
	    case COLOR_RED:
	      return 59;
	      break;
	    case COLOR_GREEN:
	      return 60;
	      break;
	    case COLOR_YELLOW:
	      return 61;
	      break;
	    case COLOR_BLUE:
	      return 62;
	      break;
	    case COLOR_MAGENTA:
	      return 63;
	      break;
	    case COLOR_CYAN:
	      return 64;
	      break;
	    }
	  break;
	  default:
	    return 0;
    }
  }
  
  void Console::RefreshScreen() {
    refresh();
  }
  
  char Console::GetChar() {
    return getch();
  }
  
  void Console::Clean() {
    endwin();
  }
  
  void Console::ClearScreen() {
    
  }