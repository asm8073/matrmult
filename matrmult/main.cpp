//
//  main.cpp
//  matrmult
//
//  Created by Anton Selikhov on 10/09/2020.
//  Copyright © 2020 Anton Selikhov. All rights reserved.
//
#include <cblas.h>

#include <random>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<typename T> class matrix {

public:
  matrix(const size_t& n) : n_(n), data_(n_*n_) {}
    
  T* data() { return data_.data(); }
    
  const T* data() const { return data_.data(); }
    
  std::vector<T>& vec() { return data_; }
    
  size_t const& n() const { return n_; }
    
  const std::vector<T>& vec() const { return data_; }

private:
  size_t n_;
  std::vector<T> data_;

};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(-1.0, 1.0);

template<typename T> matrix<T> random(const size_t& n) {
  matrix<T> m(n);
  std::generate_n(m.vec().begin(), m.vec().size(), std::bind(dis, gen));
  return m;

}

template<typename T> ostream& operator<<(ostream& o, const matrix<T>& m) {
  auto const n = m.n();
  size_t j = 0;
  for (auto const& i : m.vec()) {
    o << i <<" ";
    if(j++%n == n-1) o << endl;
  }
  return o;
}

int main () {

    const size_t n = 1000;
    
    int a = 100;
    
    int *pa = &a;
    
    cout << "a= " << a << endl;
    
    (*pa) = 120;
    
    cout << "a= " << a << endl;
    
    matrix<float> A = random<float>(n), B = random<float>(n), C(n);
 //   cout << A << endl << B << endl;

    auto start = high_resolution_clock::now();
    
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n,
              1.0, A.data(), n, B.data(), n, 0.0, C.data(), n);
    auto stop = high_resolution_clock::now();
    
//    cout << C << endl;
    
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    
    return 0;
}

