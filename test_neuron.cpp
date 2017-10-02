//check slide 20 to creat the main
//on calcule exp(-h/tho) et (1-exp(-h/tho) une fois pour toute car il est constant au cours du temps
	//Iext est entré au début de la simulation, il s'agit d'une constante
	//qui est R?
	//tho= so called time of neuron, scaled time axis = 20 ms
	//takes 20 ms so V(t)=1/e V(b), speed of decay
	//t= n*h, ou h est infitésimal
//tho=R*C
	// Iext dans (0, 400) pA
	//1000 ms = durée simulation

#include <iostream>
#include <fstream>
#include "neuron.hpp"

using namespace std;

double simtime (0);
double simduration(1000);
double I_ext(200);
double I_ext_start(175);
double I_ext_end(840);

const double h (0.1); // = H du cpp, problème

int main() 
{
	cout << "How long do you want the simulation to be? (in ms, 1000 is good)" << endl;
	cin >> simduration;

	cout << "Please specify an external current I_ext (between 0 and 400)" << endl;
	cin >> I_ext;

	cout << "Please specify the time_start of I_ext (between 0 and the above promted simduration)"
			<< endl;
	cout << "175 is great" << endl;
	cin >> I_ext_start;

	cout << "Please specify the time_end of I_ext (between time_start and simduration)" << endl;
	cout << "840 is great" << endl;
	cin >> I_ext_end;

	Neuron neuron1;

	ofstream myfile;

	myfile.open ("neuron1.txt");

	while (simtime < simduration)
	{
		if((simtime >= I_ext_start) && (simtime <= I_ext_end))
	{
		neuron1.update(simtime, I_ext);		
	} else {
		neuron1.update(simtime, 0);
	}

	myfile << neuron1.getMemPot() << " ";

	simtime+=h;
	}
}