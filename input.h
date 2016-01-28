#ifndef SYS_INPUT_H
#define SYS_INPUT_H

#include "sigslot.h"

/* enumeration of standard buttons. */
enum {
  TV_INPUT_BUTTON0 = 0,
  TV_INPUT_BUTTON1,
  TV_INPUT_BUTTON2,
  TV_INPUT_BUTTON3,
  TV_INPUT_BUTTON4,
  TV_INPUT_BUTTON5,
  TV_INPUT_BUTTON6,
  TV_INPUT_BUTTON7,
  TV_INPUT_BUTTON8,
  TV_INPUT_BUTTON9,
  TV_INPUT_BUTTON10,
  TV_INPUT_BUTTON11,
  TV_INPUT_BUTTON12,
};

/* enumeration of standard axes. */
enum {
  TV_INPUT_AXIS0 = 0,
  TV_INPUT_AXIS1,
  TV_INPUT_AXIS2,
  TV_INPUT_AXIS3,
};

/* ButtonDown is a signal emitted when a button is pressed. */
SIGNAL(ButtonDown, int)
/* ButtonUp is a signal emitted when a button is released. */
SIGNAL(ButtonUp, int)
/* AxisMove is a signal emitted when an axis is moved. */
SIGNAL(AxisMoved, int, int)
/* Kill is a signal emitted when the engine's execution is to be terminated. */
SIGNAL(Kill)

void tv_InputInit();
void tv_InputUpdate();

#endif
