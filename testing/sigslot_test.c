#include "test.h"
#include "../sigslot.h"

SIGNAL(TestSignal, int)
SIGDEF(TestSignal)

void slot(int a){
  printf(" signal detected - received <%d>\n", a);
}

void TestSigSlot()
{
  puts("connecting slot...");
  CONNECT(TestSignal, slot);
  puts("emitting signal...");
  EMIT(TestSignal, 30);

  puts("\ndone");
}

