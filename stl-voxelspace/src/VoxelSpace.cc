#include "stdafx.h"
#include "OpenGL.h"
#include <math.h>

#ifdef _MSC_VER
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <VoxelBox.h>
#include <VoxelSpace.h>
#include <Bernoulli.h>

#include <fstream>


extern float cam_x;  //camera position
extern float cam_y;
extern float cam_z;

namespace Lignum {



  // 
  //	Default constructor
  //
  VoxelSpace::VoxelSpace():voxboxes(10,10,10),Xn(10),Yn(10),Zn(10)
  {
     sky = NULL;
  }


  //
  // Constructor
  //
  // parametres
  //	corner1 : the corner from the VoxelSpace where x,y and z have their minimum values
  //  corner2 : opposite corner to corner1
  //	xn		: number of VoxBoxescd  in x direction
  //	yn		: number of VoxBoxes in y direction
  //  zn		: number of VoxBoxes in z direction
  //	f		: Firmament
  //
  VoxelSpace::VoxelSpace(Point c1, Point c2, int xn, int yn, int zn, Firmament &f)
    :corner1(c1),corner2(c2),voxboxes(xn,yn,zn),Xn(xn),Yn(yn),Zn(zn)
  {
    Xbox = (corner2-corner1).getX()/static_cast<int>(Xn);
    Ybox = (corner2-corner1).getY()/static_cast<int>(Yn);
    Zbox = (corner2-corner1).getZ()/static_cast<int>(Zn);
    
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox,(LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }
    sky = &f;
  }

  //Constructor: 
  //c1, c2: the corner points
  //xsize, ysize, zsize: voxel box size
  //xn, yn, zn: number of voxel boxes (size of the matrix)
  //f: the firmament
  VoxelSpace::VoxelSpace(Point c1, Point c2, 
			 double xsize, double ysize, double zsize,
			 int xn, int yn, int zn, 
			 Firmament &f)
    :corner1(c1),corner2(c2),Xbox(xsize),Ybox(ysize),Zbox(zsize),
     voxboxes(xn,yn,zn),Xn(xn),Yn(yn),Zn(zn)
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }
    sky = &f;
  }


 //Change number (=input) of VoxelBoxes in x, y, and z-directions. The whole
 //VoxelSpace, that is, the big box from corner1 to corner2 retains
 //its size => size of VoxelBox changes.

  void VoxelSpace::resize(int x, int y, int z) {
    if(x < 1) x = 1;
    if(y < 1) y = 1;
    if(z < 1) z = 1;
    voxboxes.resize(x, y, z);
    Xn = x, Yn = y, Zn = z;

    //Update now the size of VoxelBox
    Xbox = (LGMdouble)Xn*Xbox / (LGMdouble)Xn;
    Ybox = (LGMdouble)Yn*Ybox / (LGMdouble)Yn;
    Zbox = (LGMdouble)Zn*Zbox / (LGMdouble)Zn;

    //The coordinates (=lower left corners) of the VoxelBoxes have to
    //be set and also the Voxelspace
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }

  }

 //Change sizes of VoxelBoxes => number of VoxelBoxes in x, y, and
 //z-direction change, since the the big box from corner1 to corner2
 //retains (approximately) its size (slight change due to change of
 //voxelbox size; corner2 changes). 

  void VoxelSpace::resize(LGMdouble lX, LGMdouble lY, LGMdouble lZ) {
    if(lX < R_EPSILON) lX = 1.0;
    if(lY < R_EPSILON) lY = 1.0;
    if(lZ < R_EPSILON) lZ = 1.0;

    Xn = static_cast<int>((LGMdouble)Xn*Xbox / lX) + 1;
    Yn = static_cast<int>((LGMdouble)Yn*Ybox / lY) + 1;
    Zn = static_cast<int>((LGMdouble)Zn*Zbox / lZ) + 1;

    voxboxes.resize(Xn, Yn, Zn);

    Xbox = lX, Ybox = lY, Zbox = lZ;

    //Update also the other corner. Lover left corner1 = origo,
    //corner2 is the opposite corner.It may have changed slightly.
    corner2 = corner1 + Point((LGMdouble)Xn*Xbox, (LGMdouble)Yn*Ybox,
			      (LGMdouble)Zn*Zbox);


    //The coordinates (=lower left corners) of the VoxelBoxes have to
    //be set and also the Voxelspace
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }

  }


 //Change sizes & numbers of VoxelBoxes => the extent of VoxelSpace
 //changes (i.e. corner2)

    void VoxelSpace::resize(LGMdouble lX, LGMdouble lY, LGMdouble lZ,
			    int nX, int nY, int nZ )
    {
    if(nX < 1) nX = 1;
    if(nY < 1) nY = 1;
    if(nZ < 1) nZ = 1;
    if(lX < R_EPSILON) lX = 1.0;
    if(lY < R_EPSILON) lY = 1.0;
    if(lZ < R_EPSILON) lZ = 1.0;

    Xn = nX, Yn = nY, Zn = nZ;
    voxboxes.resize(Xn, Yn, Zn);

    Xbox = lX, Ybox = lY, Zbox = lZ;

    //Update the other corner. Lover left corner1 = origo,
    //corner2 is the opposite corner.It may have changed slightly.

    corner2 = corner1 + Point((LGMdouble)Xn*Xbox, (LGMdouble)Yn*Ybox,
			      (LGMdouble)Zn*Zbox);

 
   //The coordinates (=lower left corners) of the VoxelBoxes have to
    //be set and also the Voxelspace
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }

    }

  //Move Voxelspace so that its lower left corner is set at corner

  void VoxelSpace::move(const Point corner)
  {
    corner1 = corner;
    
    //Update also the other corner
    corner2 = corner1 + Point((LGMdouble)Xn*Xbox, (LGMdouble)Yn*Ybox,
			      (LGMdouble)Zn*Zbox);
    
    
    //Set also the coordinates (=lower left corners) of the VoxelBoxes
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point c = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, c); 
	  }
    
  }


  // 
  // Converts a global point to local point of the VoxelSpace
  //
  // parametres:
  //	p : global point
  //	return : local point
  //
  Point VoxelSpace::getLocalPoint(const Point& p)const
  {
    return p - corner1;
  }




  //
  // Returns indicates the x-index of the VoxBox including
  // then x-coordinate given as parameter
  //
  int VoxelSpace::getXindex(LGMdouble local_xcoord)
  {
    return (int)(local_xcoord/Xbox);
  }


  //
  // Returns indicates the y-index of the VoxBox including
  // then y-coordinate given as parameter
  //
  int VoxelSpace::getYindex(LGMdouble local_ycoord)
  {
    return (int)(local_ycoord/Ybox);
  }


  //
  // Returns indicates the z-index of the VoxBox including
  // then z-coordinate given as parameter
  //
  int VoxelSpace::getZindex(LGMdouble local_zcoord)
  {
    return (int)(local_zcoord/Zbox);
  }



  //
  // The Function calculates the root from start point to the direction given as parameter.
  // The route is stored to a vector
  //
  // Parametres:
  // vec	:	the vector where the route is stored
  // startx : the x-index of the starting VoxelBox
  // starty : the y-index of the starting VoxelBox
  // startz : the z-index of the starting VoxelBox
  // dir	  : direction
  // returns : the route stored in a vector
  //
  std::vector<VoxelMovement>& VoxelSpace::getRoute(std::vector<VoxelMovement> &vec, int startx, 
						   int starty, int startz, PositionVector dir)const
  {
    dir.normalize();	

    int x_jump = +1;
    int y_jump = +1;
    int z_jump = +1;
	

    if (dir.getX()<0)
      x_jump = -1;
    if (dir.getY()<0)
      y_jump = -1;
    if (dir.getZ()<0)
      z_jump = -1;

    LGMdouble xmove=9999;
    LGMdouble ymove=9999;
    LGMdouble zmove=9999;

    if (dir.getX() != 0);
    xmove = fabs(Xbox / dir.getX());

    if (dir.getY() != 0);
    ymove = fabs(Ybox / dir.getY());
	
    if (dir.getZ() != 0)
      zmove = fabs(Zbox / dir.getZ());

    LGMdouble next_x = xmove / 2;
    LGMdouble next_y = ymove / 2;
    LGMdouble next_z = zmove / 2;

    LGMdouble dist = 0;


    while(startx>=0 && starty>=0 && startz>=0 && startx<Xn &&
	  starty<Yn && startz<Zn)
      {
	VoxelMovement vm;

	if (next_x <= next_y && next_x<= next_z)
	  {
	    startx = startx + x_jump;
	    vm.l = next_x - dist;
	    dist = next_x;
	    next_x = next_x + xmove;
			
	  }
	else if (next_y <= next_x && next_y<= next_z)
	  {
	    starty = starty + y_jump;
	    vm.l = next_y - dist;
	    dist = next_y;
	    next_y = next_y + ymove;
			
	  }
	else if (next_z <= next_y && next_z<= next_x)
	  {
	    startz = startz + z_jump;
	    vm.l = next_z - dist;
	    dist = next_z;
	    next_z = next_z + zmove;
	  }
		
	if (startx>=-1 && starty>=-1 && startz>=-1 && startx<Xn+1 &&
	    starty<Yn+1 && startz<Zn+1)
	  {
	    vm.x = startx;
	    vm.y = starty;
	    vm.z = startz;
	    vec.push_back(vm);
	  }
      }



    return vec;
  }




  //
  // A function used to fill all the VoxBoxes with a initial
  // value
  //
  void VoxelSpace::fillVoxelBoxes(M2 needleA, M2 leafA)
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    voxboxes[i1][i2][i3].setArea(needleA,leafA);
	  }
  }

  //
  // A function used to fill all the VoxBoxes with a initial
  // value downwards 
  //
  void VoxelSpace::fillVoxelBoxes(LGMdouble inivalue, int beginZ, int endZ)
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (i3 >= beginZ && i3 <= endZ){
	      voxboxes[i1][i2][i3].setArea(inivalue,inivalue);
	    }
	    else
	      voxboxes[i1][i2][i3].setArea(0,0);
	  }
  }

  void VoxelSpace::fillVoxelBoxesWithNeedles(LGMdouble Sf, LGMdouble Wf,
					     LGMdouble Rf, LGMdouble L,
					     int beginZ, int endZ)
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (i3 >= beginZ && i3 <= endZ){
	      voxboxes[i1][i2][i3].addNeedleArea(Sf*Wf);
	      voxboxes[i1][i2][i3].addNeedleMass(Wf);
	      //for-loop runs eight times (says mika).
	      for (double phi=0; phi<PI_VALUE/2.0; phi+=PI_VALUE/16)
		{
		  //As in DumpSegment
		  voxboxes[i1][i2][i3].addStarSum(voxboxes[i1][i2][i3].
						  S(phi,Sf,Wf,Rf,L)/8.0);
		  voxboxes[i1][i2][i3].updateValues();
		}
	      voxboxes[i1][i2][i3].increaseNumberOfSegments();
	      voxboxes[i1][i2][i3].updateValues();
	    }
	  }
  }

  //
  // Returns the VoxelBox where the global Point p belongs
  //
  VoxelBox& VoxelSpace::getVoxelBox(Point p)
  {
    Point localP = p - corner1;

    int Xi = static_cast<int>(localP.getX()/Xbox);
    int Yi = static_cast<int>(localP.getY()/Ybox);
    int Zi = static_cast<int>(localP.getZ()/Zbox);


    LGMassert(Xi>-1);
    LGMassert(Yi>-1);
    LGMassert(Zi>-1);

    LGMassert(Xi<Xn);
    LGMassert(Yi<Yn);
    LGMassert(Zi<Zn);

    return voxboxes[Xi][Yi][Zi]; 
  }


  //
  //	for Poplar: The function calculates the Qin and Qabs-values to
  //	every VoxelBox.
  //
  LGMdouble VoxelSpace::calculatePoplarLight()
  {
    //ofstream file("calculateVoxelSpace.txt");
    cout << " VoxelSpace::calculatePoplarLight Begin for poplar: " << endl;
    updateStar();
    srand(time(NULL));

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    int num_dirs = sky->numberOfRegions();
	    //This might  make the voxel  space slow in  execution: if
	    //there  is something  is voxboxes  the following  loop is
	    //executed.
	    if (voxboxes[i1][i2][i3].isEmpty() == false)
	      {				
		voxboxes[i1][i2][i3].updateValues();
		for(int i = 0; i < num_dirs; i++)
		  {	
		    vector<double> rad_direction(3);
		    LGMdouble iop = 
		      sky->diffuseRegionRadiationSum(i,rad_direction);
		    PositionVector 
		      radiation_direction(rad_direction[0], rad_direction[1], 
					  rad_direction[2]);
		    radiation_direction.normalize();
		    //cout <<  iop << endl;
		    vector<VoxelMovement> vec;		
		    getRoute(vec, i1, i2, i3, radiation_direction);
		    int size = vec.size();

		    long int seed = -rand();
		      if (size>1)
		      {
                      int a=1;
		      bool flag=0;
		      // long int seed= time(0);
                      double p, result, test;
                      Bernoulli ber(seed);
                      
                      while (a<size && flag==0)
			{
			  
			  VoxelMovement v1 = vec[a-1];
			  //  VoxelMovement v2 = vec[a];
					
                          LGMdouble starsum=voxboxes[v1.x][v1.y][v1.y].getStarSum();			
			 
                          p=min(starsum, 1.0);     //need to work on my
			  //field data to get the p value
			  // cout<<starsum<<" ";
                          result=ber(0.3, 1);
			  // cout<<result<<" ________________show result____________"<<endl; 
  			  if (result>0.5)
			    flag=1;
                          else 
                            a++;
			}
		      //   cout<<endl;
                      if (a==size-1)
                      {
                           voxboxes[i1][i2][i3].addRadiation(iop);
			   //  cout<<a<<"________-the hit voxelbox:"<<size<<endl;
		      }
		
		      }	
		  }
		//calculate the light for direct beam

		vector<double> direct_direction(3);
		LGMdouble iop= sky->directRadiation(direct_direction);
                 vector<VoxelMovement> vec;
		  getRoute(vec, i1, i2, i3, direct_direction);
	          int size = vec.size();
		      if (size>1)
		      {
                      int a=1;
		      bool flag=0;
		      // long int seed= time(0);
		      long int seed = -rand();
                      double p, result, test;
                      Bernoulli ber(seed);
                      
                      while (a<size && flag==0)
			{
			  
			  VoxelMovement v1 = vec[a-1];
			  //  VoxelMovement v2 = vec[a];
					
                          LGMdouble starsum=voxboxes[v1.x][v1.y][v1.y].getStarSum();			
			 
                          p=min(starsum, 1.0);     //need to work on my field data to get the p value
			  // cout<<starsum<<" ";
                          result=ber(0.3, 1);
			  // cout<<result<<" ________________show result____________"<<endl; 
  			  if (result>0.5)
			    flag=1;
                          else 
                            a++;
			}

                      if (a==size-1)
                      {
                           voxboxes[i1][i2][i3].addRadiation(iop);
			   //  cout<<a<<"________-the hit voxelbox:"<<size<<endl;
		      }
		      }
		      //calculate the light for direct beam done 
              }             	      
	  }   
    // file.close();
    return 0;
  }



  //
  //	The function calculates the Qin and Qabs-values to every VoxelBox.
  //
  LGMdouble VoxelSpace::calculateTurbidLight()
  {
    //ofstream file("calculateVoxelSpace.txt");
    cout << " VoxelSpace::calculateTurbidLight Begin: " << endl;
    updateStar();
    cout << " Star values updated " << endl;    
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    int num_dirs = sky->numberOfRegions();
	    //This might  make the voxel  space slow in  execution: if
	    //there  is something  is voxboxes  the following  loop is
	    //executed.
	    if (voxboxes[i1][i2][i3].isEmpty() == false)
	      {				
		//		for(int i = 0; i < num_dirs; i++)
		for(int i = 0; i < 1; i++)
		  {	
		    vector<double> rad_direction(3);
		    LGMdouble iop = sky->
		      diffuseRegionRadiationSum(i,rad_direction);
		    PositionVector
		      radiation_direction(rad_direction[0],
					  rad_direction[1], rad_direction[2]);
		    radiation_direction.normalize();
		    vector<VoxelMovement> vec;		
		    getRoute(vec, i1, i2, i3, radiation_direction);
		    int size = vec.size();

		    if (size>1)
		      for (int a=1; a<size; a++)
			{
			  VoxelMovement v1 = vec[a-1];
			  VoxelMovement v2 = vec[a];
			  
			  LGMdouble ext = voxboxes[v1.x][v1.y][v1.z].
			    extinction(v2.l); 
			  iop = iop * ext;
			}

		    if (size>0)
		      {
			// qin on t�ss� arvo vokseliboksin pinnalla
			LGMdouble qin = iop;

			// Matka jonka s�de kulkee boksin sis�ll� jolle arvoja 
			// ollaan laskemassa
			LGMdouble inner_length = vec[0].l*2;

			// vaimennuskerroin boksin l�pi kulkiessa
			LGMdouble ext2 = voxboxes[i1][i2][i3].
			  extinction(inner_length);
							
			//s�teilyn voimakkuus kun se tulee boksista ulos
			LGMdouble qout = iop * ext2;

			//ja vaimeneminen boksin sis�ll�
			voxboxes[i1][i2][i3].addQabs(qin - qout);
							
			// Nyt lasketaan vain keskipisteeseen, eli
			// boksin saama s�teily on se arvo joka
			// saadaan boksin keskipisteest�.
			LGMdouble ext = voxboxes[i1][i2][i3].
			  extinction(inner_length/2.0);
			iop = iop * ext;
		      }

		    voxboxes[i1][i2][i3].addRadiation(iop); //s�teily
							    //joka
							    //tulee..
						
		  }
	      }
	  }
    
    // file.close();
    return 0;
  }



  //
  //	This function adds a ScotsPine to the VoxelSpace 
  //
    void VoxelSpace::AddScotspine(Tree<ScotsPineVisual, ScotsBud> &tree)
  {
    vecScotspines.push_back(&tree);
  }



  //
  //	This function searches for the minimum BoundingBox where every tree is included in

  //
  BoundingBox& VoxelSpace::searchDimensions(BoundingBox &bbox, bool boolDimensionsWithNumBoxes)
  {
    int size, i;


    //Scotspines
    size = vecScotspines.size();
    for (i = 0; i<size; i++)
      {
		
	FindBoundingBox<ScotsPineVisual, ScotsBud> fbb;	
	bbox = Accumulate(*vecScotspines[i], bbox, fbb);
      }

    LGMdouble scaleOdd = 1.1;
    LGMdouble scaleOdd2 = 0.05;

    LGMdouble dx = (0.1 + bbox.getMax().getX() - bbox.getMin().getX()) * scaleOdd;
    LGMdouble dy = (0.1 + bbox.getMax().getY() - bbox.getMin().getY()) * scaleOdd;
    LGMdouble dz = (0.1 + bbox.getMax().getZ() - bbox.getMin().getZ()) * scaleOdd;

    if (boolDimensionsWithNumBoxes)
      {
	Xbox = dx / (Xn-0.5);
	Ybox = dy / (Yn-0.5);
	Zbox = dz / (Zn-0.5);
      }
    else
      {
	Xn = static_cast<int>(dx / Xbox + 1);
	Yn = static_cast<int>(dy / Ybox + 1);
	Zn = static_cast<int>(dz / Zbox + 1);
      }

    corner1 = Point(bbox.getMin().getX()-dx*scaleOdd2,
		    bbox.getMin().getY()-dy*scaleOdd2,
		    bbox.getMin().getZ()-dz*scaleOdd2); 

    double fx = corner1.getX();
    double fy = corner1.getY();
    double fz = corner1.getZ();
	


    voxboxes.resize(Xn, Yn, Zn);

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 + Point(i1*Xbox, i2*Ybox, i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }

    return bbox;
  }


  void VoxelSpace::updateStar()
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    voxboxes[i1][i2][i3].updateValues(); 
	  }

  }

  void VoxelSpace::reset()
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    voxboxes[i1][i2][i3].reset(); 
	  }
  } 

  LGMdouble VoxelSpace::getQabs()const
  {
    LGMdouble qabs = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    qabs = qabs + voxboxes[i1][i2][i3].getQabs(); 
	  }
    return qabs;
  }  

  LGMdouble VoxelSpace::getQin()const
  {
    LGMdouble qin = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    qin = qin + voxboxes[i1][i2][i3].getQin(); 
	  }
    return qin;
  }  

  //Return Min and Max foliage mass in the voxel boxes. The first holds
  //the minimum value and the second the maximum value
  pair<double,double> VoxelSpace::getMinMaxNeedleMass()const
  {
    pair<double,double> p(0.0,0.0);

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    double fm = voxboxes[i1][i2][i3].getNeedleMass();
	    //new minimum
	    if (fm < p.first)
	      p.first = fm;
	    //new maximum
	    if (fm > p.second)
	      p.second = fm;
	  }
    return p;
  }
  //
  //	This function Dumps every tree included in the VoxelSpace to
  //	VoxelBoxes.
  //
  void VoxelSpace::dumpTrees()
  {
    int size, i;


    //Scotspines first
    size = vecScotspines.size();
    for (i = 0; i<size; i++)
      {
	//This does not compile on Linux g++ with ScotsPineVisual
	//DumpCfTree(*this, *vecScotspines[i]);
      }

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
				
	    voxboxes[i1][i2][i3].updateValues(); 
	  }
  }


  //
  //	This function is called after calculateTurbidLight-function. The light values calculated in VoxelBoxes
  //	are now tranformed to treesegments.
  //
  void VoxelSpace::setLightValues()
  {
    int size, i;

    //Scotspines
    size = vecScotspines.size();
    for (i = 0; i<size; i++)
      {
	SetCfTreeQabs(*this, *vecScotspines[i]);
      }
  } 






 

  //
  //	Visualizes the VoxelSpace
  //

  
  
  void VoxelSpace::draw()
  {
    //#ifdef _MSC_VER
    int num = 0;
    vector<VisualCube> cubes;
    vector<VisualCube> ordered_cubes;

    //cout << "koko " << Xn << " " << Yn << " " << Zn << endl;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {			
	    if (voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		VisualCube cube;
		Point c1 = voxboxes[i1][i2][i3].getCornerPoint();

		cube.x = c1.getX();
		cube.y = c1.getY();
		cube.z = c1.getZ();

		cube.ready = false;
		cube.areaden = voxboxes[i1][i2][i3].getAreaDensity(); 

		Point cpoint;
		cpoint = voxboxes[i1][i2][i3].getCenterPoint(); 

		float xx = cpoint.getX();
		float yy = cpoint.getY();
		float zz = cpoint.getZ();

		cube.dist = pow(cam_x-xx, 2) + pow(cam_y-yy, 2) + pow(cam_z-zz, 2); 
				
		cubes.push_back(cube);
		num ++;
	      }
	  }

    //cout << "kuutioita jossa tavaraa " << cubes.size() << endl;

    for (int i = 0; i<num; i++)
      {
	int max_dist = -10;
	int mem_num = -1;
	int a = cubes.size();
	for (int ii=0; ii<a; ii++)
	  {
	    VisualCube c = cubes[ii];
	    if (c.ready == false)
	      {
		if (c.dist > max_dist)
		  mem_num = ii;
	      }
	  }
	if (mem_num > -1)
	  {
	    VisualCube &c = cubes[mem_num];
	    c.ready = true;
	    ordered_cubes.push_back(c);
	  }
      }

    //cout << "piirt�minen " << endl;
    glPushMatrix();
					
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glLineWidth(1);
    glColor3f(1,0.2,0.2);

    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(5,0,0);

    glVertex3f(0,0,0);
    glVertex3f(0,5,0);

    glVertex3f(0,0,0);
    glVertex3f(0,0,5);
    glEnd();

    glLineWidth(1);

    int s = ordered_cubes.size();

    //cout << "kuutioita " << endl;
    for (int i = 0; i< s; i++)
      {
	VisualCube cube = cubes[i];
		

	glColor3f(0.2,0.2,1);
				
				
	float half_edgeX = Xbox/2.0;
	float half_edgeY = Ybox/2.0;
	float half_edgeZ = Zbox/2.0;



	//pikkukuution keskipiste
	float xx = cube.x + half_edgeX;
	float yy = cube.y + half_edgeY;
	float zz = cube.z + half_edgeZ;
		

	glBegin(GL_LINE_LOOP);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
				
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glEnd();

		
	float shadow_odd = 0.1 + cube.areaden * (0.3 * half_edgeX*half_edgeY*half_edgeZ); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0, 0.8, 0.0, shadow_odd);

	glBegin(GL_POLYGON);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glEnd();



	glBegin(GL_POLYGON);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
	glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
	glEnd();

	glDisable(GL_BLEND);
      }
    glEnable(GL_LIGHTING);
    glPopMatrix();
    // glEndList();
    //#endif
    }


  //Write voxel boxes  to file. If 'all' is true  write all boxes else
  //write  only boxes  with foliage.  By  default 'all'  is true  (old
  //beaviour)
  void VoxelSpace::writeVoxBoxesToFile(const string& filename, bool all)
  {
    ofstream file(filename.c_str());
    file << "Vokselien koko " << Xbox << " " << Ybox << " " << Zbox << endl;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (all){
	      file << "[" << i1 << "," << i2 << "," << i3 << "]   ";
	      file << voxboxes[i1][i2][i3] << endl;
	    }
	    else if (voxboxes[i1][i2][i3].getFoliageMass() > R_EPSILON){
	      file << "[" << i1 << "," << i2 << "," << i3 << "]   ";
	      file << voxboxes[i1][i2][i3] << endl;
	    }
	  }
    file.close();

  }	

  void VoxelSpace::writeVoxBoxesToFile(const string& filename, int z)
  {
    ofstream file(filename.c_str());
    file << "Vokselien koko " << Xbox << " " << Ybox << " " << Zbox << endl;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (i3 <= z){
	      file << "[" << i1 << "," << i2 << "," << i3 << "]   ";
	      file << voxboxes[i1][i2][i3] << endl;
	    }
	  }
    file.close();
    
  }	
  
  void VoxelSpace::writeVoxBoxesToFile2(const string& filename)
  {
    ofstream file(filename.c_str());

    file << "Index "; 
    file << "Qabs " <<  "    Qin " << "     star " << "   needleArea " << " leafarea ";
    file << "  centerpoint " << endl;
	
    LGMdouble sumQabs = 0.0;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    //	    if(voxboxes[i1][i2][i3].isEmpty() == false)
	    if(voxboxes[i1][i2][i3].isEmpty() == true)
	      {
		file <<  i1 << ":" << i2 << ":" << i3 << "   ";
		Point p;
		p = voxboxes[i1][i2][i3].getCenterPoint();
					
		file << voxboxes[i1][i2][i3];
		file << "  " << p << " ";
	
		sumQabs += voxboxes[i1][i2][i3].getQabs();
	      }
	  }
    file << endl << endl << "Sum of Qabs " << sumQabs << endl;
  }	


  LGMdouble VoxelSpace::getFoliageMass(void)
  {
    LGMdouble ret = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    ret += voxboxes[i1][i2][i3].getFoliageMass();
	  }
    return ret;
  }




  int VoxelSpace::getNumberOfFilledBoxes()const
  {
    int count = 0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if(voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		count++;
	      }
	  }
    return count;
  }

  int VoxelSpace::getNumberOfTreeSegments()const
  {
    int count=0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if(voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		count += voxboxes[i1][i2][i3].getNumSegments();
	      }
	  }
    return count;
  }


 
  void VoxelSpace::draw(bool blackBG)
  {
    glEnable(GL_LIGHTING);
    int num = 0;
    vector<VisualCube> cubes;
    vector<VisualCube> ordered_cubes;

    pair<double, double> pa = getMinMaxNeedleMass();
    double max = pa.second;

    if (max == 0) return;

    //cout << "koko " << Xn << " " << Yn << " " << Zn << endl;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {			
	    if (voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		VisualCube cube;
		Point c1 = voxboxes[i1][i2][i3].getCornerPoint();

		cube.x = c1.getX();
		cube.y = c1.getY();
		cube.z = c1.getZ();

		cube.ready = false;
		cube.areaden = voxboxes[i1][i2][i3].getAreaDensity(); 

		LGMdouble nmass = voxboxes[i1][i2][i3].getNeedleMass();
	      
		
		
		float half_edgeX = Xbox/2.0;
		float half_edgeY = Ybox/2.0;
		float half_edgeZ = Zbox/2.0;
		
		
		
		//pikkukuution keskipiste
		float xx = cube.x + half_edgeX;
		float yy = cube.y + half_edgeY;
		float zz = cube.z + half_edgeZ;
		
		
		half_edgeX = half_edgeX / 10.0;
		half_edgeY = half_edgeX;
		half_edgeZ = half_edgeX;
	      
		//cout << cube.areaden << endl;


		double green=0.0;
		double red=0.0;
		double blue=0.0;
		if (blackBG)
		  {
		    red = 0.0;
		    blue = 0.0;
		    green = nmass / max; 
		  }
		else
		  {
		    green = 1.0;
		    red = (max-nmass)/max;
		    blue= (max-nmass)/max;
		  }
		

	       

		GLfloat mat_amb[] = { red, green, blue, 1.0 }; 
		GLfloat mat_dif[] = { red, green, blue, 1.0 }; 
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb); 
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);

		
		
		glBegin(GL_POLYGON);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();
		
		glBegin(GL_POLYGON);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glEnd();
		
		
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glEnd();
		
		
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();
		
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glEnd();
	      }
	  }
  }









}  // closing namespace Lignum


