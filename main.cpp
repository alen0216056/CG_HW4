#include "scene.h"
#include "light.h"
#include "view.h"

#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "ShaderLoader.h"

GLhandleARB MyShader;

void LoadShaders();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouse_motion(int x, int y);

int width = 1024, height = 768;
scenes* s;
lights* l;
view* v;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("HW3");

	GLenum glew_error;
	if ((glew_error = glewInit()) != GLEW_OK)return -1;

	LoadShaders();

	l = new lights("Scene1.light");
	v = new view("Scene1.view");
	s = new scenes("Scene1.scene");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutMainLoop();
	return 0;
}

void LoadShaders()
{
	MyShader = glCreateProgram();
	if (MyShader != 0)
	{
		ShaderLoad(MyShader, "../../test1/hw3.vs", GL_VERTEX_SHADER);
		ShaderLoad(MyShader, "../../test1/hw3.fs", GL_FRAGMENT_SHADER);
	}
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);

	v->viewing();
	l->lighting();
	glUseProgram(MyShader);
	s->scene_setting(MyShader);

	glutSwapBuffers();

	glDisable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			v->zoom(1);
		break;
		case 'a':
			v->rotate(1);
		break;
		case 's':
			v->zoom(0);
		break;
		case 'd':
			v->rotate(0);
		break;
		default:
			if (key >= '0' && key <= '9')
				s->select(key - '0');
		break;
	}
	glutPostRedisplay();
}
/*
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state)
				s->set_x_y(-1, -1);
			else
				s->set_x_y(x, y);
		break;
		case GLUT_RIGHT_BUTTON :
			if (state)
				s->set_x_y(-1, -1);
			else
				s->set_x_y(x, y);
		break;
	}
}

void mouse_motion(int x, int y)
{
	s->move(x, y, v->viewport[2], v->viewport[3]);
	s->set_x_y(x, y);
	glutPostRedisplay();
}
*/

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state)
			l->set_start_pos(-1, -1);
		else
			l->set_start_pos(x, y);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state)
			l->set_start_pos(-1, -1);
		else
			l->set_start_pos(x, y);
		break;
	}
}

void mouse_motion(int x, int y)
{
	l->move_light(x, y, v->viewport[2], v->viewport[3]);
	l->set_start_pos(x, y);
	glutPostRedisplay();
}