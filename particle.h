// Clive Marvelous, last updated 15/3/24

#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<string>
#include<vector>
#define light_spd 2.99792458e8 // m/s

using std::string;

// Beginning of particle class
class particle
{
private:
  string particle_name;
  int charge;
  std::vector<double>* four_momentum; // MeV
  
  // Validation functions
  double validate_energy(double energy_in) 
  {
    if(energy_in<0) throw std::invalid_argument("Energy cannot be negative.");
    else if(energy_in>light_spd) throw std::invalid_argument("Energy cannot be greater than the speed of light.");
    return energy_in/light_spd;
  }
  int validate_charge(int charge_in) 
  {
    if(charge_in != 1 && charge_in != -1) throw std::invalid_argument("Charge must be either +1 or -1.");
    return charge_in;
  }
  double safe_get(size_t index) const 
  {
    // Check for nullptr
    if(four_momentum == nullptr) throw std::logic_error("Error: four_momentum is nullptr");
    return four_momentum->at(index);
  }
  void safe_set(size_t index, double value) 
  {
    // Check for nullptr
    if(four_momentum == nullptr) throw std::logic_error("Error: four_momentum is nullptr.");
    four_momentum->at(index) = value;
  }

public:
  // Constructors
  particle() : particle_name{}, charge{}, four_momentum{new std::vector<double>(4)} {std::cout<<"Default constructor"<<std::endl;}
  particle(string particle_name, int particle_charge, double E, double px, double py, double pz) : 
    particle_name{particle_name}, charge{validate_charge(particle_charge)} 
    {
      std::cout<<"Constructing "<<particle_name<<std::endl;
      four_momentum = new std::vector<double>; 
      four_momentum->push_back(validate_energy(E));
      four_momentum->push_back(px);
      four_momentum->push_back(py);
      four_momentum->push_back(pz);
    }

  // Destructor
  ~particle() 
  {
    delete four_momentum; // Deallocate memory
    std::cout<<"Destroying "<<particle_name<<std::endl;
  }

  // The copy constructor needs to make a deep copy of the std::vector holding the 4-momentum
  particle(const particle&); 
  particle& operator=(const particle&);
  
  // Move constructor and assignment operator
  particle(particle&&);
  particle& operator=(particle&&);
  
  // Getter functions (accessors) to individual elements of 4-momentum
  double get_E() const {return safe_get(0);}
  double get_px() const {return safe_get(1);}
  double get_py() const {return safe_get(2);}
  double get_pz() const {return safe_get(3);}

  // Setter functions, to change values of 4-momentum
  void set_E(double E) {safe_set(0, validate_energy(E));}
  void set_px(double px) {safe_set(1, px);}
  void set_py(double py) {safe_set(2, py);}
  void set_pz(double pz) {safe_set(3, pz);}

  // Dot product function
  double dotProduct(const particle& p) const
  {
    // Check for nullptr
    if(four_momentum == nullptr || p.four_momentum == nullptr) 
    {
      std::cout<<"Error: four_momentum is nullptr"<<std::endl;
      return 0;
    }

    // Calculation
    double sum{four_momentum->at(0)*p.four_momentum->at(0)};
    for(size_t i = 1; i<four_momentum->size(); ++i)
    {
      sum -= four_momentum->at(i)*p.four_momentum->at(i);
    }
    return sum;
  }

  // Overload sum operator
  std::vector<double> operator+(const particle& p) const
  {
    // Check for nullptr
    if(four_momentum == nullptr || p.four_momentum == nullptr) 
    {
      throw std::logic_error("Error: four_momentum is nullptr");
    }
    std::vector<double> sum(four_momentum->size()); 
    for(size_t i = 0; i<sum.size(); ++i) sum[i] = four_momentum->at(i) + p.four_momentum->at(i);
    return sum;
  }

  // Antiparticle function
  particle antiparticle(double E, double px, double py, double pz)  
  {
    // Anti particle object
    particle antipart = *this;

    // Update name and charge 
    if(particle_name == "electron") antipart.particle_name = "positron";
    else if(particle_name == "positron") antipart.particle_name = "electron";
    else if(particle_name == "muon") antipart.particle_name = "antimuon";
    else if(particle_name == "antimuon") antipart.particle_name = "muon";
    antipart.charge = -charge;

    // Update the four_momentum 
    *antipart.four_momentum = {validate_energy(E), px, py, pz};

    return antipart;
  }

  // Function to print info about a particle 
  void print_data();
};

// Implementation of functions
// Copy constructor 
particle::particle(const particle& p)
{
  std::cout<<"Calling copy constructor"<<std::endl;
  particle_name = p.particle_name;
  charge = p.charge;
  four_momentum = new std::vector<double>(*p.four_momentum);
}
// Copy assignment
particle & particle::operator=(const particle& p) 
{
  std::cout<<"Calling copy assignment"<<std::endl;
  // Check for self-assignment
  if(&p != this) 
  { 
    particle_name = p.particle_name;
    charge = p.charge;
    delete four_momentum; 
    four_momentum = new std::vector<double>(*p.four_momentum);
  }
  return *this;
}

// Move constructor 
particle::particle(particle &&p)
{ 
  std::cout <<"Calling move constructor"<<std::endl;
  if(&p != this) // Prevent self-move
  {
    particle_name = std::move(p.particle_name);
    charge = p.charge;
    four_momentum = p.four_momentum;
    p.charge = 0; 
    p.four_momentum = nullptr;
  }
}
// Move assginment
particle & particle::operator=(particle&& p)
{
  std::cout<<"Calling move assignment"<<std::endl;
  if(&p != this) // Prevent self-move
  {
    std::swap(particle_name, p.particle_name);
    std::swap(charge, p.charge);
    std::swap(four_momentum, p.four_momentum);
  }
  return *this;
}

// Print function
void particle::print_data()
{
  // Check for nullptr
  if(four_momentum == nullptr) 
  {
    std::cout<<"Particle data not found"<<std::endl;
    return;
  }

  size_t vector_size{four_momentum->size()};
  std::cout<<"Particle: [name, charge, E/c, px, py, pz] = ["<<particle_name<<", "<<charge<<", ";
  std::cout.precision(3);
  for(size_t i=0; i<vector_size; ++i) 
  {
    std::cout<<four_momentum->at(i);
    if(i != vector_size-1) std::cout<<", ";
  }
  std::cout<<"]"<<std::endl;
  return;
}

#endif