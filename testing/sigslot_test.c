#include "test.h"
#include "../sigslot.h"

void slot() 
{
  puts(" signal detected");
}

void TestSigSlot()
{
  struct tv_Signalv sig;

  tv_SignalvInit(&sig);
  puts("connecting slot...");
  tv_SignalvConnect(&sig, slot);
  puts("emitting signal...");
  tv_SignalvEmit(&sig);

  puts("");
  puts("done");
}

