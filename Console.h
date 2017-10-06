#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>

class Console {
public:
  void Init();
  bool HasColour();
  
  void InitColourPairs();
  
  void SetColour(const int &fore, const int &back);
  
  void ResetColour();
  
  void PrintChar(char c);
  
  void PrintChar(char c, const int &fore, const int &back);
  
  void PrintString(const std::string &str);
  
  void PrintString(const std::string &str, const int &fore, const int &back);
  
  void MoveCursor(const int &x, const int &y);
  
  int GetColourPairIndex(const int &fore, const int &back);
  
  void RefreshScreen();
  
  char GetChar();
  
  void Clean();
  
  void ClearScreen();
private:
  bool m_hasColour;
  int m_lastColour;
};


#endif //CONSOLE_H