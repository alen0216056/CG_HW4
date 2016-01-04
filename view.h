#include <string>
#include <iostream>
#include <fstream>
#include "glut.h"
using namespace std;

class view
{
public:
	float eye[3];
	float at[3];
	float up[3];
	double fovy, near, far;
	int viewport[4];

	view(const char* file_name);
	~view();

	void viewing(float move_up = 0, float move_right = 0);
	void zoom(bool flag);
	void rotate(bool flag);
};