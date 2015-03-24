/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/03/24 10:00:38 by gmp              ###   ########.fr       */
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
	int	x, y;
	this->tmp.clear();
	this->find_blank(current, &x, &y);
	if ((y - 1) >= 0)
		this->search_moves_case_1(current, x, y);
	if ((x + 1) < current->_size)
		this->search_moves_case_2(current, x, y);
	if ((y + 1) < current->_size)
		this->search_moves_case_3(current, x, y);
	if ((x - 1) >= 0)
		this->search_moves_case_4(current, x, y);
}

void	Astar::search_moves_case_1(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y - 1][x];
	tab[y - 1][x] = 0;
	node *new_node = new node(tab, current->_size);
	this->tmp.push_back(new_node);
	// std::cout << "case 1 possible" << std::endl;
}

void	Astar::search_moves_case_2(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y][x + 1];
	tab[y][x + 1] = 0;
	node *new_node = new node(tab, current->_size);
	this->tmp.push_back(new_node);
	// std::cout << "case 2 possible" << std::endl;
}

void	Astar::search_moves_case_3(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y + 1][x];
	tab[y + 1][x] = 0;
	node *new_node = new node(tab, current->_size);
	this->tmp.push_back(new_node);
	// std::cout << "case 3 possible" << std::endl;
}

void	Astar::search_moves_case_4(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y][x - 1];
	tab[y][x - 1] = 0;
	node *new_node = new node(tab, current->_size);
	this->tmp.push_back(new_node);
	// std::cout << "case 4 possible" << std::endl;
}

int		**Astar::copy_state(int **state, int size)
{
	int **tab = (int **)malloc(sizeof(int *) * size);
	for (int j = 0; j < size; j++){
		tab[j] = (int *)malloc(sizeof(int) * size);
		for (int i = 0; i < size; i++){
			tab[j][i] = state[j][i];
		}
	}
	return tab;
}

void	Astar::find_blank(node *current, int *x, int *y){
	for (*y = 0; *y < current->_size; *y += 1){
		for (*x = 0; *x < current->_size; *x += 1){
			if (current->_state[*y][*x] == 0)
				return ;
		}
	}
}

// bool	Astar::is_solution(node *current){
// 	int		counter = 1;
// 	int		dimension = current->_size;

// 	while (counter != ((current->_size * current->_size) - 1))
// 	{
// 		for (int x = 0; x < dimension; x++){
// 			if (counter != current->_state[y][x])
// 				return false;
// 			counter++;
// 		}
// 		for (int v = 0; v < dimension; v++){
// 			if (counter != current->_state[y][x])
// 				return false;
// 			counter++;
// 		}
// 		for (int x = (dimension - 1); x == 0; x--){
// 			if (counter != current->_state[y][x])
// 				return false;
// 			counter++;
// 		}
// 	}
// }