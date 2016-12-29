#ifndef COMPONENT_GUI_H
#define COMPONENT_GUI_H

#include "entity.h"

/* GUIText holds a short message. */
struct GUIText {
	TV_COMPONENT
	char text[64];
};

struct GUIText NewGUIText(const char *);

#endif
