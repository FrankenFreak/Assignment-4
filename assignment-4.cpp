// PHYS 30762 Programming in C++
// Assignment 4
// Practice special functions and operators in C++ classes
// Author: Clive Marvelous (10916086)
// Date: 13/3/24

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<cctype>
#include<algorithm>
#include "particle.h"

#define light_spd 2.99792458e8 // m/s

using std::string;

// Main program
int main()
{
  // Create the following particles: 
  // two electrons, four muons, one antielectron, one antimuon 
  particle electron1("electron", -1, 5110, 900, 800, 700); 
  particle electron2("electron", -1, 5110, -900, 850, -750);
  particle antielectron1 = electron1.antiparticle(5110, -900, -800, -700);
  particle muon1("muon", -1, 120000, 30000, -20000, 10000); 
  particle muon2("muon", -1, 120000, 40000, 25000, -15000);
  particle muon3("muon", -1, 120000, -35000, 20000, 5000);
  particle muon4("muon", -1, 120000, -45000, -30000, 20000);
  particle antimuon1 = muon1.antiparticle(120000, -30000, 20000, -10000);

  // (optional but nice) Print out the data from all the particles (put them in a vector)
  std::vector<particle> particle_data{electron1, electron2, antielectron1, muon1, muon2, muon3, muon4, antimuon1};
  std::cout<<std::endl;
  for(auto particle_it=particle_data.begin(); particle_it!=particle_data.end(); ++particle_it) particle_it->print_data();
  std::cout<<std::endl;

  // Sum the four-momenta of the two electrons 
  std::vector<double> four_momentum_sum = electron1 + electron2;
  std::cout<<"Sum of four momentum of the two electrons: [E/c, px, py, pz] = [";
  std::cout<<four_momentum_sum[0]<<", "<<four_momentum_sum[1]<<", "<<four_momentum_sum[2]<<", "<<four_momentum_sum[3]<<"]"<<std::endl;

  // Do the dot product of the first two four-muons
  double dot_product = muon1.dotProduct(muon2);
  std::cout<<"Dot product of the first two muons = "<<dot_product<<std::endl;
  std::cout<<std::endl;

  // Assignment operator of an electron to a new electron
  particle electron3;
  electron3 = electron1;
  std::cout<<"electron1 ";
  electron1.print_data();
  std::cout<<"electron3 ";
  electron3.print_data();
  std::cout<<std::endl;

  // Copy constructor of the first muon to a new muon
  particle muon5{muon1};
  std::cout<<"muon1 ";
  muon1.print_data();
  std::cout<<"muon5 ";
  muon5.print_data();
  std::cout<<std::endl;

  // Move the antielectron into another antielectron using the move constructor 
  particle antielectron2{std::move(antielectron1)};
  std::cout<<"antielectron1 ";
  antielectron1.print_data();
  std::cout<<"antielectron2 ";
  antielectron2.print_data();
  std::cout<<std::endl;

  // Assign the antimuon to another antimuon using the move assignment
  particle antimuon2;
  antimuon2 = std::move(antimuon1);
  std::cout<<"antimuon1 ";
  antimuon1.print_data();
  std::cout<<"antimuon2 ";
  antimuon2.print_data();
  std::cout<<std::endl;

  return 0;
}
