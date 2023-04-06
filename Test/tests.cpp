#include "test.hpp"
#include "../BiTree/BiTree.hpp"
#include <iostream>
#include <vector>
#include <chrono>

#define FILLER_AVARAGE 100
#define FINDER_AVARAGE 1000
#define ADD_DELETE_AVARAGE 1000
#define BUFFER_SIZE 10

using namespace std;

long long lcg(){
  static long long x = 0;
  x = (1021*x+24631) % 116640;
  return x;
}

int tests()
{
  auto start = chrono::high_resolution_clock::now();

  auto end = chrono::high_resolution_clock::now();

  chrono::duration<float> duration = end - start;

  duration.

  return EXIT_SUCCESS;
}