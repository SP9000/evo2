# platforms
Platform cross-compatibility is achieved through the implementation of a small set of functions responsible for hardware-specific tasks such as rendering and audio.

### Rendering Functions
"""
void tv_DrawInit(void) 
"""
Perform any needed initialization before the engine begins any attempt to write to the display.

"""
void tv_DrawQuit(void)
"""
Do any cleanup necessary for gracefully terminating the engine once the application is halted.  If the target is not a host, you need not do anything.

"""
void tv_DrawStartFrame(void)
"""
Prepare for accepting draw commands for a new frame.

"""
void tv_DrawEndFrame(void)
"""
Stop accepting draw commands and copy the backbuffer to the framebuffer.

"""
void tv_Draw(Mesh*, Material*)
"""
Draw the given mesh (applying the provided material in the process).

#### Input Functions 
"""
void tv_InputInit(void)
"""
Initialize the platform for accepting hardware from the desired source.

"""
void tv_InputUpdate(void)
"""
The input system works via signals and slots.  This function is called once a frame and should emit a signal upon detection.

### Audio Functions
"""
void tv_AudioInit(void)
"""
Initialize the engine for audio playback.

"""
void tv_AudioPlay(AudioClip,bool)
"""
Play the given audioclip (looping if requested. 


## Adding a new platform
To add a new target platform:
1) Create a directory of the same name as the platform you wish to implement in the platform (this) directory.
2) Implement the above platform-specific functions in that directory.
3) Make the platform by changing the PLATFORM variable to the name of  your platform directory.

Good luck!

