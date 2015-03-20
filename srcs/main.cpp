/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:07:03 by gmp               #+#    #+#             */
/*   Updated: 2015/03/19 16:54:42 by gmp              ###   ########.fr       */
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
		puzzle.parse(av[1]);
	}
	else
		puzzle.ft_usage();
}