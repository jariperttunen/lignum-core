#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP
#include <list>
#include <Tree.h>


#include <BroadLeaf.h>
#include <Firmament.h>

namespace Lignum{

template <class TS, class BUD=DefaultBud<TS> >
class HwTreeSegment:public TreeSegment<TS,BUD>{
  template <class TS1,class BUD1>
  friend list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend void InsertLeaf(HwTreeSegment<TS1,BUD1>& ts, BroadLeaf* l);
  template <class TS1,class BUD1>
  friend void InitializeForRadiation(HwTreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend int GetNumberOfLeaves(const HwTreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend LGMdouble GetLeafArea(const HwTreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend LGMdouble SetLeafArea(HwTreeSegment<TS1,BUD1>& ts, const LGMdouble value);
  template <class TS1,class BUD1>
  friend LGMdouble GetValue(const HwTreeSegment<TS1,BUD1>& ts, const LGMAD name);
public:
  HwTreeSegment(const cxxadt::Point<METER>& p,const PositionVector& pv,
		const LGMdouble go,const Lignum::METER l, const Lignum::METER r,
		const Lignum::METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
private:
  list<BroadLeaf*> leaf_ls;
};

#include <HwTreeSegmentI.h>

} //close namespace Lignum



#endif
