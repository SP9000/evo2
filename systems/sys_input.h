#ifndef SYS_INPUT_H
#define SYS_INPUT_H

#include "../system.h"

/* sys_Input is the system that handles the receiving and signalling of I/O */
struct sys_Input{
  struct tv_System sys;
};

struct sys_Input * NewInputSystem();

/* ButtonDown is a signal emitted when a button is pressed */
SIGNAL(ButtonDown, int);
/* ButtonUp is a signal emitted when a button is released */
SIGNAL(ButtonUp, int);
/* MoveMove is a signal emitted when the mouse is moved */
SIGNAL(MouseMove, int, int);

#endif
