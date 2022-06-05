#include "Buss.h"
int Buss::ClassCreationCount = 0;

/*
Delegating constructors(calling other class constructors.)
If you don't want to repeat code, you should use it.

Also you can define "SetDefault function"
*/

//Constructors
Buss::Buss() : Buss(0) // Calls "Buss(float amount)"  -----------------------------------------------------
{	//																									   |
	std::cout << "\Buss() constructor" << ClassCreationCount << '.' << "object\n";//					   |
}	//																									   |
//																								-----------|
//  																							|jumps to other constructor
//  																							v		   
Buss::Buss(float amount) : Buss(amount, 0) // Cals "Buss(float fuel_amount, int passengers_amount)"--------|
{	//																									   |
	std::cout << "\Buss(float amount) constructor" << ClassCreationCount << '.' << "object\n";//		   |
}	//																									   |
//												-----------------------------------------------------------|
//  											|jumps to other constructor														   
//  											v
Buss::Buss(float fuel_amount, int passengers_amount)
{
	++ClassCreationCount;
	fuel = fuel_amount;
	speed = 0;
	passengers = passengers_amount;
	std::cout << "\Buss(float fuel_amount, int passengers_amount) constructor" << ClassCreationCount << '.' << "object\n";;
}

// Destructors
Buss::~Buss()
{
	--ClassCreationCount;
	std::cout << "\nCar destructor" << ClassCreationCount << '.' << "object\n";
}


// Methots
void Buss::SetDefaults()
{
	fuel = 0;
	speed = 0;
	passengers = 0;
}

void Buss::FillFuel(float litre)
{
	fuel = litre;
}

void Buss::Accelerate()
{
	speed++;
	fuel -= 0.5f;
}

void Buss::Brake()
{
	speed = 0;
}


void Buss::AddPassengers(int passengers)
{
	this->passengers = passengers;

}

void Buss::Dashboard() const
{
	// this->fuel++; // !!! Error !!! // You are trying to change member variable inside const function. BE CARREFUL
	std::cout << '\n'
		<< "Fuel= " << fuel << " || "
		<< "Speed= " << speed << " || "
		<< "Passengers= " << passengers << " || "
		<< "ClassCreationCount = " << ClassCreationCount << '\n';
}

void Buss::GetShowCount()
{
	std::cout << "Total cars: " << ClassCreationCount << '\n';
}
