// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
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
  mat3 AMat = mat3(0, axis.z, -1*axis.y,
		   -1*axis.z, 0, axis.x,
		   axis.y, -1*axis.x, 0);

  // create rotation matrix
  return cos(rad) * I + PMat * (1 - cos(rad)) + AMat * sin(rad);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotMat = Transform::rotate(degrees, up);
  up = rotMat * glm::normalize(up);
  eye = rotMat * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // prepare rotation axis
  vec3 w = glm::normalize(eye);
  vec3 v = glm::normalize(up);
  vec3 rotAxis = glm::normalize(glm::cross(w, v));


  // generate rotation matrix
  mat3 rotMat = Transform::rotate(degrees, rotAxis);
  
  // apply rotation matrix to eye and up vecs
  eye = rotMat * eye;
  up = rotMat * glm::normalize(up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
  // create a coordinate frame for camera
  vec3 w = glm::normalize(eye - center);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::normalize(glm::cross(w, u));

  // rotation matrix
  mat3 R = glm::transpose(mat3(u, v, w));
  
  // translation
  vec3 T(-glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye));

  // return matrix  
  return mat4(vec4(R[0], 0.0),
	      vec4(R[1], 0.0),
	      vec4(R[2], 0.0),
	      vec4(T, 1.0));

}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.  
  float d = 1 / tan(glm::radians(fovy) / 2.0);

  return mat4(d / aspect, 0.0, 0.0, 0.0,
	      0.0, d, 0.0, 0.0,
	      0.0, 0.0, (zFar + zNear) / (zNear - zFar), -1.0,
	      0.0, 0.0, (2.0 * zFar * zNear) / (zNear - zFar), 0.0);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  mat4 ret(sx, 0.0, 0.0, 0.0,
	      0.0, sy, 0.0, 0.0,
	      0.0, 0.0, sz, 0.0,
	      0.0, 0.0, 0.0, 1.0);
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
   // YOUR CODE FOR HW2 HERE
  // Implement translation 
  mat4 ret(1.0, 0.0, 0.0, 0.0,
	      0.0, 1.0, 0.0, 0.0,
	      0.0, 0.0, 1.0, 0.0,
	      tx, ty, tz, 1.0);
  return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 &zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}



