#include "test.h"
#include "../draw.h"

void TestDraw()
{
  SDL_Renderer *renderer;
  SDL_Rect rect;

  tv_DrawInit();
  rect.x = 10;
  rect.y = 10;
  rect.w = 100;
  rect.h = 100;

  puts("beginning frame...");
  tv_DrawStartFrame();
  puts("finishing frame...");
  tv_DrawEndFrame();

  puts("\ndone");
  tv_DrawQuit();
}
