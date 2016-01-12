#include "test.h"

void TestDraw()
{
  test_puts(" initializing...");
  tv_DrawInit();

  test_puts("beginning frame...");
  tv_DrawStartFrame();
  test_puts("finishing frame...");
  tv_DrawEndFrame();

  test_puts("\ndone");
  tv_DrawQuit();
}
