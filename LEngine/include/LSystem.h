/*********************************************************************
 *The  class  LSystem provides  programming  interface  to L-system  *
 *rewriting of  the language L that lsystem.h  implements.  Note that*
 *neither lsystem.h nor this  file LSystem.h are wrapped with #infdef*
 *... #define ... #endif directives to prevent multiple inclusions of*
 *the header files. This is because both LSystem.h and lsystem.h must*
 *be  included several  times, once  for each  species of  the model.*
 *Multiple  decalarations and  definitions are  prevented by wrapping*
 *LSystem.h and lsystem.h in namespaces.                             *
 *********************************************************************/
#include <lsystem.h>


ProdCaller  ContextMatch(const LstringIterator& pos,CallerData& caller_data,int& prod);

//The succstrg, the temporary  expanded string or 'storage', is common
//within a species, but it is cleared after each derivation so it does
//not prevent multiple individuals of  the species to be modelled.  It
//only makes the program strictly sequential.
SuccessorStorage succstrg;

void _Add(const void* pX, int size)
{
  succstrg.Add(pX, size);
}

template <class TS, class BUD, class N = LGMAD, class F=LGMdouble>
class LSystem{
 public:
 void start();
 void derive();
 int derivationLength();
 void end();
 int lignumToLstring(Tree<TS,BUD>& t,int argnum = 0,...);
 int lstringToLignum(Tree<TS,BUD>& t,int argnum = 0,...);
 protected:
 int lignum2Lstring(Tree<TS,BUD>& t, vector<N>& vav);
 int lignum2Lstring(list<Axis<TS,BUD>*>& ls, 
		    typename list<Axis<TS,BUD>*>::iterator current, 
		    LstringIterator& ltr, vector<N>& vav);
 int lignum2Lstring(list<TreeCompartment<TS,BUD>*>& ls,
		    typename list<TreeCompartment<TS,BUD>*>::iterator current,
		    LstringIterator& ltr, vector<N>& vav);
 int lstring2Lignum(Tree<TS,BUD>& t, vector<N>& vav);
 int lstring2Lignum(list<TreeCompartment<TS,BUD>*>& ls,
		    typename list<TreeCompartment<TS,BUD>*>::iterator current,
		    Tree<TS,BUD>& tree,
		    LstringIterator& ltr,
		       stack<Turtle>& turtle_stack,vector<N>& vav);
 int lstring2Lignum(list<Axis<TS,BUD>*>& ls, 
		    typename list<Axis<TS,BUD>*>::iterator current, 
		    Tree<TS,BUD>& tree, LstringIterator& ltr, 
		    stack<Turtle>& turtle_stack, vector<N>& vav);	       
 private:
  Lstring mainstring;
  Lstring derivedstring;
};

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::start()
{
  Start();
  mainstring.Add(succstrg);
}

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::end()
{
  End();
}

template <class TS, class BUD, class N, class F>
inline int LSystem<TS,BUD,N,F>::derivationLength()
{
  return DerivationLength();
}

template <class TS, class BUD, class N, class F>
inline void LSystem<TS,BUD,N,F>::derive()
{
  StartEach();
  LstringIterator iterator(mainstring);
  derivedstring.Clear();

  while (!iterator.AtEnd())
  {
    CallerData cd;
    int i;
    //ProdCaller pCaller = FindMatch(iterator, cd);
    ProdCaller pCaller = ContextMatch(iterator, cd, i);
    if (NULL == pCaller)
    {
      iterator.AppendCurrent(succstrg);
      iterator++;
    }
    else
    {
      pCaller(&cd);
      iterator+=cd.Strct.Count();
    }
    derivedstring.Add(succstrg);
  }
  mainstring.Swap(derivedstring);
  EndEach();
}



#include <LSystemI.h>
