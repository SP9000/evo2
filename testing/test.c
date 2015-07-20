#include "test.h"

/* put test prototypes here */
void TestEntity();
void TestSigSlot();
void TestDraw();
void TestEngine();
void TestComponents();

void Tests()
{
  /* put tests to run here. */
  puts("\nDoing entity test");
  puts("-----------------------------------------");
  TestEntity();

  puts("\nDoing signal slot test");
  puts("-----------------------------------------");
  TestSigSlot();

  puts("\nDoing draw test");
  puts("-----------------------------------------");
  TestDraw();

  puts("\nDoing engine test");
  puts("-----------------------------------------");
  TestEngine();
}

int main()
{
  puts("\n\n*****************************************");
  puts("beginning tests");
  puts("*****************************************");
  
  Tests();

  puts("*****************************************");
  puts("done with tests");
  puts("*****************************************");
  return 0;
}

