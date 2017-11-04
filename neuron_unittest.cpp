#include <iostream>
#include <cmath>
#include "constants.hpp"
#include "neuron.hpp"
#include "network.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, MembPot_1step_positivInput) {
	Neuron neuron;
	neuron.setIext(1.0);

	//test after 1 step
	neuron.update(1,0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
}

TEST (NeuronTest, MembPot_ManyStep_posInput) {
	Neuron neuron;
	neuron.setIext(1.0);

	//test after 10 000 steps, positive input
	neuron.update(10000,0);

	EXPECT_EQ(0, neuron.getNbSpike());
	ASSERT_LT(neuron.getMemPot(), 20.0);
}

TEST (NeuronTest, MembPot_ManyStep_noInput) {
	Neuron neuron;
	neuron.setIext(0.0);

	//test after 10 000 steps, no input
	neuron.update(10000,0);

	EXPECT_EQ(0, neuron.getNbSpike());
}

TEST (NeuronTest, MembPot_ManyStep_negInput) {
	Neuron neuron;
	neuron.setIext(-1.0);

	//test after 10 000 steps, negativ input
	neuron.update(10000,0);

	EXPECT_EQ(0, neuron.getNbSpike());
	ASSERT_LT(0.00001, std::fabs(20 - neuron.getMemPot()));
}

TEST (NeuronTest, SpikeTiming) {
	Neuron neuron;
	neuron.setIext(1.01);

	//Iext is applied during all the simulation
	//1e spike should occur at 92.4ms
	neuron.update(925,0);
	EXPECT_EQ(1, neuron.getNbSpike());
	EXPECT_EQ(924, neuron.getLastSpike());

	//2e spike should occur at 186.8ms, 94.4 ms after the first spike
	neuron.update(944,0);
	EXPECT_EQ(2, neuron.getNbSpike());
	EXPECT_EQ(1868, neuron.getLastSpike());

	//3e spike should occur at 281.2ms, 94.4 ms after the second spike
	neuron.update(944,0);
	EXPECT_EQ(3, neuron.getNbSpike());
	EXPECT_EQ(2812, neuron.getLastSpike());

	//4e spike should occur at 375.6ms, 94.4 ms after the third spike
	neuron.update(944,0);
	EXPECT_EQ(4, neuron.getNbSpike());
	EXPECT_EQ(3756, neuron.getLastSpike());

}

TEST (NetworkTest, Buffertest) {
	Network twoneurons(2);
	twoneurons.addPostSynap(0,1);

	//update the Network until the first spike of Neuron0
	twoneurons.update(1.01, 925, 0, 925, 0);

	//update the Neuron1 for the numbers of steps equals to the delay
	twoneurons.getNeuron(1)->update(D, 0);

	EXPECT_EQ(twoneurons.getNeuron(1)->getMemPot(), 0.1);
	ASSERT_LT(std::fabs(0.1 - twoneurons.getNeuron(1)->getMemPot()), 1E-5);

}

TEST (NetworkTest, Buffer_InhitoExci) {
	Network twoneurons(2);
	twoneurons.addPostSynap(0,1);
	twoneurons.getNeuron(0)->setExcitatory(false);

	//update the Network until the first spike of Neuron0
	twoneurons.update(1.01, 925, 0, 925, 0); //was 925
	
	EXPECT_EQ(1, twoneurons.getNeuron(0)->getNbSpike());

	//update the Neuron1 for the numbers of steps equals to the delay
	twoneurons.getNeuron(1)->update(D, 0);

	EXPECT_EQ(twoneurons.getNeuron(1)->getMemPot(), -0.5);
}

TEST (NetworkTest, RefractBufferReset) {
	Network twoneurons(2);
	twoneurons.addPostSynap(0,1);

	twoneurons.getNeuron(0)->setMemPot(21);
	twoneurons.update(1.01, 14, 0, 9, 0);
	twoneurons.getNeuron(1)->setMemPot(21);
	//update where the neuron 1 spikes
	twoneurons.update(0, 1, 0, 0, 0);

	//testing if the buffer has the right value for the update of neuron 1 (refractory)
	ASSERT_LT(std::fabs(0.1 - twoneurons.getNeuron(1)->getBuffer().at(twoneurons.getNeuron(1)->getReadOutPos())), 1E-5);
	//update where the neuron 1 is refractory, receiving the spike of neuron 0
	twoneurons.update(0, 1, 0, 0, 0);

	EXPECT_EQ(1, twoneurons.getNeuron(0)->getNbSpike());
	EXPECT_EQ(1, twoneurons.getNeuron(1)->getNbSpike());

	ASSERT_DOUBLE_EQ(0, twoneurons.getNeuron(1)->getMemPot());

	twoneurons.getNeuron(1)->update(D, 0);

	//checking if the value of the buffer has been reset when updating neuron 1 while refractory
	EXPECT_EQ(0, twoneurons.getNeuron(1)->getBuffer().at(twoneurons.getNeuron(1)->getReadOutPos()));
}

TEST (NetworkTest, SpikeBufferReset) {
	Network twoneurons(2);
	twoneurons.addPostSynap(0,1);

	twoneurons.getNeuron(0)->setMemPot(21);
	twoneurons.update(1.01, 15, 0, 9, 0);
	twoneurons.getNeuron(1)->setMemPot(21);

	//testing if the buffer has the right value for the update of neuron 1 (spiking)
	ASSERT_LT(std::fabs(0.1 - twoneurons.getNeuron(1)->getBuffer().at(twoneurons.getNeuron(1)->getReadOutPos())), 1E-5);

	twoneurons.update(0, 1, 0, 0, 0);

	EXPECT_EQ(1, twoneurons.getNeuron(0)->getNbSpike());
	EXPECT_EQ(1, twoneurons.getNeuron(1)->getNbSpike());

	ASSERT_DOUBLE_EQ(0, twoneurons.getNeuron(1)->getMemPot());

	twoneurons.getNeuron(1)->update(D, 0);

	//checking if the value of the buffer has been reset when updating neuron 1 while spiking
	EXPECT_EQ(0, twoneurons.getNeuron(1)->getBuffer().at(twoneurons.getNeuron(1)->getReadOutPos()));
}

TEST (NetworkTest, NumberofConnection) {
	//create a network of 1000 excitatory & 250 inhibitotary neurons
	//connections are random
	Network smallbrain(1000, 250);

	unsigned int NbConnectiontoNeuron5(0);

	for (auto neuronTargets : smallbrain.getNeuronsGraphe()) {
		for (auto target : neuronTargets) {
			if (target == 4) {
				NbConnectiontoNeuron5+=1;
			}
		}
	}
	// 10% of 1000 = 10, 10% of 250 = 25
	EXPECT_EQ(NbConnectiontoNeuron5, 125);
}

TEST (NetworkTest, InhibitorNetwork) {
	//create a 1 000 inhibitor neurons network
	Network slowbrain(0, 1000);
	//the external activity has a normal influence on the network (100%)
	slowbrain.update(0, 1000, 0, 0, 1);

	unsigned int NbSpikeSample1(0);

	//we consider a sample of 100 neurons, 10% of the network
	for (unsigned int j(0); j<100; ++j) {
		NbSpikeSample1+= slowbrain.getNeuron(j)->getNbSpike();
	}

	//create a 1 000 neurons (50-50 inhi/exci) network
	Network normalbrain(500, 500);
	//the external activity has a normal influence on the network (100%)
	normalbrain.update(0, 1000, 0, 0, 1);

	unsigned int NbSpikeSample2(0);

	//we consider a sample of 100 neurons, 10% of the network
	for (unsigned int j(0); j<100; ++j) {
		NbSpikeSample2+= normalbrain.getNeuron(j)->getNbSpike();
	}

	ASSERT_LT(NbSpikeSample1, NbSpikeSample2);
}
//vérifier que quasi personne ne spike sur un network d'inhibitor avec du poisson



int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}