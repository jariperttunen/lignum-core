######################################################################
# Automatically generated by qmake (2.00a) Ti Kes 20 12:39:50 2006
######################################################################

TEMPLATE = app
TARGET += 
# Input
HEADERS += LGMPolygonTree.h GLDrawer.h BSPPolygon.h BSPTree.h SceneObject.h BSPPolygonMaterial.h CylinderVolume.h Volume.h
SOURCES += LGMPolygonTree.cpp GLDrawer.cpp main.cpp BSPPolygon.cpp BSPTree.cpp SceneObject.cpp BSPPolygonMaterial.cpp CylinderVolume.cpp

DEPENDPATH += .
INCLUDEPATH += . ../stl-lignum/include ../c++adt/include ../Firmament/include ../LEngine/include ../stl-voxelspace/include ../Graphics ../Pine ../Lig-Crobas/include ../XMLTree ../ScotsPine/include .. 
CONFIG += qt
QT += opengl xml
# -L/usr/freeware/lib32 -lglut -lXmu -pine
LIBS	+= -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib -L../LEngine/lib -L../Lig-Crobas -L../stl-voxelspace/lib -L../Graphics -lVisual -lsky -llsys -lL -lvoxel -lLGM  -lc++adt

