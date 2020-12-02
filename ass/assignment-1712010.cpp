
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846
#define COLORNUM 14
#define NUM 36

using namespace std;

bool isV = false;

// supportClass
#pragma region
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
#pragma endregion

// Mesh
#pragma region
class VertexID
{
public:
	int vertIndex;
	int colorIndex;
};

class Face
{
public:
	int nVerts;
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
	int numVerts;
	Point3* pt;

	int numFaces;
	Face* face;

	float rotateX, rotateY, rotateZ;
	float scaleX, scaleY, scaleZ;
	float translateX, translateY, translateZ;

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
		//

		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		scaleX = 0;
		scaleY = 0;
		scaleZ = 0;
		translateX = 0;
		translateY = 0;
		translateZ = 0;

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
	void SetColor(int colorIdx);
	// Lab 2
	void CreateTetrahedron();
	void CreateCube(float fSize);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	// Lab 3
	void CreateCylinderHollow(int nSegment, float fHeight, float fRadiusO, float fRadiusI);
	void CreateCylinder(int N, float baseHeight, float baseRadius);
	void CreateRectangleHollow(int nSegment, float fLong, float fHeight, float fWidth, float fRadius);
	void CreateRectangleGrooveUp(float fLong, float fWidth, float fHeight, float fBigBottomG, float fSmallBottomG, float fHeightG);
	void CreateRectangleGroove(float fLong, float fWidth, float fHeight, float fBigBottomG, float fSmallBottomG, float fHeightG);
	// Lab 5
	void CalculateFacesNorm();
	void Draw();
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
};

float ColorArr[COLORNUM][3] = {
	{1.0, 0.0, 0.0}, //0
	{0.0, 1.0, 0.0}, //1
	{0.0, 0.0, 1.0}, //2
	{1.0, 1.0, 0.0}, //3
	{1.0, 0.0, 1.0}, //4
	{0.0, 1.0, 1.0}, //5
	{0.3, 0.3, 0.3}, //6
	{0.5, 0.5, 0.5}, //7
	{0.9, 0.9, 0.9}, //8
	{1.0, 0.5, 0.5}, //9
	{0.5, 1.0, 0.5}, //10
	{0.5, 0.5, 1.0}, //11
	{0.0, 0.0, 0.0}, //12
	{1.0, 1.0, 1.0} }; //13

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

			// Bật nên: mỗi mặt một màu
			// ic = f % COLORNUM;

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

// Tìm vector pháp tuyến theo phương pháp Newell
void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float mx = 0, my = 0, mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
}

// To mau cho doi tuong (Lab 5)
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

// Thiet lap vat lieu cho doi tuong (Lab 5)
void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

// Hinh lap phuong
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

// Hinh tu dien
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

// Hinh hop chu nhat
void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];

	pt[0].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[1].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[2].set(fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[3].set(-fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[4].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[5].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[6].set(fSizeX / 2, fSizeY / 2, fSizeZ / 2);
	pt[7].set(-fSizeX / 2, fSizeY / 2, fSizeZ / 2);

	numFaces = 6;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 4;
	face[0].vert[2].vertIndex = 7;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 3;
	face[1].vert[1].vertIndex = 7;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 2;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 1;
	face[2].vert[1].vertIndex = 2;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 5;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = 1;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 6;
	face[4].vert[1].vertIndex = 7;
	face[4].vert[2].vertIndex = 4;
	face[4].vert[3].vertIndex = 5;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 2;
	face[5].vert[1].vertIndex = 1;
	face[5].vert[2].vertIndex = 0;
	face[5].vert[3].vertIndex = 3;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius) {
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++) {
		x = fRadius * cos(fAngle*i);
		z = fRadius * sin(fAngle*i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++) {
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

	for (i = 0; i < nSegment; i++) {
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

	for (i = 0; i < nSegment; i++) {
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

void Mesh::CreateCylinderHollow(int nSegment, float fHeight, float fRadiusO, float fRadiusI) {
	numVerts = nSegment * 4;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	xO, xI, yO, yI, zO, zI;

	//Khoi tao diem
	for (i = 0; i < nSegment; i++) {
		xO = fRadiusO * cos(fAngle*i);
		zO = fRadiusO * sin(fAngle*i);
		yO = fHeight / 2;
		pt[i].set(xO, yO, zO);

		xI = fRadiusI * cos(fAngle*i);
		zI = fRadiusI * sin(fAngle*i);
		yI = fHeight / 2;
		pt[i + nSegment].set(xI, yI, zI);

		yO = -fHeight / 2;
		pt[i + 2 * nSegment].set(xO, yO, zO);

		yI = -fHeight / 2;
		pt[i + 3 * nSegment].set(xI, yI, zI);
	}

	numFaces = nSegment * 4;
	face = new Face[numFaces];

	idx = 0;

	//day tren
	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 0;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		idx++;
	}

	//mat tru ngoai
	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 0;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}

	//mat tru trong
	for (i = nSegment; i < 2 * nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;
		if (i < 2 * nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = nSegment;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}

	//day duoi
	for (i = 2 * nSegment; i < 3 * nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		if (i < 3 * nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 2 * nSegment;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		idx++;
	}
}

void Mesh::CreateRectangleHollow(int nSegment, float fLong, float fHeight, float fWidth, float fRadius) {
	numVerts = (nSegment + 1) * 4;
	numFaces = nSegment * 4 + 2;

	pt = new Point3[numVerts];
	float x, y, z;
	float fAlpha = asin(fWidth / (2 * fRadius));
	float	fAngle = 2 * fAlpha / nSegment;

	for (int i = 1; i < nSegment; i++) {
		x = fLong / 2 + fRadius * cos(fAlpha) - fRadius * cos(fAlpha - fAngle * i);
		z = fRadius * sin(fAlpha - fAngle * i);
		y = fHeight / 2;
		pt[i].set(x, y, z);
		pt[i + nSegment + 1].set(x, -y, z);
		pt[i + 2 * (nSegment + 1)].set(-x, y, z);
		pt[i + 3 * (nSegment + 1)].set(-x, -y, z);
	}

	pt[0].set(fLong / 2, fHeight / 2, fWidth / 2);
	pt[nSegment].set(fLong / 2, fHeight / 2, -fWidth / 2);

	pt[nSegment + 1].set(fLong / 2, -fHeight / 2, fWidth / 2);
	pt[2 * nSegment + 1].set(fLong / 2, -fHeight / 2, -fWidth / 2);

	pt[2 * (nSegment + 1)].set(-fLong / 2, fHeight / 2, fWidth / 2);
	pt[3 * nSegment + 2].set(-fLong / 2, fHeight / 2, -fWidth / 2);

	pt[3 * (nSegment + 1)].set(-fLong / 2, -fHeight / 2, fWidth / 2);
	pt[4 * nSegment + 3].set(-fLong / 2, -fHeight / 2, -fWidth / 2);

	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[4];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = nSegment + 1;
	face[0].vert[2].vertIndex = 3 * (nSegment + 1);
	face[0].vert[3].vertIndex = 2 * (nSegment + 1);

	face[1].nVerts = 4;
	face[1].vert = new VertexID[4];
	face[1].vert[0].vertIndex = nSegment;
	face[1].vert[1].vertIndex = 2 * (nSegment + 1) - 1;
	face[1].vert[2].vertIndex = 4 * (nSegment + 1) - 1;
	face[1].vert[3].vertIndex = 3 * (nSegment + 1) - 1;
	int idx = 2;
	for (int i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[4];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + 1;
		face[idx].vert[2].vertIndex = i + 1 + nSegment + 1;
		face[idx].vert[3].vertIndex = i + nSegment + 1;

		face[idx + nSegment].nVerts = 4;
		face[idx + nSegment].vert = new VertexID[4];
		face[idx + nSegment].vert[0].vertIndex = i + 2 * (nSegment + 1);
		face[idx + nSegment].vert[1].vertIndex = i + 1 + 2 * (nSegment + 1);
		face[idx + nSegment].vert[2].vertIndex = i + 1 + 3 * (nSegment + 1);
		face[idx + nSegment].vert[3].vertIndex = i + 3 * (nSegment + 1);


		face[idx + 2 * nSegment].nVerts = 4;
		face[idx + 2 * nSegment].vert = new VertexID[4];
		face[idx + 2 * nSegment].vert[0].vertIndex = i;
		face[idx + 2 * nSegment].vert[1].vertIndex = i + 1;
		face[idx + 2 * nSegment].vert[2].vertIndex = i + 1 + 2 * (nSegment + 1);
		face[idx + 2 * nSegment].vert[3].vertIndex = i + 2 * (nSegment + 1);

		face[idx + 3 * nSegment].nVerts = 4;
		face[idx + 3 * nSegment].vert = new VertexID[4];
		face[idx + 3 * nSegment].vert[0].vertIndex = i + nSegment + 1;
		face[idx + 3 * nSegment].vert[1].vertIndex = i + 1 + nSegment + 1;
		face[idx + 3 * nSegment].vert[2].vertIndex = i + 1 + 3 * (nSegment + 1);
		face[idx + 3 * nSegment].vert[3].vertIndex = i + 3 * (nSegment + 1);

		idx++;
	}

}

void Mesh::CreateRectangleGrooveUp(float fLong, float fWidth, float fHeight, float fBigBottomG, float fSmallBottomG, float fHeightG)
{
	numVerts = 16;
	numFaces = 11;

	pt = new Point3[numVerts];
	//phia x+
	pt[0].set(fLong / 2, fHeight / 2, fWidth / 2);
	pt[1].set(fLong / 2, fHeight / 2, -fWidth / 2);
	pt[2].set(fLong / 2, fHeightG - fHeight / 2, -fWidth / 2);
	pt[3].set(fLong / 2, fHeightG - fHeight / 2, fWidth / 2);
	pt[4].set(fLong / 2, fHeightG - fHeight / 2, -fSmallBottomG / 2);
	pt[5].set(fLong / 2, fHeightG - fHeight / 2, fSmallBottomG / 2);
	pt[6].set(fLong / 2, -fHeight / 2, fBigBottomG / 2);
	pt[7].set(fLong / 2, -fHeight / 2, -fBigBottomG / 2);
	//phia x-
	pt[8].set(-fLong / 2, fHeight / 2, fWidth / 2);
	pt[9].set(-fLong / 2, fHeight / 2, -fWidth / 2);
	pt[10].set(-fLong / 2, fHeightG - fHeight / 2, -fWidth / 2);
	pt[11].set(-fLong / 2, fHeightG - fHeight / 2, fWidth / 2);
	pt[12].set(-fLong / 2, fHeightG - fHeight / 2, -fSmallBottomG / 2);
	pt[13].set(-fLong / 2, fHeightG - fHeight / 2, fSmallBottomG / 2);
	pt[14].set(-fLong / 2, -fHeight / 2, fBigBottomG / 2);
	pt[15].set(-fLong / 2, -fHeight / 2, -fBigBottomG / 2);

	int id = 0;
	//mat cat oyz
	face = new Face[numFaces];
	for (int i = 0; i < 4; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		for (int j = 0; j < 4; j++)
		{
			face[i].vert[j].vertIndex = id;
			id++;
		}
	}

	//mat cat oxy
	face[4].nVerts = 4;
	face[4].vert = new VertexID[4];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 3;
	face[4].vert[2].vertIndex = 11;
	face[4].vert[3].vertIndex = 8;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[4];
	face[5].vert[0].vertIndex = 1;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 10;
	face[5].vert[3].vertIndex = 9;

	face[6].nVerts = 4;
	face[6].vert = new VertexID[4];
	face[6].vert[0].vertIndex = 5;
	face[6].vert[1].vertIndex = 6;
	face[6].vert[2].vertIndex = 14;
	face[6].vert[3].vertIndex = 13;

	face[7].nVerts = 4;
	face[7].vert = new VertexID[4];
	face[7].vert[0].vertIndex = 4;
	face[7].vert[1].vertIndex = 7;
	face[7].vert[2].vertIndex = 15;
	face[7].vert[3].vertIndex = 12;
	//mat day oxz
	face[8].nVerts = 4;
	face[8].vert = new VertexID[4];
	face[8].vert[0].vertIndex = 0;
	face[8].vert[1].vertIndex = 1;
	face[8].vert[2].vertIndex = 9;
	face[8].vert[3].vertIndex = 8;

	face[9].nVerts = 4;
	face[9].vert = new VertexID[4];
	face[9].vert[0].vertIndex = 2;
	face[9].vert[1].vertIndex = 3;
	face[9].vert[2].vertIndex = 11;
	face[9].vert[3].vertIndex = 10;

	face[10].nVerts = 4;
	face[10].vert = new VertexID[4];
	face[10].vert[0].vertIndex = 6;
	face[10].vert[1].vertIndex = 7;
	face[10].vert[2].vertIndex = 15;
	face[10].vert[3].vertIndex = 14;

}

void Mesh::CreateRectangleGroove(float fLong, float fWidth, float fHeight, float fBigBottomG, float fSmallBottomG, float fHeightG) {


	numVerts = 20;
	numFaces = 14;

	pt = new Point3[numVerts];
	//phia x-
	pt[0].set(fLong / 2, fHeight / 2, fWidth / 2);
	pt[1].set(fLong / 2, fHeight / 2 - fHeightG, fWidth / 2);
	pt[2].set(fLong / 2, -fHeight / 2, fWidth / 2);
	pt[3].set(fLong / 2, -fHeight / 2, -fWidth / 2);
	pt[4].set(fLong / 2, fHeight / 2 - fHeightG, -fWidth / 2);
	pt[5].set(fLong / 2, fHeight / 2, -fWidth / 2);
	pt[6].set(fLong / 2, fHeight / 2, -fSmallBottomG / 2);
	pt[7].set(fLong / 2, fHeight / 2 - fHeightG, -fBigBottomG / 2);
	pt[8].set(fLong / 2, fHeight / 2 - fHeightG, fBigBottomG / 2);
	pt[9].set(fLong / 2, fHeight / 2, fSmallBottomG / 2);
	//phia x+
	pt[10].set(-fLong / 2, fHeight / 2, fWidth / 2);
	pt[11].set(-fLong / 2, fHeight / 2 - fHeightG, fWidth / 2);
	pt[12].set(-fLong / 2, -fHeight / 2, fWidth / 2);
	pt[13].set(-fLong / 2, -fHeight / 2, -fWidth / 2);
	pt[14].set(-fLong / 2, fHeight / 2 - fHeightG, -fWidth / 2);
	pt[15].set(-fLong / 2, fHeight / 2, -fWidth / 2);
	pt[16].set(-fLong / 2, fHeight / 2, -fSmallBottomG / 2);
	pt[17].set(-fLong / 2, fHeight / 2 - fHeightG, -fBigBottomG / 2);
	pt[18].set(-fLong / 2, fHeight / 2 - fHeightG, fBigBottomG / 2);
	pt[19].set(-fLong / 2, fHeight / 2, fSmallBottomG / 2);
	face = new Face[numFaces];


	//mat cat oyz
	face[0].nVerts = 4;
	face[0].vert = new VertexID[4];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 8;
	face[0].vert[3].vertIndex = 9;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[4];
	face[1].vert[0].vertIndex = 1;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 3;
	face[1].vert[3].vertIndex = 4;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[4];
	face[2].vert[0].vertIndex = 4;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 7;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[4];
	face[3].vert[0].vertIndex = 10;
	face[3].vert[1].vertIndex = 11;
	face[3].vert[2].vertIndex = 18;
	face[3].vert[3].vertIndex = 19;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[4];
	face[4].vert[0].vertIndex = 11;
	face[4].vert[1].vertIndex = 12;
	face[4].vert[2].vertIndex = 13;
	face[4].vert[3].vertIndex = 14;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[4];
	face[5].vert[0].vertIndex = 14;
	face[5].vert[1].vertIndex = 15;
	face[5].vert[2].vertIndex = 16;
	face[5].vert[3].vertIndex = 17;

	//mat cat oxy
	face[6].nVerts = 4;
	face[6].vert = new VertexID[4];
	face[6].vert[0].vertIndex = 0;
	face[6].vert[1].vertIndex = 2;
	face[6].vert[2].vertIndex = 12;
	face[6].vert[3].vertIndex = 10;

	face[7].nVerts = 4;
	face[7].vert = new VertexID[4];
	face[7].vert[0].vertIndex = 3;
	face[7].vert[1].vertIndex = 5;
	face[7].vert[2].vertIndex = 15;
	face[7].vert[3].vertIndex = 13;

	face[8].nVerts = 4;
	face[8].vert = new VertexID[4];
	face[8].vert[0].vertIndex = 8;
	face[8].vert[1].vertIndex = 9;
	face[8].vert[2].vertIndex = 19;
	face[8].vert[3].vertIndex = 18;

	face[9].nVerts = 4;
	face[9].vert = new VertexID[4];
	face[9].vert[0].vertIndex = 6;
	face[9].vert[1].vertIndex = 7;
	face[9].vert[2].vertIndex = 17;
	face[9].vert[3].vertIndex = 16;
	//mat day oxz
	face[10].nVerts = 4;
	face[10].vert = new VertexID[4];
	face[10].vert[0].vertIndex = 0;
	face[10].vert[1].vertIndex = 9;
	face[10].vert[2].vertIndex = 19;
	face[10].vert[3].vertIndex = 10;

	face[11].nVerts = 4;
	face[11].vert = new VertexID[4];
	face[11].vert[0].vertIndex = 5;
	face[11].vert[1].vertIndex = 6;
	face[11].vert[2].vertIndex = 16;
	face[11].vert[3].vertIndex = 15;

	face[12].nVerts = 4;
	face[12].vert = new VertexID[4];
	face[12].vert[0].vertIndex = 7;
	face[12].vert[1].vertIndex = 8;
	face[12].vert[2].vertIndex = 18;
	face[12].vert[3].vertIndex = 17;

	face[13].nVerts = 4;
	face[13].vert = new VertexID[4];
	face[13].vert[0].vertIndex = 2;
	face[13].vert[1].vertIndex = 3;
	face[13].vert[2].vertIndex = 13;
	face[13].vert[3].vertIndex = 12;

}


#pragma endregion

// Tham so
#pragma region
// Mesh
Mesh base;
Mesh cylinder;
Mesh banDo;
Mesh giado1;
Mesh giado2;
Mesh giado3;
Mesh contruot;
Mesh taynoi;
Mesh cylinderHollow;
Mesh tayquay;
Mesh chot1;
Mesh chot2;
Mesh chot3;


// Tham so cua cua so
int screenWidth = 600;
int screenHeight = 600;

// Tham so cua vat the
float baseRadius = 0.8;
float baseHeight = 0.2;
float baseRotateStep = 5;

float cylinderRadius = 0.4;
float cylinderHeight = 2.6;
float cylinderTranslationStep = 0.05;
float cylinderOffset = cylinderHeight / 2;

// Mat ban
float banDoX = 7;
float banDoY = baseHeight;
float banDoZ = 3;

// Gia do tay quay
float giado3_Long = 0.5;
float giado3_Height = 0.4;
float giado3_Width = 0.5;

// Gia do con truot trai
float giado1_Long = 2.7;
float giado1_Height = 0.3;
float giado1_Width = 0.5;
float giado1_BigG = 0.35;
float giado1_SmallG = 0.2;
float giado1_HeightG = 0.1;


// Gia do con truot phai
float giado2_Long = 2.0;
float giado2_Height = 0.7;
float giado2_Width = 0.5;
float giado2_BigG = 0.35;
float giado2_SmallG = 0.2;
float giado2_HeightG = 0.1;

// Con truot
float contruot_Long = 1;
float contruot_Height = 0.2;
float contruot_Width = 0.5;
float contruot_BigG = 0.35;
float contruot_SmallG = 0.2;
float contruot_HeightG = 0.1;
float contruot_translate_step = 0.1;
// chot1
float chot1_Height = 0.2;
float chot_Radius = 0.1;

float chot2_Height = 0.4;

float chot3_Height = 0.6;

// Tay noi
float taynoi_height = 0.2;
float taynoi_width = 0.1;
float taynoi_radiusO = 0.15;
float taynoi_radiusI = 0.1;
float taynoi_long = (float)sqrt(1073.0 / 200) - 2 * sqrt(taynoi_radiusO*taynoi_radiusO - taynoi_width * taynoi_width / 4.0);

// Tay quay

float tayquay_height = 0.2;
float tayquay_width = 0.1;
float tayquay_radiusO = 0.15;
float tayquay_radiusI = 0.1;
float tayquay_rotate_step = 5;
float tayquay_rotate = 0.0;
float tayquay_long = 0.5 - sqrt(tayquay_radiusO*tayquay_radiusO - tayquay_width * tayquay_width / 4.0) * 2;

// khoang cach tay quay
float d = sqrt(tayquay_radiusO*tayquay_radiusO - tayquay_width * tayquay_width / 4.0) + tayquay_long / 2.0;
float d1 = sqrt(taynoi_radiusO*taynoi_radiusO - taynoi_width * taynoi_width / 4.0) + taynoi_long / 2.0;
float taynoi1_rotate_step = 5 / 90.0 * (asin(d / d1) * 180 / PI);
float taynoi1_rotate = 90;


float x1 = -banDoX / 2.0 + contruot_Long / 2.0 + contruot.translateX;
float z1 = -banDoZ / 2.0 + giado1_Width / 2.0;

float x3 = cos(tayquay_rotate/180.0*PI)*d * 2;
float z3 = -sin(tayquay_rotate/180.0*PI) * 2 * d + (banDoZ / 2.0 - giado3_Width / 2.0);

float xI = (x1 + x3) / 2.0;
float zI = (z1 + z3) / 2.0;

float distance1 = sqrt((x1 - xI)*(x1 - xI) + (z1 - zI)*(z1 - zI));
float distance2 = sqrt((d1 * 2)*(d1 * 2) - distance1 * distance1);

float x = abs(x1 - x3);
float z = abs(z1 - z3);

float beta = acos(distance1 / d1/2.0) / PI * 180.0;
float alpha = atan(z/x)/PI*180.0;

double angle = 0;

bool au = false;
bool isFrame = false;
bool light = true;
bool flag_contruot = false;

// Tham so cho camera
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool bCamera = true;

#pragma endregion
void calcThongsoTruot()
{
	x1 = -banDoX / 2.0 + contruot_Long / 2.0 + contruot.translateX;
	z1 = -banDoZ / 2.0 + giado1_Width / 2.0;

	x3 = cos(tayquay_rotate/180.0*PI)*d * 2;
	z3 = -sin(tayquay_rotate/180.0*PI) * 2 * d + (banDoZ / 2.0 - giado3_Width / 2.0);

	xI = (x1 + x3) / 2.0;
	zI = (z1 + z3) / 2.0;

	distance1 = sqrt((x1 - xI)*(x1 - xI) + (z1 - zI)*(z1 - zI));
	distance2 = sqrt((d1 * 2)*(d1 * 2) - distance1 * distance1);

	x = abs(x1 - x3);
	z = abs(z1 - z3);

	beta = acos(distance1 / d1 / 2.0) / PI * 180.0;
	alpha = atan(z / x) / PI * 180.0;

}

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		if (camera_height < 0)
			camera_height = 0;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 5;
		break;
	defautolt:
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case '1':
		base.rotateY += baseRotateStep;
		if (base.rotateY > 360)
			base.rotateY -= 360;
		break;
	case '2':
		base.rotateY -= baseRotateStep;
		if (base.rotateY < 0)
			base.rotateY += 360;
		break;
	case '3':
		tayquay_rotate += tayquay_rotate_step;
		if (tayquay_rotate > 360)
			tayquay_rotate -= 360;
		calcThongsoTruot();
		break;
	case '4':
		tayquay_rotate -= tayquay_rotate_step;
		if (tayquay_rotate < 0)
			tayquay_rotate += 360;
		calcThongsoTruot();
		break;
	case '5':
		contruot.translateX += contruot_translate_step;
		if (contruot.translateX > 1.4)
			contruot.translateX = 1.4;
		calcThongsoTruot();
		break;
	case '6':
		contruot.translateX -= contruot_translate_step;
		if (contruot.translateX < 0)
			contruot.translateX = 0;
		calcThongsoTruot();
		break;

	case '7':
		cylinderOffset += cylinderTranslationStep;
		if (cylinderOffset > cylinderHeight / 2)
			cylinderOffset = cylinderHeight / 2;
		break;
	case '8':
		cylinderOffset -= cylinderTranslationStep;
		if (cylinderOffset < 0)
			cylinderOffset = 0;
		break;
	case 'w':
	case 'W':
		isFrame = !isFrame;
		break;
	case 'a':
	case 'A':
		au = !au;
		break;
	case 'v':
	case 'V':
		isV = !isV;
	case 'd':
	case 'D':
		light = !light;
		break;
	case '+':
		camera_dis += 0.5;
		break;
	case '-':
		camera_dis -= 0.5;
		break;
	}
	glutPostRedisplay();
}

// Ve vat the
#pragma region
void drawLucGiac(float x, float y, float z, float R, float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(-60 * PI / 180), y, z + R * sin(-60 * PI / 180));
	glVertex3f(x + R * cos(0), y, z + R * sin(0));
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(77.0 / 255.0, 166.0 / 255.0, 210.0 / 255.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x + R * cos(120 * PI / 180), y, z + R * sin(120 * PI / 180));
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x + R * cos(240 * PI / 180), y, z + R * sin(240 * PI / 180));
	glVertex3f(x + R * cos(300 * PI / 180), y, z + R * sin(300 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
}

void drawNen(float alpha)
{
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	float d = 0.7, R = d / cos(PI / 6);
	int i = 0;
	for (float x = -30; x < 30; x += R + R * cos(PI / 3))
	{
		float z = (i % 2 == 0) ? -20 : (-20 - d);
		for (; z < 20; z += 2 * d)
			drawLucGiac(x, y, z, R, alpha);
		i++;
	}
	glEnable(GL_LIGHTING);
}

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0); //x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0); //y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0); //z
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawBase()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	base.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		base.DrawWireframe();
	else
		base.Draw();

	glPopMatrix();
}

void drawCylinder()
{
	glPushMatrix();

	glTranslated(0, baseHeight + cylinderOffset, 0);
	glRotatef(cylinder.rotateY + base.rotateY, 0, 1, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.2, 0.2, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinder.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		cylinder.DrawWireframe();
	else
		cylinder.Draw();

	glPopMatrix();
}

void drawBanDo()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY / 2.0, 0);
	glRotatef(cylinder.rotateY + base.rotateY, 0, 1, 0);

	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	banDo.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		banDo.DrawWireframe();
	else
		banDo.Draw();

	glPopMatrix();
}

void drawGiaDo1() {
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado1_Height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated( - banDoX / 2.0 + giado1_Long / 2.0, 0, 0);
	glTranslated(0, 0, -banDoZ / 2.0 + giado1_Width / 2.0);

	GLfloat ambient[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.2, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	giado1.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		giado1.DrawWireframe();
	else
		giado1.Draw();

	glPopMatrix();

}

void drawContruot1() {
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado1_Height + contruot_Height / 2.0 - contruot_HeightG, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(-banDoX / 2.0 + contruot_Long / 2.0 + contruot.translateX, 0, -banDoZ / 2.0 + giado1_Width / 2.0);

	GLfloat ambient[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.8, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	contruot.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		contruot.DrawWireframe();
	else
		contruot.Draw();

	glPopMatrix();

}


void drawChot2() {

	glPushMatrix();

	float height_contruot = contruot_Height - contruot_HeightG;
	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado1_Height + height_contruot + chot1_Height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(-banDoX / 2.0 + contruot_Long / 2.0 + contruot.translateX, 0, 0);
	glTranslated(0, 0, -banDoZ / 2.0 + giado1_Width / 2.0);

	GLfloat ambient[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot1.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot1.DrawWireframe();
	else
		chot1.Draw();

	glPopMatrix();
}

void drawGiaDo2() {
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado2_Height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(banDoX/2.0-giado2_Long/2.0, 0, -banDoZ / 2.0 + giado1_Width / 2.0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.2, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	giado2.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		giado2.DrawWireframe();
	else
		giado2.Draw();

	glPopMatrix();

}
void drawContruot2() {



	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado2_Height + contruot_Height / 2.0 - contruot_HeightG, 0);
	glRotatef(base.rotateY, 0, 1, 0);

	float temp = cos((alpha - beta)/180*PI)*2*d1*2 + contruot.translateX ;

	glTranslated(contruot_Long/2.0 + temp - banDoX/2.0, 0, -banDoZ / 2.0 + giado1_Width / 2.0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.8, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	contruot.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		contruot.DrawWireframe();
	else
		contruot.Draw();

	glPopMatrix();

}

void drawChot3()
{

	glPushMatrix();

	float height_contruot = contruot_Height - contruot_HeightG;
	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado2_Height + height_contruot + chot1_Height / 2.0, 0);
	glRotatef(cylinder.rotateY + base.rotateY, 0, 1, 0);

	float temp = cos((alpha - beta) / 180 * PI) * 2 * d1 * 2 + contruot.translateX;

	glTranslated(contruot_Long / 2.0 + temp - banDoX / 2.0, 0, 0);
	glTranslated(0, 0, -banDoZ / 2.0 + giado2_Width / 2.0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot1.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot1.DrawWireframe();
	else
		chot1.Draw();

	glPopMatrix();


}
void drawGiaDo3() {
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height / 2.0, 0);
	glRotatef(cylinder.rotateY + base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ/2.0 - giado3_Width/2.0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.2, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	giado3.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		giado3.DrawWireframe();
	else
		giado3.Draw();

	glPopMatrix();

}

void drawChot1() {
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + chot1_Height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ/2.0-giado3_Width/2.0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot1.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot1.DrawWireframe();
	else
		chot1.Draw();

	glPopMatrix();


}

void drawTayquay() {

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.2, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinderHollow.setupMaterial(ambient, diffuse, specular, shininess);
	tayquay.setupMaterial(ambient, diffuse, specular, shininess);

	//khop noi 1
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + tayquay_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ / 2.0 - giado3_Width / 2.0);
	glRotated(tayquay_rotate, 0, 1, 0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();
	//tay don
	glPushMatrix();


	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + tayquay_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ / 2.0 - giado3_Width / 2.0);
	glRotated(tayquay_rotate, 0, 1, 0);
	glTranslated(d, 0, 0);

	if (isFrame)
		tayquay.DrawWireframe();
	else
		tayquay.Draw();
	glPopMatrix();
	//khop noi 2
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + tayquay_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ / 2.0 - giado3_Width / 2.0);
	glRotated(tayquay_rotate, 0, 1, 0);
	glTranslated(2 * d, 0, 0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();
}

void drawChot4() {
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + chot2_Height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ / 2.0 - giado3_Width / 2.0);
	glRotated(tayquay_rotate, 0, 1, 0);
	glTranslated(2 * d, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot1.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot2.DrawWireframe();
	else
		chot2.Draw();

	glPopMatrix();

}

void drawTayNoi1() {

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.2, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinderHollow.setupMaterial(ambient, diffuse, specular, shininess);
	taynoi.setupMaterial(ambient, diffuse, specular, shininess);

	//khop noi 1
	glPushMatrix();
	            
	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + chot1_Height + taynoi_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ / 2.0 - giado3_Width / 2.0);
	glRotated(tayquay_rotate, 0, 1, 0);
	glTranslated(2 * d, 0, 0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();
	//tay don
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + chot1_Height + taynoi_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ / 2.0 - giado3_Width / 2.0);

	glTranslated(2 * d * cos(tayquay_rotate/180.0*PI), 0, - 2*d*sin(tayquay_rotate / 180.0 * PI));
	
	glRotatef(180 - alpha - beta, 0, 1, 0);
	glTranslated(d1, 0, 0);

	if (isFrame)
		taynoi.DrawWireframe();
	else
		taynoi.Draw();
	glPopMatrix();
	//khop noi 2
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + chot1_Height + taynoi_height / 2.0, 0);
	glRotatef(cylinder.rotateY + base.rotateY, 0, 1, 0);
	glTranslated(0, 0, banDoZ / 2.0 - giado3_Width / 2.0);

	glTranslated(2 * d * cos(tayquay_rotate / 180 * PI), 0, -2 * d*sin(tayquay_rotate / 180 * PI));
	glRotatef(180 - alpha - beta, 0, 1, 0);
	glTranslated(2 * d1, 0, 0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();

}

void drawChot5() {

	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + chot3_Height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(xI, 0, zI);
	glRotatef(90-alpha, 0, 1, 0);
	glTranslated(distance2, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot3.setupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot3.DrawWireframe();
	else
		chot3.Draw();

	glPopMatrix();
}

void drawTayNoi2() {

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.2, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinderHollow.setupMaterial(ambient, diffuse, specular, shininess);
	taynoi.setupMaterial(ambient, diffuse, specular, shininess);

	//khop noi 1
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + taynoi_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(-banDoX / 2.0 + contruot_Long / 2.0 + contruot.translateX, 0, -banDoZ/2.0 + giado2_Width/2.0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();
	//tay don
	glPushMatrix();


	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + taynoi_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(-banDoX / 2.0 + contruot_Long / 2.0 + contruot.translateX, 0, -banDoZ / 2.0 + giado2_Width / 2.0);
	glRotated(-alpha+beta, 0, 1, 0);
	glTranslated(d1, 0, 0);

	if (isFrame)
		taynoi.DrawWireframe();
	else
		taynoi.Draw();
	glPopMatrix();
	//khop noi 2
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + taynoi_height / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(-banDoX / 2.0 + contruot_Long / 2.0 + contruot.translateX, 0, -banDoZ / 2.0 + giado2_Width / 2.0);
	glRotated(-alpha + beta, 0, 1, 0);
	glTranslated(2 * d1, 0, 0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();

}

void drawTayNoi3() {



	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.2, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinderHollow.setupMaterial(ambient, diffuse, specular, shininess);
	taynoi.setupMaterial(ambient, diffuse, specular, shininess);

	//khop noi 1
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + taynoi_height * 2.5, 0);
	glRotatef(base.rotateY, 0, 1, 0);

	float temp = cos((alpha - beta) / 180 * PI) * 2 * d1 * 2 + contruot.translateX;
	glTranslated(contruot_Long / 2.0 + temp - banDoX / 2.0, 0, -banDoZ / 2.0 + giado2_Width / 2.0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();
	//tay don
	glPushMatrix();


	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + taynoi_height * 2.5, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(contruot_Long / 2.0 + temp - banDoX / 2.0, 0, -banDoZ / 2.0 + giado2_Width / 2.0);
	glRotated(alpha-beta, 0, 1, 0);
	glTranslated(-d1, 0, 0);
	if (isFrame)
		taynoi.DrawWireframe();
	else
		taynoi.Draw();
	glPopMatrix();
	//khop noi 2
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + baseHeight + cylinderOffset + banDoY + giado3_Height + taynoi_height * 2.5, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glTranslated(contruot_Long / 2.0 + temp - banDoX / 2.0, 0, -banDoZ / 2.0 + giado2_Width / 2.0);
	glRotated(alpha - beta, 0, 1, 0);
	glTranslated(-d1*2, 0, 0);

	if (isFrame)
		cylinderHollow.DrawWireframe();
	else
		cylinderHollow.Draw();
	glPopMatrix();
}
#pragma endregion

void drawAll()
{
	drawBase();
	drawCylinder();
	drawBanDo();
	drawGiaDo1();
	drawContruot1();
	drawGiaDo2();
	drawContruot2();
	drawGiaDo3();
	drawChot1();
	drawTayquay();
	drawChot2();
	drawChot3();
	drawChot4();
	drawTayNoi1();
	drawChot5();
	drawTayNoi2();
	drawTayNoi3();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	if (light == true)
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

	camera_X = camera_dis * sinf(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * PI / 180);

	if (isV) {
		gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, -1);
	}
	else if (camera_dis == 0)
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
	}
	else
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
	}

	glViewport(0, 0, screenWidth, screenHeight);

	// Clear the stencil buffers
	glClearStencil(0);
	// Clear depth
	glClearDepth(1.0f);
	// Draw
	drawAll();
	/* Don't update color or depth. */
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	/* Draw 1 into the stencil buffer. */
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	drawNen(1.0f);
	/* Re-enable update of color and depth. */
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	/* Now, only render where stencil is set to 1. */
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//Draw the cube, reflected vertically, at all PIxels where the stencil
	//buffer is 1
	glPushMatrix();
	glScalef(1, -1, 1);
	drawAll();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	// // Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawNen(0.7f);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}
void processTimer(int value)
{
	if (au)
	{
		if (contruot.translateX >= 1.4)
			flag_contruot = true;
		if (contruot.translateX <= 0)
			flag_contruot = false;

		if(flag_contruot)
			contruot.translateX -= contruot_translate_step;
		else
			contruot.translateX += contruot_translate_step;

		if (contruot.translateX < 0)
			contruot.translateX = 0;

		tayquay_rotate += tayquay_rotate_step;
		if (tayquay_rotate > 360)
			tayquay_rotate -= 360;

		calcThongsoTruot();
	}
	glutTimerFunc(25, processTimer, 0);
	glutPostRedisplay();
}
void myInit()
{
	camera_angle = -30;  // Góc quay camera xung quanh trục Oy
	camera_height = 5.5; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 6.5;	// Khoảng cách đến trục Oy

	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	float fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(25, processTimer, 0);

	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
}

void create(int N)
{
	int M = 2 * (N - 1);

	// // Đe
	base.CreateCylinder(M, baseHeight, baseRadius);
	base.SetColor(2);
	base.CalculateFacesNorm();

	// // // Xy lanh
	cylinder.CreateCylinder(M, cylinderHeight, cylinderRadius);
	cylinder.SetColor(3);
	cylinder.CalculateFacesNorm();

	// // Bàn đỡ
	banDo.CreateCuboid(banDoX, banDoY, banDoZ);
	banDo.SetColor(4);
	banDo.CalculateFacesNorm();

	// //gia do 1
	giado1.CreateRectangleGroove(giado1_Long, giado1_Width, giado1_Height, giado1_BigG, giado1_SmallG, giado1_HeightG);
	giado1.SetColor(2);
	giado1.CalculateFacesNorm();

	// //con truot
	contruot.CreateRectangleGrooveUp(contruot_Long, contruot_Width, contruot_Height, contruot_BigG, contruot_SmallG, contruot_HeightG);
	contruot.SetColor(2);
	contruot.CalculateFacesNorm();

	// //gia do 2
	giado2.CreateRectangleGroove(giado2_Long, giado2_Width, giado2_Height, giado2_BigG, giado2_SmallG, giado2_HeightG);
	giado2.SetColor(2);
	giado2.CalculateFacesNorm();

	// //gia do 3
	giado3.CreateCuboid(giado3_Long, giado3_Height, giado3_Width);
	giado3.SetColor(5);
	giado3.CalculateFacesNorm();

	// //chot cua tay noi va tay quay
	cylinderHollow.CreateCylinderHollow(M, tayquay_height, tayquay_radiusO, tayquay_radiusI);
	cylinderHollow.SetColor(3);
	cylinderHollow.CalculateFacesNorm();

	//tay quay
	tayquay.CreateRectangleHollow(M, tayquay_long, tayquay_height, tayquay_width, tayquay_radiusO);
	tayquay.SetColor(3);
	tayquay.CalculateFacesNorm();

	//tay noi
	taynoi.CreateRectangleHollow(M, taynoi_long, taynoi_height, taynoi_width, taynoi_radiusO);
	taynoi.SetColor(3);
	taynoi.CalculateFacesNorm();

	//chot 1
	chot1.CreateCylinder(M, chot1_Height, chot_Radius);
	chot1.SetColor(2);
	chot1.CalculateFacesNorm();

	//chot 2
	chot2.CreateCylinder(M, chot2_Height, chot_Radius);
	chot2.SetColor(2);
	chot2.CalculateFacesNorm();

	//chot 3
	// chot3.CreateCylinder(M, chot3_Height, chot_Radius);
	// chot3.SetColor(2);
	// chot3.CalculateFacesNorm();
}

void print()
{

	cout << "1, 2: Xoay de" << endl
		<< "3, 4 : Xoay tay quay" << endl
		<< "5, 6 : Dich con truot 1" << endl
		<< "7, 8 : Xy lanh dich chuyen" << endl
		<< "W, w : Chuyen doi qua lai giua che do khung day va to mau" << endl
		<< "V, v : Chuyen doi qua lai giua hai che do nhin khac nhau" << endl
		<< "+ : Tang khoang cach camera" << endl
		<< "- : Giam khoang cach camera" << endl
		<< "up arrow : Tang chieu cao camera" << endl
		<< "down arrow : Giam chieu cao camera" << endl
		<< "< -: Quay camera theo chieu kim dong ho" << endl
		<< "-> : Quay camera nguoc chieu kim dong ho" << endl
		<< "D, d : Bat / tat nguon sang thu 2" << endl
		<< "A, a : Bat / tat nguon che do hoat hinh" << endl;
}


int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);									//initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		//set the display mode
	glutInitWindowSize(screenWidth, screenHeight);					//set window size
	glutInitWindowPosition(100, 100);								// set window position on screen
	glutCreateWindow("Assignment - Le Hoang Long 1712010");	// open the screen window

	print();
	int N = NUM / 2 + 1;		// So dinh tren mot nua hinh tron
	create(N);

	
	myInit();

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutDisplayFunc(myDisplay);

	glutMainLoop();
	return 0;
}

