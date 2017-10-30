#include "network.hpp"

using namespace std;

Network::Network(unsigned int NbNeurons)
: neurons_graphe_(NbNeurons, vector<unsigned int>())
{
	for (unsigned int i(0); i<NbNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron());
		Neurons_.push_back(p_neuron);	
	}
}

Network::Network(unsigned int nbExciNeurons, unsigned int nbInhiNeurons)
: neurons_graphe_(nbExciNeurons+nbInhiNeurons, vector<unsigned int> (nbExciNeurons+nbInhiNeurons))
{
	for (unsigned int i(0); i<nbExciNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron(true));
		Neurons_.push_back(p_neuron);	
	}

	for (unsigned int i(0); i<nbInhiNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron(false));
		Neurons_.push_back(p_neuron);	
	}

	creatRandomCon(nbExciNeurons, nbInhiNeurons);
}

Neuron* Network::getNeuron(unsigned int ID)
{
	return Neurons_[ID];
}

void Network::addPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur)
{
	neurons_graphe_[IDPreNeur].push_back(IDPostNeur);
}

void Network::creatRandomCon(unsigned int nbExciNeurons, unsigned int nbInhiNeurons)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distExci(0, nbExciNeurons-1);
	uniform_int_distribution<> distInhi(nbExciNeurons, nbExciNeurons+nbInhiNeurons-1);


	for (unsigned int i(0); i< Neurons_.size(); ++i) {

		for (unsigned int j(0); j < nbExciNeurons/10; ++j) {
			addPostSynap(distExci(gen), i);
		}

		for (unsigned int k(0); k < nbInhiNeurons/10; ++k) {
			addPostSynap(distInhi(gen), i);
		}
	}
}


void Network::update (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence)
{
	unsigned int TotNbNeurons(Neurons_.size());

	for (unsigned int k(0); k < nbSteps; ++k) {

		if((k >= Iext_start) && (k <= Iext_stop)) {
			getNeuron(0)->setIext(Iext);
		} else {
			getNeuron(0)->setIext(0.0);
		}
			
		for (unsigned int i(0); i < TotNbNeurons; ++i) {
						
			if (getNeuron(i)->update(1, backgroundInfluence)) {

				for (auto PostSynap : neurons_graphe_[i]) {

					if(getNeuron(i)->isExcitatory()) {
					getNeuron(PostSynap)->addArrivingSpike(k+D, 1);						
					} else {
					getNeuron(PostSynap)->addArrivingSpike(k+D, g);
					}
					
				}
			}				
		}
	}
}

void Network::updateWritingPot (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence, string filename)
{
	unsigned int TotNbNeurons(Neurons_.size());

	vector<double> mempot_values (TotNbNeurons);

	ofstream myfile;

	myfile.open (filename+".dat");

	myfile << TotNbNeurons << "\n";

	for (unsigned int k(0); k < nbSteps; ++k) {

		if((k >= Iext_start) && (k <= Iext_stop)) {
			getNeuron(0)->setIext(Iext);
		} else {
			getNeuron(0)->setIext(0.0);
		}
			
		for (unsigned int i(0); i < TotNbNeurons; ++i) {
						
			if (getNeuron(i)->update(1, backgroundInfluence)) {

				for (auto PostSynap : neurons_graphe_[i]) {

					if(getNeuron(i)->isExcitatory()) {
					getNeuron(PostSynap)->addArrivingSpike(k+D, 1);						
					} else {
					getNeuron(PostSynap)->addArrivingSpike(k+D, g);
					}
					
				}
			}

		mempot_values[i] = getNeuron(i)->getMemPot();

		}

		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}
	}
}

void Network::updateWritingSpi (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence, string filename)
{
	unsigned int TotNbNeurons(Neurons_.size());

	ofstream myfile;

	myfile.open (filename+".dat");

	for (unsigned int k(0); k < nbSteps; ++k) {

		if((k >= Iext_start) && (k <= Iext_stop)) {
			getNeuron(0)->setIext(Iext);
		} else {
			getNeuron(0)->setIext(0.0);
		}
			
		for (unsigned int i(0); i < TotNbNeurons; ++i) {
						
			if (getNeuron(i)->update(1, backgroundInfluence)) {

				myfile << k << "\t" << i << "\n";

				for (auto PostSynap : neurons_graphe_[i]) {

					if(getNeuron(i)->isExcitatory()) {
					getNeuron(PostSynap)->addArrivingSpike(k+D, 1);						
					} else {
					getNeuron(PostSynap)->addArrivingSpike(k+D, g);
					}
				}
			}
		}
	}
}