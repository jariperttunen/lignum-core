#ifndef VOXELSPACE_H
#define VOXELSPACE_H


#include <vector>
#include <Tree.h>
#include <TMatrix3D.h>
#include <VoxelBox.h>
#include <Firmament.h>

#include <ScotsBud.h>
#include <ScotsPineVisual.h>


namespace Lignum {


class VoxelBox;

struct VoxelMovement
{
	int x;
	int y;
	int z;
	LGMdouble l;
};


class VoxelSpace
{
public:
	LGMdouble Xbox, Ybox, Zbox;
	VoxelSpace();
	VoxelSpace(Point corner1, Point corner2, int xn, int yn, int zn, Firmament &f);
	int GetNumBoxes() { return Xn*Yn*Zn; }
	int getNumTreeSegments();

	VoxelBox& getVoxelBox(Point p);
	LGMdouble calculateLight(ostream& os);

	std::vector<VoxelMovement>& getRoute(std::vector<VoxelMovement> &vec, int startx, int starty, int startz, PositionVector dir);

	void fillVoxelBoxes(LGMdouble inivalue);

	
	void AddScotspine(Tree<ScotsPineVisual, ScotsBud> &tree);

	template <class TS,class BUD>
	friend void dumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts);

	template <class TS,class BUD>
	friend void dumpCfTree(VoxelSpace &s, Tree<TS, BUD> &ts);

	template <class TS,class BUD>
	friend void setCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree);
	
	BoundingBox& searchDimensions(BoundingBox &bbox, bool boolDimensionsWithNumBoxes);

	void searchDimensions(bool boolDimensionsWithNumBoxes=true) { searchDimensions(bbox, boolDimensionsWithNumBoxes); };

	void dumpTrees();

	void setLightValues();

	void setLight();

	void draw();

	Point getLocalPoint(Point p); //Funktio palauttaa globaalissa koordinaatistossa olevan pisteen VoxelSpacen koordinaatistossa
	
	void writeVoxBoxesToFile(CString filename);
	void writeVoxBoxesToFile(ofstream &file);

	int getNumVoxBoxes();
	int Xn, Yn, Zn;
private:

	vector<Tree<ScotsPineVisual,ScotsBud> *> vecScotspines;

	TMatrix3D<VoxelBox> voxboxes;
	BoundingBox bbox;

	Point corner1;  //origo
	Point corner2;
	
	LGMdouble Xspan, Yspan, Zspan;

	

	
	int getXindex(LGMdouble xcoord);
	int getYindex(LGMdouble ycoord);
	int getZindex(LGMdouble zcoord);

	Firmament* sky;

	
public:

	// returns the total foliage mass of the tree segments dumped into the VoxelSpace
	LGMdouble getFoliageMass(void);
	
};


template <class TS,class BUD>
class DumpCfTreeFunctor
{
public:
  TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
  mutable VoxelSpace *space;
};


template <class TS,class BUD>
class SetQabsCfTreeFunctor
{
public:
  TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
  mutable VoxelSpace *space;
};





} // namespace Lignum

#include "VoxelSpaceI.h"

#endif

