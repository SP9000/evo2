#ifndef SYS_INPUT_H
#define SYS_INPUT_H

#include "sigslot.h"

/* ButtonDown is a signal emitted when a button is pressed. */
SIGNAL(ButtonDown, int)
/* ButtonUp is a signal emitted when a button is released. */
SIGNAL(ButtonUp, int)
/* MoveMove is a signal emitted when the mouse is moved. */
SIGNAL(MouseMove, int, int)
/* Kill is a signal emitted when the engine's execution is to be terminated. */
SIGNAL(Kill)

void tv_InputInit();
void tv_InputUpdate();

#endif
