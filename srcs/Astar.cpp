/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/07/03 12:11:49 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Astar.hpp"

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


// FIND OCCURENCE IN A LIST

node*				Astar::isNodeInList(node *current, std::list<node *> & list){
	for (std::list<node *>::iterator it = list.begin(); it != list.end(); ++it){
		if (**it == *current && (*it)->_heuristic == current->_heuristic){
			return *it;
		}
	}
	return NULL;
}

// INSERT NODE IN LIST

void				Astar::insertInList(node * current, std::list<node *>& list){
	std::list<node *>::iterator it;
	for (it = list.begin(); it != list.end(); ++it){
		if (current->_heuristic <= (*it)->_heuristic){
			list.insert(it, current);
			return ;
		}
	}
	list.insert(it, current);
}

// Search moves available from current node and returns them

std::list<node *> Astar::search_moves(node * current){

	// variables for the coordinates of the blank tile
	int	x, y;
	this->find_blank(current, &x, &y);

	std::list<node *> moves;

	if ((y - 1) >= 0)
	{
		moves.push_back(search_moves_case(current, x, y, x, y - 1));
	}
	if ((x + 1) < current->_size)
	{
		moves.push_back(search_moves_case(current, x, y, x + 1, y));
	}
	if ((y + 1) < current->_size)
	{
		moves.push_back(search_moves_case(current, x, y, x, y + 1));
	}
	if ((x - 1) >= 0)
	{
		moves.push_back(search_moves_case(current, x, y, x - 1, y));
	}
	return moves;
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
        if (this->heuristicType == "manhattan")
    	   node->_heuristic = manhattan_heuristic(node);
        else if (this->heuristicType == "hamming")
    	   node->_heuristic = hamming_heuristic(node);
        else if (this->heuristicType == "euclidean")
            node->_heuristic = euclidean_heuristic(node);
    	node->_rate = node->_heuristic + node->_generation;
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

    int     Astar::euclidean_heuristic(node *node){
        int current_x;
        int current_y;
        int goal_x;
        int goal_y;
        int result = 0;

        for (int counter = 1; counter < (node->_size * node->_size); counter++){
            this->getCurrentPos(node, &current_x, &current_y, counter);
            this->getGoalPos(node, &goal_x, &goal_y, counter);
            int x = pow(goal_x - current_x, 2);
            int y = pow(goal_y - current_y, 2);
            result += (x + y);
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
    	node->print_state();
        std::cout << std::endl;
    }

    node	*Astar::best_move(std::list<node *> & open_list, std::list<node *> & closed_list){
        (void)closed_list;
    	node *possible_movements_node;
    	possible_movements_node = *open_list.begin();
    	open_list.erase(open_list.begin());
    	return possible_movements_node;
    }

    bool compare_generation(node *i, node *j) { return (i->_generation < j->_generation); }

    std::list<node *>	Astar::get_path(node *current)
    {
    	node *possible_movements_node = current;
    	std::list<node *> path;

    	while (possible_movements_node->_parent){
    		path.push_front(possible_movements_node);
    		possible_movements_node = possible_movements_node->_parent;
    	}

    	path.sort(compare_generation);
    	for_each(path.begin(), path.end(), print_it);
        return path;
    }
