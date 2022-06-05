#pragma once
#include "AllStandartHeaders.h"
class Buss
{
private:
	float fuel;
	float speed;
	int passengers;
	static int ClassCreationCount;
public:
	// Constructors
	Buss();
	Buss(float fuel_amount);
	Buss(float fuel_amount, int passengers_amount);
	//Destructors
	~Buss();
	//Methods
	void SetDefaults(); // uninitialized variables gives random and strange results;
	void FillFuel(float litre);
	void Accelerate();
	void Brake();
	void AddPassengers(int passengers);
	void Dashboard() const;
	//Static Member Functions
	static void GetShowCount();

};

