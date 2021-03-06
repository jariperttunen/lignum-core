#ifndef FIRMAMENT_WITH_MASK
#define FIRMAMENT_WITH_MASK

#include <list>
using namespace std;
#include <Firmament.h>
#include <string>
#include <sstream>
#include <Lex.h>
#include <vector>
#include<iterator>
#include<algorithm> 

using namespace cxxadt;
namespace sky{

  class FindNextMask{
  public:
      FindNextMask() {};

    FindNextMask(int i):iter(i){}
    bool operator()(const pair<int,string>& p)const{
      if (iter <= p.first)
	return true;
      else
	return false;

    }
  private:
    int iter;
  };

//!FirmamentWithMask models a gap in a forest.
//!The gaps are often analyzed by foresters
//!by taking photograhs  with fish-eye lenses.
//!The size and the form of the gap is further
//!analyzed by marking the path of the sun 
//!in the photograph and the effect of the direct and 
//!diffuse radiation can be estimated (somehow).
//!The idea of this class is simply to mimic such
//!fish-eye photograph and to model the effect
//!of the blocked incoming radiation, direct and diffuse.
//!Thus the name FirmamentWithMask.
//!Ideally the user could define the gap (i.e., the photograph)
//!in a file, though in a somewhat simplified manner.    
//!Methods:
//!1. readMaskFile
//!   Read the mask file and adjust radiation
//!2.  setMask
//!   This naive approach: in a file for each inclination 
//!   the percentage of remaining radiation is given
//!   100% means gap, less than 100% means obstacle.
class FirmamentWithMask:public Firmament{
public: 
  FirmamentWithMask(int no_incl = NUM_OF_INCL/*9*/, int no_azim = NUM_OF_AZIM /*24*/,double rad_plane=1200.0);
  void resize(int no_incl,int no_azim, double rad);
  void configure(const string& file);
  void configure(int iter, bool verbose = false);
  void readAllMasks(const string& file);
  void readMaskFile(const string& file);
  void readAzimuthInclinationMaskFile(const string& file);
  void getMask(int incl_index,double percentage){return  setMask(incl_index, percentage);}
  void getreadMask(Lex& file){ return readMask(file);}
  LGMdouble getBallChange() {return  ballChange; }
  LGMdouble getPlaneChange() {return  planeChange; }
  LGMdouble getDrp_orig() {return  drp_orig; }
   std::vector<std::pair<int,std::string> > getResultVector() const{
   std::vector<std::pair<int, std::string> > result( gap_ls.begin(), gap_ls.end() );
   return result;
   }
protected:
  void readMask(Lex& file);
  void setMask(int incl_index,double percentage);
  void setRegionMask(int region,double mask_percentage);
 private:
  LGMdouble ballChange;    //Change to diffuseRadBall caused by SetMask
  LGMdouble planeChange;   //Change to diffuseRadPlane  caused by SetMask
  LGMdouble drp_orig; //The original plane sensor radiation of the sky 
  list<pair<int,string> > gap_ls; //List of gap files 
  vector<pair<int,string> > result;

};

}//closing namespace sky
#endif
