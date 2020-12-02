#include "Mesh.h"
#include <math.h>
#include <stdio.h>

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
								{1.0, 1.0, 1.0}};


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

void Mesh::CreateShape1(float fSizeX, float fSizeY, float fSizeZ, float zRange, int nSegment)
{	
	// TODO Ve tiep tuyen
	int numCyVerts = nSegment * 3 + 2;
	int numCubeVerts = 8;
	numVerts = numCyVerts + numCubeVerts;
	pt = new Point3[numVerts];

	int i;
	int idx;
	float fAngle = PI / 2 / nSegment;
	nSegment += 1;
	float x, y, z;

	float fSizeZ2 = fSizeZ - zRange;
	float fRadius = zRange;

	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(PI + fAngle * i) - fSizeX;
		z = fRadius * sin(PI + fAngle * i) + fSizeZ;
		y = fSizeY;
		pt[i + 1].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numCyVerts - 1].set(-fSizeX, -fSizeY, fSizeZ);

	int numCyFaces = (nSegment - 1) * 3;
	int numCubeFaces = 5;
	numFaces = numCyFaces + numCubeFaces;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = i + 2;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		face[idx].vert[1].vertIndex = i + 2;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numCyVerts - 1;
		face[idx].vert[2].vertIndex = i + 2 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

	pt[numCyVerts].set(fSizeX, -fSizeY, fSizeZ);
	pt[numCyVerts + 1].set(fSizeX, fSizeY, fSizeZ);
	pt[numCyVerts + 2].set(fSizeX, fSizeY, -fSizeZ);
	pt[numCyVerts + 3].set(fSizeX, -fSizeY, -fSizeZ);
	pt[numCyVerts + 4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[numCyVerts + 5].set(-fSizeX, fSizeY, fSizeZ);
	pt[numCyVerts + 6].set(-fSizeX, fSizeY, fSizeZ2);
	pt[numCyVerts + 7].set(-fSizeX, -fSizeY, fSizeZ2);

	face[numCyFaces].nVerts = 4;
	face[numCyFaces].vert = new VertexID[face[numCyFaces].nVerts];
	face[numCyFaces].vert[0].vertIndex = numCyVerts;
	face[numCyFaces].vert[1].vertIndex = numCyVerts + 1;
	face[numCyFaces].vert[2].vertIndex = numCyVerts + 2;
	face[numCyFaces].vert[3].vertIndex = numCyVerts + 3;
	for (int i = 0; i < face[numCyFaces].nVerts; i++)
		face[numCyFaces].vert[i].colorIndex = 0;

	// face[numCyFaces + 1].nVerts = 4;
	// face[numCyFaces + 1].vert = new VertexID[face[numCyFaces + 1].nVerts];
	// face[numCyFaces + 1].vert[0].vertIndex = numCyVerts + 4;
	// face[numCyFaces + 1].vert[1].vertIndex = numCyVerts + 5;
	// face[numCyFaces + 1].vert[2].vertIndex = numCyVerts + 6;
	// face[numCyFaces + 1].vert[3].vertIndex = numCyVerts + 7;
	// for (int i = 0; i < face[numCyFaces + 1].nVerts; i++)
	// 	face[numCyFaces + 1].vert[i].colorIndex = 0;

	face[numCyFaces + 1].nVerts = 4;
	face[numCyFaces + 1].vert = new VertexID[face[numCyFaces + 1].nVerts];
	face[numCyFaces + 1].vert[0].vertIndex = numCyVerts + 0;
	face[numCyFaces + 1].vert[1].vertIndex = numCyVerts + 1;
	face[numCyFaces + 1].vert[2].vertIndex = 1;
	face[numCyFaces + 1].vert[3].vertIndex = 1 + nSegment;
	for (int i = 0; i < face[numCyFaces + 1].nVerts; i++)
		face[numCyFaces + 1].vert[i].colorIndex = 0;

	face[numCyFaces + 2].nVerts = 4;
	face[numCyFaces + 2].vert = new VertexID[face[numCyFaces + 2].nVerts];
	face[numCyFaces + 2].vert[0].vertIndex = numCyVerts + 3;
	face[numCyFaces + 2].vert[1].vertIndex = numCyVerts + 2;
	face[numCyFaces + 2].vert[2].vertIndex = numCyVerts + 6;
	face[numCyFaces + 2].vert[3].vertIndex = numCyVerts + 7;
	for (int i = 0; i < face[numCyFaces + 2].nVerts; i++)
		face[numCyFaces + 2].vert[i].colorIndex = 0;

	face[numCyFaces + 3].nVerts = 4;
	face[numCyFaces + 3].vert = new VertexID[face[numCyFaces + 3].nVerts];
	face[numCyFaces + 3].vert[0].vertIndex = numCyVerts + 1;
	face[numCyFaces + 3].vert[1].vertIndex = numCyVerts + 2;
	face[numCyFaces + 3].vert[2].vertIndex = numCyVerts + 6;
	face[numCyFaces + 3].vert[3].vertIndex = numCyVerts + 5;
	for (int i = 0; i < face[numCyFaces + 3].nVerts; i++)
		face[numCyFaces + 3].vert[i].colorIndex = 0;

	face[numCyFaces + 4].nVerts = 4;
	face[numCyFaces + 4].vert = new VertexID[face[numCyFaces + 4].nVerts];
	face[numCyFaces + 4].vert[0].vertIndex = numCyVerts + 0;
	face[numCyFaces + 4].vert[1].vertIndex = numCyVerts + 3;
	face[numCyFaces + 4].vert[2].vertIndex = numCyVerts + 7;
	face[numCyFaces + 4].vert[3].vertIndex = numCyVerts + 4;
	for (int i = 0; i < face[numCyFaces + 4].nVerts; i++)
		face[numCyFaces + 4].vert[i].colorIndex = 0;

}

void Mesh::CreateShape2(float fSizeX, float fSizeX2, float fSizeY, float fSizeZ1, float fSizeZ2, float fSizeZ3, int nSegment){
	int numCyVerts1 = (nSegment + 1) * 2 + 2;
	int numCubeVerts = 8;
	int numTriangleVerts = 6;
	numVerts = numCyVerts1 * 2 + numCubeVerts * 2 + numTriangleVerts * 4;
	pt = new Point3[numVerts];

	int i;
	int idx;
	float fAngle = PI / nSegment;
	nSegment += 1;
	float x, y, z;

	float fRadius1 = fSizeZ2;

	pt[0].set(-fSizeX, fSizeY, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius1 * cos(PI / 2 + fAngle * i) - fSizeX;
		z = fRadius1 * sin(PI / 2 + fAngle * i);
		y = fSizeY;
		pt[i + 1].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numCyVerts1 - 1].set(-fSizeX, -fSizeY, 0);

	int numCyFaces = (nSegment - 1) * 3;
	int numCubeFaces = 6;
	int numTriangleFaces = 5;
	numFaces = numCyFaces * 2 + numCubeFaces * 2 + numTriangleFaces * 4;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = i + 2;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		face[idx].vert[1].vertIndex = i + 2;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numCyVerts1 - 1;
		face[idx].vert[2].vertIndex = i + 2 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

	// Mat ren ben trai
	pt[numCyVerts1].set(fSizeX, -fSizeY, fSizeZ1);
	pt[numCyVerts1 + 1].set(fSizeX, fSizeY, fSizeZ1);
	pt[numCyVerts1 + 2].set(fSizeX, fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 3].set(fSizeX, -fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 4].set(-fSizeX, -fSizeY, fSizeZ2);
	pt[numCyVerts1 + 5].set(-fSizeX, fSizeY, fSizeZ2);
	pt[numCyVerts1 + 6].set(-fSizeX, fSizeY, 0);
	pt[numCyVerts1 + 7].set(-fSizeX, -fSizeY, 0);

	face[numCyFaces].nVerts = 4;
	face[numCyFaces].vert = new VertexID[face[numCyFaces].nVerts];
	face[numCyFaces].vert[0].vertIndex = numCyVerts1;
	face[numCyFaces].vert[1].vertIndex = numCyVerts1 + 1;
	face[numCyFaces].vert[2].vertIndex = numCyVerts1 + 2;
	face[numCyFaces].vert[3].vertIndex = numCyVerts1 + 3;
	for (int i = 0; i < face[numCyFaces].nVerts; i++)
		face[numCyFaces].vert[i].colorIndex = 0;

	face[numCyFaces + 1].nVerts = 4;
	face[numCyFaces + 1].vert = new VertexID[face[numCyFaces + 1].nVerts];
	face[numCyFaces + 1].vert[0].vertIndex = numCyVerts1 + 4;
	face[numCyFaces + 1].vert[1].vertIndex = numCyVerts1 + 5;
	face[numCyFaces + 1].vert[2].vertIndex = numCyVerts1 + 6;
	face[numCyFaces + 1].vert[3].vertIndex = numCyVerts1 + 7;
	for (int i = 0; i < face[numCyFaces + 1].nVerts; i++)
		face[numCyFaces + 1].vert[i].colorIndex = 0;

	face[numCyFaces + 2].nVerts = 4;
	face[numCyFaces + 2].vert = new VertexID[face[numCyFaces + 2].nVerts];
	face[numCyFaces + 2].vert[0].vertIndex = numCyVerts1 + 0;
	face[numCyFaces + 2].vert[1].vertIndex = numCyVerts1 + 1;
	face[numCyFaces + 2].vert[2].vertIndex = numCyVerts1 + 5;
	face[numCyFaces + 2].vert[3].vertIndex = numCyVerts1 + 4;
	for (int i = 0; i < face[numCyFaces + 2].nVerts; i++)
		face[numCyFaces + 2].vert[i].colorIndex = 0;

	face[numCyFaces + 3].nVerts = 4;
	face[numCyFaces + 3].vert = new VertexID[face[numCyFaces + 3].nVerts];
	face[numCyFaces + 3].vert[0].vertIndex = numCyVerts1 + 3;
	face[numCyFaces + 3].vert[1].vertIndex = numCyVerts1 + 2;
	face[numCyFaces + 3].vert[2].vertIndex = numCyVerts1 + 6;
	face[numCyFaces + 3].vert[3].vertIndex = numCyVerts1 + 7;
	for (int i = 0; i < face[numCyFaces + 3].nVerts; i++)
		face[numCyFaces + 3].vert[i].colorIndex = 0;

	face[numCyFaces + 4].nVerts = 4;
	face[numCyFaces + 4].vert = new VertexID[face[numCyFaces + 4].nVerts];
	face[numCyFaces + 4].vert[0].vertIndex = numCyVerts1 + 1;
	face[numCyFaces + 4].vert[1].vertIndex = numCyVerts1 + 2;
	face[numCyFaces + 4].vert[2].vertIndex = numCyVerts1 + 6;
	face[numCyFaces + 4].vert[3].vertIndex = numCyVerts1 + 5;
	for (int i = 0; i < face[numCyFaces + 4].nVerts; i++)
		face[numCyFaces + 4].vert[i].colorIndex = 0;

	face[numCyFaces + 5].nVerts = 4;
	face[numCyFaces + 5].vert = new VertexID[face[numCyFaces + 5].nVerts];
	face[numCyFaces + 5].vert[0].vertIndex = numCyVerts1 + 0;
	face[numCyFaces + 5].vert[1].vertIndex = numCyVerts1 + 3;
	face[numCyFaces + 5].vert[2].vertIndex = numCyVerts1 + 7;
	face[numCyFaces + 5].vert[3].vertIndex = numCyVerts1 + 4;
	for (int i = 0; i < face[numCyFaces + 5].nVerts; i++)
		face[numCyFaces + 5].vert[i].colorIndex = 0;


	// Mat tren ben phai
	pt[numCyVerts1 + numCubeVerts].set(fSizeX, -fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + numCubeVerts + 1].set(fSizeX, fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + numCubeVerts + 2].set(fSizeX, fSizeY, -fSizeZ1);
	pt[numCyVerts1 + numCubeVerts + 3].set(fSizeX, -fSizeY, -fSizeZ1);
	pt[numCyVerts1 + numCubeVerts + 4].set(-fSizeX, -fSizeY, 0);
	pt[numCyVerts1 + numCubeVerts + 5].set(-fSizeX, fSizeY, 0);
	pt[numCyVerts1 + numCubeVerts + 6].set(-fSizeX, fSizeY, -fSizeZ2);
	pt[numCyVerts1 + numCubeVerts + 7].set(-fSizeX, -fSizeY, -fSizeZ2);

	face[numCyFaces + numCubeFaces].nVerts = 4;
	face[numCyFaces + numCubeFaces].vert = new VertexID[face[numCyFaces + numCubeFaces].nVerts];
	face[numCyFaces + numCubeFaces].vert[0].vertIndex = numCyVerts1 + numCubeVerts;
	face[numCyFaces + numCubeFaces].vert[1].vertIndex = numCyVerts1 + numCubeVerts + 1;
	face[numCyFaces + numCubeFaces].vert[2].vertIndex = numCyVerts1 + numCubeVerts + 2;
	face[numCyFaces + numCubeFaces].vert[3].vertIndex = numCyVerts1 + numCubeVerts + 3;
	for (int i = 0; i < face[numCyFaces + numCubeFaces].nVerts; i++)
		face[numCyFaces + numCubeFaces].vert[i].colorIndex = 0;

	face[numCyFaces + numCubeFaces + 1].nVerts = 4;
	face[numCyFaces + numCubeFaces + 1].vert = new VertexID[face[numCyFaces + numCubeFaces + 1].nVerts];
	face[numCyFaces + numCubeFaces + 1].vert[0].vertIndex = numCyVerts1 + numCubeVerts + 4;
	face[numCyFaces + numCubeFaces + 1].vert[1].vertIndex = numCyVerts1 + numCubeVerts + 5;
	face[numCyFaces + numCubeFaces + 1].vert[2].vertIndex = numCyVerts1 + numCubeVerts + 6;
	face[numCyFaces + numCubeFaces + 1].vert[3].vertIndex = numCyVerts1 + numCubeVerts + 7;
	for (int i = 0; i < face[numCyFaces + numCubeFaces + 1].nVerts; i++)
		face[numCyFaces + numCubeFaces + 1].vert[i].colorIndex = 0;

	face[numCyFaces + numCubeFaces + 2].nVerts = 4;
	face[numCyFaces + numCubeFaces + 2].vert = new VertexID[face[numCyFaces + numCubeFaces + 2].nVerts];
	face[numCyFaces + numCubeFaces + 2].vert[0].vertIndex = numCyVerts1 + numCubeVerts + 0;
	face[numCyFaces + numCubeFaces + 2].vert[1].vertIndex = numCyVerts1 + numCubeVerts + 1;
	face[numCyFaces + numCubeFaces + 2].vert[2].vertIndex = numCyVerts1 + numCubeVerts + 5;
	face[numCyFaces + numCubeFaces + 2].vert[3].vertIndex = numCyVerts1 + numCubeVerts + 4;
	for (int i = 0; i < face[numCyFaces + numCubeFaces + 2].nVerts; i++)
		face[numCyFaces + numCubeFaces + 2].vert[i].colorIndex = 0;

	face[numCyFaces + numCubeFaces + 3].nVerts = 4;
	face[numCyFaces + numCubeFaces + 3].vert = new VertexID[face[numCyFaces + numCubeFaces + 3].nVerts];
	face[numCyFaces + numCubeFaces + 3].vert[0].vertIndex = numCyVerts1 + numCubeVerts + 3;
	face[numCyFaces + numCubeFaces + 3].vert[1].vertIndex = numCyVerts1 + numCubeVerts + 2;
	face[numCyFaces + numCubeFaces + 3].vert[2].vertIndex = numCyVerts1 + numCubeVerts + 6;
	face[numCyFaces + numCubeFaces + 3].vert[3].vertIndex = numCyVerts1 + numCubeVerts + 7;
	for (int i = 0; i < face[numCyFaces + numCubeFaces + 3].nVerts; i++)
		face[numCyFaces + numCubeFaces + 3].vert[i].colorIndex = 0;

	face[numCyFaces + numCubeFaces + 4].nVerts = 4;
	face[numCyFaces + numCubeFaces + 4].vert = new VertexID[face[numCyFaces + numCubeFaces + 4].nVerts];
	face[numCyFaces + numCubeFaces + 4].vert[0].vertIndex = numCyVerts1 + numCubeVerts + 1;
	face[numCyFaces + numCubeFaces + 4].vert[1].vertIndex = numCyVerts1 + numCubeVerts + 2;
	face[numCyFaces + numCubeFaces + 4].vert[2].vertIndex = numCyVerts1 + numCubeVerts + 6;
	face[numCyFaces + numCubeFaces + 4].vert[3].vertIndex = numCyVerts1 + numCubeVerts + 5;
	for (int i = 0; i < face[numCyFaces + numCubeFaces + 4].nVerts; i++)
		face[numCyFaces + numCubeFaces + 4].vert[i].colorIndex = 0;

	face[numCyFaces + numCubeFaces + 5].nVerts = 4;
	face[numCyFaces + numCubeFaces + 5].vert = new VertexID[face[numCyFaces + numCubeFaces + 5].nVerts];
	face[numCyFaces + numCubeFaces + 5].vert[0].vertIndex = numCyVerts1 + numCubeVerts + 0;
	face[numCyFaces + numCubeFaces + 5].vert[1].vertIndex = numCyVerts1 + numCubeVerts + 3;
	face[numCyFaces + numCubeFaces + 5].vert[2].vertIndex = numCyVerts1 + numCubeVerts + 7;
	face[numCyFaces + numCubeFaces + 5].vert[3].vertIndex = numCyVerts1 + numCubeVerts + 4;
	for (int i = 0; i < face[numCyFaces + numCubeFaces + 5].nVerts; i++)
		face[numCyFaces + numCubeFaces + 5].vert[i].colorIndex = 0;


	// Mat tren chinh giua
	pt[numCyVerts1 + 2 * numCubeVerts].set(fSizeX, -fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + 1].set(fSizeX, fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + 2].set(fSizeX, fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + 3].set(fSizeX, -fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + 4].set(-fSizeX, fSizeY, 0);
	pt[numCyVerts1 + 2 * numCubeVerts + 5].set(-fSizeX, -fSizeY, 0);

	face[numCyFaces + 2 * numCubeFaces].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces].nVerts];
	face[numCyFaces + 2 * numCubeFaces].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts;
	face[numCyFaces + 2 * numCubeFaces].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + 1;
	face[numCyFaces + 2 * numCubeFaces].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + 2;
	face[numCyFaces + 2 * numCubeFaces].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + 3;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + 1].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + 1].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + 1].nVerts];
	face[numCyFaces + 2 * numCubeFaces + 1].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts;
	face[numCyFaces + 2 * numCubeFaces + 1].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + 1;
	face[numCyFaces + 2 * numCubeFaces + 1].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + 4;
	face[numCyFaces + 2 * numCubeFaces + 1].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + 1].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + 1].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + 2].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + 2].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + 2].nVerts];
	face[numCyFaces + 2 * numCubeFaces + 2].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + 2;
	face[numCyFaces + 2 * numCubeFaces + 2].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + 3;
	face[numCyFaces + 2 * numCubeFaces + 2].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + 5;
	face[numCyFaces + 2 * numCubeFaces + 2].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + 4;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + 2].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + 2].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + 3].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + 3].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + 3].nVerts];
	face[numCyFaces + 2 * numCubeFaces + 3].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + 1;
	face[numCyFaces + 2 * numCubeFaces + 3].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + 2;
	face[numCyFaces + 2 * numCubeFaces + 3].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + 4;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + 3].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + 3].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + 4].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + 4].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + 4].nVerts];
	face[numCyFaces + 2 * numCubeFaces + 4].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts;
	face[numCyFaces + 2 * numCubeFaces + 4].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + 3;
	face[numCyFaces + 2 * numCubeFaces + 4].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + 4].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + 4].vert[i].colorIndex = 0;


	// Can
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts].set(fSizeX, -fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 1].set(fSizeX, fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 2].set(fSizeX + fSizeX2, fSizeY, fSizeZ3);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 3].set(fSizeX + fSizeX2, -fSizeY, fSizeZ3);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 4].set(fSizeX + fSizeX2, fSizeY, 0);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 5].set(fSizeX + fSizeX2, -fSizeY, 0);

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 3;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 1].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 5;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 3;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 2].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 4;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 3].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces + 4].vert[i].colorIndex = 0;


	// Chinh giua
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2].set(fSizeX, -fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 1].set(fSizeX, fSizeY, fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 2].set(fSizeX, fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 3].set(fSizeX, -fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 4].set(fSizeX + fSizeX2, fSizeY, 0);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 5].set(fSizeX + fSizeX2, -fSizeY, 0);

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 3;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 1].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 2].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 4;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 3].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 2 + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 2 + 4].vert[i].colorIndex = 0;


	// Ben phai
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3].set(fSizeX, -fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 1].set(fSizeX, fSizeY, -fSizeZ1 / 2);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 2].set(fSizeX + fSizeX2, fSizeY, -fSizeZ3);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 3].set(fSizeX + fSizeX2, -fSizeY, -fSizeZ3);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 4].set(fSizeX + fSizeX2, fSizeY, 0);
	pt[numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 5].set(fSizeX + fSizeX2, -fSizeY, 0);

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 3;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 1].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].nVerts = 4;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 5;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].vert[3].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 4;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 2].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 1;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 2;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 4;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 3].vert[i].colorIndex = 0;

	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].nVerts = 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].vert = new VertexID[face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].nVerts];
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].vert[0].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].vert[1].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 3;
	face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].vert[2].vertIndex = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 3 + 5;
	for (int i = 0; i < face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].nVerts; i++)
		face[numCyFaces + 2 * numCubeFaces + numTriangleFaces * 3 + 4].vert[i].colorIndex = 0;


	int node = numCyVerts1 + 2 * numCubeVerts + numTriangleVerts * 4;

	pt[node].set(fSizeX + fSizeX2, fSizeY, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fSizeZ3 * cos(- PI / 2 + fAngle * i) + fSizeX + fSizeX2;
		z = fSizeZ3 * sin(- PI / 2 + fAngle * i);
		y = fSizeY;
		pt[i + 1 + node].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + node + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(fSizeX + fSizeX2, -fSizeY, 0);

	idx = numCyFaces + numCubeFaces * 2 + numTriangleFaces * 4;
	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = node;
		face[idx].vert[1].vertIndex = i + 2 + node;
		face[idx].vert[2].vertIndex = i + 1 + node;
		idx++;
	}

	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + node;
		face[idx].vert[1].vertIndex = i + 2 + node;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		face[idx].vert[2].vertIndex = i + 2 + nSegment + node;
		face[idx].vert[1].vertIndex = i + 1 + nSegment + node;
		idx++;
	}
}

void Mesh::CreateShape3(float fSizeX, float fSizeY, float fSizeXCut, float fSizeZ, float fRadius, int nSegment)
{
	int i, idx;
	float x, y, z;

	int numCuboidVerts = 8;
	int numTriVerts = 6;
	int numCyVerts = (nSegment + 1) * 2 + 2;
	numVerts = numCuboidVerts + numTriVerts + numTriVerts * 3 + numCyVerts;

	pt = new Point3[numVerts];
	pt[0].set(fSizeX, -fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(fSizeX, -fSizeY, -fSizeZ);
	pt[4].set(-fSizeXCut, -fSizeY, fSizeZ);
	pt[5].set(-fSizeXCut, fSizeY, fSizeZ);
	pt[6].set(-fSizeX, fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	int numCuboidFaces = 6;
	int numTriFaces = 5;
	int numCyFaces = (nSegment - 1) * 3;
	numFaces = numCuboidFaces + numTriFaces * 3 + numCyFaces;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 4;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 7;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 5;
	face[2].vert[3].vertIndex = 4;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 2;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 7;
	face[3].vert[3].vertIndex = 6;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 2;
	face[4].vert[2].vertIndex = 6;
	face[4].vert[3].vertIndex = 5;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[2].vertIndex = 7;
	face[5].vert[3].vertIndex = 4;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;


	float distanceX = fSizeX - fSizeXCut;
	float titleX = sqrt(distanceX * distanceX + (2 * fSizeZ) * (2 * fSizeZ));
	float angle = asin(fRadius / titleX) + asin(2 * fSizeZ / titleX);
	float edge = sqrt(titleX * titleX - fRadius * fRadius);

	float dX1 = edge * cos(angle) - fSizeX;
	float dZ1 = edge * sin(angle) -fSizeZ;

	float dX2 = edge * cos(angle + asin(fRadius / titleX)) - fSizeX;
	float dZ2 = edge * sin(angle + asin(fRadius / titleX)) - fSizeZ;

	pt[numCuboidVerts].set(dX1, -fSizeY, dZ1);
	pt[numCuboidVerts + 1].set(dX1, fSizeY, dZ1);
	pt[numCuboidVerts + 2].set(-fSizeX, -fSizeY, -fSizeZ);
	pt[numCuboidVerts + 3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[numCuboidVerts + 4].set(-fSizeXCut, -fSizeY, fSizeZ);
	pt[numCuboidVerts + 5].set(-fSizeXCut, fSizeY, fSizeZ);

	// Left triangle
	// face[numCuboidFaces].nVerts = 4;
	// face[numCuboidFaces].vert = new VertexID[face[numCuboidFaces].nVerts];
	// face[numCuboidFaces].vert[0].vertIndex = numCuboidVerts;
	// face[numCuboidFaces].vert[1].vertIndex = numCuboidVerts + 1;
	// face[numCuboidFaces].vert[2].vertIndex = numCuboidVerts + 3;
	// face[numCuboidFaces].vert[3].vertIndex = numCuboidVerts + 2;
	// for (i = 0; i < face[numCuboidFaces].nVerts; i++)
	// 	face[numCuboidFaces].vert[i].colorIndex = 0;

	face[numCuboidFaces + 1].nVerts = 4;
	face[numCuboidFaces + 1].vert = new VertexID[face[numCuboidFaces + 1].nVerts];
	face[numCuboidFaces + 1].vert[0].vertIndex = numCuboidVerts + 2;
	face[numCuboidFaces + 1].vert[1].vertIndex = numCuboidVerts + 3;
	face[numCuboidFaces + 1].vert[2].vertIndex = numCuboidVerts + 5;
	face[numCuboidFaces + 1].vert[3].vertIndex = numCuboidVerts + 4;
	for (i = 0; i < face[numCuboidFaces + 1].nVerts; i++)
		face[numCuboidFaces + 1].vert[i].colorIndex = 1;

	// face[numCuboidFaces + 2].nVerts = 4;
	// face[numCuboidFaces + 2].vert = new VertexID[face[numCuboidFaces + 2].nVerts];
	// face[numCuboidFaces + 2].vert[0].vertIndex = numCuboidVerts + 0;
	// face[numCuboidFaces + 2].vert[1].vertIndex = numCuboidVerts + 1;
	// face[numCuboidFaces + 2].vert[2].vertIndex = numCuboidVerts + 5;
	// face[numCuboidFaces + 2].vert[3].vertIndex = numCuboidVerts + 4;
	// for (i = 0; i < face[numCuboidFaces + 2].nVerts; i++)
	// 	face[numCuboidFaces + 2].vert[i].colorIndex = 2;

	face[numCuboidFaces + 3].nVerts = 3;
	face[numCuboidFaces + 3].vert = new VertexID[face[numCuboidFaces + 3].nVerts];
	face[numCuboidFaces + 3].vert[0].vertIndex = numCuboidVerts + 1;
	face[numCuboidFaces + 3].vert[1].vertIndex = numCuboidVerts + 3;
	face[numCuboidFaces + 3].vert[2].vertIndex = numCuboidVerts + 5;
	for (i = 0; i < face[numCuboidFaces + 3].nVerts; i++)
		face[numCuboidFaces + 3].vert[i].colorIndex = 3;

	face[numCuboidFaces + 4].nVerts = 3;
	face[numCuboidFaces + 4].vert = new VertexID[face[numCuboidFaces + 4].nVerts];
	face[numCuboidFaces + 4].vert[0].vertIndex = numCuboidVerts + 0;
	face[numCuboidFaces + 4].vert[1].vertIndex = numCuboidVerts + 2;
	face[numCuboidFaces + 4].vert[2].vertIndex = numCuboidVerts + 4;
	for (i = 0; i < face[numCuboidFaces + 4].nVerts; i++)
		face[numCuboidFaces + 4].vert[i].colorIndex = 3;


	// Right triangle
	pt[numCuboidVerts + numTriVerts].set(dX2, -fSizeY, dZ2);
	pt[numCuboidVerts + numTriVerts + 1].set(dX2, fSizeY, dZ2);
	pt[numCuboidVerts + numTriVerts + 2].set(-fSizeX, -fSizeY, -fSizeZ);
	pt[numCuboidVerts + numTriVerts + 3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[numCuboidVerts + numTriVerts + 4].set(dX1, -fSizeY, dZ1);
	pt[numCuboidVerts + numTriVerts + 5].set(dX1, fSizeY, dZ1);

	face[numCuboidFaces + numTriFaces].nVerts = 4;
	face[numCuboidFaces + numTriFaces].vert = new VertexID[face[numCuboidFaces + numTriFaces].nVerts];
	face[numCuboidFaces + numTriFaces].vert[0].vertIndex = numCuboidVerts + numTriVerts;
	face[numCuboidFaces + numTriFaces].vert[1].vertIndex = numCuboidVerts + numTriVerts + 1;
	face[numCuboidFaces + numTriFaces].vert[2].vertIndex = numCuboidVerts + numTriVerts + 3;
	face[numCuboidFaces + numTriFaces].vert[3].vertIndex = numCuboidVerts + numTriVerts + 2;
	for (i = 0; i < face[numCuboidFaces + numTriFaces].nVerts; i++)
		face[numCuboidFaces + numTriFaces].vert[i].colorIndex = 0;

	// face[numCuboidFaces + numTriFaces + 1].nVerts = 4;
	// face[numCuboidFaces + numTriFaces + 1].vert = new VertexID[face[numCuboidFaces + numTriFaces + 1].nVerts];
	// face[numCuboidFaces + numTriFaces + 1].vert[0].vertIndex = numCuboidVerts + numTriVerts + 2;
	// face[numCuboidFaces + numTriFaces + 1].vert[1].vertIndex = numCuboidVerts + numTriVerts + 3;
	// face[numCuboidFaces + numTriFaces + 1].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
	// face[numCuboidFaces + numTriFaces + 1].vert[3].vertIndex = numCuboidVerts + numTriVerts + 4;
	// for (i = 0; i < face[numCuboidFaces + numTriFaces + 1].nVerts; i++)
	// 	face[numCuboidFaces + numTriFaces + 1].vert[i].colorIndex = 1;

	// face[numCuboidFaces + numTriFaces + 2].nVerts = 4;
	// face[numCuboidFaces + numTriFaces + 2].vert = new VertexID[face[numCuboidFaces + numTriFaces + 2].nVerts];
	// face[numCuboidFaces + numTriFaces + 2].vert[0].vertIndex = numCuboidVerts + numTriVerts + 0;
	// face[numCuboidFaces + numTriFaces + 2].vert[1].vertIndex = numCuboidVerts + numTriVerts + 1;
	// face[numCuboidFaces + numTriFaces + 2].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
	// face[numCuboidFaces + numTriFaces + 2].vert[3].vertIndex = numCuboidVerts + numTriVerts + 4;
	// for (i = 0; i < face[numCuboidFaces + numTriFaces + 2].nVerts; i++)
	// 	face[numCuboidFaces + numTriFaces + 2].vert[i].colorIndex = 1;

	face[numCuboidFaces + numTriFaces + 3].nVerts = 3;
	face[numCuboidFaces + numTriFaces + 3].vert = new VertexID[face[numCuboidFaces + numTriFaces + 3].nVerts];
	face[numCuboidFaces + numTriFaces + 3].vert[0].vertIndex = numCuboidVerts + numTriVerts + 1;
	face[numCuboidFaces + numTriFaces + 3].vert[1].vertIndex = numCuboidVerts + numTriVerts + 3;
	face[numCuboidFaces + numTriFaces + 3].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
	for (i = 0; i < face[numCuboidFaces + numTriFaces + 3].nVerts; i++)
		face[numCuboidFaces + numTriFaces + 3].vert[i].colorIndex = 3;

	face[numCuboidFaces + numTriFaces + 4].nVerts = 3;
	face[numCuboidFaces + numTriFaces + 4].vert = new VertexID[face[numCuboidFaces + numTriFaces + 4].nVerts];
	face[numCuboidFaces + numTriFaces + 4].vert[0].vertIndex = numCuboidVerts + numTriVerts + 0;
	face[numCuboidFaces + numTriFaces + 4].vert[1].vertIndex = numCuboidVerts + numTriVerts + 2;
	face[numCuboidFaces + numTriFaces + 4].vert[2].vertIndex = numCuboidVerts + numTriVerts + 4;
	for (i = 0; i < face[numCuboidFaces + numTriFaces + 4].nVerts; i++)
		face[numCuboidFaces + numTriFaces + 4].vert[i].colorIndex = 3;



	// Circle
	float angle_x = acos(dX1 / sqrt(1 + dX1 * dX1 + fSizeX * fSizeX + dZ1 * dZ1));
	float fAngle = PI / nSegment;
	int node = numCuboidVerts + numTriVerts * 2;

	pt[node].set(dX1, fSizeY, dZ1);
	for (i = 0; i < nSegment - 1; i++)
	{
		x = fRadius * cos(angle_x - fAngle * (i - 2)) + dX1;
		z = fRadius * sin(angle_x - fAngle * (i - 2)) + dZ1;
		y = fSizeY;
		pt[i + 1 + node].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + node + nSegment].set(x, y, z);
	}
	pt[node + 2 * nSegment].set(dX1, -fSizeY, dZ1);

	idx = numCuboidFaces + numTriFaces * 2;
	for (i = 0; i < nSegment - 2; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = node;
		face[idx].vert[1].vertIndex = i + 2 + node;
		face[idx].vert[2].vertIndex = i + 1 + node;
		idx++;
	}

	for (i = 0; i < nSegment - 2; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = node + 2 * nSegment;
		face[idx].vert[2].vertIndex = i + 2 + nSegment + node;
		face[idx].vert[1].vertIndex = i + 1 + nSegment + node;
		idx++;
	}

	for (i = 0; i < nSegment - 2; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + node;
		face[idx].vert[1].vertIndex = i + 2 + node;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}


	node = numCuboidVerts + numTriVerts * 2 + numCyVerts;

	pt[node].set(-fSizeXCut, -fSizeY, fSizeZ);
	pt[node + 1].set(-fSizeXCut, fSizeY, fSizeZ);
	pt[node + 4].set(dX1, -fSizeY, dZ1);
	pt[node + 5].set(dX1, fSizeY, dZ1);

	idx -= 1;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces].nVerts = 3;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces].vert = new VertexID[face[numCuboidFaces + numTriFaces * 2 + numCyFaces].nVerts];
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces].vert[0].vertIndex = node;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces].vert[1].vertIndex = face[idx].vert[2].vertIndex;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces].vert[2].vertIndex = node + 4;
	for (i = 0; i < face[numCuboidFaces + numTriFaces * 2 + numCyFaces].nVerts; i++)
		face[numCuboidFaces + numTriFaces * 2 + numCyFaces].vert[i].colorIndex = 0;

	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].nVerts = 3;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].vert = new VertexID[face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].nVerts];
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].vert[0].vertIndex = node + 1;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].vert[1].vertIndex = node + 5;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].vert[2].vertIndex = face[idx].vert[1].vertIndex;
	for (i = 0; i < face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].nVerts; i++)
		face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 1].vert[i].colorIndex = 0;

	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].nVerts = 4;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].vert = new VertexID[face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].nVerts];
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].vert[0].vertIndex = node;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].vert[1].vertIndex = node + 1;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].vert[2].vertIndex = face[idx].vert[1].vertIndex;
	face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].vert[3].vertIndex = face[idx].vert[2].vertIndex;
	for (i = 0; i < face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].nVerts; i++)
		face[numCuboidFaces + numTriFaces * 2 + numCyFaces + 2].vert[i].colorIndex = 2;

}

void Mesh::CreateShape4(float fSizeX1, float fSizeX2, float fSizeX3, float fSizeY, float fSizeZ1, float fSizeZ2, float fSizeZ3, float fRadius, int nSegment)
{
	int i, idx;
	float x, y, z;

	int numCuboidVerts = 8;
	int numTriVerts = 6;
	int numCircleVerts = 2 * (nSegment + 1) + 2;
	numVerts = numCuboidVerts + numTriVerts * 2 + numCircleVerts;

	pt = new Point3[numVerts];
	pt[0].set(-fSizeX1, -fSizeY, -fSizeZ1);
	pt[1].set(-fSizeX1, fSizeY, -fSizeZ1);
	pt[2].set(-fSizeX1, -fSizeY, fSizeZ1);
	pt[3].set(-fSizeX1, fSizeY, fSizeZ1);
	pt[4].set(-fSizeX2, -fSizeY, fSizeZ2);
	pt[5].set(-fSizeX2, fSizeY, fSizeZ2);
	pt[6].set(-fSizeX3, -fSizeY, -fSizeZ3);
	pt[7].set(-fSizeX3, fSizeY, -fSizeZ3);

	int numCuboidFaces = 6;
	int numTriFaces = 5;
	int numCircleFaces = (nSegment + 1) * 3;
	numFaces = numCuboidFaces + numTriFaces * 2 + numCircleFaces;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 3;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 2;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 5;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 4;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 6;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 6;
	face[3].vert[1].vertIndex = 7;
	face[3].vert[2].vertIndex = 1;
	face[3].vert[3].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 3;
	face[4].vert[2].vertIndex = 5;
	face[4].vert[3].vertIndex = 7;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 4;
	face[5].vert[3].vertIndex = 6;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	float fSizeZ4 = fSizeZ2 + 0.2;
	float fSizeX4 = -fSizeX3 + 0.1;

	float centerZ = (fSizeZ4 - fSizeZ3) / 2;
	float centerX = -fSizeX4 + (fSizeX4 - fSizeX3);

	fRadius = (fSizeZ4 + fSizeZ3) / 2;

	pt[numCuboidVerts].set(-fSizeX2, -fSizeY, fSizeZ2);
	pt[numCuboidVerts + 1].set(-fSizeX2, fSizeY, fSizeZ2);
	pt[numCuboidVerts + 2].set(fSizeX4, -fSizeY, fSizeZ4);
	pt[numCuboidVerts + 3].set(fSizeX4, fSizeY, fSizeZ4);
	pt[numCuboidVerts + 4].set(centerX, -fSizeY, centerZ);
	pt[numCuboidVerts + 5].set(centerX, fSizeY, centerZ);

	face[numCuboidFaces].nVerts = 4;
	face[numCuboidFaces].vert = new VertexID[face[numCuboidFaces].nVerts];
	face[numCuboidFaces].vert[0].vertIndex = numCuboidVerts;
	face[numCuboidFaces].vert[1].vertIndex = numCuboidVerts + 1;
	face[numCuboidFaces].vert[2].vertIndex = numCuboidVerts + 3;
	face[numCuboidFaces].vert[3].vertIndex = numCuboidVerts + 2;
	for (int i = 0; i < face[numCuboidFaces].nVerts; i++)
		face[numCuboidFaces].vert[i].colorIndex = 0;

	face[numCuboidFaces + 1].nVerts = 4;
	face[numCuboidFaces + 1].vert = new VertexID[face[numCuboidFaces + 1].nVerts];
	face[numCuboidFaces + 1].vert[0].vertIndex = numCuboidVerts;
	face[numCuboidFaces + 1].vert[1].vertIndex = numCuboidVerts + 1;
	face[numCuboidFaces + 1].vert[2].vertIndex = numCuboidVerts + 5;
	face[numCuboidFaces + 1].vert[3].vertIndex = numCuboidVerts + 4;
	for (int i = 0; i < face[numCuboidFaces + 1].nVerts; i++)
		face[numCuboidFaces + 1].vert[i].colorIndex = 0;

	face[numCuboidFaces + 2].nVerts = 4;
	face[numCuboidFaces + 2].vert = new VertexID[face[numCuboidFaces + 2].nVerts];
	face[numCuboidFaces + 2].vert[0].vertIndex = numCuboidVerts + 2;
	face[numCuboidFaces + 2].vert[1].vertIndex = numCuboidVerts + 3;
	face[numCuboidFaces + 2].vert[2].vertIndex = numCuboidVerts + 5;
	face[numCuboidFaces + 2].vert[3].vertIndex = numCuboidVerts + 4;
	for (int i = 0; i < face[numCuboidFaces + 2].nVerts; i++)
		face[numCuboidFaces + 2].vert[i].colorIndex = 0;

	face[numCuboidFaces + 3].nVerts = 3;
	face[numCuboidFaces + 3].vert = new VertexID[face[numCuboidFaces + 3].nVerts];
	face[numCuboidFaces + 3].vert[0].vertIndex = numCuboidVerts;
	face[numCuboidFaces + 3].vert[1].vertIndex = numCuboidVerts + 2;
	face[numCuboidFaces + 3].vert[2].vertIndex = numCuboidVerts + 4;
	for (int i = 0; i < face[numCuboidFaces + 3].nVerts; i++)
		face[numCuboidFaces + 3].vert[i].colorIndex = 0;
	
	face[numCuboidFaces + 4].nVerts = 3;
	face[numCuboidFaces + 4].vert = new VertexID[face[numCuboidFaces + 4].nVerts];
	face[numCuboidFaces + 4].vert[0].vertIndex = numCuboidVerts + 1;
	face[numCuboidFaces + 4].vert[1].vertIndex = numCuboidVerts + 3;
	face[numCuboidFaces + 4].vert[2].vertIndex = numCuboidVerts + 5;
	for (int i = 0; i < face[numCuboidFaces + 4].nVerts; i++)
		face[numCuboidFaces + 4].vert[i].colorIndex = 0;


	pt[numCuboidVerts + numTriVerts].set(-fSizeX2, -fSizeY, fSizeZ2);
	pt[numCuboidVerts + numTriVerts + 1].set(-fSizeX2, fSizeY, fSizeZ2);
	pt[numCuboidVerts + numTriVerts + 2].set(centerX, -fSizeY, centerZ);
	pt[numCuboidVerts + numTriVerts + 3].set(centerX, fSizeY, centerZ);
	pt[numCuboidVerts + numTriVerts + 4].set(-fSizeX3, -fSizeY, -fSizeZ3);
	pt[numCuboidVerts + numTriVerts + 5].set(-fSizeX3, fSizeY, -fSizeZ3);

	face[numCuboidFaces + numTriFaces].nVerts = 4;
	face[numCuboidFaces + numTriFaces].vert = new VertexID[face[numCuboidFaces + numTriFaces].nVerts];
	face[numCuboidFaces + numTriFaces].vert[0].vertIndex = numCuboidVerts;
	face[numCuboidFaces + numTriFaces].vert[1].vertIndex = numCuboidVerts + numTriVerts + 1;
	face[numCuboidFaces + numTriFaces].vert[2].vertIndex = numCuboidVerts + numTriVerts + 3;
	face[numCuboidFaces + numTriFaces].vert[3].vertIndex = numCuboidVerts + numTriVerts + 2;
	for (int i = 0; i < face[numCuboidFaces + numTriFaces].nVerts; i++)
		face[numCuboidFaces + numTriFaces].vert[i].colorIndex = 0;

	face[numCuboidFaces + numTriFaces + 1].nVerts = 4;
	face[numCuboidFaces + numTriFaces + 1].vert = new VertexID[face[numCuboidFaces + numTriFaces + 1].nVerts];
	face[numCuboidFaces + numTriFaces + 1].vert[0].vertIndex = numCuboidVerts;
	face[numCuboidFaces + numTriFaces + 1].vert[1].vertIndex = numCuboidVerts + numTriVerts + 1;
	face[numCuboidFaces + numTriFaces + 1].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
	face[numCuboidFaces + numTriFaces + 1].vert[3].vertIndex = numCuboidVerts + numTriVerts + 4;
	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 1].nVerts; i++)
		face[numCuboidFaces + numTriFaces + 1].vert[i].colorIndex = 0;

	face[numCuboidFaces + numTriFaces + 2].nVerts = 4;
	face[numCuboidFaces + numTriFaces + 2].vert = new VertexID[face[numCuboidFaces + numTriFaces + 2].nVerts];
	face[numCuboidFaces + numTriFaces + 2].vert[0].vertIndex = numCuboidVerts + numTriVerts + 2;
	face[numCuboidFaces + numTriFaces + 2].vert[1].vertIndex = numCuboidVerts + numTriVerts + 3;
	face[numCuboidFaces + numTriFaces + 2].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
	face[numCuboidFaces + numTriFaces + 2].vert[3].vertIndex = numCuboidVerts + numTriVerts + 4;
	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 2].nVerts; i++)
		face[numCuboidFaces + numTriFaces + 2].vert[i].colorIndex = 0;

	face[numCuboidFaces + numTriFaces + 3].nVerts = 3;
	face[numCuboidFaces + numTriFaces + 3].vert = new VertexID[face[numCuboidFaces + numTriFaces + 3].nVerts];
	face[numCuboidFaces + numTriFaces + 3].vert[0].vertIndex = numCuboidVerts;
	face[numCuboidFaces + numTriFaces + 3].vert[1].vertIndex = numCuboidVerts + numTriVerts + 2;
	face[numCuboidFaces + numTriFaces + 3].vert[2].vertIndex = numCuboidVerts + numTriVerts + 4;
	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 3].nVerts; i++)
		face[numCuboidFaces + numTriFaces + 3].vert[i].colorIndex = 0;
	
	face[numCuboidFaces + numTriFaces + 4].nVerts = 3;
	face[numCuboidFaces + numTriFaces + 4].vert = new VertexID[face[numCuboidFaces + numTriFaces + 4].nVerts];
	face[numCuboidFaces + numTriFaces + 4].vert[0].vertIndex = numCuboidVerts + numTriVerts + 1;
	face[numCuboidFaces + numTriFaces + 4].vert[1].vertIndex = numCuboidVerts + numTriVerts + 3;
	face[numCuboidFaces + numTriFaces + 4].vert[2].vertIndex = numCuboidVerts + numTriVerts + 5;
	for (int i = 0; i < face[numCuboidFaces + numTriFaces + 4].nVerts; i++)
		face[numCuboidFaces + numTriFaces + 4].vert[i].colorIndex = 0;

	// float fStartAngle = acos(abs(-fSizeX2) / ((sqrt(fSizeX2 * fSizeX2 + fSizeY * fSizeY + fSizeZ2 * fSizeZ2) + 1)));

	// float fAngle = acos(abs(centerX * -fSizeX2 + fSizeY * -fSizeY + centerZ * fSizeZ2) \
	// 				/ (sqrt(centerX * centerX + fSizeY * fSizeY + centerZ * centerZ) \
	// 				+ sqrt(fSizeX2 * fSizeX2 + fSizeY * fSizeY + fSizeZ2 * fSizeZ2)));
	float fAngle = PI / nSegment;
	int node = numCuboidVerts + numTriVerts * 2;
	pt[node].set(centerX, fSizeY, centerZ);
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(PI / 2 + fAngle * i) + centerX;
		z = fRadius * sin(PI / 2 + fAngle * i) + centerZ;
		y = fSizeY;
		pt[i + 1 + node].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + nSegment + 1 + node].set(x, y, z);
	}
	pt[(nSegment + 1) * 2 + node + 1].set(centerX, -fSizeY, centerZ);

	idx = numCuboidFaces + numTriFaces * 2;
	for (i = 0; i < nSegment + 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = node;

		if (i < nSegment)
			face[idx].vert[1].vertIndex = node + i + 2;
		else
			face[idx].vert[1].vertIndex = node;
		face[idx].vert[2].vertIndex = node + i + 1;
		idx++;
	}

	for (i = 0; i < nSegment + 1; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = node + i + 1;
		if (i < nSegment)
			face[idx].vert[1].vertIndex = node + i + 2;
		else
			face[idx].vert[1].vertIndex = node + i;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + (nSegment + 1);
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + (nSegment + 1);

		idx++;
	}

	for (i = 0; i < nSegment + 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = node + 2 * (nSegment + 1) + 1;

		face[idx].vert[1].vertIndex = node + i + 2 + (nSegment + 1);
		face[idx].vert[2].vertIndex = node + i + 1 + (nSegment + 1);
		idx++;
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
