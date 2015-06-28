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

using namespace std;

Astar::Astar(const Astar & src){
	*this = src;
}

Astar::~Astar(void){
    // TODO delete all tmp nodes
}

Astar &	Astar::operator=(Astar const & rhs){
	(void)rhs;
	return *this;
}

// Search moves available from current node and add to open list
void	Astar::search_moves(node *current, std::vector<node *> & open_list, std::vector<node *> & closed_list){

        // find free item in map
        int	x, y;
        this->find_blank(current, &x, &y);

        this->possible_movements.clear();

        if ((y - 1) >= 0)
        {
            this->possible_movements.push_back(search_moves_case(current, x, y, x, y-1));
        }
        if ((x + 1) < current->_size)
        {
            this->possible_movements.push_back(search_moves_case(current, x, y, x+1, y));
        }
        if ((y + 1) < current->_size)
        {
            this->possible_movements.push_back(search_moves_case(current, x, y, x, y+1));
        }
        if ((x - 1) >= 0)
        {
            this->possible_movements.push_back(search_moves_case(current, x, y, x-1, y));
        }

        /*
        cout << "possible movements " << endl;

        for(unsigned int i=0;i<possible_movements.size();++i)
        {
            cout << "-------" << i << "--------" << endl;

            possible_movements[i]->print_state();
        }
        cout << "------------------" << endl;
        */

        /*
        if(current->_parent)
        {
            cout << "parent " << endl;
            current->_parent->print_state();
            cout << "------------------" << endl;
        }
        */

	this->remove_or_update_if_already_in_open_list(open_list);

        // avoid to examine same path twice
        this->remove_if_already_in_closed_list(closed_list);
}

void	Astar::remove_if_already_in_closed_list(std::vector<node *>& closed_list){
	bool occur = false;
        for (std::vector<node *>::iterator it_possible_movements = possible_movements.begin(); it_possible_movements != possible_movements.end(); it_possible_movements++){
		if (occur == true){
                        it_possible_movements = possible_movements.begin();
			occur = false;
		}
		for (std::vector<node *>::const_iterator it_closed = closed_list.begin(); it_closed != closed_list.end(); it_closed++){
                        if ((*(*it_possible_movements)) == (*(*it_closed))){
                                if ((*(*it_possible_movements)) < (*(*it_closed))){
                                        // possible_movements.erase(it_possible_movements);
					closed_list.erase(it_closed);
					it_closed = closed_list.begin();
					if (it_closed == closed_list.end())
						return;
				}
				else{
                                        possible_movements.erase(it_possible_movements);
					occur = true;
                                        it_possible_movements = possible_movements.begin();
                                        if(it_possible_movements == possible_movements.end())
						return;
					break ;
				}
			}
		}
	}
}

void	Astar::remove_or_update_if_already_in_open_list(std::vector<node *>& open_list){
	bool occur = false;
        for (std::vector<node *>::iterator it_possible_movements = possible_movements.begin(); it_possible_movements != possible_movements.end(); it_possible_movements++){
		if (occur == true){
                        it_possible_movements = possible_movements.begin();
			occur = false;
		}
		for (std::vector<node *>::iterator it_open = open_list.begin(); it_open != open_list.end(); it_open++){
                        if ((*(*it_possible_movements)) == (*(*it_open))){
                                if ((*(*it_possible_movements)) < (*(*it_open))){
                                        (*(*it_open)) = (*(*it_possible_movements));
				}
                                delete *it_possible_movements;
                                possible_movements.erase(it_possible_movements);
				occur = true;
                                it_possible_movements = possible_movements.begin();
                                if (it_possible_movements == possible_movements.end())
					return;
				break ;
			}
		}
	}
}


node* Astar::search_moves_case(node *current, int x_blank, int y_blank, int x_mov, int y_mov){

        // apply movement to current map
        node *new_node = new node(*current);

        new_node->_state[y_blank][x_blank] = new_node->_state[y_mov][x_mov]; // move
        new_node->_state[y_mov][x_mov] = 0; // set empty

	this->rate_node(new_node);

        new_node->incrGeneration();

        // assign parent
        new_node->_parent = current;

        return new_node;
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
        node *possible_movements_node;

	std::sort(open_list.begin(), open_list.end());
        possible_movements_node = *open_list.begin();
        closed_list.push_back(possible_movements_node);
	std::reverse(open_list.begin(), open_list.end());
	open_list.pop_back();
        return possible_movements_node;
}

bool compare_generation(node *i, node *j) { return (i->_generation < j->_generation); }

void	Astar::get_path(node *current)
{
        node *possible_movements_node = current;
        std::vector<node *> path;
        while (possible_movements_node->_parent){
                path.push_back(possible_movements_node);
                possible_movements_node = possible_movements_node->_parent;
	}
	std::sort(path.begin(), path.end(), compare_generation);
	std::reverse(path.begin(), path.end());
	for_each(path.begin(), path.end(), print_it);
	std::cout << "NUMBER OF STEP" << path.size() << std::endl;

}
