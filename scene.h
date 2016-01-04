#include <vector>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "mesh.h"
using namespace std;

class scene
{
public:
	int type, texture_id[3];
	char name[50];
	float s[3];
	float r[4];
	float t[3];
	vector< vector<float> > tangent_t[3];

	scene(char* scene_str, int t, int id[]);
	~scene();
	void compute_t(const char* file_name);
};

class scenes
{
public:
	vector<scene> scene_list;
	unsigned int texture_obj[30];
	int selected, x, y;

	scenes(const char* file_name);
	~scenes();

	void object(const char* file_name, int scene_index);
	void shader_object(const char* file_name, int scene_index);
	void shadow(const char* file_name, int scene_index, float* light_pos);
	void shadow_setting(float* light_pos);
	void LoadTexture(char* pFilename, int texture_count);
	void LoadCubeTexture(char* pFilename, int texture_count);
	void scene_setting(GLhandleARB MyShader);

	void select(unsigned int i);
	void set_x_y(int a, int b);
	void move(int a, int b, int w, int h);
};