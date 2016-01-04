#include "view.h"
#include <math.h>
#define PI 3.14159265

view::view(const char* file_name)
{
	string tmp;
	char buffer[100];
	fstream f_view;
	f_view.open(file_name, ios::in);

	if (!f_view)
	{
		cout << "can not open the file\n";
		return;
	}

	while (f_view>>tmp)
	{
		if (tmp=="eye")
		{
			f_view >> eye[0] >> eye[1] >> eye[2];
		}
		else if (tmp=="vat")
		{
			f_view >> at[0] >> at[1] >> at[2];
		}
		else if (tmp=="vup")
		{
			f_view >> up[0] >> up[1] >> up[2];
		}
		else if (tmp=="fovy")
		{
			f_view >> fovy;
		}
		else if (tmp == "dnear")
		{
			f_view >> near;
		}
		else if (tmp == "dfar")
		{
			f_view >> far;
		}
		else if (tmp == "viewport")
		{
			f_view >> viewport[0] >> viewport[1] >> viewport[2] >> viewport[3];
		}	
	}
	f_view.close();
}

view::~view()
{
}

void view::viewing(float move_up, float move_right)
{
	float vup[3] = { up[0] / pow(up[0] * up[0] + up[1] * up[1] + up[2] * up[2], 0.5), up[1] / pow(up[0] * up[0] + up[1] * up[1] + up[2] * up[2], 0.5), up[2] / pow(up[0] * up[0] + up[1] * up[1] + up[2] * up[2], 0.5) };
	float vat[3] = { (at[0] - eye[0]) / pow((pow(at[0] - eye[0], 2.0) + pow(at[1] - eye[1], 2.0) + pow(at[2] - eye[2], 2.0)), 0.5), (at[1] - eye[1]) / pow((pow(at[0] - eye[0], 2.0) + pow(at[1] - eye[1], 2.0) + pow(at[2] - eye[2], 2.0)), 0.5), (at[2] - eye[2]) / pow((pow(at[0] - eye[0], 2.0) + pow(at[1] - eye[1], 2.0) + pow(at[2] - eye[2], 2.0)), 0.5) };
	float vright[3] = { (vup[1] * vat[2] - vup[2] * vat[1]), (vup[2] * vat[0] - vup[0] * vat[2]), (vup[0] * vat[1] - vup[1] * vat[0]) };
	float vright_normal[3] = { vright[0] / pow(vright[0] * vright[0] + vright[1] * vright[1] + vright[2] * vright[2], 0.5), vright[1] / pow(vright[0] * vright[0] + vright[1] * vright[1] + vright[2] * vright[2], 0.5), vright[2] / pow(vright[0] * vright[0] + vright[1] * vright[1] + vright[2] * vright[2], 0.5) };

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0] + vup[0] * move_up + vright_normal[0] * move_right, eye[1] + vup[1] * move_up + vright_normal[1] * move_right, eye[2] + vup[2] * move_up + vright_normal[2] * move_right, at[0], at[1], at[2], up[0], up[1], up[2]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (float)viewport[2] / viewport[3], near, far);

	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}


void view::zoom(bool flag)
{
	double scale = flag ? 0.05 : -0.05;
	double diff[3] = { at[0] - eye[0], at[1] - eye[1], at[2] - eye[2] };

	eye[0] += diff[0] * scale;
	eye[1] += diff[1] * scale;
	eye[2] += diff[2] * scale;

	at[0] += diff[0] * scale;
	at[1] += diff[1] * scale;
	at[2] += diff[2] * scale;
}

void view::rotate(bool flag)
{
	double new_eye[3];
	double theta = flag ? -10.0 * PI / 180 : 10.0 * PI / 180;

	//double vx = at[0] - eye[0], vy = at[1] - eye[1], vz = at[2] - eye[2];
	double vx = up[0], vy = up[1], vz = up[2];
	double tmp = sqrt(pow(vx, 2.0) + pow(vy, 2.0) + pow(vz, 2.0));
	vx /= tmp;
	vy /= tmp;
	vz /= tmp;

	for (int i = 0; i < 3; i++)
		eye[i] = eye[i] - at[i];

	new_eye[0] = (cos(theta) + (1 - cos(theta))*pow(vx, 2.0))*eye[0] + ((1 - cos(theta))*vx*vy - sin(theta)*vz)*eye[1] + ((1 - cos(theta))*vx*vz + sin(theta)*vy)*eye[2];
	new_eye[1] = ((1 - cos(theta))*vy*vx + sin(vz))*eye[0] + (cos(theta) + (1 - cos(theta))*pow(vy, 2.0))*eye[1] + ((1 - cos(theta))*vy*vz - sin(theta)*vx)*eye[2];
	new_eye[2] = ((1 - cos(theta))*vz*vx - sin(theta)*vy)*eye[0] + ((1 - cos(theta))*vz*vy + sin(theta)*vx)*eye[1] + (cos(theta) + (1 - cos(theta))*pow(vz, 2.0))*eye[2];
	
	for (int i = 0; i < 3; i++)
		eye[i] = new_eye[i] + at[i];
}