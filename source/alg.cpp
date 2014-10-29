#include "./headers/alg.hpp"



void Mixture_of_gaussian::estimate_Z(){
	for(std::vector<Datapoint>::iterator it = Y.begin(); it != Y.end(); ++it){
		float numerator1 = exp(-0.5 * (pow(((*it).value - current_h.means[0]),2)));
		float numerator2 = exp(-0.5 * (pow(((*it).value - current_h.means[1]),2)));

		/* Should not be possible, but i am a paranoid mofo. */
		assert((numerator1 + numerator2) != 0);

		(*it).z1 = numerator1 / (numerator1 + numerator2);
		(*it).z2 = numerator2 / (numerator1 + numerator2);
	}
}

Means Mixture_of_gaussian::maximation_step(){
	float z1_denominator_sum = 0.0;
	float z2_denominator_sum = 0.0;
	float z1_numerator_sum = 0.0;
	float z2_numerator_sum = 0.0;

	for(std::vector<Datapoint>::iterator it = Y.begin(); it != Y.end(); ++it){
		z1_numerator_sum += (*it).value * (*it).z1;
		z1_denominator_sum += (*it).z1;

		z2_numerator_sum += (*it).value * (*it).z2;
		z2_denominator_sum += (*it).z2;
	}

	assert(z1_denominator_sum != 0);
	assert(z2_denominator_sum != 0);

	return Means(z1_numerator_sum/z1_denominator_sum, z2_numerator_sum/z2_denominator_sum);
	
}

void Mixture_of_gaussian::present_state(SDL_Renderer* ren){
	std::cout << "Expected value of the first gaussian mean :" << current_h.means[0] << "\n" << "Expected value of the second gaussian mean :" << current_h.means[1] << std::endl;
	int block = EMconsts::windowlength/EMconsts::scale;
	SDL_SetRenderDrawColor(ren, 
						EMconsts::emptycolor[0], 
						EMconsts::emptycolor[1], 
						EMconsts::emptycolor[2], 255);
	SDL_RenderClear(ren);

	SDL_SetRenderDrawColor(ren, 
						EMconsts::linecolor[0], 
						EMconsts::linecolor[1], 
						EMconsts::linecolor[2], 255);

	SDL_RenderDrawLine(ren,
						0,
						EMconsts::windowheight - block,
						EMconsts::windowlength,
						EMconsts::windowheight - block);

	SDL_SetRenderDrawColor(ren, 
						EMconsts::pointcolor[0], 
						EMconsts::pointcolor[1], 
						EMconsts::pointcolor[2], 255);

	for(std::vector<Datapoint>::iterator it = Y.begin(); it != Y.end(); ++it){
		SDL_RenderDrawLine(ren,
						(*it).value*block + EMconsts::offset - EMconsts::pointsize,
						EMconsts::windowheight - block - EMconsts::pointsize,
						(*it).value*block + EMconsts::offset + EMconsts::pointsize,
						EMconsts::windowheight - block + EMconsts::pointsize);
		SDL_RenderDrawLine(ren,
						(*it).value*block + EMconsts::offset - EMconsts::pointsize,
						EMconsts::windowheight - block + EMconsts::pointsize,
						(*it).value*block + EMconsts::offset + EMconsts::pointsize,
						EMconsts::windowheight - block - EMconsts::pointsize);
	}

	SDL_SetRenderDrawColor(ren, 
						EMconsts::meancolor[0], 
						EMconsts::meancolor[1], 
						EMconsts::meancolor[2], 255);
	
	SDL_RenderDrawLine(ren,
						current_h.means[0] * block + EMconsts::offset,
						EMconsts::windowheight - block,
						current_h.means[0] * block + EMconsts::offset,
						EMconsts::windowheight - 2*block);
	SDL_RenderDrawLine(ren,
						current_h.means[0] * block + EMconsts::offset + EMconsts::variancedummy,
						(EMconsts::windowheight - block),
						current_h.means[0] * block + EMconsts::offset,
						(EMconsts::windowheight - 2*block));
	SDL_RenderDrawLine(ren,
						current_h.means[0] * block + EMconsts::offset - EMconsts::variancedummy,
						(EMconsts::windowheight - block),
						current_h.means[0] * block + EMconsts::offset,
						(EMconsts::windowheight - 2*block));

	SDL_RenderDrawLine(ren,
						current_h.means[1] * block + EMconsts::offset,
						EMconsts::windowheight - block,
						current_h.means[1] * block + EMconsts::offset,
						EMconsts::windowheight - 2*block);
	SDL_RenderDrawLine(ren,
						current_h.means[1] * block + EMconsts::offset + EMconsts::variancedummy,
						EMconsts::windowheight - block,
						current_h.means[1] * block + EMconsts::offset,
						EMconsts::windowheight - 2*block);
	SDL_RenderDrawLine(ren,
						current_h.means[1] * block + EMconsts::offset - EMconsts::variancedummy,
						EMconsts::windowheight - block,
						current_h.means[1] * block + EMconsts::offset,
						EMconsts::windowheight - 2*block);

	SDL_SetRenderDrawColor(ren, 
						EMconsts::zerocolor[0], 
						EMconsts::zerocolor[1], 
						EMconsts::zerocolor[2], 255);
	SDL_RenderDrawLine(ren,
						EMconsts::offset,
						EMconsts::windowheight,
						EMconsts::offset,
						0);
}

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

Mixture_of_gaussian::Mixture_of_gaussian(const Means& initmeans, const char* filename){
	this->current_h = initmeans;

	float line;
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