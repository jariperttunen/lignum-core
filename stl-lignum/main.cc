#include <stdlib.h>
#include <iostream.h>
#include <list>
#include <MyTreeSegment.h>
#include <TreeFunctor.h>
#include <algorithm>
#include <list>

using namespace std;

CString ParseCommandLine(int argc, char *argv[],const CString& flag)
{
  int i = 1;
  CString clarg;

  //loop through command line options, argc - 1 checks possible missing last argument
  //to command line option does not cause core dump
  while (i < argc - 1){ 
    if (CString(argv[i]) == flag){
      clarg = argv[++i]; //pick the argument to command line option
      break; 
    }
    else
      i++;   //jump to next 
    i++;     //command line option
  }
  return clarg;
}

MyTreeSegment::MyTreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
			     const METER l, const METER r, const METER rn, 
			     Tree<MyTreeSegment>* t)
  :TreeSegment<MyTreeSegment>(p,d,go,l,r,rn,t)
{
  cout << "Hello from MyTreeSegment!!!" <<endl;
}

int main(int argc, char *argv[])
{
  Tree<MyTreeSegment> tree(Point<METER>(0,0,0),PositionVector(0,0,1.0));
  CString clarg,empty;

  clarg = ParseCommandLine(argc,argv,"-file");
  if (clarg != empty)
    InitializeTree(tree,clarg);

  //create a tree with a structure [TS,[[B],[B]],B]
  //i.e, [TS,BP,B] which expands to [TS,[A,A],B] and to [TS,[[B],[B]],B]
  //A= Axis, BP = BranchingPoint, TS = TreeSegment and B = Bud 
  Axis<MyTreeSegment>* axis2 = new Axis<MyTreeSegment>();
  Axis<MyTreeSegment>* axis3 = new Axis<MyTreeSegment>();
  Axis<MyTreeSegment>& axis = GetAxis(tree);
  //create the first tree segment
  TreeSegment<MyTreeSegment> *ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&tree);
  //create the branching point
  BranchingPoint<MyTreeSegment> *bp = 
    new BranchingPoint<MyTreeSegment>(Point<METER>(0,0,0),
				      PositionVector(0,0,1.0),&tree);
  //create the terminating bud
  Bud<MyTreeSegment> *bud = new  Bud<MyTreeSegment>(Point<METER>(0,0,0),
						    PositionVector(0,0,1.0),
						    0,
						    &tree);
  //create a branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyTreeSegment>(Point<METER>(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &tree));
  //create another branch with one bud (Axis containing one Bud) into the branching point
  InsertTerminatingBud(*bp,new Bud<MyTreeSegment>(Point<METER>(0,0,0),
						  PositionVector(0,0,1.0),
						  0,
						  &tree));


  //The tree will now look as  [TS,[[B],[B]],B]

  InsertAxis(*bp, axis2);
  InsertAxis(*bp, axis3);



  InsertTreeCompartment(axis,ts);
  InsertTreeCompartment(axis,bp);
  InsertTreeCompartment(axis,bud);
  
  ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&tree);

  InsertTreeCompartment(*axis2, ts);
  InsertTreeCompartment(*axis2,bud);


 ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&tree);

  InsertTreeCompartment(*axis3, ts);

 ts = 
    new TreeSegment<MyTreeSegment>(Point<METER>(0,0,0),PositionVector(0,0,1.0),
				   0,1,0.5,0.2,&tree);

  InsertTreeCompartment(*axis3, ts);

  //traverse the tree and print out  the datatypes of tree compartments
  //see class DisplayType in TreeFunctor.h and in TreeFunctor.cc
  axis = GetAxis(tree);

  list<TreeCompartment<MyTreeSegment>*>& ls = GetTreeCompartmentList(axis);


  list<TreeCompartment<MyTreeSegment>*>::iterator I = ls.begin();
  while(I != ls.end())
    {
      if (TreeSegment<MyTreeSegment>* myts = dynamic_cast<TreeSegment<MyTreeSegment>*>(*I))
      	cout << "tree segment" << endl;
      if (BranchingPoint<MyTreeSegment>* mybp = dynamic_cast<BranchingPoint<MyTreeSegment>*>(*I))
      	cout << "branching point" << endl;
      I++;

    }

  for_each(ls.begin(),ls.end(),DisplayType<MyTreeSegment>());
  //  for_each(ls.begin(),ls.end(),DisplayType<MyTreeSegment>());
  tree.makeConnectionMatrix();
}






