#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>

#define PI 3.14159265358979323846
#define COLORNUM 14
#define NUM 36

/********************* GLOBAL CONSTANTS ***************************/
int screenWidth = 600, screenHeight = 600;


/************************** SUPPORT CLASS *************************/
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


/****************************** MESH ******************************/
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



int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);									// initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		// set the display mode
	glutInitWindowSize(screenWidth, screenHeight);					// set window size
	glutInitWindowPosition(100, 100);								// set window position on screen
	glutCreateWindow("Assignment - Nguyen Huu Thang 1713239");	    // open the screen window

	// print();
	// int N = NUM / 2 + 1;		// So dinh tren mot nua hinh tron
	// create(N);

	
	// myInit();

	// glutKeyboardFunc(myKeyboard);
	// glutSpecialFunc(mySpecialKeyboard);
	// glutDisplayFunc(myDisplay);

	glutMainLoop();
	return 0;
}