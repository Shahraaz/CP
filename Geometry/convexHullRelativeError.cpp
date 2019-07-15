#include <algorithm>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

/* A flag used by some geometry routines to indicate exceptional circumstances.
 */
static bool geoerror;

/* Uncomment to switch to floating point calculations.  Whenever possible you
 * should try to avoid this but it can occasionally be necessary if the
 * intermediate numbers can get quite large or you need line-line intersections.
 * It's safer to use floats if you're unsure what to do. */
#define USE_FLOAT

/* Use this if the magnitude of numbers being compared can get quite large.
 * This adjusts the fudge factor in comparisons to grow with the magnitude of
 * the numbers being compared (it's probably safest to turn this on when using
 * floats). */
#define USE_RELATIVE_ERROR

#ifdef USE_FLOAT
/* When comparing floating point numbers it's necessary to use a fudge factor to
 * test for less than, less than equal, and equality. */
#define EPS 1e-9
typedef double num;
#else
#define EPS 0
typedef long long num;
#endif

inline num nabs(num x) {
  return x < 0 ? -x : x;
}

/* Define basic numeric comparison routines. */
bool num_lt(num X, num Y) { /* numeric less than */
#ifdef USE_RELATIVE_ERROR
  return X + max(num(1), nabs(Y)) * EPS < Y;
#else
  return X + EPS < Y;
#endif
}

bool num_lteq(num X, num Y) { /* numeric less than equal */
#ifdef USE_RELATIVE_ERROR
  return X <= Y + max(num(1), nabs(Y)) * EPS;
#else
  return X <= Y + EPS;
#endif
}

bool num_eq(num X, num Y) { /* numeric equality */
#ifdef USE_FLOAT
  return num_lteq(X, Y) && num_lteq(Y, X);
#else
  return X == Y;
#endif
}

/* A point is represented as a complex number.  This definition allows adding
 * points through the standard + operator and allows for rotations through
 * multiplication.  Additionally you can use the standard output operator with
 * cout for debugging. */
typedef complex<num> point;
typedef vector<point> poly;

/* A line is defined in the form dot(norm, A) = C. */
struct line {
  line(point norm, num C) : norm(norm), C(C) {}
  point norm;
  num C;
};

/* Computes the cross product of A and B relative to the optional origin, C. */
num cp(point A, point B, point C = point(0, 0)) {
  A -= C; B -= C;
  return A.real() * B.imag() - B.real() * A.imag();
}

/* Returns true if C is strictly counter-clockwise AB in cartesian coordinates.
 * In other words as you walk from A to B, C would be on your left.  */
bool ccw(point A, point B, point C) {
  return num_lt(0, cp(A, B, C));
}

/* Same but returns true if the three points are colinear as well */
bool ccweq(point A, point B, point C) {
  return num_lteq(0, cp(A, B, C));
}

/* Returns the dot (inner) product of A and B relative to an optional origin C.
 */
num dot(point A, point B, point C = point(0, 0)) {
  A -= C; B -= C;
  return A.real() * B.real() + A.imag() * B.imag();
}

/* pointCmp, angleCmp, unwind, and hull are all part of an O(N log N) convex
 * hull implementation. */
bool pointCmp(point A, point B) {
  return make_pair(A.real(), A.imag()) < make_pair(B.real(), B.imag());
}

point pivot;

bool angleCmp(point A, point B) {
  num c = cp(pivot, A, B);
  return num_eq(c, 0) && dot(A, A, pivot) < dot(B, B, pivot) || num_lt(0, c);
}

void unwind(poly& P, point A) {
  int sz = P.size();
  while(sz > 1 && ccweq(A, P[sz - 1], P[sz - 2])) --sz;
  P.resize(sz);
}

/* Computes the convex hull of the list of points P.  Returns the points
 * defining the convex hull in ccw order. */
poly hull(poly P) {
  swap(P[0], *min_element(P.begin(), P.end(), pointCmp));
  pivot = P[0];
  sort(P.begin() + 1, P.end(), angleCmp);

  poly ret(1, pivot);
  for(int i = 1; i < P.size(); i++) {
    unwind(ret, P[i]);
    ret.push_back(P[i]);
  }
  unwind(ret, pivot);
  return ret;
}

/* Check if A is in the convex polygon P (in ccw order) in O(log(N)) time.  If
 * on is false A must be strictly in the interior of P. */
bool in_convex(poly& P, point A, bool on) {
  if(ccw(P[0], A, P[1]) || ccw(P[0], P.back(), A)) return false;
  int lo = 1;
  int hi = P.size() - 2;
  while(lo < hi) {
    int md = (lo + hi + 1) / 2;
    if(ccw(P[0], P[md], A)) {
      lo = md;
    } else {
      hi = md - 1;
    }
  }
  return (on || lo != 1 ? ccweq : ccw)(P[0], P[lo], A) &&
         (on ? ccweq : ccw)(P[lo], P[lo + 1], A) &&
         (on || lo + 2 != P.size() ? ccweq : ccw)(P[lo + 1], P[0], A);
}

/* Returns the line that passes through points A and B */
line get_line(point A, point B) {
  point norm(B.imag() - A.imag(), A.real() - B.real());
  return line(norm, dot(A, norm));
}

/* Returns the line that passes between A and B orthogonal to the line formed by
 * A and B. */
line bisector(point A, point B) {
  point norm(B.real() - A.real(), B.imag() - A.imag());
  return line(norm * num(2), dot(norm, A + B));
}

/* Returns the point where lines A and B intersect.  Sets geoerror to true if
 * the lines are parallel. */
point intersect(line A, line B) {
  num det = A.norm.real() * B.norm.imag() - A.norm.imag() * B.norm.real();
  if(num_eq(det, 0)) {
    geoerror = true;
    return point(0, 0);
  }
  return point(B.norm.imag() * A.C - A.norm.imag() * B.C,
               -B.norm.real() * A.C + A.norm.real() * B.C) / det;
}

/* Returns the center of the circle that contains the three points A, B, and C.
 * If the points are colinear sets geoerror to true. */
point get_circle_center(point A, point B, point C) {
  return intersect(bisector(A, B), bisector(B, C));
}

/* Returns true if X is on the line segment with endpoints at A and B.  If
 * closed is false X does not include A and B itself. */
bool on_segment(point A, point B, point X, bool closed = true) {
  point lnorm(B.imag() - A.imag(), A.real() - B.real());
  point bnorm(B.real() - A.real(), B.imag() - A.imag());
  if(!num_eq(dot(lnorm, A), dot(lnorm, X))) {
    return false;
  }
  num AN = dot(bnorm, A);
  num BN = dot(bnorm, B);
  num XN = dot(bnorm, X);
  if(BN < AN) {
    swap(AN, BN);
  }
  return (closed ? num_lteq : num_lt)(AN, XN) &&
         (closed ? num_lteq : num_lt)(XN, BN);
}

/* Rotates the point X by R around the center C (and scales by the magnitude of
 * R).  If you want to rotate counter-clockwise by ang radians you should use
 *
 * rotate(X, exp(point(0, ang)), C)
 */
point rotate(point X, point R, point C = 0) {
  return (X - C) * R + C;
}

/* Returns the area of the simple (not-necessarily convex) polygon P
 * (in ccw order).  However when using integer arithmetic the area may be a
 * half integer.  In this case you can set nohalf to true and twice the area
 * will be returned.
 *
 * If P is clockwise order the result will be negative.
 */
num area(poly P, bool nohalf = false) {
  num result = 0;
  for(int i = 1; i + 1 < P.size(); i++) {
    result += cp(P[i], P[i + 1], P[0]);
  }
  return nohalf ? result : result / 2;
}