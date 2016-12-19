# evo2
evo2 is an efficient low-level, and low-dependency game engine.

evo2 follows the ECS (entity-component-system) paradigm quite purely.
As such, most of its functionality is implemented through "systems".

## Components
Components are just data.  That's it.

## Entities
Entities are basically arrays of components.  Every single object represented
in the game is done so through an entity.  Text, monsters, terrain, etc.

## Systems
Updates to entities are done every frame through systems.
Systems run through the list of game entities each frame and update those that
contain the propert(y/ies) that the particular system requires.  
The rendering system, for example, finds all entities that have a material,
mesh, and render component.
The collision system looks updates any entities  with a collider component.

## Messages
Inter-entity communication is handled one of two ways:
 a) directly accessing component data
 b) listening for a particular signal

### Component Data Access
Often the simplest way to communicate with other entities is by accessing
data in their components.  While slots wait for particular events to occur,
direct member access requires zero knowledge of the entity which it is 
interacting with at runtime.

To access components of other entities you use the tv_EntityGetComponent
function as shown in this example:
"""
  tv_Entity *target = GetEntity("Apple");
  struct Collider * c = tv_EntityGetComponent(target, COLLIDER);
  if(c){
    ...
  }
"""
Once a pointer has been acquired, you can access the internals of the component
as normal.


### Signals and Slots
For scenarios where pre-defined messages are required to drive certain aspects
of the engine, signals/slots are the best solution.  
Signals and slots are the means with which you receive important engine
informations such as input, but they can also be defined by the user to trigger
functions as requested. 
"""
SIGNAL(SignalName)
SIGDEF(SignalName)
void OnSignal()
{
  puts("signal caught");
}
void setup()
{
  CONNECT(SignalName, OnSignal)
  EMIT(SignalName);
}
"""
