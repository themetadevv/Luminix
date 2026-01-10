
#include "lxglpch.h"
#include "lxgldebug.h"
#include "lxgl.h"

int LoadOpenGL(GLADloadproc fp) {
	return gladLoadGLLoader(fp);
}

void Draw(lxu32 count) {
	glCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}