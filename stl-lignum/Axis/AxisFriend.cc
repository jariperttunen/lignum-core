
#include <Axis.h>

//Return the terminating bud of the axis
Bud* GetTerminatingBud(const Axis& axis)
{
  return (Bud *) axis.tc_ls.back();
}

//insert a tree compartment to the last position of the list
void InsertTreeCompartment(Axis& axis, TreeCompartment* tc)
{
  list<TreeCompartment*>::iterator iter = axis.tc_ls.end();
  axis.tc_ls.insert(--iter,tc);
}

