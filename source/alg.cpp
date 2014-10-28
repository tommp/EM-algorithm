#include "./headers/alg.hpp"

/*Constructor definitions----------------------------*/

Means::Means(){
	means[0] = 0;
	means[1] = 0;
}

Means::Means(const float& mean1, const float& mean2){
	means[0] = mean1;
	means[1] = mean2;
}

Datapoint::Datapoint(){
	value = 0.0;
	z1 = 0;
	z2 = 0;
}

Datapoint::Datapoint(const float& initval, const float& initz1, const float& initz2){
	value = initval;
	z1 = initz1;
	z2 = initz2;
}

Mixture_of_gaussian::Mixture_of_gaussian(){
	this->current_h = Means(0, 0);
}

Mixture_of_gaussian::Mixture_of_gaussian(const Means& initmeans, std::string& filename){
	this->current_h = initmeans;

	int line;
	std::ifstream data (filename);
	if(!data.is_open()){
		errorlogger("Failed to open data file!");
		std::cout << "Failed to open data file!\n";
		exit(1);
	}
	while(data>>line){
		Y.push_back(Datapoint(line, -1.0, -1.0));
	}
}

/*Constructor definitions END------------------------*/