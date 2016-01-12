#ifndef ENUM_H
#define ENUM_H

/*
 * This enumeration contains the unique identifiers for every component.
 * Component's, in their "New" function, must assign their id to the 
 * appropriate value.
 * example:
 *   struct MyComponent * NewMyComponent()
 *   {
 *     struct tv_Component *c = malloc(sizeof(MyComponent));
 *     c->id = COMPONENT_MYCOMPONENT
 *     ...
 *   }
 */
enum{
  COMPONENT_TRANSFORM = 1,
  COMPONENT_MESH,
  COMPONENT_MATERIAL,

  COMPONENT_END /* must be at end - end of component enumeration */
};

#endif
