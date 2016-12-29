#ifndef GUI_H
#define GUI_H

#include <stdint.h>

/* enumerations for the virtual GUI display. */
enum { TV_GUI_W = 320, TV_GUI_H = 240 };

void tv_GuiRect(unsigned, unsigned, unsigned, unsigned, uint32_t);
void tv_GuiText(unsigned, unsigned, const char*);

#endif
