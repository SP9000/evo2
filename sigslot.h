#ifndef SIGSLOT_H
#define SIGSLOT_H

#include <stdbool.h>

/*
 * TV_SIGNAL_MAX_SLOTS maximum number of slots that may be connected to a 
 * signal. You can easily work around this limitation by using multiple slots
 * if need be.
 */
#define TV_SIGNAL_MAX_SLOTS 31

/**
 * SIGNAL is a macro that defines a new type of signal and slot as well as the
 * necessary functions to connect and emit to/from it.
 *
 * Every signal has an emit method that signals the triggering of the signal
 * to all connected slots. 
 * Here is a simple signal implementation:
 *   struct 
 *   {
 *     int (*emit)(int, int)  //the emit function
 *     struct mySlot slots[]  //slots that expect an emit of this signal's form.
 *   }mySignal;
 * Slots are named by the following convention:
 * tv_SlotABC... where A, B,C, etc. are the types of the parameters to the slot.
 * the types are represented by the following lowercase characters:
 *  c- character
 *  f- float
 *  i- integer
 *  v- void 
 *  p- pointer 
 * It is recommended that you typedef slots and signals to more useful names 
 * in each case they are used.  For example:
 * typedef tv_Slotv openDoorSlot;
 * typedef tv_Signalv openDoorSignal;
 */
#define SIGNAL(name, ...) \
  typedef void (*tv_Slot ## name)( __VA_ARGS__ ); \
  struct tv_Signal ## name \
  { \
    struct tv_Signal sig; \
    tv_Slot ## name slots[TV_SIGNAL_MAX_SLOTS]; \
  }; \
  void tv_Signal ## name ## Init(struct tv_Signal ## name *sig); \
  void tv_Signal ## name ## Emit(struct tv_Signal ## name *sig, ## __VA_ARGS__); \
  void tv_Signal ## name ## Connect(struct tv_Signal ## name *sig, tv_Slot ## name slot);

/**
 * tv_Signal is a struct that contains basic information used to trigger slots
 */
struct tv_Signal 
{
  unsigned _numSlots;
  bool _active;
};

/* put signal/slot type declarations here. */
SIGNAL(v);
SIGNAL(i, int);
SIGNAL(ii, int, int);

#endif

