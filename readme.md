Config file structure:
	- model: VGG16
	- layers (CONV 2D | GlobalAveragePooling):
		- 1
			- number of neurons e.g. 64
			- filter size e.g. (3, 3)
			- padding e.g. "same"
			- activation e.g. "relu"
|| create a structure that is going to be stored in binary format inside of that file. 
How does the thing with the networks work?
	- to create a network, I have to have some main loop (again) to have a place where the network structure is going to live.
	This reminds me of another infinite loop for this task?

	- Another thing is, I'll have two parts, a frontend and a backend. In the backend it is going to be solved using structures and linked lists. For the frontend...? 

	Frontend:
		- when selecting the option of creating a new network, the first thing that happens is to input the new name....
		- after that there are two options, I am going to cover the "from scratch" one first.
			- all I want to be able to controll are the middle layers, I'm not interested in modifying the first or last layer...
			- this should make things a bit easier. If I want to add a new layer, press a specific key or sth (like "+")

			- one screen is showing the network overview; another is for each layer configuration


What do I want to be able to do from this UI:
	- start the learning
		- this option should create a process running the python script that reads the training config from a config file...
	
	- create new network parameters
		- create a whole new entry into the config file

	- configure the network parameters (for an existing network configuration)
		- this one should be able to create a new layer
		- delete the layer
		- set the number of neurons
		- select the activation funcion
		- select the batch size
		- select the number of epochs

	- see the results of the training...

dev notes:
	- a menu is a new screen that is going to be drawn...
	- a function is supposed to be sth to be executed in the background...



The config file has to have:
	- unique network configuration identifier
	- parameter ranges 
		- if for example one layer can have a range of neurons inside of it...
	- number of layers
	- configuration for each layer