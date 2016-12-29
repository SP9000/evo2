#include "gui.h"
#include <string.h>

/* NewGUIText returns a new GUI widget that will display text. */
struct GUIText NewGUIText(const char *text) {
	struct GUIText g = {.C = {.size = sizeof(struct GUIText)}};
	strncpy(g.text, text, sizeof(g.text));

	return g;
}
