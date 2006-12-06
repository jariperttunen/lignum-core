#ifndef VOXELBOXI_H
#define VOXELBOXI_H

namespace Lignum {


  //
  //	Dumps a conifer segment to the VoxelBox given as a parameter.
  //	Updates also the star value 
  //
  template <class TS,class BUD>
    void DumpSegment(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts,
		     int num_parts)
    {	
      LGMdouble r_f = GetValue(ts, LGARf);
      LGMdouble lenght = GetValue(ts, LGAL) / num_parts;
      LGMdouble S_f = GetValue(GetTree(ts), LGPsf);
      LGMdouble fmass = GetValue(ts, LGAWf) / num_parts;

      if (GetValue(GetTree(ts), LGPsf) == 0)
	S_f = 28;

      LGMdouble farea = S_f * fmass;	
      b.addNeedleArea(farea);
      b.addNeedleMass(fmass);

      LGMdouble needle_rad = GetValue(ts, LGARf);
	
     
      //Tarkistettu ett� for-looppi ajetaan tasan 8 kertaa (mika).
      for (double phi=0; phi<PI_VALUE/2.0; phi+=PI_VALUE/16)
	{		
	  b.starSum += b.S(phi, S_f, fmass, needle_rad, lenght)/8.0;
	}

      b.number_of_segments++;
    }
  
  //  Woody part
  //
  //    Dumps wood information to the VoxelBox given as a parameter.
  // 
  //
  template <class TS,class BUD>
    void DumpSegmentWood(VoxelBox &b, const TreeSegment<TS,BUD>& ts,
                     int num_parts)
    {   
      LGMdouble r = GetValue(ts, LGAR);
      LGMdouble length = GetValue(ts, LGAL) / num_parts;
      LGMdouble mass = GetValue(ts, LGAWood) / num_parts;
      LGMdouble area = 2.0*PI_VALUE*r*length;
      b.addWoodMass(mass);
      b.addWoodArea(area);
    }



  template <class OBJ>
  void InsertVoxelObject(VoxelBox& b, OBJ* obj)
  {
    b.objects.push_back(obj);
  }

   //Dump one leaf of a deciduous tree - corresponds to DumpSegment of
   //coniferous segments (CfTreeSegment)

   template <class S>
    void DumpLeaf(VoxelBox &b, const BroadLeaf<S> &leaf)
   { 
      LGMdouble xx = GetValue(leaf, LGAA);   //LGAA is defined in LGMSymbols.h
      b.addLeafArea(xx);
      b.addOneLeaf(); //increase the number of leaves by one
      xx = GetValue(leaf, LGAWf);
      b.addLeafMass(xx);

      //The weighted sum of the  leaf normals. Bigger leaf has more to
      //say to  the direction  of the "big  leaf" normal  than smaller
      //leaf
      b.big_leaf_normal=b.big_leaf_normal+GetLeafNormal(leaf)*GetValue(leaf, 
								       LGAA);
    }
  

  //
  //	Calculates the Qabs value to the CfTreeSegment
  //
  template <class TS,class BUD>
    void SetSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts, double num_parts)
    {
	
      LGMdouble S_f = GetValue(GetTree(ts), LGPsf);
      LGMdouble farea = S_f * GetValue(ts, LGAWf) / num_parts;
      LGMdouble qabs = 0.0;

      //Qabs computetd based on Qin, mean star and foliage area.
      qabs = b.getQin()*GetValue(ts,LGAstarm)*(GetValue(GetTree(ts), LGPsf)*GetValue(ts, LGAWf));

      SetValue(ts, LGAQabs, GetValue(ts, LGAQabs)+qabs);
      SetValue(ts, LGAQin, GetValue(ts, LGAQin)+b.getQin()/num_parts);
    }

  //Accumulate (multiply) the extinctions of the objects in the voxel
  class AccumulateObjectExtinction{
  public:
    AccumulateObjectExtinction(const Point& point,const PositionVector& direction,
			       const ParametricCurve& Kfun)
      :p0(point),dir(direction),K(Kfun){}
    LGMdouble operator()(LGMdouble tau, VoxelObject* object){
      tau = tau*(object->getExtinction(p0,dir,K));
      return tau;
    }
  private:
    const Point& p0;//Start of the light beam
    const PositionVector& dir;//Direction of th light beam
    const ParametricCurve& K;//The extinction function 
  };

} //namespace Lignum


#endif




