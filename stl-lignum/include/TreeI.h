#ifndef TREEI_H
#define TREEI_H


#include <TreeMetabolism.h>

using namespace sky;

namespace Lignum{

template <class TS,class BUD>
Tree<TS,BUD>::Tree()
  :root_axis(Point(0,0,0),PositionVector(0,0,-1),*this)
{
  tree = NULL;
}

//Construct a tree at a certain position to a certain direction
//with one terminating bud in the main axis
template <class TS,class BUD>
Tree<TS,BUD>::Tree(const Point& p, const PositionVector& d)
  :TreeCompartment<TS,BUD>(p,d,this),f(5,5),axis(p,d,this),
  root_axis(p,d,*this){ }


template <class TS,class BUD>
Tree<TS,BUD>::Tree(const Point& p, const PositionVector& d, LGMdouble len, LGMdouble rad, int num_buds) :TreeCompartment<TS,BUD>(p,d,this),f(5,5),axis(p,d,this),
    root_axis(p,d,*this)
{
  //force the instantiation of BranchingPoint
  BranchingPoint<TS,BUD>(p,d,this);
  
  TreeSegment<TS,BUD> *ts = new TreeSegment<TS,BUD>(p,d, 0, len, rad,0, this);

  SetValue(*ts, LGAomega, 1);
  SetValue(*ts, LGAage, 0);

  if(TS* tts = dynamic_cast<TS *>(ts))
    {
      SetValue(*tts, LGAWf, 0.03);
    }
  SetValue(*ts, LGARf, rad + 0.02);

  LGMdouble x_i = GetValue(*this, LGPxi);
  LGMdouble ts_rad = GetValue(*ts, LGAR);
  
  //Sapwood area corresponds to foliage mass
  LGMdouble A_s = (1.0 - GetValue(*this, LGPxi)) * 
    GetValue(*ts, LGAWf)/(2.0*GetValue(*this, LGPaf)*
			  GetValue(*this, LGPlr));
  
  if (A_s > PI_VALUE*ts_rad*ts_rad)
    SetValue(*ts, LGARh, 0);
  
  
  LGMdouble r_h = sqrt((PI_VALUE*ts_rad*ts_rad - A_s)/PI_VALUE);
  SetValue(*ts, LGARh, r_h);
  
  Point end_point = p + Point(0,0,len);
  BranchingPoint<TS,BUD> *bp = 
    new BranchingPoint<TS,BUD>(end_point,
			       PositionVector(0,0,1), 
			       this);
  
  Bud<TS,BUD> *bud1 = new Bud<TS,BUD>(end_point, d, 1, this);
  SetValue(*bud1, LGAage, 1);
  SetValue(*bud1, state, ALIVE);

  Axis<TS,BUD> &axis = GetAxis(*this);
  InsertTreeCompartment(axis, ts);      
  InsertTreeCompartment(axis, bp);
  InsertTreeCompartment(axis , bud1);
  
  Axis<TS,BUD> *new_axes[20];
  int index = 0;
  
  PositionVector v2(0, sqrt(2.0)/2.0, sqrt(2.0)/2.0);
  LGMdouble delta_angle = 2 * PI_VALUE / num_buds;              
  while(num_buds > 0)
    {
      new_axes[index] = new Axis<TS,BUD>();
      
      v2.rotate(Point(0,0,0), PositionVector(0,0,1), delta_angle);
      Bud<TS,BUD> *new_bud = 
	new Bud<TS,BUD>(GetPoint(*bud1), v2, 2, this);
      SetValue(*new_bud,LGAage, 1);
      SetValue(*new_bud,state, ALIVE);
      
      InsertTreeCompartment(*new_axes[index], new_bud);
      index++;
      num_buds--;
    }
}



//Get a parameter value 
template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMPD name)
{
  if (name == LGPaf)
    return tree.tp.af;

  else if (name == LGPaleafmax)
    return tree.tp.aleafmax;

  else if (name == LGPar)
     return tree.tp.ar;

  else if (name == LGPdof)
     return tree.tp.dof;

  else if (name == LGPlr)
    return tree.tp.lr;		 
  
  else if (name == LGPmf)
    return tree.tp.mf;

  else if (name == LGPmr)
    return tree.tp.mr;

  else if (name == LGPms)
    return tree.tp.ms;

  else if (name == LGPna)
    return tree.tp.na;

  else if (name == LGPnl)
    return tree.tp.nl;

  else if (name == LGPpr)
    return tree.tp.pr;

  else if (name == LGPq)
    return tree.tp.q;

  else if (name == LGPrhoW)
    return tree.tp.rhoW;

  else if (name == LGPrho_root)
    return tree.tp.rho_root;
  
  else if ( name == LGPrho_hair)
    return tree.tp.rho_hair;

  else if (name == LGPsf)
    return tree.tp.sf;

  else if (name == LGPsr)
    return tree.tp.sr;

  else if (name == LGPss)
    return tree.tp.ss;

  else if (name == LGPtauL)
    return tree.tp.tauL;

  else if (name == LGPxi)
    return tree.tp.xi;

  else if (name == LGPyc)
    return tree.tp.yc;

  else if (name == LGPzbrentEpsilon)
     return tree.tp.zbrentEpsilon;

  else{
    cerr << "Tree::GetValue() uknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return 0.0;
}


//Change a parameter value, return the old value
template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMPD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tree,name);

  if (name == LGPaf)
    tree.tp.af = value;

  else if (name == LGPaleafmax)
    tree.tp.aleafmax = value;

  else if (name == LGPar)
    tree.tp.ar = value;

  else if (name == LGPdof)
    tree.tp.dof = value;

  else if (name == LGPlr)
    tree.tp.lr = value;
  
  else if (name == LGPmf)
    tree.tp.mf = value;

  else if (name == LGPmr)
    tree.tp.mr = value;

  else if (name == LGPms)
    tree.tp.ms = value;

  else if (name == LGPna)
    tree.tp.na = value;

  else if (name == LGPnl)
    tree.tp.nl = value;

  else if (name == LGPpr)
    tree.tp.pr = value;

  else if (name == LGPq)
    tree.tp.q = value;

  else if (name == LGPrhoW)
    tree.tp.rhoW = value;

  else if (name == LGPrho_root)
    tree.tp.rho_root = value;

  else if (name == LGPrho_hair)
    tree.tp.rho_hair = value;

  else if (name == LGPsf)
    tree.tp.sf = value;

  else if (name == LGPsr)
    tree.tp.sr = value;

  else if (name == LGPss)
    tree.tp.ss = value;

  else if (name == LGPtauL)
    tree.tp.tauL = value;

  else if (name == LGPxi)
    tree.tp.xi = value;

  else if (name == LGPyc)
     tree.tp.yc = value;

  else if (name == LGPzbrentEpsilon)
    tree.tp.zbrentEpsilon = value;

  else{
    cerr << "Tree::SetValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return old_value;
}



//Index the tree attribute vector with range check.
template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMTAD name)
{ 
  //no need to go to tree compartment, these are tree level attributes
  return  tree.ta.v[name];
}

//Index the tree attribute vector with range check.
template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMTAD name, const LGMdouble value)
{

  LGMdouble old_value = GetValue(tree,name);
  //no need to go to tree compartment, these are tree level attributes
  tree.ta.v[name] = value;
  
  return old_value;
}
  

template <class TS,class BUD>
Axis<TS,BUD>& GetAxis(Tree<TS,BUD>& t)
{
  return t.axis;
}

template <class TS,class BUD>
RootAxis<Tree<TS,BUD> >& GetRootAxis(Tree<TS,BUD>& t)
{
  return t.root_axis;
}

//Return a tree function as a ParametricCurve
template<class TS, class BUD>
const ParametricCurve& GetFunction(const Tree<TS,BUD>& tree, LGMF name)
{  

  if (name == LGMAL){
    return tree.tf.al;
  }

  else if (name == LGMFM){
     return tree.tf.fm;
  }

  else if (name == LGMIP){
    return tree.tf.ip;
  }

  else if (name == LGMNB){
    return tree.tf.nb;
  }


  else if (name == LGMLONB){
    return tree.tf.LightOnNumBuds;
  }

  else if (name == LGMVI){
    return tree.tf.vi;
  }

  else if (name == LGMVIONB){
    return tree.tf.VigourOnNumBuds;
  }

  else{
    cerr << "GetFunction unknown function: " << name << endl;
  }
  throw ParametricCurve();
}
  
//At the moment returns the name of the only (ASCII) file that contains
//the definition of the initial tree. Later - maybe - several such files.
template<class TS, class BUD>
string GetTreeInitializationFile(Tree<TS,BUD>& tree) {
  return tree.tif.treeFile;
}


template <class TS,class BUD>
void SetFirmament(const Tree<TS,BUD>& tree, const FirmamentWithMask& frmnt)
{
  tree.f = frmnt;
}
 
template <class TS,class BUD>
FirmamentWithMask& GetFirmament(Tree<TS,BUD>& tree) {
  return tree.f;
}


template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMAD name)
{
	
  if (name == LGAH){
    Axis<TS,BUD>& axis = GetAxis(const_cast<Tree<TS,BUD>&>(tree));
    list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
    BUD* bud = dynamic_cast<BUD*>(ls.back());
    return GetPoint(*bud).getZ();
  }
  else if (name == LGADbase){
    Axis<TS,BUD>& axis = GetAxis(const_cast<Tree<TS,BUD>&>(tree));
    list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
    if (ls.size()> 1){
      TS* ts= dynamic_cast<TS*>(*(ls.begin()));
      return 2.0*GetValue(*ts,LGAR);
    }
    else
      return 0.0;
  }
  else if (name == LGADbaseHw){
    Axis<TS,BUD>& axis = GetAxis(const_cast<Tree<TS,BUD>&>(tree));
    list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
    if (ls.size()> 1){
      TS* ts= dynamic_cast<TS*>(*(ls.begin()));
      return 2.0*GetValue(*ts,LGARh);
    }
    else
      return 0.0;
  }
  else if (name == LGADbh){
    Axis<TS,BUD>& axis = GetAxis(const_cast<Tree<TS,BUD>&>(tree));
    list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
    DiameterBreastHeight<TS,BUD> dbh;
    pair<double,double> d13(0.0,0.0);
    //traverse the axis in reverse order, the last segment having
    //dbh >= 1.3 will assign its diameter to Dbh.
    d13 = accumulate(ls.rbegin(),ls.rend(),d13,dbh);
    return d13.first;
  }
  else if (name == LGADbhHw){
    Axis<TS,BUD>& axis = GetAxis(const_cast<Tree<TS,BUD>&>(tree));
    list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(axis);
    DiameterBreastHeight<TS,BUD> dbh;
    pair<double,double> d13(0.0,0.0);
    //traverse the axis in reverse order, the last segment having
    //dbh >= 1.3 will assign its diameter to Dbh and Hw diam at BH
    d13 =  accumulate(ls.rbegin(),ls.rend(),d13,dbh);
    return d13.second;
  }
  else
    cout << "Tree GetValue unknown parameter: " << name << endl;
  return 0.0;
}





} //close namespace Lignum

#endif //TREEI_H



#ifdef TREE
#include <stdlib.h>
#include <iostream>

int main()
{
  cout << "OK" << endl;
  exit(0);
}


#endif

