#include <math.h>
#include <stdio.h>

#include "Mesh.h"

#define PI 3.1415926
#define COLORNUM 14


float ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0},
								{0.0, 1.0, 0.0},
								{0.0, 0.0, 1.0},
								{1.0, 1.0, 0.0},
								{1.0, 0.0, 1.0},
								{0.0, 1.0, 1.0},
								{0.3, 0.3, 0.3},
								{0.5, 0.5, 0.5},
								{0.9, 0.9, 0.9},
								{1.0, 0.5, 0.5},
								{0.5, 1.0, 0.5},
								{0.5, 0.5, 1.0},
								{0.0, 0.0, 0.0},
								{1.0, 1.0, 0.5}};


void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int i;
	int idx;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}
}

void Mesh::CreateCube(float fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(fSizeX, -fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(fSizeX, -fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(-fSizeX, fSizeY, fSizeZ);
	pt[6].set(-fSizeX, fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	for (int i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 4;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 7;
	for (int i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 0;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 5;
	face[2].vert[3].vertIndex = 4;
	for (int i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 0;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 3;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 7;
	for (int i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 0;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 2;
	face[4].vert[2].vertIndex = 6;
	face[4].vert[3].vertIndex = 5;
	for (int i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 0;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[2].vertIndex = 7;
	face[5].vert[3].vertIndex = 4;
	for (int i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 0;
}

void Mesh::CreateShape1(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment)
{	
	// TODO Ve tiep tuyen
	int numCyVerts = nSegment * 3 + 2;
	int numCubeVerts = 8;
	numVerts = numCyVerts + numCubeVerts;
	pt = new Point3[numVerts];

	int i;
	int face_idx = -1, point_idx = 0;
	float fAngle = PI / 2 / nSegment;
	float x, y, z;

	/*************************************** TETRAHEDRON *****************************************/
	// Initialize points for cylinder
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(PI + fAngle * i) - fSizeX;
		z = fRadius * sin(PI + fAngle * i) + fSizeZ;
		y = fSizeY;
		pt[i + 1].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + (nSegment + 1)].set(x, y, z);
	}
	pt[numCyVerts - 1].set(-fSizeX, -fSizeY, fSizeZ);

	int numCyFaces = nSegment * 3;
	int numCubeFaces = 6;
	numFaces = numCyFaces + numCubeFaces;
	face = new Face[numFaces];

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = 0;
		face[face_idx].vert[1].vertIndex = i + 2;
		face[face_idx].vert[2].vertIndex = i + 1;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 4;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = i + 1;
		face[face_idx].vert[1].vertIndex = i + 2;
		face[face_idx].vert[2].vertIndex = face[face_idx].vert[1].vertIndex + (nSegment + 1);
		face[face_idx].vert[3].vertIndex = face[face_idx].vert[0].vertIndex + (nSegment + 1);
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = numCyVerts - 1;
		face[face_idx].vert[2].vertIndex = i + 2 + (nSegment + 1);
		face[face_idx].vert[1].vertIndex = i + 1 + (nSegment + 1);
	}

	/*************************************** CUBOID *****************************************/
	// Initialize points for cuboid
	point_idx = numCyVerts;
	pt[point_idx].set(fSizeX, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(fSizeX, fSizeY, fSizeZ);
	pt[point_idx + 2].set(fSizeX, fSizeY, -fSizeZ);
	pt[point_idx + 3].set(fSizeX, -fSizeY, -fSizeZ);
	pt[point_idx + 4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[point_idx + 5].set(-fSizeX, fSizeY, fSizeZ);
	pt[point_idx + 6].set(-fSizeX, fSizeY, fSizeZ - fRadius);
	pt[point_idx + 7].set(-fSizeX, -fSizeY, fSizeZ - fRadius);

	// Frontal face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Rear face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 4;
	face[face_idx].vert[1].vertIndex = point_idx + 5;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = 1;
	face[face_idx].vert[3].vertIndex = nSegment + 2;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;
	
	// Top face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;
}

void Mesh::CreateShape2(float fSizeX, float fSizeY, float fSizeZ, int nSegment){
	int numCyVerts = (nSegment + 1) * 2 + 2;
	int numCubeVerts = 8;
	int numTriangleVerts = 6;
	numVerts = numCyVerts * 2 + numCubeVerts * 2 + numTriangleVerts * 4;
	pt = new Point3[numVerts];

	int i;
	int face_idx = -1, point_idx;
	float x, y, z;

	float fSizeX2 = 3 * fSizeX / 2;
	float fSizeZ2 = 4 * fSizeZ / 5;

	float fSizeZ3 = fSizeZ / 2;

	float fRadius = fSizeZ2;
	float fAngle = PI / nSegment;

	pt[0].set(-fSizeX, fSizeY, 0);
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(PI / 2 + fAngle * i) - fSizeX;
		z = fRadius * sin(PI / 2 + fAngle * i);
		y = fSizeY;
		pt[i + 1].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + (nSegment + 1)].set(x, y, z);
	}
	pt[numCyVerts - 1].set(-fSizeX, -fSizeY, 0);

	int numCyFaces = nSegment * 3;
	int numCubeFaces = 6;
	int numTriangleFaces = 5;
	numFaces = numCyFaces * 2 + numCubeFaces * 2 + numTriangleFaces * 4;
	face = new Face[numFaces];

	/*************************************** TOP TETRAHEDRON *****************************************/
	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = 0;
		face[face_idx].vert[1].vertIndex = i + 2;
		face[face_idx].vert[2].vertIndex = i + 1;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 4;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];

		face[face_idx].vert[0].vertIndex = i + 1;
		face[face_idx].vert[1].vertIndex = i + 2;
		face[face_idx].vert[2].vertIndex = face[face_idx].vert[1].vertIndex + (nSegment + 1);
		face[face_idx].vert[3].vertIndex = face[face_idx].vert[0].vertIndex + (nSegment + 1);
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = numCyVerts - 1;
		face[face_idx].vert[2].vertIndex = i + 2 + (nSegment + 1);
		face[face_idx].vert[1].vertIndex = i + 1 + (nSegment + 1);
	}

	/*************************************** CENTRAL CUBOID *****************************************/
	/********* LEFT CUBOID *********/
	// Initialize points
	point_idx = numCyVerts;
	pt[point_idx].set(fSizeX, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(fSizeX, fSizeY, fSizeZ);
	pt[point_idx + 2].set(fSizeX, fSizeY, fSizeZ / 2);
	pt[point_idx + 3].set(fSizeX, -fSizeY, fSizeZ / 2);
	pt[point_idx + 4].set(-fSizeX, -fSizeY, fSizeZ2);
	pt[point_idx + 5].set(-fSizeX, fSizeY, fSizeZ2);
	pt[point_idx + 6].set(-fSizeX, fSizeY, 0);
	pt[point_idx + 7].set(-fSizeX, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Rear face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 4;
	face[face_idx].vert[1].vertIndex = point_idx + 5;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;
	
	/********* RIGHT CUBOID *********/
	// Initialize points
	point_idx += numCubeVerts;
	pt[point_idx].set(fSizeX, -fSizeY, -fSizeZ / 2);
	pt[point_idx + 1].set(fSizeX, fSizeY, -fSizeZ / 2);
	pt[point_idx + 2].set(fSizeX, fSizeY, -fSizeZ);
	pt[point_idx + 3].set(fSizeX, -fSizeY, -fSizeZ);
	pt[point_idx + 4].set(-fSizeX, -fSizeY, 0);
	pt[point_idx + 5].set(-fSizeX, fSizeY, 0);
	pt[point_idx + 6].set(-fSizeX, fSizeY, -fSizeZ2);
	pt[point_idx + 7].set(-fSizeX, -fSizeY, -fSizeZ2);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Rear face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex =point_idx + 4;
	face[face_idx].vert[1].vertIndex =point_idx + 5;
	face[face_idx].vert[2].vertIndex =point_idx + 6;
	face[face_idx].vert[3].vertIndex =point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex =point_idx;
	face[face_idx].vert[1].vertIndex =point_idx + 1;
	face[face_idx].vert[2].vertIndex =point_idx + 5;
	face[face_idx].vert[3].vertIndex =point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex =point_idx + 3;
	face[face_idx].vert[1].vertIndex =point_idx + 2;
	face[face_idx].vert[2].vertIndex =point_idx + 6;
	face[face_idx].vert[3].vertIndex =point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex =point_idx + 1;
	face[face_idx].vert[1].vertIndex =point_idx + 2;
	face[face_idx].vert[2].vertIndex =point_idx + 6;
	face[face_idx].vert[3].vertIndex =point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex =point_idx;
	face[face_idx].vert[1].vertIndex =point_idx + 3;
	face[face_idx].vert[2].vertIndex =point_idx + 7;
	face[face_idx].vert[3].vertIndex =point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	/********* CENTER CUBOID *********/
	// Initialize points
	point_idx += numCubeVerts;
	pt[point_idx].set(fSizeX, -fSizeY, fSizeZ / 2);
	pt[point_idx + 1].set(fSizeX, fSizeY, fSizeZ / 2);
	pt[point_idx + 2].set(fSizeX, fSizeY, -fSizeZ / 2);
	pt[point_idx + 3].set(fSizeX, -fSizeY, -fSizeZ / 2);
	pt[point_idx + 4].set(-fSizeX, fSizeY, 0);
	pt[point_idx + 5].set(-fSizeX, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;
	
	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	/*************************************** BOTTOM CUBOID *****************************************/
	/********* LEFT CUBOID *********/
	// Initialize points
	point_idx += numTriangleVerts;
	pt[point_idx].set(fSizeX, -fSizeY, fSizeZ / 2);
	pt[point_idx + 1].set(fSizeX, fSizeY, fSizeZ / 2);
	pt[point_idx + 2].set(fSizeX2, fSizeY, fSizeZ3);
	pt[point_idx + 3].set(fSizeX2, -fSizeY, fSizeZ3);
	pt[point_idx + 4].set(fSizeX2, fSizeY, 0);
	pt[point_idx + 5].set(fSizeX2, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 4;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;


	/********* CENTER CUBOID *********/
	// Initialize points
	point_idx += numTriangleVerts;
	pt[point_idx].set(fSizeX, -fSizeY, fSizeZ / 2);
	pt[point_idx + 1].set(fSizeX, fSizeY, fSizeZ / 2);
	pt[point_idx + 2].set(fSizeX, fSizeY, -fSizeZ / 2);
	pt[point_idx + 3].set(fSizeX, -fSizeY, -fSizeZ / 2);
	pt[point_idx + 4].set(fSizeX2, fSizeY, 0);
	pt[point_idx + 5].set(fSizeX2, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	/********* RIGHT CUBOID *********/
	// Initialize points
	point_idx += numTriangleVerts;
	pt[point_idx].set(fSizeX, -fSizeY, -fSizeZ / 2);
	pt[point_idx + 1].set(fSizeX, fSizeY, -fSizeZ / 2);
	pt[point_idx + 2].set(fSizeX2, fSizeY, -fSizeZ3);
	pt[point_idx + 3].set(fSizeX2, -fSizeY, -fSizeZ3);
	pt[point_idx + 4].set(fSizeX2, fSizeY, 0);
	pt[point_idx + 5].set(fSizeX2, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	/*************************************** BOTTOM TETRAHEDRON *****************************************/
	// Ininitalize points
	point_idx += numTriangleVerts;
	pt[point_idx].set(fSizeX2, fSizeY, 0);
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fSizeZ3 * cos(- PI / 2 + fAngle * i) + fSizeX2;
		z = fSizeZ3 * sin(- PI / 2 + fAngle * i);
		y = fSizeY;
		pt[i + 1 + point_idx].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + point_idx + (nSegment + 1)].set(x, y, z);
	}
	pt[point_idx + (nSegment + 1) * 2 + 1].set(fSizeX2, -fSizeY, 0);

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = point_idx;
		face[face_idx].vert[1].vertIndex = i + 2 + point_idx;
		face[face_idx].vert[2].vertIndex = i + 1 + point_idx;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 4;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];

		face[face_idx].vert[0].vertIndex = i + 1 + point_idx;
		face[face_idx].vert[1].vertIndex = i + 2 + point_idx;
		face[face_idx].vert[2].vertIndex = face[face_idx].vert[1].vertIndex + (nSegment + 1);
		face[face_idx].vert[3].vertIndex = face[face_idx].vert[0].vertIndex + (nSegment + 1);
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = numVerts - 1;
		face[face_idx].vert[2].vertIndex = i + 2 + point_idx + (nSegment + 1);
		face[face_idx].vert[1].vertIndex = i + 1 + point_idx + (nSegment + 1);
	}
}

void Mesh::CreateShape3(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment)
{
	int i;
	float x, y, z;
	int face_idx = -1, point_idx = 0;

	int numCuboidVerts = 8;
	int numTriVerts = 6;
	int numCyVerts = (nSegment + 1) * 2 + 2;
	numVerts = numCuboidVerts + numCyVerts + numTriVerts * 3;
	pt = new Point3[numVerts];

	/*fSizeX *= 2;
	fSizeZ *= 2;*/
	float fSizeX2 = fSizeX / 1.5;

	int numCyFaces = nSegment * 3;
	int numCubeFaces = 6;
	int numTriFaces = 5;
	numFaces = numCubeFaces + numCyFaces + numTriFaces * 3;
	face = new Face[numFaces];

	// Initialize points
	point_idx = 0;
	pt[point_idx].set(0, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(0, fSizeY, fSizeZ);
	pt[point_idx + 2].set(0, fSizeY, 0);
	pt[point_idx + 3].set(0, -fSizeY, 0);
	pt[point_idx + 4].set(-fSizeX2, -fSizeY, fSizeZ);
	pt[point_idx + 5].set(-fSizeX2, fSizeY, fSizeZ);
	pt[point_idx + 6].set(-fSizeX, fSizeY, 0);
	pt[point_idx + 7].set(-fSizeX, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Rear face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 4;
	face[face_idx].vert[1].vertIndex = point_idx + 5;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	float distZ = 1.5 * fSizeZ;
	float distX = (fSizeX - fSizeX2) / 2;
	fRadius = distX / 1.5;

	float fX2 = sqrt(distX * distX + distZ * distZ);
	float angle = asin(distZ / fX2) + asin(fRadius / fX2);
	float startAngle = PI / 2 - angle;

	float fAngle = 2 * angle / nSegment;

	point_idx += numCuboidVerts;
	pt[point_idx].set(-(fSizeX2 + distX), fSizeY, distZ);
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(startAngle + fAngle * i) - (fSizeX2 + distX);
		z = fRadius * sin(startAngle + fAngle * i) + distZ;
		y = fSizeY;
		pt[i + 1 + point_idx].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + (nSegment + 1) + point_idx].set(x, y, z);
	}
	pt[point_idx + (nSegment + 1) * 2 + 1].set(-(fSizeX2 + distX), -fSizeY, distZ);

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = point_idx;
		face[face_idx].vert[1].vertIndex = i + 2 + point_idx;
		face[face_idx].vert[2].vertIndex = i + 1 + point_idx;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 4;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];

		face[face_idx].vert[0].vertIndex = i + 1 + point_idx;
		face[face_idx].vert[1].vertIndex = i + 2 + point_idx;
		face[face_idx].vert[2].vertIndex = face[face_idx].vert[1].vertIndex + (nSegment + 1);
		face[face_idx].vert[3].vertIndex = face[face_idx].vert[0].vertIndex + (nSegment + 1);
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 3;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];
		face[face_idx].vert[0].vertIndex = point_idx + (nSegment + 1) * 2 + 1;
		face[face_idx].vert[2].vertIndex = i + 2 + point_idx + (nSegment + 1);
		face[face_idx].vert[1].vertIndex = i + 1 + point_idx + (nSegment + 1);
	}

	/*************************************** CENTER TETRAHEDRON *****************************************/
	/********* CENTER TETRAHEDRON *********/
	// Initialize points
	point_idx += numCyVerts;
	pt[point_idx].set(-fSizeX2, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(-fSizeX2, fSizeY, fSizeZ);
	pt[point_idx + 2].set(-(fSizeX2 + distX), fSizeY, distZ);
	pt[point_idx + 3].set(-(fSizeX2 + distX), -fSizeY, distZ);
	pt[point_idx + 4].set(-fSizeX, fSizeY, 0);
	pt[point_idx + 5].set(-fSizeX, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	/********* LEFT TETRAHEDRON *********/
	// Initialize points
	point_idx += numTriVerts;
	pt[point_idx].set(-fSizeX2, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(-fSizeX2, fSizeY, fSizeZ);
	pt[point_idx + 2].set(fRadius * cos(startAngle) - (fSizeX2 + distX), fSizeY, fRadius * sin(startAngle) + distZ);
	pt[point_idx + 3].set(fRadius * cos(startAngle) - (fSizeX2 + distX), -fSizeY, fRadius * sin(startAngle) + distZ);
	pt[point_idx + 4].set(-(fSizeX2 + distX), fSizeY, distZ);
	pt[point_idx + 5].set(-(fSizeX2 + distX), -fSizeY, distZ);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	/********* RIGHT TETRAHEDRON *********/
	// Initialize points
	point_idx += numTriVerts;
	pt[point_idx].set(-(fSizeX2 + distX), -fSizeY, distZ);
	pt[point_idx + 1].set(-(fSizeX2 + distX), fSizeY, distZ);
	pt[point_idx + 2].set(fRadius * cos(startAngle + fAngle * nSegment) - (fSizeX2 + distX), fSizeY, fRadius * sin(startAngle + fAngle * nSegment) + distZ);
	pt[point_idx + 3].set(fRadius * cos(startAngle + fAngle * nSegment) - (fSizeX2 + distX), -fSizeY, fRadius * sin(startAngle + fAngle * nSegment) + distZ);
	pt[point_idx + 4].set(-fSizeX, fSizeY, 0);
	pt[point_idx + 5].set(-fSizeX, -fSizeY, 0);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 0;
}

//void Mesh::CreateShape4(float fSizeX1, float fSizeX2, float fSizeX3, float fSizeY, float fSizeZ1, float fSizeZ2, float fSizeZ3, float fRadius, int nSegment)
//{
//	int i, idx;
//	float x, y, z;
//
//	int numCuboidVerts = 8;
//	int numTriVerts = 6;
//	int numCircleVerts = 2 * (nSegment + 1) + 2;
//	numVerts = numCuboidVerts + numTriVerts * 2 + numCircleVerts;
//
//	pt = new Point3[numVerts];
//	pt[0].set(-fSizeX1, -fSizeY, -fSizeZ1);
//	pt[1].set(-fSizeX1, fSizeY, -fSizeZ1);
//	pt[2].set(-fSizeX1, -fSizeY, fSizeZ1);
//	pt[3].set(-fSizeX1, fSizeY, fSizeZ1);
//	pt[4].set(-fSizeX2, -fSizeY, fSizeZ2);
//	pt[5].set(-fSizeX2, fSizeY, fSizeZ2);
//	pt[6].set(-fSizeX3, -fSizeY, -fSizeZ3);
//	pt[7].set(-fSizeX3, fSizeY, -fSizeZ3);
//
//	int numCuboidFaces = 6;
//	int numTriFaces = 5;
//	int numCircleFaces = (nSegment + 1) * 3;
//	numFaces = numCuboidFaces + numTriFaces * 2 + numCircleFaces;
//	face = new Face[numFaces];
//
//	face[0].nVerts = 4;
//	face[0].vert = new VertexID[face[0].nVerts];
//	face[0].vert[0].vertIndex = 0;
//	face[0].vert[1].vertIndex = 1;
//	face[0].vert[2].vertIndex = 3;
//	face[0].vert[3].vertIndex = 2;
//	for (i = 0; i < face[0].nVerts; i++)
//		face[0].vert[i].colorIndex = 0;
//
//	face[1].nVerts = 4;
//	face[1].vert = new VertexID[face[1].nVerts];
//	face[1].vert[0].vertIndex = 2;
//	face[1].vert[1].vertIndex = 3;
//	face[1].vert[2].vertIndex = 5;
//	face[1].vert[3].vertIndex = 4;
//	for (i = 0; i < face[1].nVerts; i++)
//		face[1].vert[i].colorIndex = 1;
//
//	face[2].nVerts = 4;
//	face[2].vert = new VertexID[face[2].nVerts];
//	face[2].vert[0].vertIndex = 4;
//	face[2].vert[1].vertIndex = 5;
//	face[2].vert[2].vertIndex = 7;
//	face[2].vert[3].vertIndex = 6;
//	for (i = 0; i < face[2].nVerts; i++)
//		face[2].vert[i].colorIndex = 2;
//
//	face[3].nVerts = 4;
//	face[3].vert = new VertexID[face[3].nVerts];
//	face[3].vert[0].vertIndex = 6;
//	face[3].vert[1].vertIndex = 7;
//	face[3].vert[2].vertIndex = 1;
//	face[3].vert[3].vertIndex = 0;
//	for (i = 0; i < face[3].nVerts; i++)
//		face[3].vert[i].colorIndex = 3;
//
//	face[4].nVerts = 4;
//	face[4].vert = new VertexID[face[4].nVerts];
//	face[4].vert[0].vertIndex = 1;
//	face[4].vert[1].vertIndex = 3;
//	face[4].vert[2].vertIndex = 5;
//	face[4].vert[3].vertIndex = 7;
//	for (i = 0; i < face[4].nVerts; i++)
//		face[4].vert[i].colorIndex = 4;
//
//	face[5].nVerts = 4;
//	face[5].vert = new VertexID[face[5].nVerts];
//	face[5].vert[0].vertIndex = 0;
//	face[5].vert[1].vertIndex = 2;
//	face[5].vert[2].vertIndex = 4;
//	face[5].vert[3].vertIndex = 6;
//	for (i = 0; i < face[5].nVerts; i++)
//		face[5].vert[i].colorIndex = 5;
//
//	float fSizeZ4 = fSizeZ2 + 0.2;
//	float fSizeX4 = -fSizeX3 + 0.1;
//
//	float centerZ = (fSizeZ4 - fSizeZ3) / 2;
//	float centerX = -fSizeX4 + (fSizeX4 - fSizeX3);
//
//	fRadius = (fSizeZ4 + fSizeZ3) / 2;
//
//	pt[numCuboidVerts].set(-fSizeX2, -fSizeY, fSizeZ2);
//	pt[numCuboidVerts + 1].set(-fSizeX2, fSizeY, fSizeZ2);
//	pt[numCuboidVerts + 2].set(fSizeX4, -fSizeY, fSizeZ4);
//	pt[numCuboidVerts + 3].set(fSizeX4, fSizeY, fSizeZ4);
//	pt[numCuboidVerts + 4].set(centerX, -fSizeY, centerZ);
//	pt[numCuboidVerts + 5].set(centerX, fSizeY, centerZ);
//
//	face[numCuboidFaces].nVerts = 4;
//	face[numCuboidFaces].vert = new VertexID[face[numCuboidFaces].nVerts];
//	face[numCuboidFaces].vert[0].vertIndex = numCuboidVerts;
//	face[numCuboidFaces].vert[1].vertIndex = numCuboidVerts + 1;
//	face[numCuboidFaces].vert[2].vertIndex = numCuboidVerts + 3;
//	face[numCuboidFaces].vert[3].vertIndex = numCuboidVerts + 2;
//	for (int i = 0; i < face[numCuboidFaces].nVerts; i++)
//		face[numCuboidFaces].vert[i].colorIndex = 0;
//
//	face[numCuboidFaces + 1].nVerts = 4;
//	face[numCuboidFaces + 1].vert = new VertexID[face[numCuboidFaces + 1].nVerts];
//	face[numCuboidFaces + 1].vert[0].vertIndex = numCuboidVerts;
//	face[numCuboidFaces + 1].vert[1].vertIndex = numCuboidVerts + 1;
//	face[numCuboidFaces + 1].vert[2].vertIndex = numCuboidVerts + 5;
//	face[numCuboidFaces + 1].vert[3].vertIndex = numCuboidVerts + 4;
//	for (int i = 0; i < face[numCuboidFaces + 1].nVerts; i++)
//		face[numCuboidFaces + 1].vert[i].colorIndex = 0;
//
//	face[numCuboidFaces + 2].nVerts = 4;
//	face[numCuboidFaces + 2].vert = new VertexID[face[numCuboidFaces + 2].nVerts];
//	face[numCuboidFaces + 2].vert[0].vertIndex = numCuboidVerts + 2;
//	face[numCuboidFaces + 2].vert[1].vertIndex = numCuboidVerts + 3;
//	face[numCuboidFaces + 2].vert[2].vertIndex = numCuboidVerts + 5;
//	face[numCuboidFaces + 2].vert[3].vertIndex = numCuboidVerts + 4;
//	for (int i = 0; i < face[numCuboidFaces + 2].nVerts; i++)
//		face[numCuboidFaces + 2].vert[i].colorIndex = 0;
//
//	face[numCuboidFaces + 3].nVerts = 3;
//	face[numCuboidFaces + 3].vert = new VertexID[face[numCuboidFaces + 3].nVerts];
//	face[numCuboidFaces + 3].vert[0].vertIndex = numCuboidVerts;
//	face[numCuboidFaces + 3].vert[1].vertIndex = numCuboidVerts + 2;
//	face[numCuboidFaces + 3].vert[2].vertIndex = numCuboidVerts + 4;
//	for (int i = 0; i < face[numCuboidFaces + 3].nVerts; i++)
//		face[numCuboidFaces + 3].vert[i].colorIndex = 0;
//	
//	face[numCuboidFaces + 4].nVerts = 3;
//	face[numCuboidFaces + 4].vert = new VertexID[face[numCuboidFaces + 4].nVerts];
//	face[numCuboidFaces + 4].vert[0].vertIndex = numCuboidVerts + 1;
//	face[numCuboidFaces + 4].vert[1].vertIndex = numCuboidVerts + 3;
//	face[numCuboidFaces + 4].vert[2].vertIndex = numCuboidVerts + 5;
//	for (int i = 0; i < face[numCuboidFaces + 4].nVerts; i++)
//		face[numCuboidFaces + 4].vert[i].colorIndex = 0;
//
//
//	pt[numCuboidVerts + numTriVerts].set(-fSizeX2, -fSizeY, fSizeZ2);
//	pt[numCuboidVerts + numTriVerts + 1].set(-fSizeX2, fSizeY, fSizeZ2);
//	pt[numCuboidVerts + numTriVerts + 2].set(centerX, -fSizeY, centerZ);
//	pt[numCuboidVerts + numTriVerts + 3].set(centerX, fSizeY, centerZ);
//	pt[numCuboidVerts + numTriVerts + 4].set(-fSizeX3, -fSizeY, -fSizeZ3);
//	pt[numCuboidVerts + numTriVerts + 5].set(-fSizeX3, fSizeY, -fSizeZ3);
//
//	face[numCuboidFaces + numTriFaces].nVerts = 4;
//	face[numCuboidFaces + numTriFaces].vert = new VertexID[face[numCuboidFaces + numTriFaces].nVerts];
//	face[numCuboidFaces + numTriFaces].vert[0].vertIndex = numCuboidVerts;
//	face[numCuboidFaces + numTriFaces].vert[1].vertIndex = numCuboidVerts + numTriVerts + 1;
//	face[numCuboidFaces + numTriFaces].vert[2].vertIndex = numCuboidVerts + numTriVerts + 3;
//	face[numCuboidFaces + numTriFaces].vert[3].vertIndex = numCuboidVerts + numTriVerts + 2;
//	for (int i = 0; i < face[numCuboidFaces + numTriFaces].nVerts; i++)
//		face[numCuboidFaces + numTriFaces].vert[i].colorIndex = 0;
//
//	face[numCuboidFaces + numTriFaces + 1].nVerts = 4;
//	face[numCuboidFaces + numTriFaces + 1].vert = new VertexID[face[numCuboidFaces + numTriFaces + 1].nVerts];
//	face[numCuboidFaces + numTriFaces + 1].vert[0].vertIndex = numCuboidVerts;
//	face[numCuboidFaces + numTriFaces + 1].vert[1].vertIndex = numCuboidVerts + numTriVerts + 1;
//	face[numCuboidFaces + numTriFaces + 1].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
//	face[numCuboidFaces + numTriFaces + 1].vert[3].vertIndex = numCuboidVerts + numTriVerts + 4;
//	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 1].nVerts; i++)
//		face[numCuboidFaces + numTriFaces + 1].vert[i].colorIndex = 0;
//
//	face[numCuboidFaces + numTriFaces + 2].nVerts = 4;
//	face[numCuboidFaces + numTriFaces + 2].vert = new VertexID[face[numCuboidFaces + numTriFaces + 2].nVerts];
//	face[numCuboidFaces + numTriFaces + 2].vert[0].vertIndex = numCuboidVerts + numTriVerts + 2;
//	face[numCuboidFaces + numTriFaces + 2].vert[1].vertIndex = numCuboidVerts + numTriVerts + 3;
//	face[numCuboidFaces + numTriFaces + 2].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
//	face[numCuboidFaces + numTriFaces + 2].vert[3].vertIndex = numCuboidVerts + numTriVerts + 4;
//	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 2].nVerts; i++)
//		face[numCuboidFaces + numTriFaces + 2].vert[i].colorIndex = 0;
//
//	face[numCuboidFaces + numTriFaces + 3].nVerts = 3;
//	face[numCuboidFaces + numTriFaces + 3].vert = new VertexID[face[numCuboidFaces + numTriFaces + 3].nVerts];
//	face[numCuboidFaces + numTriFaces + 3].vert[0].vertIndex = numCuboidVerts;
//	face[numCuboidFaces + numTriFaces + 3].vert[1].vertIndex = numCuboidVerts + numTriVerts + 2;
//	face[numCuboidFaces + numTriFaces + 3].vert[2].vertIndex = numCuboidVerts + numTriVerts + 4;
//	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 3].nVerts; i++)
//		face[numCuboidFaces + numTriFaces + 3].vert[i].colorIndex = 0;
//	
//	face[numCuboidFaces + numTriFaces + 4].nVerts = 3;
//	face[numCuboidFaces + numTriFaces + 4].vert = new VertexID[face[numCuboidFaces + numTriFaces + 4].nVerts];
//	face[numCuboidFaces + numTriFaces + 4].vert[0].vertIndex = numCuboidVerts + numTriVerts + 1;
//	face[numCuboidFaces + numTriFaces + 4].vert[1].vertIndex = numCuboidVerts + numTriVerts + 3;
//	face[numCuboidFaces + numTriFaces + 4].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
//	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 4].nVerts; i++)
//		face[numCuboidFaces + numTriFaces + 4].vert[i].colorIndex = 0;
//
//	// float fStartAngle = acos(abs(-fSizeX2) / ((sqrt(fSizeX2 * fSizeX2 + fSizeY * fSizeY + fSizeZ2 * fSizeZ2) + 1)));
//
//	// float fAngle = acos(abs(centerX * -fSizeX2 + fSizeY * -fSizeY + centerZ * fSizeZ2) \
//	// 				/ (sqrt(centerX * centerX + fSizeY * fSizeY + centerZ * centerZ) \
//	// 				+ sqrt(fSizeX2 * fSizeX2 + fSizeY * fSizeY + fSizeZ2 * fSizeZ2)));
//	float fAngle = PI / nSegment;
//	int node = numCuboidVerts + numTriVerts * 2;
//	pt[node].set(centerX, fSizeY, centerZ);
//	for (i = 0; i < nSegment + 1; i++)
//	{
//		x = fRadius * cos(PI / 2 + fAngle * i) + centerX;
//		z = fRadius * sin(PI / 2 + fAngle * i) + centerZ;
//		y = fSizeY;
//		pt[i + 1 + node].set(x, y, z);
//
//		y = -fSizeY;
//		pt[i + 1 + nSegment + 1 + node].set(x, y, z);
//	}
//	pt[(nSegment + 1) * 2 + node + 1].set(centerX, -fSizeY, centerZ);
//
//	idx = numCuboidFaces + numTriFaces * 2;
//	for (i = 0; i < nSegment + 1; i++)
//	{
//		face[idx].nVerts = 3;
//		face[idx].vert = new VertexID[face[idx].nVerts];
//		face[idx].vert[0].vertIndex = node;
//
//		if (i < nSegment)
//			face[idx].vert[1].vertIndex = node + i + 2;
//		else
//			face[idx].vert[1].vertIndex = node;
//		face[idx].vert[2].vertIndex = node + i + 1;
//		idx++;
//	}
//
//	for (i = 0; i < nSegment + 1; i++)
//	{
//		face[idx].nVerts = 4;
//		face[idx].vert = new VertexID[face[idx].nVerts];
//
//		face[idx].vert[0].vertIndex = node + i + 1;
//		if (i < nSegment)
//			face[idx].vert[1].vertIndex = node + i + 2;
//		else
//			face[idx].vert[1].vertIndex = node + i;
//		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + (nSegment + 1);
//		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + (nSegment + 1);
//
//		idx++;
//	}
//
//	for (i = 0; i < nSegment + 1; i++)
//	{
//		face[idx].nVerts = 3;
//		face[idx].vert = new VertexID[face[idx].nVerts];
//		face[idx].vert[0].vertIndex = node + 2 * (nSegment + 1) + 1;
//
//		face[idx].vert[1].vertIndex = node + i + 2 + (nSegment + 1);
//		face[idx].vert[2].vertIndex = node + i + 1 + (nSegment + 1);
//		idx++;
//	}
//
//}

void Mesh::CreateShape5(float fSizeX, float fSizeY, float fSizeZ, int nSegment)
{
	int i;
	float x, y, z;
	int face_idx = -1, point_idx = 0;

	int numCyVerts = (nSegment + 1) * 2;
	numVerts = numCyVerts * 2;
	pt = new Point3[numVerts];

	int numCyFaces = nSegment * 2;
	numFaces = numCyFaces * 2 + 2;
	face = new Face[numFaces];

	float fAngle = PI / nSegment;
	float fRadius = fSizeX / 4;

	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(-PI/2 + fAngle * i);
		z = fRadius * sin(-PI/2 + fAngle * i);
		y = fSizeY;
		pt[i].set(x, y, z);

		y = -fSizeY;
		pt[i + (nSegment + 1)].set(x, y, z);
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 4;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];

		face[face_idx].vert[0].vertIndex = i;
		face[face_idx].vert[1].vertIndex = i + 1;
		face[face_idx].vert[2].vertIndex = face[face_idx].vert[1].vertIndex + (nSegment + 1);
		face[face_idx].vert[3].vertIndex = face[face_idx].vert[0].vertIndex + (nSegment + 1);
	}

	point_idx += numCyVerts;
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(PI / 2 + fAngle * i) - fSizeX;
		z = fRadius * sin(PI / 2 + fAngle * i);
		y = fSizeY;
		pt[i + point_idx].set(x, y, z);

		y = -fSizeY;
		pt[i + point_idx + (nSegment + 1)].set(x, y, z);
	}

	for (i = 0; i < nSegment; i++)
	{
		face[++face_idx].nVerts = 4;
		face[face_idx].vert = new VertexID[face[face_idx].nVerts];

		face[face_idx].vert[0].vertIndex = i + point_idx;
		face[face_idx].vert[1].vertIndex = i + 1 + point_idx;
		face[face_idx].vert[2].vertIndex = face[face_idx].vert[1].vertIndex + (nSegment + 1);
		face[face_idx].vert[3].vertIndex = face[face_idx].vert[0].vertIndex + (nSegment + 1);
	}

	int top_face_idx = face_idx + 1;
	int below_face_idx = face_idx + 2;

	face[top_face_idx].nVerts = numCyVerts;
	face[top_face_idx].vert = new VertexID[face[top_face_idx].nVerts];
	face[below_face_idx].nVerts = numCyVerts;
	face[below_face_idx].vert = new VertexID[face[below_face_idx].nVerts];

	int top_idx = -1;
	int below_idx = -1;
	for (i = 0; i < numCyVerts; i++)
	{
		if (i < (nSegment + 1))
			face[top_face_idx].vert[++top_idx].vertIndex = i;
		else
			face[below_face_idx].vert[++below_idx].vertIndex = i;
	}

	for (i = numCyVerts; i < numVerts; i++)
	{
		if (i < numCyVerts + (nSegment + 1))
			face[top_face_idx].vert[++top_idx].vertIndex = i;
		else
			face[below_face_idx].vert[++below_idx].vertIndex = i;
	}
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
