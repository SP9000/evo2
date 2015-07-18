#include "test.h"

/* put test prototypes here */
void TestEntity();
extern void TestSigSlot();

void Tests()
{
  /* put tests to run here. */
  puts("\nDoing entity test");
  puts("-----------------------------------------");
  TestEntity();

  puts("\nDoing signal slot test");
  puts("-----------------------------------------");
  TestSigSlot();
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

