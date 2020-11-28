#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateShape1(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment);
	void CreateShape2(float fSizeX, float fSizeY, float fSizeZ, int nSegment);
	void CreateShape3(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment);
	//void CreateShape4(float fSizeX1, float fSizeX2, float fSizeX3, float fSizeY, float fSizeZ1, float fSizeZ2, float fSizeZ3, float fRadius, int nSegment);
	void CreateShape5(float fSizeX, float fSizeY, float fSizeZ, int nSegment);
};

#endif