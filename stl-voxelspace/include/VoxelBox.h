#ifndef VOXELBOX_H
#define VOXELBOX_H

#include <fstream>
#include <Lignum.h>

struct VisualCube
{
  LGMdouble x,y,z;
  float dist;
  float areaden;
  bool ready;
};

namespace Lignum {

  class VoxelSpace;


  class VoxelBox
  {
	
    template <class TS,class BUD>
      friend void DumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts, 
			    int num_parts);
    template <class SH>
      friend void DumpLeaf(VoxelBox &b, const BroadLeaf<SH>& leaf);

    template <class TS,class BUD>
      friend void SetSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts, 
			       int num_parts);
    friend ostream &operator << (ostream& os, VoxelBox &b);
  public:
    VoxelBox(VoxelSpace *s); 
    VoxelBox();
    //Recalculate star and val_c,  k_b and val_b
    //currently star and k_b hard-coded!!
    void updateValues();
    LGMdouble extinction(LGMdouble l)const;

    //reset the box to 0
    void reset(){resetQinQabs(); resetCfData();}

    bool isEmpty()const;

    Point getCenterPoint()const;
    Point getCornerPoint()const;
    int getNumSegments()const{ return number_of_segments; }
    int getNumLeaves()const{ return number_of_leaves; }
    LGMdouble getAreaDensity();
    LGMdouble getQabs()const{ return Q_abs; }
    LGMdouble getQin()const{ return Q_in; }
    LGMdouble getStarSum()const{ return starSum; }
    LGMdouble getStar()const{ return star; }
    LGMdouble getNeedleMass()const{return needleMass;}
    LGMdouble getNeedleArea()const{return needleArea;}
    LGMdouble getLeafMass()const{return leafMass;}
    LGMdouble getLeafArea()const{return leafArea;}
    LGMdouble getFoliageMass()const{return needleMass + leafMass;}

    void setArea( M2 needleA, M2 leafA);
    void setVoxelSpace(VoxelSpace *s, Point c);

    // Q_absbox
    LGMdouble interceptedRadiation;
    void addRadiation(LGMdouble r);
    void addNeedleArea(M2 narea) { needleArea += narea; }
    void addNeedleMass(M2 nmass) { needleMass += nmass; }
    void addLeafArea(M2 larea) { leafArea += larea; }
    void addLeafMass(LGMdouble lmass) {leafMass += lmass; }
    void addQabs(LGMdouble val) { Q_abs += val; }
    void addInterceptedRadiation(LGMdouble rad) { interceptedRadiation += rad; }
    void addStarSum(LGMdouble star){starSum += star;}
    void increaseNumberOfSegments(){number_of_segments++;}
    void addOneLeaf() {number_of_leaves++;}
    LGMdouble S(LGMdouble phi, LGMdouble sf, LGMdouble Wf,
		LGMdouble r, LGMdouble l);
  protected:
    void resetQinQabs(){Q_in = 0.0; Q_abs = 0.0;interceptedRadiation = 0.0;}
    void resetCfData(){starSum = 0.0;needleArea = 0.0;needleMass = 0.0;}
    LGMdouble star;
    LGMdouble starSum;
    LGMdouble SAc(LGMdouble phi, LGMdouble r, LGMdouble l);

    LGMdouble K(LGMdouble phi);
    M2 leafArea;
    M2 needleArea;
    LGMdouble Q_in;
    LGMdouble Q_abs;

    LGMdouble needleMass;
    LGMdouble leafMass;
    int number_of_segments;
    int number_of_leaves;

  private:
    void init();	
    Point corner1;

    LGMdouble val_c; //coniferous
    LGMdouble val_b; //broadleaf
    LGMdouble k_c;
    LGMdouble k_b;

    VoxelSpace *space;
  };

} //namespace Lignum

#include <VoxelBoxI.h>

#endif

