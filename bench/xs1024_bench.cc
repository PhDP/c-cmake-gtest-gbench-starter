#include "benchmark/benchmark.h"
#include <random>
#include "xs/xs1024.h"

static void BM_StdRandom(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::mt19937 gen(state.range(0));
    std::uniform_real_distribution<double> dis(0, 1);
    double sum = 0.0;
    for (int i = 0; i < state.range(0); ++i) sum += dis(gen);
  }
}
BENCHMARK(BM_StdRandom)
    ->Args({10000})
    ->Args({100000})
    ->Args({1000000})
    ->Args({10000000});

static void BM_Xs1024(benchmark::State& state) {
  while (state.KeepRunning()) {
    xs1024 r;
    xs1024_init(&r, state.range(0));
    double sum = 0.0;
    for (int i = 0; i < state.range(0); ++i) sum += xs1024_double(&r);
  }
}
BENCHMARK(BM_Xs1024)
    ->Args({10000})
    ->Args({100000})
    ->Args({1000000})
    ->Args({10000000});

BENCHMARK_MAIN();
