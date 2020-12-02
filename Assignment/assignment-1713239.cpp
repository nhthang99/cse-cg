#include <math.h>
#include <iostream>

#include <GL/glut.h>

#define PI 3.1415926
#define COLORNUM 14

using namespace std;

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Point3& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
	void set(Color3& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	} // constructor 2
	void set(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	float getX() { return x; }
	float getY() { return y; }
	void draw()
	{
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}

private:
	float x, y;
};
class IntRect
{
public:
	IntRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void draw()
	{
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int getWidth() { return (r - l); }
	int getHeight() { return (t - b); }

private:
	int l, r, b, t;
};

class RealRect
{
public:
	RealRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	float getWidth() { return (r - l); }
	float getHeight() { return (t - b); }
	void draw()
	{
		glRectf(l, b, r, t);
		glFlush();
	}; // draw this rectangle using OpenGL
private:
	float l, r, b, t;
};

class Vector3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	void flip()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}



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
	VertexID* vert;
	Vector3 facenorm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
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
	Point3* pt;

	int		numFaces;
	Face* face;

	float slideX, slideY, slideZ;
	float rotateX, rotateY, rotateZ;
	float scaleX, scaleY, scaleZ;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;

		slideX = 0;
		slideY = 0;
		slideZ = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		scaleX = 0;
		scaleY = 0;
		scaleZ = 0;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void Draw();
	void SetColor(int colorIdx);

	void CalculateFacesNorm();
	void SetupMaterial(float ambient[], float diffuse[], float specular[], float shiness);

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateShape1(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment);
	void CreateShape2(float fSizeX, float fSizeY, float fSizeZ, int nSegment);
	void CreateShape3(float fSizeX, float fSizeY, float fSizeZ, float fSizeX2, float fRadius, int nSegment);
	void CreateShape4(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment);
	void CreateShape5(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment);
};


float ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0},
								{0.0, 1.0, 0.0},
								{0.0, 0.0, 1.0}, // blue(2)
								{1.0, 1.0, 0.0},
								{1.0, 0.0, 1.0},
								{0.0, 1.0, 1.0},  // yello(5)
								{0.3, 0.3, 0.3},
								{0.5, 0.5, 0.5}, // gray(7)
								{0.9, 0.9, 0.9},
								{1.0, 0.5, 0.5},
								{0.5, 1.0, 0.5},
								{0.5, 0.5, 1.0},
								{0.0, 0.0, 0.0}, // black(12)
								{1.0, 1.0, 1.0} }; // white(13)


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
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 5;
	face[2].vert[3].vertIndex = 4;
	for (int i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 2;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 7;
	face[3].vert[3].vertIndex = 6;
	for (int i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 2;
	face[4].vert[2].vertIndex = 6;
	face[4].vert[3].vertIndex = 5;
	for (int i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[2].vertIndex = 7;
	face[5].vert[3].vertIndex = 4;
	for (int i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateShape1(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment)
{
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
	pt[point_idx + 6].set(fRadius * cos(PI + fAngle * nSegment) - fSizeX, fSizeY, fRadius * sin(PI + fAngle * nSegment) + fSizeZ);
	pt[point_idx + 7].set(fRadius * cos(PI + fAngle * nSegment) - fSizeX, -fSizeY, fRadius * sin(PI + fAngle * nSegment) + fSizeZ);

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
		face[face_idx].vert[i].colorIndex = 1;

	// Left face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = 1;
	face[face_idx].vert[3].vertIndex = nSegment + 2;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 2;

	// Right face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 3;

	// Top face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 4;

	// Bottom face of cuboid
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 5;
}

void Mesh::CreateShape2(float fSizeX, float fSizeY, float fSizeZ, int nSegment) {
	int numCyVerts = (nSegment + 1) * 2 + 2;
	int numCubeVerts = 8;
	int numTriangleVerts = 6;
	numVerts = numCyVerts * 2 + numCubeVerts * 2 + numTriangleVerts * 4;
	pt = new Point3[numVerts];

	int i;
	int face_idx = -1, point_idx;
	float x, y, z;

	float fSizeX2 = 3 * fSizeX / 2;
	float fSizeZ2 = 7 * fSizeZ / 8;

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
		face[face_idx].vert[i].colorIndex = 1;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 2;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 3;

	// Top face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 4;

	// Bottom face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 5;

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
		face[face_idx].vert[i].colorIndex = 6;

	// Rear face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 4;
	face[face_idx].vert[1].vertIndex = point_idx + 5;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 7;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 8;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 9;

	// Top face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 10;

	// Bottom face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 11;

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
		face[face_idx].vert[i].colorIndex = 12;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 13;

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
		face[face_idx].vert[i].colorIndex = 1;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 2;

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
		face[face_idx].vert[i].colorIndex = 3;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 4;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 4;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 5;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 6;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 7;


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
		face[face_idx].vert[i].colorIndex = 8;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 9;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 10;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 11;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 12;

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
		face[face_idx].vert[i].colorIndex = 13;

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
		face[face_idx].vert[i].colorIndex = 1;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 2;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 3;

	/*************************************** BOTTOM TETRAHEDRON *****************************************/
	// Ininitalize points
	point_idx += numTriangleVerts;
	pt[point_idx].set(fSizeX2, fSizeY, 0);
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fSizeZ3 * cos(-PI / 2 + fAngle * i) + fSizeX2;
		z = fSizeZ3 * sin(-PI / 2 + fAngle * i);
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

void Mesh::CreateShape3(float fSizeX, float fSizeY, float fSizeZ, float fSizeX2, float fRadius, int nSegment)
{
	int i;
	float x, y, z;
	int face_idx = -1, point_idx = 0;

	int numCuboidVerts = 8;
	int numTriVerts = 6;
	int numCyVerts = (nSegment + 1) * 2 + 2;
	numVerts = numCuboidVerts + numCyVerts + numTriVerts * 3;
	pt = new Point3[numVerts];

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
		face[face_idx].vert[i].colorIndex = 1;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 2;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 3;

	// Top face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 4;

	// Bottom face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 5;

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
		face[face_idx].vert[i].colorIndex = 6;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 7;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 8;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 9;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 10;

	/********* LEFT TETRAHEDRON *********/
	// Initialize points
	point_idx += numTriVerts;
	pt[point_idx].set(-fSizeX2, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(-fSizeX2, fSizeY, fSizeZ);
	pt[point_idx + 2].set(fRadius * cos(startAngle + fAngle * 3) - (fSizeX2 + distX), fSizeY, fRadius * sin(startAngle + fAngle * 3) + distZ);
	pt[point_idx + 3].set(fRadius * cos(startAngle + fAngle * 3) - (fSizeX2 + distX), -fSizeY, fRadius * sin(startAngle + fAngle * 3) + distZ);
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
		face[face_idx].vert[i].colorIndex = 11;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 12;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 13;

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
		face[face_idx].vert[i].colorIndex = 1;

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
		face[face_idx].vert[i].colorIndex = 2;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 3;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 4;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 5;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 6;
}

void Mesh::CreateShape4(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment)
{
	int i;
	float x, y, z;

	int face_idx = -1, point_idx = 0;

	int numCuboidVerts = 8;
	int numTriVerts = 6;
	int numCircleVerts = 2 * (nSegment + 1) + 2;
	numVerts = numCircleVerts + numCuboidVerts + numTriVerts * 2;
	pt = new Point3[numVerts];

	int numCuboidFaces = 6;
	int numTriFaces = 5;
	int numCircleFaces = nSegment * 3;
	numFaces = numCircleFaces + numCuboidFaces + numTriVerts * 2;
	face = new Face[numFaces];

	float fSizeX2 = fSizeX / 1.5;
	float fSizeZ2 = fSizeZ / 1.6;

	/*************************************** CYLINDER *****************************************/
	float distZ = (fSizeZ - fSizeZ2) / 7;
	float fZ = fSizeZ2 + 6 * distZ;
	float fHeightX = fSizeX2 + fSizeX2 / 2;

	float fHuyen = sqrt(fHeightX * fHeightX + fZ * fZ);
	float angle = asin(fHeightX / fHuyen) + asin(fRadius / fHuyen);

	float startAngle = PI - angle;
	float fAngle = 2 * angle / nSegment;

	pt[point_idx].set(-fHeightX, fSizeY, fZ);
	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(startAngle + fAngle * i) - fHeightX;
		z = fRadius * sin(startAngle + fAngle * i) + fZ;
		y = fSizeY;
		pt[i + 1 + point_idx].set(x, y, z);

		y = -fSizeY;
		pt[i + 1 + point_idx + (nSegment + 1)].set(x, y, z);
	}
	pt[point_idx + (nSegment + 1) * 2 + 1].set(-fHeightX, -fSizeY, fZ);

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

	/*************************************** BOTTOM CUBOID *****************************************/
	// Initialize points
	point_idx = numCircleVerts;
	pt[point_idx].set(0, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(0, fSizeY, fSizeZ);
	pt[point_idx + 2].set(0, fSizeY, 0);
	pt[point_idx + 3].set(0, -fSizeY, 0);
	pt[point_idx + 4].set(-fSizeX2, -fSizeY, fSizeZ);
	pt[point_idx + 5].set(-fSizeX2, fSizeY, fSizeZ);
	pt[point_idx + 6].set(fRadius * cos(startAngle + fAngle * nSegment) - fHeightX, fSizeY, fRadius * sin(startAngle + fAngle * nSegment) + fZ);
	pt[point_idx + 7].set(fRadius * cos(startAngle + fAngle * nSegment) - fHeightX, -fSizeY, fRadius * sin(startAngle + fAngle * nSegment) + fZ);

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
		face[face_idx].vert[i].colorIndex = 1;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 2;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 3;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 7;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 3;

	// Top face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 6;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 4;

	// Bottom face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 7;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 5;

	/*************************************** LEFT TOP TETRAHEDRON *****************************************/
	// Initialize points
	point_idx = numCircleVerts + numCuboidVerts;
	pt[point_idx].set(-fSizeX2, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(-fSizeX2, fSizeY, fSizeZ);
	pt[point_idx + 2].set(fRadius * cos(startAngle) - fHeightX, fSizeY, fRadius * sin(startAngle) + fZ);
	pt[point_idx + 3].set(fRadius * cos(startAngle) - fHeightX, -fSizeY, fRadius * sin(startAngle) + fZ);
	pt[point_idx + 4].set(-fHeightX, fSizeY, fZ);
	pt[point_idx + 5].set(-fHeightX, -fSizeY, fZ);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 6;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 7;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 8;

	// Top face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 1;
	face[face_idx].vert[1].vertIndex = point_idx + 2;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 9;

	// Bottom face
	face[++face_idx].nVerts = 3;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 10;

	/*************************************** RIGHT TOP TETRAHEDRON *****************************************/
	// Initialize points
	point_idx = numCircleVerts + numCuboidVerts + numTriVerts;
	pt[point_idx].set(-fSizeX2, -fSizeY, fSizeZ);
	pt[point_idx + 1].set(-fSizeX2, fSizeY, fSizeZ);
	pt[point_idx + 2].set(-fHeightX, fSizeY, fZ);
	pt[point_idx + 3].set(-fHeightX, -fSizeY, fZ);
	pt[point_idx + 4].set(fRadius * cos(startAngle + fAngle * nSegment) - fHeightX, fSizeY, fRadius * sin(startAngle + fAngle * nSegment) + fZ);
	pt[point_idx + 5].set(fRadius * cos(startAngle + fAngle * nSegment) - fHeightX, -fSizeY, fRadius * sin(startAngle + fAngle * nSegment) + fZ);

	// Frontal face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 2;
	face[face_idx].vert[3].vertIndex = point_idx + 3;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 11;

	// Left face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx;
	face[face_idx].vert[1].vertIndex = point_idx + 1;
	face[face_idx].vert[2].vertIndex = point_idx + 4;
	face[face_idx].vert[3].vertIndex = point_idx + 5;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 12;

	// Right face
	face[++face_idx].nVerts = 4;
	face[face_idx].vert = new VertexID[face[face_idx].nVerts];
	face[face_idx].vert[0].vertIndex = point_idx + 2;
	face[face_idx].vert[1].vertIndex = point_idx + 3;
	face[face_idx].vert[2].vertIndex = point_idx + 5;
	face[face_idx].vert[3].vertIndex = point_idx + 4;
	for (int i = 0; i < face[face_idx].nVerts; i++)
		face[face_idx].vert[i].colorIndex = 13;

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
		face[face_idx].vert[i].colorIndex = 1;
}

void Mesh::CreateShape5(float fSizeX, float fSizeY, float fSizeZ, float fRadius, int nSegment)
{
	int i;
	float x, y, z;
	int face_idx = -1, point_idx = 0;

	int numCyVerts = (nSegment + 1) * 2;
	numVerts = numCyVerts * 2;
	pt = new Point3[numVerts];

	int numCyFaces = nSegment * 2;
	numFaces = numCyFaces * 2 + 4;
	face = new Face[numFaces];

	float fAngle = PI / nSegment;

	for (i = 0; i < nSegment + 1; i++)
	{
		x = fRadius * cos(-PI / 2 + fAngle * i);
		z = fRadius * sin(-PI / 2 + fAngle * i);
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
	int left_face_idx = face_idx + 3;
	int right_face_idx = face_idx + 4;

	face[top_face_idx].nVerts = numCyVerts;
	face[top_face_idx].vert = new VertexID[face[top_face_idx].nVerts];
	face[below_face_idx].nVerts = numCyVerts;
	face[below_face_idx].vert = new VertexID[face[below_face_idx].nVerts];

	face[left_face_idx].nVerts = 4;
	face[left_face_idx].vert = new VertexID[face[left_face_idx].nVerts];
	face[right_face_idx].nVerts = 4;
	face[right_face_idx].vert = new VertexID[face[right_face_idx].nVerts];

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

	face[left_face_idx].vert[0].vertIndex = (nSegment + 1) - 1;
	face[left_face_idx].vert[1].vertIndex = 2 * (nSegment + 1) - 1;
	face[left_face_idx].vert[2].vertIndex = 3 * (nSegment + 1);
	face[left_face_idx].vert[3].vertIndex = 2 * (nSegment + 1);

	face[right_face_idx].vert[0].vertIndex = 0;
	face[right_face_idx].vert[1].vertIndex = (nSegment + 1);
	face[right_face_idx].vert[2].vertIndex = 4 * (nSegment + 1) - 1;
	face[right_face_idx].vert[3].vertIndex = 3 * (nSegment + 1) - 1;

}

void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float fX = 0, fY = 0, fZ = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			fX += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			fY += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			fZ += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(fX, fY, fZ);
		face[f].facenorm.normalize();
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

			// Uncomment this line to show every face unique color.
			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx)
{
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::Draw()
{
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}


// Screen size
int		screenWidth = 1200;
int		screenHeight = 600;

// Camera parameter
float camera_angle;
float camera_height;
float camera_dis;

float lookAt_X, lookAt_Y, lookAt_Z;

// Boolean feature
bool isView = false;
bool isFrame = false;
bool isLight = true;

Mesh	base;
Mesh 	shape1;
Mesh 	shape2;
Mesh 	shape3;
Mesh 	shape4;
Mesh	shape5;
Mesh	chot1;
Mesh	chot2;
Mesh	chot3;
Mesh	chot4;

int nSegment = 32;
float distanceLeftXBase = 1.0;
float distanceRightXBase = 1.5;

// Base size
float fSizeXBase = 7.0;
float fSizeYBase = 0.25;
float fSizeZBase = 1.6;

// Shape 1 size
float fSizeXShape1 = fSizeXBase / 2.0 - distanceLeftXBase / 2.0;
float fSizeYShape1 = fSizeYBase * 1.5;
float fSizeZShape1 = 0.65;
float fRadiusShape1 = 0.9;

// Shape 2 size
float fSizeXShape2 = 3.5;
float fSizeYShape2 = fSizeYBase * 1.5;
float fSizeZShape2 = 0.6;

// Shape 3 size
float fSizeXShape3 = fSizeXBase - distanceLeftXBase * 2;
float fSizeYShape3 = fSizeYBase * 1.5;
float fSizeZShape3 = 1.0;
float fSizeX2Shape3 = fSizeXShape3 / 1.5;
float fRadiusShape3 = 0.45;

// Shape 4 size
float fSizeXShape4 = 4.0;
float fSizeYShape4 = fSizeYBase * 1.5;
float fSizeZShape4 = 2.4;
float fRadiusShape4 = 0.6;

// Shape 5 size
float fSizeXShape5 = 1.8;
float fSizeYShape5 = fSizeYBase * 1.5;
float fSizeZShape5 = 2.0;
float fRadiusShape5 = fSizeXShape5 / 3.2;

// Chot size
float fHeightChot = fSizeYBase * 6 + 0.2;
float fRadiusChot = 0.2;

// Chot 2 translation
float fSizeX2 = fSizeXShape4 / 1.5;
float fHeightX = fSizeX2 + fSizeX2 / 2;

float fSizeZ2 = fSizeZShape4 / 1.6;
float distZ = (fSizeZShape4 - fSizeZ2) / 7;
float fZ = fSizeZ2 + 6 * distZ;
float fXTranslateChot2 = (fSizeXBase - distanceRightXBase) - fZ;

void drawAxis()
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}

void makeBackground(float fSizeX, float fSizeZ, float fRadius, float fSizeY = 0, float alpha = 0.7) {
	int mode = GL_QUADS;
	if (isFrame) {
		mode = GL_LINE_LOOP;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(mode);
	glColor4f(0.6f, 0.6f, 0.6f, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + 2 * fRadius / 3);
	glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + fRadius / 3);
	glVertex3f(fSizeX + fRadius / 2, fSizeY, fSizeZ + fRadius / 2);
	glVertex3f(fSizeX + 1.8 * fRadius / 3, fSizeY, fSizeZ + 2.4 * fRadius / 3);
	glEnd();

	glBegin(mode);
	glColor4f(0.6f, 0.6f, 0.6f, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + 2 * fRadius / 3);
	glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + fRadius / 3);
	glVertex3f(fSizeX + fRadius / 2, fSizeY, fSizeZ + fRadius / 2);
	glVertex3f(fSizeX + 1.8 * fRadius / 3, fSizeY, fSizeZ + 2.4 * fRadius / 3);
	glEnd();

	glBegin(mode);
	glColor4f(0.6f, 0.6f, 0.6f, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(fSizeX + fRadius / 2, fSizeY, fSizeZ + fRadius / 2);
	glVertex3f(fSizeX + 2 * fRadius / 3, fSizeY, fSizeZ);
	glVertex3f(fSizeX + fRadius / 3, fSizeY, fSizeZ);
	glVertex3f(fSizeX + 0.6 * fRadius / 3, fSizeY, fSizeZ + 1.2 * fRadius / 3);
	glEnd();

	glBegin(mode);
	glColor4f(0.6f, 0.6f, 0.6f, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(fSizeX, fSizeY, fSizeZ + fRadius / 3);
	glVertex3f(fSizeX + 0.6 * fRadius / 3, fSizeY, fSizeZ + 1.2 * fRadius / 3);
	glVertex3f(fSizeX + 0.3 * fRadius / 3, fSizeY, fSizeZ + 2.1 * fRadius / 3);
	glVertex3f(fSizeX, fSizeY, fSizeZ + 2 * fRadius / 3);
	glEnd();

	glBegin(mode);
	glColor4f(0.6f, 0.6f, 0.6f, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(fSizeX + 0.3 * fRadius / 3, fSizeY, fSizeZ + 2.1 * fRadius / 3);
	glVertex3f(fSizeX + 0.6 * fRadius / 3, fSizeY, fSizeZ + 1.2 * fRadius / 3);
	glVertex3f(fSizeX, fSizeY, fSizeZ + fRadius / 3);
	glVertex3f(fSizeX, fSizeY, fSizeZ + 2 * fRadius / 3);
	glEnd();

	glBegin(mode);
	glColor4f(0.6f, 0.6f, 0.6f, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(fSizeX + 2 * fRadius / 3, fSizeY, fSizeZ + fRadius);
	glVertex3f(fSizeX + 1.8 * fRadius / 3, fSizeY, fSizeZ + 2.4 * fRadius / 3);
	glVertex3f(fSizeX + 0.9 * fRadius / 3, fSizeY, fSizeZ + 2.7 * fRadius / 3);
	glVertex3f(fSizeX + fRadius / 3, fSizeY, fSizeZ + fRadius);
	glEnd();

	glBegin(mode);
	glColor4f(0.6f, 0.6f, 0.6f, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(fSizeX + 0.9 * fRadius / 3, fSizeY, fSizeZ + 2.7 * fRadius / 3);
	glVertex3f(fSizeX + 0.75 * fRadius / 3, fSizeY, fSizeZ + 2.25 * fRadius / 3);
	glVertex3f(fSizeX + 0.3 * fRadius / 3, fSizeY, fSizeZ + 2.1 * fRadius / 3);
	glVertex3f(fSizeX, fSizeY, fSizeZ + fRadius);
	glEnd();

}

void drawSmallPart(int fRadius)
{
	for (int fX = 0; fX < 2; fX += fRadius) {
		for (int fZ = 0; fZ < 2; fZ += fRadius) {
			glTranslatef(-fRadius / 2, 0, -fRadius / 2);
			glRotatef((fX % 2) * 180 + (fZ % 2) * 90, 0, 1, 0);
			glTranslatef(fRadius / 2, 0, fRadius / 2);
			makeBackground(fZ / 2, fX / 2, fRadius, 0);
			//makeBackground(fZ / 2, fX / 2, fRadius, -0.01);
		}
	}
}

void drawBackground(float alpha, float fSizeY = -0.005, int fRadius = 1) {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);

	/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(-200, fSizeY, -200);
	glVertex3f(-200, fSizeY, 200);
	glVertex3f(200, fSizeY, 200);
	glVertex3f(200, fSizeY, -200);

	glEnd();*/

	for (int idx_i = 0; idx_i < 3; idx_i++) {
		glTranslatef(0, 0, 20 * idx_i);
		for (int idx_k = -10; idx_k < 10; idx_k++) {
			glTranslatef(0, 0, 2 * idx_k);
			for (int idx_j = -5; idx_j < 12; idx_j++) {
				glTranslatef(2 * idx_j, 0, 0);
				drawSmallPart(fRadius);
			}
		}
	}
	glEnable(GL_LIGHTING);
}

void drawBase()
{
	glPushMatrix();

	glTranslated(0, fSizeYBase, 0);

	// Red material
	GLfloat diffuse[] = { 0.5, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	base.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		base.DrawWireframe();
	else
		base.Draw();

	glPopMatrix();
}

void drawShape1()
{
	glPushMatrix();

	float distXShape3 = fSizeXShape3 - fSizeX2Shape3;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;

	float translateXright = fSizeXShape1 + fRadiusShape1;
	float translateXleft = distanceLeftXBase + distXShape3 / 2 + halfXShape1;

	glTranslated(translateXright - translateXleft, fSizeYBase * 2 + fSizeZShape1 + fSizeZShape3, -fSizeYShape1);
	glRotatef(90, 1, 0, 0);

	// Pink material
	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape1.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape1.DrawWireframe();
	else
		shape1.Draw();

	glPopMatrix();
}

void drawShape2()
{
	glPushMatrix();

	float distBaseY = 2 * fSizeYBase + fSizeZShape2;
	float fRadiusShape2 = 7 * fSizeZShape2 / 8;
	float fSizeX2Shape2 = 3 * fSizeXShape2 / 2;
	float fSizeZ3Shape2 = fSizeZShape2 / 2;

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;

	float distX = halfXShape1 - (halfDistXShape3 + distanceLeftXBase) - fRadiusShape5 * 2;

	float lengthX = fRadiusShape2 + fSizeXShape2 + fSizeX2Shape2 + fSizeZ3Shape2 * 2;
	float centerX = lengthX / 2;

	float fRotateAngle = -15;
	float fTranslateAfterRotate = centerX * sin(-fRotateAngle / 180) + fRadiusShape2;

	glTranslated(fSizeXShape2 + fRadiusShape2 + distX, distBaseY + fSizeZShape3 + fSizeXShape5 + fTranslateAfterRotate, -fSizeYShape2);
	glRotatef(-90, 1, 0, 0);
	glRotatef(fRotateAngle, 0, 1, 0);

	//glTranslatef(-distX - centerX + fXTranslateChot2, 0, 0);
	glRotatef(chot2.rotateY, 0, 1, 0);
	//glTranslatef(-(-distX - centerX + fXTranslateChot2), 0, 0);

	// Pink material
	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape2.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape2.DrawWireframe();
	else
		shape2.Draw();

	glPopMatrix();
}

void drawShape3()
{
	glPushMatrix();

	glTranslated(-(fSizeXShape3 + distanceLeftXBase), 2 * fSizeYBase, fSizeYShape3);
	glRotatef(180, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);

	// Green material
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape3.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape3.DrawWireframe();
	else
		shape3.Draw();

	glPopMatrix();
}

void drawShape4()
{
	glPushMatrix();

	glTranslated(fSizeXBase - distanceRightXBase, 2 * fSizeYBase, fSizeYShape4);
	glRotatef(-90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	// Green material
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape4.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape4.DrawWireframe();
	else
		shape4.Draw();

	glPopMatrix();
}

void drawShape5()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;
	float Z = halfXShape1 - (halfDistXShape3 + distanceLeftXBase);

	glTranslated(-fRadiusShape5 + Z, fSizeYBase * 2 + fRadiusShape5 + fSizeZShape3, fSizeYShape5);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);

	// Gold material
	GLfloat diffuse[] = { 0.780392, 0.568627, 0.113725, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape5.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape5.DrawWireframe();
	else
		shape5.Draw();

	glPopMatrix();
}

void drawChot1()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float distZ = 1.5 * fSizeZShape3;

	glTranslated(-(halfDistXShape3 + distanceLeftXBase), 2 * fSizeYBase + distZ, 0);
	glRotatef(-90, 1, 0, 0);

	// Black material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot1.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot1.DrawWireframe();
	else
		chot1.Draw();

	glPopMatrix();
}

void drawChot2()
{
	glPushMatrix();

	glTranslated(fXTranslateChot2, 2 * fSizeYBase + fHeightX, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(chot2.rotateY, 0, 1, 0);

	// Black material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot2.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot2.DrawWireframe();
	else
		chot2.Draw();

	glPopMatrix();
}

void drawChot3()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;
	float Z = halfXShape1 - (halfDistXShape3 + distanceLeftXBase);

	glTranslated(Z - fRadiusShape5, 2 * fSizeYBase + fSizeZShape3 + fRadiusShape5 + fSizeXShape5, 0);
	glRotatef(-90, 1, 0, 0);

	// Black material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot3.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot3.DrawWireframe();
	else
		chot3.Draw();

	glPopMatrix();
}

void drawChot4()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;
	float Z = halfXShape1 - (halfDistXShape3 + distanceLeftXBase);

	glTranslated(Z - fRadiusShape5, 2 * fSizeYBase + fSizeZShape3 + fRadiusShape5, 0);
	glRotatef(-90, 1, 0, 0);

	// Black material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot4.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot4.DrawWireframe();
	else
		chot4.Draw();

	glPopMatrix();
}

void drawAllItems()
{
	//drawAxis();
	drawBase();
	drawShape1();
	drawShape2();
	drawShape3();
	drawShape4();
	drawShape5();
	drawChot1();
	drawChot2();
	drawChot3();
	drawChot4();
}

void myDisplay()
{
	// Clear parameter
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	// Turn on/off light mode
	if (isLight)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float camera_X = camera_dis * sinf(camera_angle * PI / 180); // camera respect to X-dimentional
	float camera_Y = camera_height; // camera respect to Y-dimentional
	float camera_Z = camera_dis * cosf(camera_angle * PI / 180); // // camera respect to Z-dimentional

	// Change view mode
	if (isView) {
		gluLookAt(0, 1, 15, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 1);
	}
	else if (camera_dis == 0)
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sin(camera_angle * PI / 180), 0, cos(camera_angle * PI / 180));
	else
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);

	// Setup view port
	glViewport(0, 0, screenWidth, screenHeight);

	// Clear the stencil buffers
	glClearStencil(0);
	// Clear depth
	glClearDepth(1.0f);

	// Draw all items
	drawAllItems();

	// No update color and depth
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	/* Draw 1 into the stencil buffer. */
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// Draw background
	drawBackground(1.0f);

	// Update of color and depth
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	// Only render where stencil is set to 1
	glStencilFunc(GL_EQUAL, 1, 2);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	// Draw the cube, reflected vertically, at all pixels where the stencil
	glPushMatrix();
	glScalef(1, -1, 1);
	drawAllItems();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw reflected background
	drawBackground(0.7f);

	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	isLight = true;

	camera_angle = -10.0;  // Góc quay camera xung quanh trục Oy
	camera_height = 6.0; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 15.0;	// Khoảng cách đến trục Oy

	// Look parameter
	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	// Clear color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Light model
	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Light parameter
	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
}

void createItem()
{
	// Base
	base.CreateCuboid(fSizeXBase, fSizeYBase, fSizeZBase);
	base.SetColor(7);
	base.CalculateFacesNorm();

	// Shape 1
	shape1.CreateShape1(fSizeXShape1, fSizeYShape1, fSizeZShape1, fRadiusShape1, nSegment);
	shape1.SetColor(1);
	shape1.CalculateFacesNorm();

	// Shape 2
	shape2.CreateShape2(fSizeXShape2, fSizeYShape2, fSizeZShape2, nSegment);
	shape2.SetColor(2);
	shape2.CalculateFacesNorm();

	// Shape 3
	shape3.CreateShape3(fSizeXShape3, fSizeYShape3, fSizeZShape3, fSizeX2Shape3, fRadiusShape3, nSegment);
	shape3.SetColor(3);
	shape3.CalculateFacesNorm();

	// Shape 4
	shape4.CreateShape4(fSizeXShape4, fSizeYShape4, fSizeZShape4, fRadiusShape4, nSegment);
	shape4.SetColor(4);
	shape4.CalculateFacesNorm();

	// Shape 5
	shape5.CreateShape5(fSizeXShape5, fSizeYShape5, fSizeZShape5, fRadiusShape5, nSegment);
	shape5.SetColor(5);
	shape5.CalculateFacesNorm();

	// Chot 1
	chot1.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot1.SetColor(6);
	chot1.CalculateFacesNorm();

	// Chot 2
	chot2.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot2.SetColor(7);
	chot2.CalculateFacesNorm();

	// Chot 3
	chot3.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot3.SetColor(8);
	chot3.CalculateFacesNorm();

	// Chot 4
	chot4.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot4.SetColor(9);
	chot4.CalculateFacesNorm();
}

void printInstruction()
{
	cout << "1, 2: Xoay can dao" << endl
		<< "W, w : Chuyen doi qua lai giua che do khung day va to mau" << endl
		<< "V, v : Chuyen doi qua lai giua hai che do nhin khac nhau" << endl
		<< "+ : Tang khoang cach camera" << endl
		<< "- : Giam khoang cach camera" << endl
		<< "up arrow : Tang chieu cao camera" << endl
		<< "down arrow : Giam chieu cao camera" << endl
		<< "< -: Quay camera theo chieu kim dong ho" << endl
		<< "-> : Quay camera nguoc chieu kim dong ho" << endl
		<< "D, d : Bat / tat nguon sang thu 2" << endl;
}

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.25;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.25;
		break;
	case GLUT_KEY_LEFT:
		camera_angle += 2;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle -= 2;
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		chot2.rotateY -= 1;
		break;
	case '2':
		chot2.rotateY += 1;
		break;
	case 'w':
	case 'W':
		isFrame = !isFrame;
		break;
	case 'v':
	case 'V':
		isView = !isView;
		if (isView)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-16, 16, -8, 8, -1000, 1000);
			break;
		}
		else
		{
			myInit();
			break;
		}
	case 'd':
	case 'D':
		isLight = !isLight;
		break;
	case '+':
		camera_dis += 0.25;
		break;
	case '-':
		camera_dis -= 0.25;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); //set window position on screen
	glutCreateWindow("Nguyen Huu Thang - 1713239"); //open the screen window

	printInstruction();

	createItem();
	myInit();

	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKeyboard);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();
	return 0;
}

