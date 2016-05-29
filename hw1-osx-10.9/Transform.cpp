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

  // parallel component mat
  mat3 PMat = mat3(pow(axis.x, 2), axis.x * axis.y, axis.x * axis.z,
		   axis.x * axis.y, pow(axis.y, 2), axis.y * axis.z,
		   axis.x * axis.z, axis.y * axis.z, pow(axis.z, 2));

  // perpendicular component mat
  mat3 AMat = mat3(0, axis[2], -1*axis[1],
		   -1*axis[2], 0, axis[0],
		   axis[1], -1*axis[0], 0);

  // create rotation matrix
  return cos(rad) * I + (1 - cos(rad))*PMat + AMat * sin(rad);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotMat = Transform::rotate(degrees, up);
  eye = rotMat * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // prepare rotation axis
  vec3 w = glm::normalize(eye);
  vec3 v = glm::normalize(up);
  vec3 rotAxis = (glm::cross(w, v));

  // generate rotation matrix
  mat3 rotMat = Transform::rotate(degrees, rotAxis);
  
  // apply rotation matrix to eye and up vecs
  eye = rotMat * eye;
  up = rotMat * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // create a coordinate frame for camera
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::cross(w, u);

  // rotation matrix
  mat3 R = glm::transpose(mat3(u, v, w));
  
  // translation
  vec3 T(-glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye));

  // return matrix  
  return mat4(vec4(R[0], 0),
	      vec4(R[1], 0),
	      vec4(R[2], 0),
	      vec4(T, 1));

}

Transform::Transform()
{

}

Transform::~Transform()
{

}
