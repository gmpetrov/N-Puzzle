/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:07:03 by gmp               #+#    #+#             */
/*   Updated: 2015/03/22 16:51:18 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzle.hpp"

int		main(int ac, char **av)
{
	NPuzzle puzzle;
	if (ac < 2){
		std::cout << "no args" << std::endl;
	}
	else if (ac == 2){
		try{
                        puzzle.resolve(av[1]);
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
	else
		puzzle.ft_usage();
}
