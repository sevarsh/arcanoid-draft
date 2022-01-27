#include "text.h"
#include "glut.h"

void text_c::Print()
{
  for (auto i : text)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)i);
}