#ifndef ALG_HPP
#define ALG_HPP


/*Included headers*/
/*---------------------------------------------*/
#include "errorlogger.h"
/*---------------------------------------------*/

/*Included dependencies*/
/*---------------------------------------------*/
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <math.h>
/*---------------------------------------------*/

/*Header content*/
/*=============================================*/

namespace EMconsts{
	const int iterations = 10;
}



template <typename Hypothesis, typename Datatype>
class EM_algorithm {
protected:

	/* The current guess/aproximated hypothesis */
	Hypothesis current_h;

	/* The current data (state) of the algorithm. */
	/* For example Y[1] should contain X[1] (the known data) and Z[1] (the unknown data) of the second point (0 indexing). */
	std::vector<Datatype> Y;

public:

	/* For a specific problem calculate Q(h'|h) and use it to derive the estimate_Z and maximation_step functions. */
	/* The Q(h'|h) function (a function of h'), should use statistical knowledge about the problem as well */
	/* as the value set by estimate_Z in order to give an expected estimate of the probablity distribution of h'.*/
	/* Remember that Q is equal to E[ln(p(Y|h'))|h,X]. */
	/* In words: The expected value of the natural logarithm of the probability of Y given h' when you know X and h. */
	/* Y is the union between X and Z. */

	/* This function should estimate Z given the current_h and X.*/
	/* It estimates the unknown data using the known data and current hypothesis guess.*/
	virtual int estimate_Z() = 0;

	/* Should return the h' that maximizes the Q(h'|h) function */
	virtual Hypothesis maximation_step() = 0;

	/* Runs the algorithm for the given number of iterations */
	int run_algorithm(const int& iterations, const bool& should_present);

	/* Present the current data and hypothesis as suited to the current problem */
	virtual void present_state(SDL_Renderer*) = 0;
};

template <typename Hypothesis, typename Datatype>
int EM_algorithm<Hypothesis, Datatype>::run_algorithm(const int& iterations, const bool& should_present){
	for(int i = 0; i < iterations; i++){
		if(this->estimate_z() != 0){
			errorlogger("Failed to estimate Z!");
			std::cout << "Failed to estimate Z, see errorlog for details.\n";
			return -1;
		}
		current_h = maximation_step();
	}

	if(should_present){
		this->present_state();
	}

	return 0;
}

/*Specific tasks-----------------------------------------------------*/

/* Hypothesis class-----------------------*/

class Means{

	friend class Mixture_of_gaussian;

	protected:
		float means[2];

	public:
		/* Constructors */
		Means();
		Means(const float& mean1, const float& mean2);
};

/*----------------------------------------*/

/* Data class---------------------------- */
class Datapoint{

	friend class Mixture_of_gaussian;

	private:
		float value;
		float z1;
		float z2;

	public:
		/* Constructors */
		Datapoint();
		Datapoint(const float& initval, const float& initz1, const float& initz2);
};

/*----------------------------------------*/

/* Mixture of gaussian instance class-----*/
/* Supports 2 gaussian distributions of 1 dimension. */
class Mixture_of_gaussian: public EM_algorithm<Means, Datapoint> {
	public:
		int estimate_Z();
		Means maximation_step();
		void present_state(SDL_Renderer* ren);

		/* Constructors */
		Mixture_of_gaussian();
		Mixture_of_gaussian(const Means& initmeans, std::string& filename);

};

void Mixture_of_gaussian::present_state(SDL_Renderer* ren){
	std::cout << "Make it happen\n";
}

int Mixture_of_gaussian::estimate_Z(){
	for(std::vector<Datapoint>::iterator it = Y.begin(); it != Y.end(); ++it){
		float numerator1 = exp(-0.5*((*it).value - current_h.means[0]));
		float numerator2 = exp(-0.5*((*it).value - current_h.means[1]));

		/* Should not be possible, but i am a paranoid mofo. */
		assert((numerator1 + numerator2) != 0);

		(*it).z1 = numerator1 / (numerator1 + numerator2);
		(*it).z2 = numerator2 / (numerator1 + numerator2);
	}
}

Means Mixture_of_gaussian::maximation_step(){

}

/*=============================================*/

#endif