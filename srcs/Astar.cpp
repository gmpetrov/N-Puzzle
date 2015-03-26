/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/03/26 23:43:26 by gmp              ###   ########.fr       */
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

void	Astar::search_moves(node *current, std::vector<node *> & open_list, std::vector<node *> & closed_list){
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

	this->remove_or_update_if_already_in_open_list(open_list);
	this->remove_if_already_in_closed_list(closed_list);
}

void	Astar::remove_if_already_in_closed_list(std::vector<node *>& closed_list){
	bool occur = false;
	for (std::vector<node *>::iterator it_tmp = tmp.begin(); it_tmp != tmp.end(); it_tmp++){
		if (occur == true){
			it_tmp = tmp.begin();
			occur = false;
		}
		for (std::vector<node *>::const_iterator it_closed = closed_list.begin(); it_closed != closed_list.end(); it_closed++){
			if ((*(*it_tmp)) == (*(*it_closed))){
				if ((*(*it_tmp)) < (*(*it_closed))){
					// tmp.erase(it_tmp);
					closed_list.erase(it_closed);
					it_closed = closed_list.begin();
					if (it_closed == closed_list.end())
						return;
				}
				else{
					tmp.erase(it_tmp);
					occur = true;
					it_tmp = tmp.begin();
					if(it_tmp == tmp.end())
						return;
					break ;
				}
			}
		}
	}
}

void	Astar::remove_or_update_if_already_in_open_list(std::vector<node *>& open_list){
	bool occur = false;
	for (std::vector<node *>::iterator it_tmp = tmp.begin(); it_tmp != tmp.end(); it_tmp++){
		if (occur == true){
			it_tmp = tmp.begin();
			occur = false;
		}
		for (std::vector<node *>::iterator it_open = open_list.begin(); it_open != open_list.end(); it_open++){
			if ((*(*it_tmp)) == (*(*it_open))){
				if ((*(*it_tmp)) < (*(*it_open))){
					(*(*it_open)) = (*(*it_tmp));
				}
				delete *it_tmp;
				tmp.erase(it_tmp);
				occur = true;
				it_tmp = tmp.begin();
				if (it_tmp == tmp.end())
					return;
				break ;
			}
		}
	}
}

void	Astar::search_moves_case_1(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y - 1][x];
	tab[y - 1][x] = 0;
	node *new_node = new node(tab, current->_size, current);
	this->rate_node(new_node);
	this->tmp.push_back(new_node);
}

void	Astar::search_moves_case_2(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y][x + 1];
	tab[y][x + 1] = 0;
	node *new_node = new node(tab, current->_size, current);
	this->rate_node(new_node);
	this->tmp.push_back(new_node);
}

void	Astar::search_moves_case_3(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y + 1][x];
	tab[y + 1][x] = 0;
	node *new_node = new node(tab, current->_size, current);
	this->rate_node(new_node);
	this->tmp.push_back(new_node);
}

void	Astar::search_moves_case_4(node *current, int x, int y){
	int		**tab = copy_state(current->_state, current->_size);
	tab[y][x] = tab[y][x - 1];
	tab[y][x - 1] = 0;
	node *new_node = new node(tab, current->_size, current);
	this->rate_node(new_node);
	this->tmp.push_back(new_node);
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

bool	Astar::is_solution(node *current){
	int		counter = 1;
	int		dimension = current->_size;

	while (counter <= ((current->_size * current->_size) - 1))
	{
		for (int x = current->_size - dimension; x < dimension; x++){
			int y = current->_size - dimension;
			if (counter != current->_state[y][x])
				return false;
			counter++;
		}
		dimension -= 1;
		for (int v = current->_size - dimension; v <= dimension; v++){
			int x = dimension;
			if (counter != current->_state[v][x])
				return false;
			counter++;
		}
		for (int x = dimension - 1; x >= (current->_size - (dimension + 1)); x--){
			int y = dimension;
			if (counter != current->_state[y][x])
				return false;
			counter++;
		}
		for (int y = dimension - 1; y >= current->_size - dimension; y--){
			int x = (current->_size - dimension) - 1;
			if (counter != current->_state[y][x])
				return false;
			counter++;
		}
	}
	return true;
}

void	Astar::rate_node(node *node){
	// int	result_heuristic = this->manhattan_heuristic(node);
	int		result_heuristic = hamming_heuristic(node);
	node->_rate = result_heuristic + node->_generation;
	// node->_rate = result_heuristic;
}

int		Astar::manhattan_heuristic(node *node){
	int	current_x;
	int	current_y;
	int	goal_x;
	int	goal_y;
	int	result = 0;

	for (int counter = 1; counter < (node->_size * node->_size); counter++){
		this->getCurrentPos(node, &current_x, &current_y, counter);
		this->getGoalPos(node, &goal_x, &goal_y, counter);
		int abs1 = abs(goal_x - current_x);
		int abs2 = abs(goal_y - current_y);
		result += (abs1 + abs2);
	}
	return result;
}

int		Astar::hamming_heuristic(node *current ){
	int		counter = 1;
	int		dimension = current->_size;
	int		result = 0;

	while (counter <= ((current->_size * current->_size) - 1))
	{
		for (int x = current->_size - dimension; x < dimension; x++){
			int y = current->_size - dimension;
			if (counter != current->_state[y][x])
				result += 1;
			counter++;
		}
		dimension -= 1;
		for (int v = current->_size - dimension; v <= dimension; v++){
			int x = dimension;
			if (counter != current->_state[v][x])
				result += 1;
			counter++;
		}
		for (int x = dimension - 1; x >= (current->_size - (dimension + 1)); x--){
			int y = dimension;
			if (counter != current->_state[y][x])
				result += 1;
			counter++;
		}
		for (int y = dimension - 1; y >= current->_size - dimension; y--){
			int x = (current->_size - dimension) - 1;
			if (counter != current->_state[y][x])
				result += 1;
			counter++;
		}
	}
	return result;
}

void	Astar::getCurrentPos(node *node, int *current_x, int *current_y, int to_find){
	for (*current_y = 0; *current_y < node->_size; *current_y += 1){
		for (*current_x = 0; *current_x < node->_size; *current_x += 1){
			if (to_find == node->_state[*current_y][*current_x])
				return ;
		}
	}
}

void	Astar::getGoalPos(node *node, int *goal_x, int *goal_y, int to_find){
	int		counter = 1;
	int		dimension = node->_size;

	while (counter <= ((node->_size * node->_size) - 1))
	{
		for (*goal_x = node->_size - dimension; *goal_x < dimension; *goal_x += 1){
			*goal_y = node->_size - dimension;
			if (counter == to_find)
				return ;
			counter++;
		}
		dimension -= 1;
		for (*goal_y = node->_size - dimension; *goal_y <= dimension; *goal_y += 1){
			*goal_x = dimension;
			if (counter == to_find)
				return ;
			counter++;
		}
		for (*goal_x = dimension - 1; *goal_x >= (node->_size - (dimension + 1)); *goal_x -= 1){
			*goal_y = dimension;
			if (counter == to_find)
				return ;
			counter++;
		}
		for (*goal_y = dimension - 1; *goal_y >= node->_size - dimension; *goal_y -= 1){
			*goal_x = (node->_size - dimension) - 1;
			if (counter == to_find)
				return ;
			counter++;
		}
	}
}

void	print_it(node *node){
	std::cout << "RATE ZBRA = ";
	std::cout << node->_rate << std::endl;
	node->print_state();
	std::cout << *node << std::endl;
}

node	*Astar::best_move(std::vector<node *> & open_list, std::vector<node *> & closed_list){
	node *tmp;

	std::sort(open_list.begin(), open_list.end());
	tmp = *open_list.begin();
	closed_list.push_back(tmp);
	std::reverse(open_list.begin(), open_list.end());
	open_list.pop_back();
	return tmp;
}

bool compare_generation(node *i, node *j) { return (i->_generation < j->_generation); }

void	Astar::get_path(node *current)
{
	node *tmp = current;
	std::vector<node *> path;
	while (tmp->_parent){
		path.push_back(tmp);
		tmp = tmp->_parent;
	}
	std::sort(path.begin(), path.end(), compare_generation);
	std::reverse(path.begin(), path.end());
	for_each(path.begin(), path.end(), print_it);
	std::cout << "NUMBER OF STEP" << path.size() << std::endl;

}