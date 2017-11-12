# neuron

# Project Title

This repository allows you to simulate a network of neurons, which can be excitatory or inhibitatory, thanks to two classes: network and neuron. Neurons have the ability to spike each other,
the spike reaching the post-synaptic neuron after a constant delay. You can change global constant is the file constants.hpp (weight of inhibitor neuron, firing rate, ...)

## Getting Started

You can use the follow commands in your terminal to create the documentation, run the simulation and obtain the two graphics:
* cd neuron (go in the neuron depository, obtained from github)
* mkdir build
* mv ploting.py build
* cd build
* cmake ..
* make doc
* make
* ./neuron
* python ploting.py

* If you're not running these commands directly, please notice that:
* IMPORTANT: You have to creat a build folder and execute the cmake and make commands from it
* IMPORTANT: You have to put the ploting.py file in the build in order to use the code as it is, else, change the path to your .dat file (output of the simulation) in the python script.

* NB: The default simulation will run for 100ms (one step is equals to 0.1ms), with a total of 12 500 neurons (10 000 excitatory neurons, 2 500 inhibitatory neurons) randomly connected.

### Prerequisites

* You need to be able to compile C++11
* You need to have the following python librairies : numpy and matplotlib.pyplot.

* NB: The googletest files are included in the repository so you don't have to reinstall it and place it in the repository.

## Running the tests

Go in the build folder, run the make command and run the neuron_unittest executable (./neuron_unittest). The last test is a bit heavy, it should last approximately 650 ms.

## Break down into end to end tests

See the neuron_unittest.cpp file to have more detailed explanation

```
* We test the behaviour of the membrane's potential of one neuron after many steps, with different input, to check the good implementation of the differential equation solution.
* We also test the buffer, check if the writing and reading index are well implented depending on the delay constant)
* We check if a neuron have the right numbers of connections to him
```

* There is no assert is the code, considering the fact that the type of all the variables are given to the user when he is asked to enter it. 

### Files of the repository

* CMakeLists.txt : manage the compilation of the simulation, gtest and doxygen documentation
* Doxyconfig: config file for doxygen generation
* constants.hpp : constants of the simualtion (encapsulation purpose)
* network. cpp & network.hpp : class network
* neuron.cpp & neuron.hpp : class neuron
* test_fun1.cpp : body of the simulation
* neuron_unittest.cpp : body of the gtest
* ploting.py : python script to plot a scatter plot and a histogramm with the output of the simulation

## Authors

* **Antoine Madrona**

## Acknowledgments

* This simulation use the paper of M.Brunel (N J. Comp Neuroscience 2000) as reference.
