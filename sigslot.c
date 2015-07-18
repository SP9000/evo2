#include "sigslot.h"

#undef SIGNAL
#define SIGNAL(name, ...) \
  void tv_Signal ## name ## Init(struct tv_Signal ## name *sig) \
  { \
    struct tv_Signal *s; \
    s = (struct tv_Signal*)sig; \
    s->_active = true; \
    s->_numSlots = 0; \
  } \
  void tv_Signal ## name ## Connect(struct tv_Signal ## name *sig, tv_Slot ## name slot) \
  { \
    struct tv_Signal *s; \
    s = (struct tv_Signal*)sig; \
    if(s->_numSlots < TV_SIGNAL_MAX_SLOTS) \
    { \
      sig->slots[s->_numSlots] = slot; \
      s->_numSlots++; \
    } \
  }  \
  void tv_Signal ## name ## Emit(struct tv_Signal ## name *sig, ## __VA_ARGS__) \
  { \
    unsigned i; \
    struct tv_Signal *s; \
    s = (struct tv_Signal*)sig; \
    for(i = 0; i < s->_numSlots; ++i) \
    { 

/**
 * EMIT is a macro that must be placed immediately following a SIGNAL macro.
 * It provides the arguments passed to every slot called when a signal is 
 * emitted. 
 */
#define EMIT(...) \
      sig->slots[i](__VA_ARGS__); \
    } \
  }
    
/* put signal type definitions here. */
SIGNAL(v)
  EMIT()

SIGNAL(i, int i0)
  EMIT(i0)

SIGNAL(ii, int i0, int i1) 
  EMIT(i0, i1)

