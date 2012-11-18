// Transform.cpp: implementation of the Transform class.
#include <iostream>
using namespace std;
#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {

  mat3 I(1);
  mat3  Astar;
  mat3 Ax(0);
  mat3 rotationmat(0);

  Astar[0] = vec3(axis[0],0,0);
  Astar[1] = vec3(axis[1],0,0);
  Astar[2] = vec3(axis[2],0,0);
  Astar = mat3(axis,vec3(0),vec3(0))*Astar;

  Ax[0][1] = -axis[2];
  Ax[0][2] = axis[1];
  Ax[1][0] = axis[2];
  Ax[1][2] = -axis[0];
  Ax[2][0] = -axis[1];
  Ax[2][1] = axis[0];

  rotationmat =I*cos(glm::radians(degrees)) + Astar*(1-cos(glm::radians(degrees))) 
  + Ax*sin(glm::radians(degrees));

  return rotationmat;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  eye = rotate(-degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  vec3 ax = glm::normalize(glm::cross(up, eye));
  eye = rotate(degrees,ax) * eye;
  up = rotate(degrees,ax) * up;
  
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {

	vec3 u = glm::normalize(eye);
	vec3 v = -glm::normalize(glm::cross(u,up));
	vec3 z = glm::normalize(glm::cross(u,v));
	mat3 rot(v,z,u);
	
	mat4 final;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
			final[i][j] = rot[i][j];
	}

	for(int i = 0; i < 3; i++){
		final[3][i] = 0;
	}

	for(int i = 0; i < 3; i++){
		final[i][3] = -glm::dot(rot[i],eye);
	}

	final[3][3] = 1;
  return final;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
