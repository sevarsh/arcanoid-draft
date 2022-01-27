#include "glut.h"
#include "game.h"

#define WIDTH 400
#define HEIGHT 500

game_c game(vector2_c(WIDTH, HEIGHT));
static int winId;

void Shift(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_LEFT:
    game.MovePlatform(-10);
    break;
  case GLUT_KEY_RIGHT:
    game.MovePlatform(10);
    break;
  case GLUT_KEY_UP:
    game.LaunchBall();
  }
}

void Keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27: // Escape key
      glutDestroyWindow(winId);
      exit(0);
      break;
  }
  glutPostRedisplay();
}

void Idle()
{
  game.Run();
  //change
}

void Display()
{
  glClearColor(0, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  game.DrawGame();
  glDisable(GL_BLEND);
  
  glFinish();

  glutSwapBuffers();
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(200, 50);
  winId = glutCreateWindow("Arcanoid");

  glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);

  glutDisplayFunc(Display);
  glutIdleFunc(Idle);  
  glutSpecialFunc(Shift);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();

  return 0;
}