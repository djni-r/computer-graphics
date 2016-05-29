// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <stdio.h>
//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // convert degrees to rad
  const float rad = glm::radians(degrees);

  // init identity matrix
  mat3 I(1.0);

  // transpose axis  matrix
  mat3 axisMat = mat3(axis, vec3(0), vec3(0));
  mat3 axisMatT = glm::transpose(axisMat);
  
  // perpendicular component mat
  mat3 AMat = mat3(0, axis[2], -1*axis[1],
		   -1*axis[2], 0, axis[0],
		   axis[1], -1*axis[0], 0);

  // create rotation matrix
  mat3 rotMat = cos(rad) * I + glm::matrixCompMult(axisMat, axisMatT) + AMat * sin(rad);  
  printf("rotMat:\n");
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      printf("%0.1f  ", rotMat[j][i]);
    }
    printf("\n");
  }
  return rotMat;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  printf("\n\n---LEFT---\nCoordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.
x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
  mat3 rotMat = Transform::rotate(degrees, up);
  printf("BEFORE\neye: %f, %f, %f\n up: %f, %f, %f\n", eye.x, eye.y, eye.z, up.x, up.y, up.z);
  eye = rotMat * eye;
  printf("AFTER\neye: %f, %f, %f\n up: %f, %f, %f\n", eye.x, eye.y, eye.z, up.x, up.y, up.z); 
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // then should first undo the change
  printf("\n\n---UP---\nCoordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
  vec3 w = glm::normalize(eye);
  vec3 v = glm::normalize(up);
  vec3 rotAxis = glm::normalize(glm::cross(w, v));
  printf("rotAxis: %f, %f, %f\n", rotAxis.x, rotAxis.y, rotAxis.z);
  mat3 rotMat = Transform::rotate(degrees, rotAxis);
  printf("BEFORE\neye: %f, %f, %f\n up: %f, %f, %f\n", eye.x, eye.y, eye.z, up.x, up.y, up.z);

  if (eye.x != 0) {
    float rad2 = glm::acos(glm::dot(eye, vec3(1.0, eye.y, 0.0))/(glm::length(eye)*glm::length(vec3(1.0, eye.y, 0.0)))); 
    eye.x = 0.0;
    eye.z = 5.0;
    eye = rotMat * eye;
    mat3 rotMat2 = Transform::rotate(glm::degrees(rad2), up);
    eye = rotMat2 * eye;
  } else {
    eye = rotMat * eye;
  }
  up = rotMat * up;
  printf("AFTER\neye: %f, %f, %f\n up: %f, %f, %f\n", eye.x, eye.y, eye.z, up.x, up.y, up.z);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

  // You will change this return call
  return mat4();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
