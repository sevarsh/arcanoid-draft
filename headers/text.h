#pragma 
#include <string>
using namespace std;

class text_c {

public:
  text_c(string s) : text(s) {};
  void Print();

private:
  string text;
};