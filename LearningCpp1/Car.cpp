#include "Car.h"
int Car::ClassCreationCount = 0;

// There is some code reputation. If you want know how to eliminate it look at "buss" class.

//Constructors
Car::Car()
{
	++ClassCreationCount;
	fuel = 0;
	speed = 0;
	passengers = 0;
	std::cout << "Car() constructor" << ClassCreationCount << '.' << "object\n";;
	// SetDefaults(); // I initialized values during declaration.
}
Car::Car(float amount)
{
	++ClassCreationCount;
	fuel = amount;
	speed = 0;
	passengers = 0;
	std::cout << "Car(float amount) constructor" << ClassCreationCount << '.' << "object\n";;
}

// Destructors
Car::~Car()
{
	--ClassCreationCount;
	std::cout << "\nCar destructor" << ClassCreationCount << '.' << "object\n";
}


// Methots
void Car::SetDefaults()
{
	fuel = 0;
	speed = 0;
	passengers = 0;
	for (size_t i = 0; i < sizeof(seats_unoccupied); ++i)
	{
		seats_unoccupied.at(i) = i;
	}
	*plate = 'p';
}

void Car::FillFuel(float litre)
{
	fuel = litre;
}

void Car::Accelerate()
{
	speed++;
	fuel -= 0.5f;
}

void Car::Brake()
{
	speed = 0;
}

void Foo(const Car& car) {}
void Car::AddPassengers(int passengers)
{
	/*
	* this increases readability and help to compiler
		implies "this->passengers" is the member of the class
		"passengers" is the argument of method.
	* Most important use case is "this pointer" is that it is a good argument when using class as a function or method input and output argument. Use it with dereference.
	*/
	// passengers = passengers; // Valid
	this->passengers = passengers; // Valid
	Foo(*this);

}

void Car::Dashboard() const
{
	// this->fuel++; // !!! Error !!! // You are trying to change member variable inside const function. BE CARREFUL
	std::cout << '\n'
		<< "Fuel= " << fuel << " || "
		<< "Speed= " << speed << " || "
		<< "Passengers= " << passengers << " || "
		<< "ClassCreationCount = " << ClassCreationCount << '\n';
}

void Car::GetShowCount()
{
	std::cout << "Total cars: " << ClassCreationCount << '\n';
	// this->fuel = 50; // !!! Error !!!
}
