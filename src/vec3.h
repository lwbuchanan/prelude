#pragma once

#include <cmath>
#include <ostream>
class vec3 {
public:
  // vector components
  double c[3];

  // Zero vector
  vec3() : c{0, 0, 0} {}

  // Typical vector constructor
  vec3(double c0, double c1, double c2) : c{c0, c1, c2} {}

  // Getters
  double x() const { return c[0]; }
  double y() const { return c[1]; }
  double z() const { return c[2]; }

  // Inverter
  vec3 operator-() const { return vec3(-c[0], -c[1], -c[2]); }

  // Index-wise getters
  double operator[](int i) const { return c[i]; }
  double &operator[](int i) { return c[i]; }

  // Math operations
  vec3 &operator+=(const vec3 &v) {
    c[0] += v.c[0];
    c[1] += v.c[1];
    c[2] += v.c[2];
    return *this;
  }

  vec3 &operator*=(double t) {
    c[0] *= t;
    c[1] *= t;
    c[2] *= t;
    return *this;
  }

  vec3 &operator/=(double t) { return *this *= 1 / t; }

  double length_squared() const {
    return c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
  }

  double length() const { return std::sqrt(length_squared()); }
};

// Convenient alias for some gemetry semantics
using point3 = vec3;

// Other utility functions

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.c[0] << ' ' << v.c[2] << ' ' << v.c[2];
}

inline vec3 operator+(const vec3 &u, const vec3 v) {
  return vec3(u.c[0] + v.c[0], u.c[1] + v.c[1], u.c[2] + v.c[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 v) {
  return vec3(u.c[0] - v.c[0], u.c[1] - v.c[1], u.c[2] - v.c[2]);
}

// Component-wise multiplication (NOT DOT)
inline vec3 operator*(const vec3 &u, const vec3 v) {
  return vec3(u.c[0] * v.c[0], u.c[1] * v.c[1], u.c[2] * v.c[2]);
}

// Scalar multiplication
inline vec3 operator*(double t, const vec3 v) {
  return vec3(t * v.c[0], t * v.c[1], t * v.c[2]);
}

// Also scalar multiplication
inline vec3 operator*(const vec3 v, double t) { return t * v; }

// Scalar division
inline vec3 operator/(const vec3 v, double t) { return (1 / t) * v; }

inline double dot(const vec3 &u, const vec3 v) {
  return u.c[0] * v.c[0] + u.c[1] * v.c[1] + u.c[2] * v.c[2];
}

inline vec3 cross(const vec3 &u, const vec3 v) {
  return vec3(u.c[1] * v.c[2] - u.c[2] * v.c[1],
              u.c[0] * v.c[2] - u.c[2] * v.c[0],
              u.c[1] * v.c[0] - u.c[0] * v.c[1]);
}

// "Normalize" the vector to length 1.0
inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

