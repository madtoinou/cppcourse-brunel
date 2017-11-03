#include "network.hpp"

using namespace std;

Network::Network(unsigned int NbNeurons)
: neurons_graphe_(NbNeurons, vector<unsigned int>())
{
	/*create neurons, excitatory by default*/
	for (unsigned int i(0); i<NbNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron());
		Neurons_.push_back(p_neuron);	
	}
}

Network::Network(unsigned int nbExciNeurons, unsigned int nbInhiNeurons)
: neurons_graphe_(nbExciNeurons+nbInhiNeurons, vector<unsigned int> (nbExciNeurons+nbInhiNeurons))
{
	/*create the excitatory neurons*/
	for (unsigned int i(0); i<nbExciNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron(true));
		Neurons_.push_back(p_neuron);	
	}
	/*create the inhibitatory neurons*/
	for (unsigned int i(0); i<nbInhiNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron(false));
		Neurons_.push_back(p_neuron);	
	}

	/*create the connections between the neurons*/
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
	/*distribution for the connections with excitatory as pre-synaptic neuron*/
	uniform_int_distribution<> distExci(0, nbExciNeurons-1);
	/*distribution for the connections with inhibitatory as pre-synaptic neuron*/
	uniform_int_distribution<> distInhi(nbExciNeurons, nbExciNeurons+nbInhiNeurons-1);


	for (unsigned int i(0); i< Neurons_.size(); ++i) {

		/*creating connection with 10% of the excitatory neurons (connection can be multiple)*/
		for (unsigned int j(0); j < nbExciNeurons/10; ++j) {
			addPostSynap(distExci(gen), i);
		}

		/*creating connection with 10% of the inhibitatory neurons (connection can be multiple)*/
		for (unsigned int k(0); k < nbInhiNeurons/10; ++k) {
			addPostSynap(distInhi(gen), i);
		}
	}
}


void Network::update (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence)
{
	unsigned int TotNbNeurons(Neurons_.size());

	/*iterating the given number of step*/
	for (unsigned int k(0); k < nbSteps; ++k) {

		/*checking if an external current should be applied to the first neuron*/
		if((k >= Iext_start) && (k <= Iext_stop)) {
			getNeuron(0)->setIext(Iext);
		} else {
			getNeuron(0)->setIext(0.0);
		}
		
		/*iterating on all the neurons of the simulation*/
		for (unsigned int i(0); i < TotNbNeurons; ++i) {
			
			/*managing the spike consequences of the neuron i*/
			if (getNeuron(i)->update(1, backgroundInfluence)) {

				/*iterating on the post-synaptic neurons of neuron i*/
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

void Network::update (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence, string filename)
{
	unsigned int TotNbNeurons(Neurons_.size());

	vector<double> mempot_values (TotNbNeurons);

	ofstream myfile;

	myfile.open (filename+".dat");

	myfile << TotNbNeurons << "\n";

	/*iterating the given number of step*/
	for (unsigned int k(0); k < nbSteps; ++k) {

		/*checking if an external current should be applied to the first neuron*/
		if((k >= Iext_start) && (k <= Iext_stop)) {
			getNeuron(0)->setIext(Iext);
		} else {
			getNeuron(0)->setIext(0.0);
		}
		
		/*iterating on all the neurons of the simulation*/
		for (unsigned int i(0); i < TotNbNeurons; ++i) {
			
			/*managing the spike consequences of the neuron i*/
			if (getNeuron(i)->update(1, backgroundInfluence)) {

				/*iterating on the post-synaptic neurons of neuron i*/
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

		/*writing the membrane potential's value in the file*/
		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}
	}
}

void Network::updateWritingSpi (unsigned int nbSteps, double backgroundInfluence, string filename)
{
	unsigned int TotNbNeurons(Neurons_.size());

	ofstream myfile;

	myfile.open (filename+".dat");

	/*iterating the given number of step*/
	for (unsigned int k(0); k < nbSteps; ++k) {

		/*iterating on all the neurons of the simulation*/
		for (unsigned int i(0); i < TotNbNeurons; ++i) {

			/*managing the spike consequences of the neuron i*/			
			if (Neurons_[i]->update(1, backgroundInfluence)) {

				myfile << k << "\t" << i << "\n";

				/*iterating on the post-synaptic neurons of neuron i*/
				for (auto PostSynap : neurons_graphe_[i]) {

					if(getNeuron(i)->isExcitatory()) {
					Neurons_[PostSynap]->addArrivingSpike(k+D, 1);						
					} else {
					Neurons_[PostSynap]->addArrivingSpike(k+D, g);
					}
				}
			}
		}
	}
}