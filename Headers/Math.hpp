#ifndef MATH_HPP
#define MATH_HPP

namespace Math {
template <typename T> inline int signof(T n) { return (n > 0) - (n < 0); }
} // namespace Math

#endif
