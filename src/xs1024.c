#include <time.h>
#include <math.h>
#include <string.h>
#include "xs/xs1024.h"

uint64_t splitmix64(uint64_t seed) {
  uint64_t z = (seed += UINT64_C(0x9E3779B97F4A7C15));
  z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
  z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
  return z ^ (z >> 31);
}

void splitmix64_arr(uint64_t seed, uint64_t *arr, size_t size) {
  while (size-- > 0) {
    seed = splitmix64(seed);
    *arr++ = seed;
  }
}

void xs1024_init(xs1024 *r, uint64_t seed) {
  splitmix64_arr(seed, r->state, 16);
  r->p = 0;
}

void xs1024_init_time(xs1024 *r) {
  xs1024_init(r, time(NULL));
}

void xs1024_init_jump(xs1024 *r, const xs1024 *r0) {
  r->p = r0->p;
  memcpy((void*)&r->state[0], (void*)&r0->state[0], 16 * sizeof(uint64_t));
  xs1024_jump(r);
}

uint64_t xs1024_next(xs1024 *r) {
  const uint64_t s0 = r->state[r->p];
  uint64_t s1 = r->state[r->p = (r->p + 1) & 15];
  s1 ^= s1 << 31; // a
  r->state[r->p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b, c
  return r->state[r->p] * UINT64_C(1181783497276652981);
}

double xs1024_double(xs1024 *r) {
  const union { uint64_t i; double d; } u = {
    .i = UINT64_C(0x3FF) << 52 | xs1024_next(r) >> 12
  };
  return u.d - 1.0;
}

double xs1024_normal(xs1024 *r) {
  double n0, n1, s;
  do {
    n0 = 2.0 * xs1024_double(r) - 1.0;
    n1 = 2.0 * xs1024_double(r) - 1.0;
    s = n0 * n0 + n1 * n1;
  } while (s >= 1 || s == 0);
  return n0 * sqrt(-2.0 * log(s) / s);
}

void xs1024_normals(xs1024 *r, double *n0, double *n1) {
  double s;
  do {
    *n0 = 2.0 * xs1024_double(r) - 1.0;
    *n1 = 2.0 * xs1024_double(r) - 1.0;
    s = (*n0) * (*n0) + (*n1) * (*n1);
  } while (s >= 1 || s == 0);
  s = sqrt(-2.0 * log(s) / s);
  *n0 *= s;
  *n1 *= s;
}

int xs1024_poisson(xs1024 *r, double lambda) {
  const double l = pow(2.71828182845904523536, -lambda);
  double p = 1.0;
  int k = 0;
  do {
    ++k;
    p *= xs1024_double(r);
  } while (p > l);
  return k - 1;
}

double xs1024_exp(xs1024 *r) {
  double x = xs1024_double(r);
  while (x == 0.0)
    x = xs1024_double(r);
  return -log(x);
}

void xs1024_jump(xs1024 *r) {
  static const uint64_t JUMP[] = { 0x84242f96eca9c41d,
    0xa3c65b8776f96855, 0x5b34a39f070b5837, 0x4489affce4f31a1e,
    0x2ffeeb0a48316f40, 0xdc2d9891fe68c022, 0x3659132bb12fea70,
    0xaac17d8efa43cab8, 0xc4cb815590989b13, 0x5ee975283d71c93b,
    0x691548c86c1bd540, 0x7910c41d10a1e6a5, 0x0b5fc64563b3e2a8,
    0x047f7684e9fc949d, 0xb99181f2d8f685ca, 0x284600e3f30e38c3
  };

  uint64_t t[16] = { 0 };
  int i, b, j;
  for (i = 0; i < sizeof JUMP / sizeof *JUMP; ++i) {
    for (b = 0; b < 64; ++b) {
      if (JUMP[i] & 1ULL << b) {
        for (j = 0; j < 16; ++j)
          t[j] ^= r->state[(j + r->p) & 15];
      }
      xs1024_next(r);
    }
  }
  for (j = 0; j < 16; j++)
    r->state[(j + r->p) & 15] = t[j];
}
