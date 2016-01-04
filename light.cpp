#include "light.h"

light::light()
{
	for (int i = 0; i < 4; i++)
	{
		position[i] = 0.0;
		specular[i] = 0.0;
		diffuse[i] = 0.0;
		ambient[i] = 0.0;
	}
}

light::light(char* light_str)
{
	char* ptr = strtok(light_str, " ");

	ptr = strtok(NULL, " ");
	for (int i = 0; i < 3; i++)
	{
		position[i] = atof(ptr);
		ptr = strtok(NULL, " ");
	}
	position[3] = 1.0;

	for (int i = 0; i < 3; i++)
	{
		ambient[i] = atof(ptr);
		ptr = strtok(NULL, " ");
	}
	ambient[3] = 1.0;

	for (int i = 0; i < 3; i++)
	{
		diffuse[i] = atof(ptr);
		ptr = strtok(NULL, " ");
	}
	diffuse[3] = 1.0;

	for (int i = 0; i < 3; i++)
	{
		specular[i] = atof(ptr);
		ptr = strtok(NULL, " ");
	}
	specular[3] = 1.0;
}

environment_light::environment_light(char* light_str)
{
	char* ptr = strtok(light_str, " ");

	ptr = strtok(NULL, " ");
	for (int i = 0; i < 3; i++)
	{
		environment_ambient[i] = atof(ptr);
		ptr = strtok(NULL, " ");
	}
}

lights::lights()
{
}

lights::lights(const char* light_file)
{
	char buffer[100];
	FILE* f_light;

	f_light = fopen(light_file, "r");
	if (!f_light)
	{
		cout << "error" << light_file << endl;
		return;
	}

	while ( fgets(buffer, 100, f_light)!=NULL )
	{
		if ( strstr(buffer, "light") != NULL )
		{
			light* new_light = new light(buffer);
			light_list.push_back(*new_light);
		}
		else if ( strstr(buffer, "ambient") != NULL )
		{
			environment_light* new_env = new environment_light(buffer);
			env_light.push_back(*new_env);
		}
		else
			continue;
	}
	fclose(f_light);
}

lights::~lights()
{
}

void lights::lighting()
{
	int gl_light[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	for (int i = 0; i < light_list.size(); i++)
	{
		glEnable(gl_light[i]);
		glLightfv(gl_light[i], GL_POSITION, light_list[i].position);
		glLightfv(gl_light[i], GL_DIFFUSE, light_list[i].diffuse);
		glLightfv(gl_light[i], GL_SPECULAR, light_list[i].specular);
		glLightfv(gl_light[i], GL_AMBIENT, light_list[i].ambient);
	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, env_light[0].environment_ambient);

}

void lights::environment_lighting()
{
	int gl_light[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };
	float tmp[4] = { 0, 0, 0, 0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	for (int i = 0; i < light_list.size(); i++)
	{
		glEnable(gl_light[i]);
		glLightfv(gl_light[i], GL_POSITION, light_list[i].position);
		glLightfv(gl_light[i], GL_DIFFUSE, tmp);
		glLightfv(gl_light[i], GL_SPECULAR, tmp);
		glLightfv(gl_light[i], GL_AMBIENT, light_list[i].ambient);
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, env_light[0].environment_ambient);	
}


void lights::set_start_pos(int a, int b)
{
	x = a;
	y = b;
}

void lights::move_light(int a, int b, int w, int h)
{
	light_list[0].position[0] += (a - x);
	light_list[0].position[2] -= (b - y);
}