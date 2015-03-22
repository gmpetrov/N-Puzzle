/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/03/22 17:19:47 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Astar.hpp"

Astar::Astar(){
}

Astar::Astar(const Astar & src){
	*this = src;
}

Astar::~Astar(void){
}

Astar &	Astar::operator=(Astar const & rhs){
	(void)rhs;
	return *this;
}

void	Astar::search_moves(node *current){
	// current->print_state();
	int	x, y;
	this->find_blank(current, &x, &y);
	if ((y - 1) >= 0)
		std::cout << "case 1 possible" << std::endl;
	if ((x + 1) < current->_size)
		std::cout << "case 2 possible" << std::endl;
	if ((y + 1) < current->_size)
		std::cout << "case 3 possible" << std::endl;
	if ((x - 1) >= 0)
		std::cout << "case 4 possible" << std::endl;
}

void	Astar::find_blank(node *current, int *x, int *y){
	for (*y = 0; *y < current->_size; *y += 1){
		for (*x = 0; *x < current->_size; *x += 1){
			if (current->_state[*y][*x] == 0)
				return ;
		}
	}
}