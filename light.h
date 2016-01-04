#include <vector>
#include <cstring>
#include <iostream>
#include "glut.h"
using namespace std;

class light
{
public:
	float position[4];
	float specular[4];
	float diffuse[4];
	float ambient[4];
	
	light();
	light(char* light_str);
};

class environment_light
{
public:
	float environment_ambient[3];

	environment_light(char* light_str);
};

class lights
{
public:
	int x, y;
	vector<light> light_list;
	vector<environment_light> env_light;

	lights();
	lights(const char* light_file);
	~lights();

	void set_start_pos(int a, int b);
	void move_light(int a, int b, int w, int h);

	void lighting();
	void environment_lighting();
};