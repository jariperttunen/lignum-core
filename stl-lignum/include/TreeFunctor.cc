#include <TreeFunctor.h>
#include <iostream.h>

//Use built-in operator dynamic_cast
//to resolve the data_type of a tree compartment
template <class TS>
void DisplayType<TS>::operator ()(TreeCompartment<TS>*tc)
{
  if (Axis<TS>* myaxis =  dynamic_cast<Axis<TS>*>(tc)){
    cout << "Hello, I'm Axis" << endl;
    list<TreeCompartment<TS>*>& tc_ls = GetTreeCompartmentList(*myaxis);
    for_each(tc_ls.begin(),tc_ls.end(),DisplayType<MyTreeSegment>());
  }

  else if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    cout << "Hello, I'm BranchingPoint" << endl;
    list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);
    for_each(axis_ls.begin(),axis_ls.end(),DisplayType<MyTreeSegment>());
  }

  else if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    cout << "Hello, I'm TreeSegment" << endl;

  else if (Bud<TS>* mybud =  dynamic_cast<Bud<TS>*>(tc))
    cout << "Hello, I'm Bud" << endl;

  else
    cout << "Who am I???" << endl;
}

template <class TS>
TreeCompartment<TS>* DisplayType2<TS>::operator()(TreeCompartment<TS>* tc)const
{
  if (Axis<TS>* myaxis =  dynamic_cast<Axis<TS>*>(tc)){
    cout << "Hello, I'm Axis" << endl;
  }

  else if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    cout << "Hello, I'm BranchingPoint" << endl;
  }

  else if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    cout << "Hello, I'm TreeSegment" << endl;

  else if (Bud<TS>* mybud =  dynamic_cast<Bud<TS>*>(tc))
    cout << "Hello, I'm Bud" << endl;

  else
    cout << "Who am I???" << endl;

  return tc;
}

template <class TS>
int& CountTreeSegments<TS>::operator()(int& n,TreeCompartment<TS>* tc)const
{
  if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    n+=1;
  
  return n;
}



template <class TS>
int& CountCompartments<TS>::operator()(int& n,TreeCompartment<TS>* tc)const
{
  if (Axis<TS>* myaxis =  dynamic_cast<Axis<TS>*>(tc)){
    cout << "Hello, I'm Axis ";
  }

  else if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    cout << "Hello, I'm BranchingPoint ";
  }

  else if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    cout << "Hello, I'm TreeSegment ";

  else if (Bud<TS>* mybud =  dynamic_cast<Bud<TS>*>(tc))
    cout << "Hello, I'm Bud ";

  else
    cout << "Who am I??? ";
  //counting them all
  n+=1;
  cout << n << endl;
  return n;
}

template <class TS>
TreeCompartment<TS>* FillWithWater<TS>::operator()(TreeCompartment<TS>* tc)const
{
  if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    {
      cout << "Filling water.." << endl;
      SetTSAttributeValue(*myts, Wm, pow(GetTSAttributeValue(*myts, R), 2) * 
			  PI_VALUE * GetTSAttributeValue(*myts, L) * 0.5 *  
			  1000); // korjaaa...1000 GetTree(*myts).ttp.rhow                                                                               
    }
  return tc;
}

template <class TS>
int& CountCompartmentsReverse<TS>::operator()(int& n,
					      TreeCompartment<TS>* tc)const
{
  if (Axis<TS>* myaxis =  dynamic_cast<Axis<TS>*>(tc)){
    cout << "Hello, I'm Axis ";
  }

  else if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    cout << "Hello, I'm BranchingPoint ";
  }

  else if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    cout << "Hello, I'm TreeSegment ";

  else if (Bud<TS>* mybud =  dynamic_cast<Bud<TS>*>(tc))
    cout << "Hello, I'm Bud ";

  else
    cout << "Who am I??? ";

  //counting them all
  n+=1;
  cout << n << endl;
  return n;
}

template <class TS> TreeCompartment<TS>* 
MyExampleSignal<TS>::operator()(int& n,
			        TreeCompartment<TS>* tc)const
{
  if (Axis<TS>* myaxis =  dynamic_cast<Axis<TS>*>(tc)){
    cout << "Hello, I'm Axis ";
  }

  else if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    cout << "Hello, I'm BranchingPoint ";
  }

  else if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    cout << "Hello, I'm TreeSegment ";

  else if (Bud<TS>* mybud =  dynamic_cast<Bud<TS>*>(tc))
    cout << "Hello, I'm Bud ";

  else
    cout << "Who am I??? ";
 
  n+=1;
  cout << n << endl;
  return tc;
}







