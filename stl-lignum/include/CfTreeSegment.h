#ifndef CFTREESEGMENT_H
#define CFTREESEGMENT_H

#include <list>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <CfTreeFunctor.h>
#include <TreeSegment.h>

namespace Lignum{

  using namespace cxxadt;

  class CfTreeSegmentAttributes{
  public:
    CfTreeSegmentAttributes():
      Hf(0.0),P(0.0),Qin(0.0),Qabs(0.0),Rf(0.0),starm(0.0),Wf(0.0){}
    METER Hf;       //Foliage height
    LGMdouble P;    //Amount of photosynthesis (kg C) during time step
    LGMdouble Qin;  //Irradiance of incoming radiation (MJ/m2)
    LGMdouble Qabs; //Amount of absorbed radiation (MJ) (during time step)
    METER Rf;       //Radius to foliage limit
    LGMdouble starm;//Star mean for the coniferous segment
    KGC Wf;         //Foliage mass of the tree segment

  };

  class CfData:public TcData{
  public:
    CfData& operator = (TcData&  tcd){
      CfData& cfdata = dynamic_cast<CfData&>(tcd);
      SetValue(*this,LGAAs,GetValue(cfdata,LGAAs)); 
      return *this;
    }
    CfData& operator += (TcData& tcd){
      CfData& cfdata = dynamic_cast<CfData&>(tcd);
      SetValue(*this,LGAAs,GetValue(*this,LGAAs)+GetValue(cfdata,LGAAs));
      return *this;
    }
    void clear(){SetValue(*this,LGAAs,0.0);} 
  };

  template <class TS,class BUD=DefaultBud<TS> >
  class CfTreeSegment:public TreeSegment<TS,BUD>{
    template <class TS1,class BUD1>
    friend LGMdouble GetValue(const CfTreeSegment<TS1,BUD1>& ts, const LGMAD name);
    template <class TS1,class BUD1>
    friend LGMdouble SetValue(CfTreeSegment<TS1,BUD1>& ts, const LGMAD name,
			      const LGMdouble);
  public:
    CfTreeSegment(const Point& p,const PositionVector& pv,const LGMdouble go,const METER l,
		  const METER r,const METER rh,Tree<TS,BUD>* tree);
    void photosynthesis();
    void respiration();
    void aging();
    TcData& diameterGrowth(TcData& data);
  private:
    CfTreeSegmentAttributes cftsa;
  };


}//close namespace Lignum

#include <CfTreeSegmentI.h>
#include <CfTreeSegmentMetabolismI.h>


#endif



