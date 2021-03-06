#To compile "l2lignum" on SGI type 
#    make l2lignum
#To compile with g++ on SGI or on Linux type 
#    make gnu 
#or copy paste
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "AR=ar"  "ARDFLAGS=rvs" l2lignum

SRC= main.cc
OBJ  = ${SRC:.cc=.o}

LIBSRC= ../src/Turtle.cc
LIBOBJ = ${LIBSRC:.cc=.o}

BIRCHSRC = birch.cc
BIRCHOBJ =  ${BIRCHSRC:.cc=.o}

PINESRC = pine.cc
PINEOBJ = ${PINESRC:.cc=.o}

FORESTSRC = forest.cc
FORESTOBJ = ${FORESTSRC:.cc=.o}

CA110SRC = ca110.cc
CA110OBJ = ${CA110SRC:.cc=.o}

CA30SRC = ca30.cc
CA30OBJ = ${CA30SRC:.cc=.o}

CA90SRC = ca90.cc
CA90OBJ = ${CA90SRC:.cc=.o}

BEARBERRYSRC = bearberry.cc
BEARBERRYOBJ = ${BEARBERRYSRC:.cc=.o}

AUVAURSISRC  = a-uvaursi.cc
AUVAURSIOBJ  = ${AUVAURSISRC:.cc=.o}


LSYS =   bearberry.L pine9bp.L cs-plantA.L cs-plantB.L  cs-plantC.L \
         cs-plantD.L cs-plant.L 
#LSYS = ca110.L
#LSYS  = ca30.L
#LSYS = ca90.L
LSYS = pine9bp.L birch.L

CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

AR =  $(CCC) -ar  
ARFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I../../c++adt/include -I../../Firmament/include \
          -I../../stl-lignum/include -I../include \
          -I../../Graphics -I../../stl-voxelspace/include \
          -I../../ScotsPine/include -I../../ScotsPineVisual \
          -I/usr/freeware/include -I/usr/X11R6/include -I/sw/include
STL     = -I/usr/include/CC

LIBD = lib64
LIBFLAGS = -L../../c++adt/lib -L../../stl-lignum/lib -L../../Firmament/lib \
           -L. -L../lsys -L../../Graphics -L/usr/X11R6/lib -L../../stl-voxelspace/lib \
           -L/usr/freeware/$(LIBD)  -L/sw/lib -L/usr/$(LIBD)

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = libL.a
LIB5   = libVisual.a
LIB6   = liblsys.a
LIB7   = libvoxel.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBL   = -lL
LIBMATH  = -lm 
LIBVISUAL = -lVisual
LIBLSYS = -llsys
LIBVOXEL = -lvoxel

LIBOGL =  -lglut -lGL -lGLU -lX11 -lXext -lXmu 

LIBS     =  $(LIBVISUAL) $(LIBLSYS) $(LIBL) $(LIBVOXEL) $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBOGL) \
            $(LIBMATH)



PROGFILES = program-files.html

.SUFFIXES: .o .cc

sinclude Makedepend

l2lignum: $(OBJ) l2c $(LIB1) $(LIB2) $(LIB3)  $(LIB4)  $(LIB5) $(LIB6)   
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(OBJ) $(LIBFLAGS) $(LIBS)

gnu:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32"  l2lignum
lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" l2lignum

birch:  l2c $(BIRCHOBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)   
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(BIRCHOBJ) $(LIBFLAGS) $(LIBS)

gnubirch:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=birch.L" birch

pine: l2c $(PINEOBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)   
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(PINEOBJ) $(LIBFLAGS) $(LIBS)
gnupine: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=pine9bp.L" pine

forest: l2c $(FORESTOBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)  
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(FORESTOBJ) $(LIBFLAGS) $(LIBS)

gnuforest:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=pine9bp.L birch.L" forest

ca110: l2c $(CA110OBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)  
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(CA110OBJ) $(LIBFLAGS) $(LIBS)

gnuca110:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=ca110.L" ca110

ca30: l2c $(CA30OBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)  
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(CA30OBJ) $(LIBFLAGS) $(LIBS)

gnuca30: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
              "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=ca30.L" ca30

ca90: l2c $(CA90OBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)  
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(CA90OBJ) $(LIBFLAGS) $(LIBS)

gnuca90:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=ca90.L" gnuca90

bearberry: l2c $(BEARBERRYOBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)  
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(BEARBERRYOBJ) $(LIBFLAGS) $(LIBS)

gnubearberry:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=bearberry.L ErythrinaRoots.L" bearberry

auvaursi: l2c  $(AUVAURSIOBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)  
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(AUVAURSIOBJ) $(LIBFLAGS) $(LIBS)

gnuauvaursi:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32" "LSYS=A-UvaUrsiSandpit.L" auvaursi

l2c:	
	(cd ../L2C; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
                          "AR=ar" "ARFLAGS=rvs" $@)
$(LIB1):
	(cd ../../c++adt; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
                               "OPTIMIZE=$(OPTIMIZE)" "AR=$(AR)" "ARFLAGS=$(ARFLAGS)" $@)
$(LIB2):
	(cd ../../stl-lignum; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
                                   "OPTIMIZE=$(OPTIMIZE)" "AR=$(AR)" "ARFLAGS = $(ARFLAGS)" $@)
$(LIB3):
	(cd ../../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)
$(LIB4):$(LIBOBJ)
	 $(AR) $(ARFLAGS) $(@) $(LIBOBJ) 
$(LIB5):
	(cd ../../Graphics; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)
$(LIB6):
	(cd ../lsys; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" "LSYS=$(LSYS)" $@ )
.cc.o: 
	$(CCC) $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
clean:
	rm -rf *.o  Makedepend core ii_files
	(cd ../lsys; make clean)
distclean: clean
	rm -rf  l2lignum $(LIB4) Makedepend
	(cd ../../Graphics; make distclean)
	(cd ../L2C; make distclean)
	(cd ../lsys; make distclean)
#When creating dependencies leave out lsys directory.
#lsys directory contains only L-files that are
#to be compiled to C++ with l2c. It does not contain project program files. 
depend:
	(cd ../../Graphics; make "CCC=$(CCC)"  depend)
	(cd ../L2C; make "CCC=$(CCC)"  depend)
	$(CCC) -M $(INCLUDE) $(SRC) $(LIBSRC) $(BIRCHSRC) $(PINESRC) $(FORESTSRC)  > Makedepend

