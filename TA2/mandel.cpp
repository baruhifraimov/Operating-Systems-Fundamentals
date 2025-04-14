#include <iostream>
#include <complex>
#include <string>
#include <cmath>
#include "mandel.hpp"


bool is_in_mandelbrot(std::complex<double> z,int n){
	std::complex<double> z_start = 0;
	for (int i = 0; i < n; i++)
	{
		z_start = z + std::pow(z_start,2);
		if (std::abs(z_start)>=n){
			return false;
		}
	}
	
	return true;
}