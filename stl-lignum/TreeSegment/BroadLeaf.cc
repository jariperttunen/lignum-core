#include <BroadLeaf.h>

namespace Lignum{

Petiole::Petiole(const Point<>& b, const Point<>& e)
  :begin(b),end(e)
{
}

Point<> GetStartPoint(const Petiole& p)
{
  return p.begin;
}

Point<> GetEndPoint(const Petiole& p)
{
  return p.end;
}

void SetStartPoint(Petiole& p, const Point<>& pnt)
{
  p.begin = pnt;
}
  
void SetEndPoint(Petiole& p, const Point<>& pnt)
{
  p.end = pnt;
}


PositionVector GetDirection(const Petiole& p)
{
  Point<> dp = p.end - p.begin;
  PositionVector d(dp.getX(),dp.getY(),dp.getZ()); //construct the vector
  d.normalize(); //normalize it

  return d;
}

BroadLeaf::BroadLeaf(LGMdouble sf,LGMdouble tauL,LGMdouble dof,int number_of_sectors,
		     const Petiole& petiole,const PositionVector& leaf_normal,const Ellipsis& shape)
  :bla(sf,tauL,dof,petiole,leaf_normal,shape,number_of_sectors)
{

  //calculate and set the center of the leaf ellipse
  Point<> petiol_proj;    //projection of petiole on leaf ellipse
  Point<> petiol;         //Petiole as a vector (Point<>!)
  petiol = GetEndPoint(petiole) - GetStartPoint(petiole);
  vector<double> v = leaf_normal.getVector();
  Point<> lnp(v[0],v[1],v[2]);
  petiol_proj = petiol - Dot(leaf_normal,PositionVector(petiol)) * lnp;
  double b = (double)shape.getSemiminorAxis();
  double ppl = sqrt((double)Dot(PositionVector(petiol_proj), PositionVector(petiol_proj)));

  if(ppl < 1.0e-10)
    bla.center = GetEndPoint(petiole);  // If petiole perpendicular to leaf ellipse
  // center = end of petiole (this is a bit arbitrary)
  else
    bla.center = GetEndPoint(petiole) + (b/ppl) * petiol_proj;
}


BroadLeafAttributes::BroadLeafAttributes(double sf1, double tauL1, 
					 double dof1, const Petiole& petiole1,
					 const PositionVector& leaf_normal1, 
					 const Ellipsis& shape1,
					 int number_of_sectors)
  :sf(sf1),tauL(tauL1),degree_of_filling(dof1),P(0.0),M(0.0),Qabs(0.0),Qin(0.0),
   petiole(petiole1),leaf_normal(leaf_normal1),shape(shape1),sv(number_of_sectors)
{
  leaf_normal.normalize();
}

LGMdouble GetValue(const BroadLeaf& bl, const LGMAD name)
{

  if (name == A)
    return  bl.bla.degree_of_filling*bl.bla.shape.getArea(); //true area of the leaf

  else if (name == dof)
    return  bl.bla.degree_of_filling;

  else if (name == sf)
    return bl.bla.sf;

  else if (name == tauL)
    return bl.bla.tauL;
  
  else if (name == P)
    return bl.bla.P;

  else if (name == LM)
    return  bl.bla.M;
  
  else if (name == Qabs)
    return  bl.bla.Qabs;
  
  else if (name == Qin)
    return  bl.bla.Qin;

  else if (name == Wf)
    return  bl.bla.degree_of_filling*GetValue(bl,A)/bl.bla.sf;
  else
    cout << "BroadLeaf unknown attribute: " << name << " returning 0.0" << endl;
 
  return 0.0;
}


LGMdouble SetValue(BroadLeaf& bl, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value= GetValue(bl,name);

  if (name == A)
    bl.bla.shape.setArea(value/bl.bla.degree_of_filling);  //value=true area of the leaf

  else if (name == dof)
    bl.bla.degree_of_filling = value;

  else if (name == sf)
    bl.bla.sf = value;

  else if (name == tauL)
    bl.bla.tauL = value;
  
  else if (name == P)
    bl.bla.P = value;

  else if (name == LM)
    bl.bla.M = value;
  
  else if (name == Qabs)
    bl.bla.Qabs = value;
  
  else if (name == Qin)
    bl.bla.Qin = value;

  if (name == Wf)
    bl.bla.shape.setArea(bl.bla.sf*value/bl.bla.degree_of_filling);
                  //sf * Wf specifies the true area of the leaf

  else 
    cout << "Unknown attribute: " << name << "returning: "  << old_value << endl;
 
  return old_value;
}

Point<> GetCenterPoint(const BroadLeaf& bl)
{
  return bl.bla.center;
}

PositionVector GetLeafNormal(const BroadLeaf& bl)
{
  return bl.bla.leaf_normal;
}

PositionVector SetLeafNormal(BroadLeaf& bl, const PositionVector& n)
{
  PositionVector vv = bl.bla.leaf_normal;
  bl.bla.leaf_normal = n;
  //normalize the normal to unit vector. 
  bl.bla.leaf_normal.normalize();

  return vv;
}


Petiole& GetPetiole(BroadLeaf& bl)
{
  return bl.bla.petiole;
}

Ellipsis& GetEllipsis(BroadLeaf& bl)
{
  return bl.bla.shape;
}

void SetCenterPoint(BroadLeaf& bl, const Point<>& p)
{
  bl.bla.center = p;
}

void SetRadiationVector(BroadLeaf& bl, const vector<LGMdouble>& v)
{
  for(int i = 0; i < bl.bla.sv.size(); i++)
    bl.bla.sv[i] = v[i];
}
     
vector<double> GetRadiationVector(BroadLeaf& bl)
{
  return bl.bla.sv;
}

//Translates BroadLeaf as specified by vector t, orientation not changed
//(= vector t added to all positions, including Petiole)
void TranslateLeaf(BroadLeaf& bl, const PositionVector& t)
{

  const Point<LGMdouble> t_point = (Point<LGMdouble>)t;
  Point<LGMdouble> pnt = GetCenterPoint(bl);

  SetCenterPoint(bl, pnt + t_point);

  pnt = GetStartPoint(bl.bla.petiole);
  SetStartPoint(bl.bla.petiole, pnt + t_point);

  pnt = GetEndPoint(bl.bla.petiole);
  SetEndPoint(bl.bla.petiole, pnt + t_point);
  
}

//Moves leaf from its current position to position where
//the starting point of the petiole is p.
//Orientation does not change
void SetLeafPosition(BroadLeaf& bl, const Point<>& p)
{
  PositionVector transvct = PositionVector(p - GetStartPoint(bl.bla.petiole));

  TranslateLeaf(bl, transvct);
}

}//closing namespace Lignum


