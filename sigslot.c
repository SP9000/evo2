#include "sigslot.h"

/* put signal type definitions here. */
SIGDEF(v)
  EMIT()

SIGDEF(i, int i0)
  EMIT(i0)

SIGDEF(ii, int i0, int i1)
  EMIT(i0, i1)

