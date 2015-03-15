/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:07:03 by gmp               #+#    #+#             */
/*   Updated: 2015/03/15 17:14:08 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzle.hpp"

void	ft_usage(void)
{
	std::cout << "[USAGE] - ./npuzzle [map] or ./npuzzle" << std::endl;
}

int		main(int ac, char **av)
{
	NPuzzle puzzle;
	if (ac < 2){
		std::cout << "nor args" << std::endl;
	}
	else if (ac == 2){
		puzzle.parse(av[1]);
	}
	else
		ft_usage();
}