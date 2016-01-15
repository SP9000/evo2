#include "draw.h"
#include "enum.h"
#include "test.h"
#include "components/mesh.h"

void TestDraw()
{
  struct Mesh mesh;
  struct Mesh *eptr, *mptr;

  test_puts(" initializing...");
  tv_DrawInit();

  test_puts("beginning frame...");
  tv_DrawStartFrame();

  test_puts("drawing quad...");
  mesh = MeshNewQuad();
  eptr = tv_EntityNew(1,
      COMPONENT_MESH, &mesh);
  test_puts("drawing quad...");
  mptr = tv_EntityGetComponent(eptr, COMPONENT_MESH);
  tv_Draw(mptr, NULL);

  test_puts("finishing frame...");
  tv_DrawEndFrame();

  test_puts("\ndone");
  tv_DrawQuit();
}
