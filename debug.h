#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#define debug_puts puts
#define debug_printf printf
#else
#define debug_puts
#define debug_printf
#endif

#endif
