#include <iostream>
#include <complex>
#include <string>
#include <cmath>

#define N 99

bool checkIfMandel(std::complex<double> z,int n){
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

int main(int argc, char* argv[]) {
    if(argc < 3 || argc > 4){
        std::cerr << "INVALID ARGUMENTS" << std::endl;
        exit(1);
    }

    std::complex<double> z(std::stod(argv[1]), std::stod(argv[2]));
    if(argc == 4){
        if(checkIfMandel(z,(int)std::stod(argv[3]))){
            std::cout<< z.real() << " + " << z.imag() << "i" << " is in the MandelBrot set" << std::endl;
            return 0;
        }
        else{
            std::cout<< z.real() << " + " << z.imag() << "i" << " is not in the MandelBrot set" << std::endl;
            return 0;
        }
    }
    else{
        if(checkIfMandel(z,N)){
        std::cout<< z.real() << " + " << z.imag() << "i" << " is in the MandelBrot set" << std::endl;
            return 0;
        }
        else{
            std::cout<< z.real() << " + " << z.imag() << "i" << " is not in the MandelBrot set" << std::endl;
            return 0;
        }
    }
}