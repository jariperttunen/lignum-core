#ifndef SHADINGI_H
#define SHADINGI_H

#include <mathsym.h>
#include <time.h>
#include <Tree.h>
using namespace Lignum;
using namespace sky;

#define HIT_THE_FOLIAGE 1
#define NO_HIT 0
#define HIT_THE_WOOD -1

int ellipsisBeamShading(Point& p0, PositionVector& v,
			BroadLeaf<Ellipse>& leaf);
int cylinderBeamShading(const Point& r0, const PositionVector& b, 
			const Point& rs, const PositionVector& a,
			double Rs, double Rw, double L, 
			double& distance );



//==============================================================
//THE HARDWOOD PART
//===============================================================

//This functor EvaluateRadiationForHwTreeSegment evaluates shading
//caused by all other leaves to all leaves of this hardwood
//segment. This functor uses functor ShadingEffectOfLeaf<TS,BUD> to
//go through all leaves and to check the shading.

//This method is not necessary for hardwoods. Having this this 'do
//nothing' method defined makes sure that programs compiles even if
//constructor of SGetFIWrapRadiationEvaluations<F,TS,BUD> is invoked with
//string argumend for hardwoods.
template <class TS,class BUD,class S>
void EvaluateRadiationForHwTreeSegment<TS,BUD,S>::setExtinction(ParametricCurve& K_in)
{
  ;
}



template <class TS,class BUD,class S>
void EvaluateRadiationForHwTreeSegment<TS,BUD,S>::operator()
  (TS* hwts)const
{

  // Radiation conditions are not evaluated if the segment has no leaves
  list<BroadLeaf<S>*> leaves = GetLeafList(*hwts);
  if (leaves.empty()) return;

  Tree<TS,BUD>& tt = GetTree(*hwts);
  FirmamentWithMask& firmament = GetFirmament(tt);
  int number_of_sectors = firmament.numberOfRegions();
  double tmp_adotb = 0, a_dot_b = 0.0;
  double help;
  MJ radiation = 0.0;
  vector<double> radiation_direction(3);
  
  vector<LGMdouble> result(number_of_sectors);
  vector<LGMdouble> init(number_of_sectors);
  typename list<BroadLeaf<S>*>::iterator Il = leaves.begin();

  ShadingEffectOfLeaf<TS,BUD>  s_e(hwts, *Il);

  //Go through of all leaves of this segment
  int i = 0;
  for (Il = leaves.begin(); Il != leaves.end(); Il++) {
    for(i = 0; i < number_of_sectors; i++)
      init[i] = 1.0;
    s_e.shaded_l = *Il;
    result = Accumulate(tt, init, s_e);
    SetRadiationVector(**Il, result);
  }

  //compute the total absorbed radiation 
  number_of_sectors = firmament.numberOfRegions();
  for (Il = leaves.begin(); Il != leaves.end(); Il++) {
    result = GetRadiationVector(**Il);
    SetValue(**Il, Qin, 0.0);
    SetValue(**Il, Qabs, 0.0);
    for(i = 0; i < number_of_sectors; i++) {
      radiation = firmament.diffuseRegionRadiationSum(i,radiation_direction);
      //cos of the angle between the leaf normal and the light beam
      tmp_adotb = Dot(GetLeafNormal(**Il),
		      PositionVector(radiation_direction[0],
				     radiation_direction[1], radiation_direction[2]) );
      a_dot_b = fabs(tmp_adotb);  
      help = radiation*result[i];
      SetValue(**Il, Qin, help+GetValue(**Il, Qin));
      help *= GetValue(**Il, dof)*(GetShape(**Il).getArea())*a_dot_b;
      SetValue(**Il, Qabs, help+GetValue(**Il, Qabs));
    }
  }
}


//This functor ShadingEffectOfLeaf<TS,BUD> evaluates shading caused
//by all leaves of a hardwood segment on a leaf (shaded_l) of a
//hardwood segment (shaded_s). 


template <class TS, class BUD,class S> 
ShadingEffectOfLeaf<TS,BUD,S>::
  ShadingEffectOfLeaf(HwTreeSegment<TS,BUD,S>* ts, BroadLeaf<S>* lf)
{
  shaded_s = ts;
  shaded_l = lf;
}


template <class TS,class BUD,class S>
vector<LGMdouble>& ShadingEffectOfLeaf<TS,BUD,S>::operator()(vector<LGMdouble>& v,
		       TreeCompartment<TS,BUD>* tc)const
{
  //  int beamShading(Point& p0, PositionVector& v,
  //	BroadLeaf& leaf);

  if (TS* ts = dynamic_cast<TS*>(tc)) {
    if (ts == shaded_s)
      return v;

    Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD> &>(GetTree(*ts));
    FirmamentWithMask& firmament = GetFirmament(tt);
    Point mp;
    int i = 0, number_of_sectors = 0, result = 0;
    LGMdouble Vp = 0.0;
    vector<double> radiation_direction(3);
    number_of_sectors = firmament.numberOfRegions();
  
    //XXXthis loop will contain the actual comparisons of tree segments and leaves
    //compare each leaf in shaded tree segment to each leaf in shading tree segment
    //to each sector

    list<BroadLeaf<S>*>& llshding = GetLeafList(*ts);
    typename list<BroadLeaf<S>*>::iterator Ishding;
    PositionVector tmp;
    mp = GetCenterPoint(*shaded_l);

    for (Ishding = llshding.begin(); Ishding != llshding.end(); Ishding++){
      for (i = 0; i < number_of_sectors; i++){
	//the radiation from the sector i and direction of sector i
	firmament.diffuseRegionRadiationSum(i,radiation_direction);
	tmp = PositionVector(radiation_direction[0],
			     radiation_direction[1],
			     radiation_direction[2]);
	result = ellipsisBeamShading(mp, tmp, **Ishding);
	if (result == HIT_THE_FOLIAGE){
	  Vp = 1.0-GetValue(**Ishding,dof)+GetValue(**Ishding,dof)*
	    GetValue(**Ishding,tauL);
	  v[i] *= Vp;
	}
      }
    }    //End of checking all leaves
  }
  return v;

} 



//=========================================================================
//THE CONIFER PART
//=========================================================================


//This functor EvaluateRadiationForCfTreeSegment evaluates shading
//caused by all other segments on this conifer segment. This functor
//uses functor ShadingEffectOfCfTreeSegment<TS,BUD> to go through all
//segments to check the shading.


template <class TS,class BUD>
void EvaluateRadiationForCfTreeSegment<TS,BUD>::setExtinction(ParametricCurve& K_in)
{
  K = K_in;
}



template <class TS, class BUD>
TreeCompartment<TS,BUD>* EvaluateRadiationForCfTreeSegment<TS,BUD>::operator() (TreeCompartment<TS, BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc)){

    // Radiation conditions are not evaluated if the segment has no foliage
    if (GetValue(*ts, Wf) < R_EPSILON)
      {
	SetValue(*ts, Qin, 0.0);
	SetValue(*ts, Qabs, 0.0);
	return tc;
      }

    Tree<TS,BUD>& tt = GetTree(*ts);
    FirmamentWithMask& firmament = GetFirmament(tt);
    int number_of_sectors = firmament.numberOfRegions();
    double a_dot_b = 0.0;
    vector<double> radiation_direction(3);
    vector<LGMdouble> shading_vector(number_of_sectors);
    vector<LGMdouble> result(number_of_sectors);
    vector<LGMdouble> init(number_of_sectors, 0.0);

    ShadingEffectOfCfTreeSegment<TS,BUD> s_e(ts, K);

    shading_vector = Accumulate(tt, init, s_e);

    MJ Iop = 0.0;
    MJ Q_in = 0.0;


    //implement "Ip = Iope^(-Vp)", shading_vector[i] = radiation coming
    //from direction i after this
    int i;
    for (i = 0; i < number_of_sectors; i++){
      if (shading_vector[i] == HIT_THE_WOOD){
	shading_vector[i] = 0.0;
      }
      else {
	Iop = firmament.diffuseRegionRadiationSum(i,radiation_direction);
	shading_vector[i] = Iop*exp((double)-shading_vector[i]);
      }
    }

    //Total incoming radiation  
    for (i = 0; i < number_of_sectors; i++){
      Q_in += shading_vector[i];
    }

    //Evaluate how much segment absorbs of incoming radation.
    // shading_vector[i] = amount of radiation absorbed from direction i after this

    LGMdouble Lk, inclination, Rfk, Ack, extinction, sfk, Ask, Wfk;
    Lk = Rfk = Ack =  extinction = sfk = Ask = Wfk = 0.0;

    vector<LGMdouble> absorbed_radiation(number_of_sectors);
    Lk = GetValue(*ts, L);   //length is > 0.0, otherwise we would not bee here
    Rfk = GetValue(*ts, Rf);  //Radius to foliage limit 
    Wfk = GetValue(*ts, Wf); //Foliage mass
    sfk  = GetValue(tt, sf); //Foliage m2/kg from tree

    for (i = 0; i < number_of_sectors; i++){
      Iop = firmament.diffuseRegionRadiationSum(i,radiation_direction);
      a_dot_b = Dot(GetDirection(*ts), PositionVector(radiation_direction));
      inclination = PI_DIV_2 - acos(fabs(a_dot_b));

      Ack = 2.0*Lk*Rfk*cos(inclination) + PI_VALUE*pow(Rfk,2.0)*sin(inclination);
      extinction = (double)K(inclination);

      if (Ack == 0.0){
	cout << "ERROR EvaluateRadiationForCfTreeSegment: Ack == 0 (division by 0)"
	     << endl;
      }

      //implement I(k)p = Ip*Ask
      Ask = (1.0 - exp(-extinction*((sfk*Wfk)/Ack)))*Ack;
      shading_vector[i] *= Ask;
    }

    //Amount of absorbed radiation

    LGMdouble Q_abs = 0.0;
    for (i = 0; i < number_of_sectors; i++){
      Q_abs += shading_vector[i];
    }

    SetValue(*ts, Qabs, Q_abs);
    SetValue(*ts, Qin, Q_in);
  }
  return tc;
}




//This functor ShadingEffectOfCfTreeSegment<TS,BUD> evaluates shading caused
//by a conifer segment on this conifer segment (shaded_s)

template <class TS,class BUD>
vector<LGMdouble>& ShadingEffectOfCfTreeSegment<TS,BUD>::
    operator()(vector<LGMdouble>& v, TreeCompartment<TS,BUD>* tc)const {

  //  int beamShading(Point& p0, PositionVector& v,

  if (CfTreeSegment<TS,BUD>* ts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc)) {
    if (ts == shaded_s)
      return v;

    int i = 0, number_of_sectors = 0, result = NO_HIT;
    double distance = 0.0;
    vector<double> radiation_direction(3);

    Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD> &>(GetTree(*ts));
    
    FirmamentWithMask& firmament = GetFirmament(tt);
    
    number_of_sectors = firmament.numberOfRegions();

    LGMdouble fol_dens = GetValue(*ts,Wf)/
      (PI_VALUE*(pow(GetValue(*ts,Rf),2.0)-pow(GetValue(*ts,R),2.0))
       *GetValue(*ts,L));

    for (i = 0; i < number_of_sectors; i++) {
      //if the sector is blocked by another shoot
      //do not make computations, check the next sector instead
      if (v[i] == HIT_THE_WOOD) { 
	continue;
      }
      //the radiation from the sector i and direction of sector i
      firmament.diffuseRegionRadiationSum(i,radiation_direction);

      Point r_0 =  GetPoint(*shaded_s)+0.5*GetValue(*shaded_s,L)*
	(Point)GetDirection(*shaded_s);        //Midpoint of shaded seg

      result = cylinderBeamShading(r_0,
			 radiation_direction,
			 GetPoint(*ts),
			 GetDirection(*ts),
			 GetValue(*ts, Rf),
			 GetValue(*ts, R),
			 GetValue(*ts, L),
			 distance);


      if (result == HIT_THE_WOOD){
	//mark the sector blocked 
	v[i] = HIT_THE_WOOD;
      }
      else if (result == HIT_THE_FOLIAGE){
	//otherwise compute Vp (the shadiness):
	//1.compute the inclination of the shaded shoot
	double a_dot_b = Dot(GetDirection(*ts),
			     PositionVector(radiation_direction));
	//      double a_dot_b = ((TVector<double>)shaded_shoot->getDirection().get_position()) *
	//	               radiation_direction;
	double inclination = PI_DIV_2 - acos(fabs(a_dot_b));
	//2.the light extinction coefficient according to inclination
	double extinction = K(inclination);
	//3.Vp = extinction*distance*foliage_density
	double Vp = extinction *distance*fol_dens;
	v[i] += Vp;
      }
  
    }
  }
  return v;
}
#undef HIT_THE_FOLIAGE
#undef NO_HIT
#undef HIT_THE_WOOD

#endif

