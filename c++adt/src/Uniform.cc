#include <Uniform.h>

namespace cxxadt{

#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

//return uniformally distributed random number [0.0,1.0]
//reinitialize the sequence with any negative integer as 'idum'
double Uniform::uran( int* idum)
{
	long mj,mk;
	int i,ii,k;

	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG;
	ma[inext]=mj;
	return mj*FAC;
}

#undef MBIG
#undef MSEED
#undef MZ
#undef FAC

}//close namespace cxxadt

#ifdef UNIFORM
#include <iostream>
#include <vector>
#include <numeric>
using namespace cxxadt;
using namespace std;
int main(int argc, char* argv[])
{
  Uniform u;

  if (argc != 4){
    cout << "Usage: uniform init seed sequence_length"  << endl;
    return -1;
  }

  //initializing with different 'initialize', negative though,  will  
  //produce different sequences.  The 'seed' in u(seed) is optional.
  int initialize = atoi(argv[argc-3]);
  int seed = atoi(argv[argc-2]);
  int n = atoi(argv[argc-1]);

  vector<double> v(n);

  u.init(initialize);

  for (int i = 0; i < n; i++){
    v[i] = u(seed);
    cout << v[i] << endl;
  }

  cout << "Mean: " << accumulate(v.begin(),v.end(),0.0)/n << endl;

  return 0;
}

#endif
