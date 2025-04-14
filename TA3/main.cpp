#include <iostream>
#include <complex>
#include "mandel.hpp"


int main(){
	std::complex<double> z;
	double a,b;
	do{
	std::cout << "Enter real and imag number:" << std::endl;
	std::cin >> a >> b;
	z.real(a);
	z.imag(b);
	if(is_in_mandelbrot(z,N)){
	std::cout<< z.real() << " + " << z.imag() << "i" << " is in the MandelBrot set\n" << std::endl;
		}
	else{
		std::cout<< z.real() << " + " << z.imag() << "i" << " is not in the MandelBrot set\n" << std::endl;
	}
}
	while(a!=0 && b!=0);
	return 0;
}