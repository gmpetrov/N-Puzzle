/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:07:03 by gmp               #+#    #+#             */
/*   Updated: 2015/07/03 16:43:33 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "NPuzzle.hpp"

void		ft_usage(void){
	std::cout << "\033[33m[USAGE] - ./npuzzle [-h <1:manhattan|2:hamming|3:euclidean>] [-s size] [-i iteration] [-f file]\033[0m" << std::endl;
	exit(0);
}

NPuzzle::Args 	checkArgs(int ac, char **av){
	NPuzzle::Args args;

	args.isFile 	   = false;
	args.isGenerate    = false;
	args.iterations    = -1;
	args.size 	  	   = -1;
	for (int i = 1; i < ac; i++){
		std::string 	option(av[i]);

		// CHECKING FOR HEURISTIC OPTION
		if (option == "-h"){

			// IF OPTION HAS NO VALUE, QUIT
			if (++i >= ac)
				ft_usage();

			// GETTING THE VALUE OF HEURISTIC OPTION
			std::string	  value(av[i]);
			if (value == "1" || value == "manhattan")
				args.heuristic = "manhattan";
			else if (value == "2" || value == "hamming")
				args.heuristic = "hamming";
			else if (value == "3" || value == "euclidean")
				args.heuristic = "euclidean";
			else
				ft_usage();
		}
		else if (option == "-s"){ // CHECKING FOR SIZE OPTION
			if (++i >= ac)
				ft_usage();

			// CONVERTING ARG TO SIZE_T VARIABLE
		    std::stringstream ss;
		    ss << av[i];
		    ss >> args.size;

		    // CHECKING MIN AND MAX SIZE FOR MAP GENERATION
		    if (args.size < 3)
		    	ft_usage();
		    args.isGenerate = true;
		}
		else if (option == "-i"){
			if (++i >= ac)
				ft_usage();

			// CHECKING FOR ITERATION OPTION
		    std::stringstream ss;
		    ss << av[i];
		    ss >> args.iterations;
		}
		else if (option == "-f"){ // CHECKING FOR FILE OPTION
			if (++i >= ac)
				ft_usage();
			args.file = std::string(av[i]);
			args.isFile = true;
		}
		else
			ft_usage();
	}
	return args;
}

int		main(int ac, char **av)
{
	NPuzzle puzzle;
	NPuzzle::Args args = checkArgs(ac, av);

  	/* initialize random seed */
  	srand(time(NULL));
	try{

		// SETTING THE HEURISTIC
		if (args.heuristic.empty())
			puzzle.algo.heuristicType = "manhattan";
		else
			puzzle.algo.heuristicType = args.heuristic;

		// CASE OF FILE INPUT
		if (args.isFile){

			// CHECK IF FILE EXIST AND IF IT'S A VALID MAP
			if(!puzzle.parse(const_cast<char *>(args.file.c_str()))){ std::cout << "unable to read input file" << std::endl; exit(0); }

			// RESOLVE N-PUZZLE FROM THE GIVEN FILE
			puzzle.resolve(new node(puzzle.parser_map, puzzle._size));
		}
		else if (args.isGenerate && args.size >= 3){

			// GENERATE A N-PUZZLE WITH THE GIVEN SIZE AND ITERATION
			node *board = puzzle.generate(static_cast<int>(args.size), static_cast<int>(args.iterations));

			// RESOLVE
			puzzle.resolve(board);
		}
		else
			ft_usage();
	}
	catch (NPuzzle::puzzle_exception e){
		std::cout << e.what() << std::endl;
		exit(0);
	}
	catch (std::exception e){
		std::cout << e.what() << std::endl;
		exit(0);
	}
}
