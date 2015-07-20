#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

/**
 * tv_EngineInit initializes the engine.  Call this before running the engine.
 */
int tv_EngineInit();

/**
 * tv_EngineTick runs one "tick" of the engine by updating all the engine's
 * systems and updating all entities.
 */
void tv_EngineTick();

/** 
 * tv_EngineRun runs the engine until it is terminated.
 */
void tv_EngineRun();

/**
 * tv_EngineRunning returns true if the engine is currently running.
 */
bool tv_EngineRunning();

#endif
