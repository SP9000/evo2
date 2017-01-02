#include "gui.h"
#include <string.h>

/* NewGUIText returns a new GUI widget that will display text. */
struct GUIText NewGUIText(const char *text) {
	struct GUIText g = {.C = {.size = sizeof(struct GUIText)}, .size = 32};
	strncpy(g.text, text, sizeof(g.text));
	return g;
}
