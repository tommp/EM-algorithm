#ifndef ALG_HPP
#define ALG_HPP


/*Included headers*/
/*---------------------------------------------*/
#include "errorlogger.hpp"
/*---------------------------------------------*/

/*Included dependencies*/
/*---------------------------------------------*/
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <math.h>
#include <assert.h>
/*---------------------------------------------*/

/*Header content*/
/*=============================================*/

namespace EMconsts{
	const int iterations = 10;
	const int algiterations = 1;

	const int windowlength = 600;
	const int windowheight = 600;
}

class Mixture_of_gaussian;
class Datapoint;
class Means;

template <typename Hypothesis, typename Datatype>
class EM_algorithm {
	protected:

		/* The current guess/aproximated hypothesis */
		Hypothesis current_h;

		/* The current data (state) of the algorithm. */
		/* For example Y[1] should contain X (the known data) and Z (the unknown data) of the second point (0 indexing). */
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
		virtual void estimate_Z() = 0;

		/* Should return the h' that maximizes the Q(h'|h) function */
		virtual Hypothesis maximation_step() = 0;

		/* Runs the algorithm for the given number of iterations */
		int run_algorithm(const int& iterations);

		/* Present the current data and hypothesis as suited to the current problem */
		virtual void present_state(SDL_Renderer*) = 0;
};

template <typename Hypothesis, typename Datatype>
int EM_algorithm<Hypothesis, Datatype>::run_algorithm(const int& iterations){
	for(int i = 0; i < iterations; i++){
		estimate_Z();
		current_h = maximation_step();
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
		void estimate_Z();
		Means maximation_step();
		void present_state(SDL_Renderer* ren);

		/* Constructors */
		Mixture_of_gaussian();
		Mixture_of_gaussian(const Means& initmeans, const char* filename);
};

/*=============================================*/

#endif