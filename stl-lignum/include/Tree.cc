#include <Tree.h>



TreeParameters::TreeParameters()
{
  af = ar = lr = mf = 0.0;
  mr = ms = na = nl = pr = q = sr = ss = rho = xi = 0.0;
}

TreeAttributes::TreeAttributes()
{
  age = 0; lb = 0.0;
  P = M = Wr = 0.0;
}

TreeTransitVariables::TreeTransitVariables()
  :lambda(0.0),g(9.81),eta(1.0),k(1.0),rhow(1000.0)
{
}


template <class TS>
Tree<TS>::Tree()
{
  tree = NULL;
}

//Construct a tree at a certain position to a certain direction
//with one terminating bud in the main axis
template <class TS>
Tree<TS>::Tree(const Point<METER>& p, const PositionVector& d)
  :TreeCompartment<TS>(p,d,this),axis(p,d,this)
{
}




template <class TS>
TreeSegment<TS>* Tree<TS>::GetTreeSegment(Axis<TS> &ax, TreeSegment<TS> *ts)
{
  list<TreeCompartment<TS>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<TS>*>::iterator I = ls.begin();
  
  while(I != ls.end())
    {
      if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(*I))
	{
	  if (myts == ts)
	    return myts;
	}
      if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(*I))
      	{	 
	  list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
	  list<Axis<TS>*>::iterator I = axis_ls.begin();
	  while(I != axis_ls.end())
	    {
	      Axis<TS> *axis = *I;
	      TreeSegment<TS> *t = GetTreeSegment(*axis, ts);
	      if (t != NULL)
		return t;
	      I++;	    
	    }
	}      
      I++;
    }
  return NULL;
}


template <class TS>
void Tree<TS>::UpdateWaterFlow(TP time_step)
{
  //<<<<<<< Tree.cc
  
  if (cm == NULL)
    cm = new ConnectionMatrix<TS>(axis);
  cm->print();
  
  // This counts the flow in for every segment
  for (int i=0; i<cm->getSize(); i++){
    TreeSegment<TS> *out;
    if(cm->getTreeSegment(i) != NULL)  
      out = GetTreeSegment(this->axis, cm->getTreeSegment(i));
    
    for (int a=0; a<cm->getSize(); a++){
      if (i != a && cm->getTreeSegment(i, a) != 0){
	TreeSegment<TS> *in = GetTreeSegment(this->axis, cm->getTreeSegment(i,a));
	//cout << "In " << a << " Out " << i << "  ";
	SetTSAttributeValue(*in, fin, CountFlow(*in, *out));
      }
      SetTSAttributeValue(*out, fout, 0);  // 
    }	
  }
  
  // This counts the flow out for every segment
  for (i=0; i<cm->getSize(); i++){
    TreeSegment<TS> *out;
    if(cm->getTreeSegment(i) != 0)  
      out = GetTreeSegment(this->axis, cm->getTreeSegment(i));
    for (int a=0; a<cm->getSize(); a++){
      if (i != a && cm->getTreeSegment(i,a) != 0){
	TreeSegment<TS> *in = GetTreeSegment(this->axis, cm->getTreeSegment(i,a));
	SetTSAttributeValue(*out, fout, GetTSAttributeValue(*out, fout)+GetTSAttributeValue(*in, fin));
      }
    }
    TP new_pressure = GetTSAttributeValue(*out, Pr) - time_step * 
      ( GetTSAttributeValue(*out, fin) - GetTSAttributeValue(*out, fout) - 
	out->GetTranspiration(0.0));  
   
    //cout << GetTSAttributeValue(*out, fin) << " "<<GetTSAttributeValue(*out, fout) <<" uusi paine " << new_pressure << "  " <<time_step * 
    //( GetTSAttributeValue(*out, fin) - GetTSAttributeValue(*out, fout) - 
    //	out->GetTranspiration(0.0)) << endl << endl;
    
    //cout << i << ";  sis " <<  GetTSAttributeValue(*out, fin) << " ; ulos " << GetTSAttributeValue(*out, fout);
    //  cout << " ; Paine " << GetTSAttributeValue(*out, Pr);

    //cout << "uusi paine " << new_pressure << endl;
    SetTSAttributeValue(*out, Pr, new_pressure); 

    //cout << "; PaineUusi " << GetTSAttributeValue(*out, Pr) << endl;
    SetTSAttributeValue(*out, Wm, GetTSAttributeValue(*out, Wm) + GetTSAttributeValue(*out, fin)-  GetTSAttributeValue(*out, fout)); 
  }
  cout << endl << endl << endl; 
 
}


// This method counts the flow from the TreeSegment below (out) to the TreeSegment above.
template <class TS>
TP Tree<TS>::CountFlow(TreeSegment<TS> &in, TreeSegment<TS> &out)
{
  TP gravity = 9.81;
  TP viscosity = 1;
  TP permiability = 1;
  TP density = 1000;

  TP ar = GetTSAttributeValue(out, area);
  TP le = GetTSAttributeValue(out, L);
  TP he = GetTSAttributeValue(out, H);
  TP pr_out = GetTSAttributeValue(out, Pr);  // Pressure in the element above
  TP pr_in = GetTSAttributeValue(in, Pr);    // Pressure in the element below
 


  return (ttp.k / ttp.eta) * (ar / le) * (pr_in - pr_out); // - ttp.rhow * ttp.g*he);
  
}


//<<<<<<< Tree.cc
//=======
/*

//This method builds the connection matrix, where the structure of the tree
//is stored. 
template <class TS>
void Tree<TS>::BuiltConnectionMatrix()
{  
  TreeSegment<MyTreeSegment> *lastSegment = NULL;
  list<TreeCompartment<MyTreeSegment>*>& ls = GetTreeCompartmentList(axis);
  list<TreeCompartment<MyTreeSegment>*>::iterator I = ls.begin();
  cm = new ConnectionMatrix<MyTreeSegment>(CountTreeSegments(this->axis));

  while(I != ls.end()){      
    if (TreeSegment<MyTreeSegment>* myts = dynamic_cast<TreeSegment<MyTreeSegment>*>(*I)){	
      cm->AddConnection(lastSegment, myts);
      lastSegment = myts;
    }      
    if (BranchingPoint<MyTreeSegment>* mybp = dynamic_cast<BranchingPoint<MyTreeSegment>*>(*I)){
      list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
      list<Axis<TS>*>::iterator I = axis_ls.begin();
      while(I != axis_ls.end()){	      
	Axis<MyTreeSegment> *axis = *I;
	if (lastSegment)
	  makeAxis(*axis, *lastSegment);
	I++;
      }  
    }  
    I++;
  }
}
*/

//>>>>>>> 1.12





//The initialization of the tree.
//Install parameters and functions.
//TreeMetaFileParser  parsers the 'meta_file'
//and after that the file names for the parameters and functions 
//are known. 
//Parameters: Then the lexer 'lex' can tokenize the parameter files
//to a list of: [name,value,name,value,...,name,value,ENDFILE]
//Then install the parameters.
//Functions: Functions are represented as parametric curves
//that are given as (x,y) pairs in an ASCII file
//ParametricCurve can read and create internal representation
//for a parametric curve and evaluate it in any point.
template <class TS>
void InitializeTree(Tree<TS>& tree, const CString& meta_file)
{
  TP p;
  CString file;
  Lex lex;
  Token name,value;
  TreeMetaFileParser tmfp(meta_file);
  MapTPD maptpd;

  tmfp.parse();

  file = tmfp.getParameterFile("Tree");
  cout << "Reading parameters for tree from: " << file << endl;
  lex.scan(file);

  name = lex.getToken();
  while (name.getType() != ENDFILE){
    value = lex.getToken(); 
    p = (TP) atof((const char *)value.getValue());
    cout << " Parameter: " << name.getValue() << " = " << p << endl;
    if (name.getValue() == CString("lambda"))
      SetTreeTransitVariableValue(tree,lambda,p);
    else{
      CString str = name.getValue();
      map<const char*,TPD,cmpstr>::iterator tpd = maptpd.tpd.find(str);
      SetTreeParameterValue(tree,(*tpd).second,p);
    }
    name = lex.getToken();
  }

  file = tmfp.getFunctionFile(CString("Buds"));
  cout << "Reading function for number of new buds from: " << file << endl;
  tree.tf.nb.install(file);

  file = tmfp.getFunctionFile(CString("DoI"));
  cout << "Reading function for DoI from: " << file << endl;
  tree.tf.ip.install(file);

  file = tmfp.getFunctionFile(CString("FoliageMortality"));
  cout << "Reading function for foliage mortality from: " << file << endl;
  tree.tf.fm.install(file);

}

//Get a parameter value 
template <class TS>
TP GetTreeParameterValue(const Tree<TS>& tree, const TPD name)
{
  if (name == af)
    return tree.tp.af;


  else if (name == ar)
     return tree.tp.ar;

  else if (name == fin)
    return tree.tp.ar;
  
  else if (name == fout)
    return tree.tp.ar;

  else if (name == lr)
    return tree.tp.lr;

  else if (name == mf)
    return tree.tp.mf;

  else if (name == mr)
    return tree.tp.mr;

  else if (name == ms)
    return tree.tp.ms;

  else if (name == na)
    return tree.tp.na;

  else if (name == nl)
    return tree.tp.nl;

  else if (name == pr)
    return tree.tp.pr;

  else if (name == q)
    return tree.tp.q;

  else if (name == sr)
    return tree.tp.sr;

  else if (name == ss)
    return tree.tp.ss;

  else if (name == rho)
    return tree.tp.rho;

  else if (name == xi)
     return tree.tp.xi;

  else{
    cerr << "GetParameterValue() uknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return 0.0;
}

//Change a parameter value, return the old value
template <class TS>
TP SetTreeParameterValue(Tree<TS>& tree, const TPD name, const TP value)
{
  TP old_value = GetTreeParameterValue(tree,name);

  if (name == af)
    tree.tp.af = value;

  else if (name == ar)
    tree.tp.ar = value;

  else if (name == lr)
    tree.tp.lr = value;

  else if (name == mf)
    tree.tp.mf = value;

  else if (name == mr)
    tree.tp.mr = value;

  else if (name == ms)
    tree.tp.ms = value;

  else if (name == na)
    tree.tp.na = value;

  else if (name == nl)
    tree.tp.nl = value;

  else if (name == pr)
    tree.tp.pr = value;

  else if (name == q)
    tree.tp.q = value;

  else if (name == sr)
    tree.tp.sr = value;

  else if (name == ss)
    tree.tp.ss = value;

  else if (name == rho)
    tree.tp.rho = value;

  else if (name == xi)
    tree.tp.rho = value;

  else{
    cerr << "SetParameterValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return old_value;
}

template <class TS>
TP GetTreeTransitVariableValue(const Tree<TS>& tree, const TTD name)
{
  if (name == lambda)
    return tree.ttp.lambda;
  
  else{
    cerr << "GetTransitVariableValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS>
TP SetTreeTransitVariableValue(Tree<TS>& tree, const TTD name, const TP value)
{
  TP old_value = GetTreeTransitVariableValue(tree,name);
  
  if (name == lambda)
    tree.ttp.lambda = value;
  else{
    cerr << "SetTransitVariableValue unknown parameter: " << name << " returning "
	 << old_value << endl;
  }
  return old_value;
}

template <class TS>
TP GetTreeAttributeValue(const Tree<TS>& tree, const TAD name)
{ 
  
  if (name == lb)
    return tree.ta.lb;

  else if (name == P)
     return tree.ta.P;

  else if (name == M)
     return tree.ta.M;

  else if (name == Wr)
     return tree.ta.Wr;

  else {
    cerr << "GetAttributeValue  unknown attribute: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS>
YEAR GetTreeAttributeValue(const Tree<TS>& tree, const TAI name)
{
  if (name == age)
    return  tree.ta.age;
  else{
     cerr << "GetAttributeValue unknown attribute: " << name << " returning 0.0"
	  << endl;
  }

  return 0;
}

template <class TS,class T1,class T2>
T2 SetTreeAttributeValue(Tree<TS>& tree, const T1 name, const T2 value)
{
  TP old_value = GetAttributeValue(tree,name);

  if (name == lb)
    tree.ta.lb = value;

  else if (name == P)
    tree.ta.P = value;

  else if (name == M)
     tree.ta.M = value;
 
  else if (name == Wr)
    tree.ta.Wr = value;

  else{
    cerr << "SetAttributeValue unknown attribute: " << name << " returning " 
	 << old_value << endl;
  }

  return old_value;
}
  
template <class TS>
YEAR SetTreeAttributeValue(Tree<TS>& tree, const TAI name, const YEAR value)
{
  YEAR old_value = GetTreeAttributeValue(tree,name);

  if (name == age)
    tree.ta.age = value;
  else{
    cerr << "SetAttributeValue unknown attribute: " << name << " returning " 
	 << old_value << endl;
  }

  return old_value;
}

#ifdef TREE
#include <stdlib.h>
#include <iostream.h>

int main()
{
  cout << "OK" << endl;
  exit(0);
}

#endif
