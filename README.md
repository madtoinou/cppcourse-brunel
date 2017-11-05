# neuron

This repository allows you to simulate a network of neurons, which can be excitatory or inhibitatory, thank to two classes: network and neuron. Neurons have the ability to spike each other,
the spike reaching the post-synaptic neuron after a constant delay (here 1.5ms, can be changed in the file constants.hpp.

Files needed:
CMakeLists.txt : manage the compilation of the simulation, gtest and doxygen documentation \n
Doxyconfig: config file for doxygen generation \n
constants.hpp : constants of the simualtion (encapsulation purpose) \n
network. cpp & network.hpp : class network \n
neuron.cpp & neuron.hpp : class neuron \n
test_fun1.cpp : body of the simulation \n
neuron_unittest.cpp : body of the gtest \n
ploting.py : python script to plot a scatter plot and a histogramm with the output of the simulation \n

Brief:
The default simulation will run for 100ms, with a total of 12 500 neurons (10 000 excitatory neurons, 2 500 inhibitatory neurons) randomly connected.

Simulation:
You can use the follow commands in your terminal to execute the simulation and obtain the two graphics:
cd neuron (go in the neuron depository, obtained from github)
mkdir build
mv ploting.py build
cd build
cmake ..
make doc
make
./neuron
python ploting.py

If you're not running these commands directly, please notice that:
IMPORTANT: You have to creat a build folder and execute the cmake and make commands from it
IMPORTANT: You have to put the ploting.py file in the build in order to use the code as it is, else, change the path to your .dat file (output of the simulation) in the python script.

Gtest:
You can find all the gtest in the file neuron_unittest.cpp.
You can run the gtest after the command "make" with the command "./neuron_unittest"

This simulation use the paper of M.Brunel (N J. Comp Neuroscience 2000) as reference.
Autor of the code: Antoine Madrona