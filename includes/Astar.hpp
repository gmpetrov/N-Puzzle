/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:40:28 by gmp               #+#    #+#             */
/*   Updated: 2015/07/03 12:09:40 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_HPP
# define ASTAR_HPP

# include "node.hpp"
# include <iostream>
# include <fstream>
# include <string>
# include <algorithm>
# include <list>
# include <math.h>

class Astar
{
	public:
                Astar(){}

		Astar(const Astar & src);
		~Astar(void);
		Astar &	operator=(Astar const & rhs);
		std::list<node *> search_moves(node *current);
		void	insertInList(node * current, std::list<node *>& list);
		void	search_moves(node *current, std::list<node *>& open_list, std::list<node *> & closed_list);
		node	*search_moves_case(node *current, int x, int y, int x_mov, int y_mov);
		node 	*isNodeInList(node *current, std::list<node *> & list);
		void	find_blank(node *current, int *x, int *y);
		bool	is_solution(node *current);
		void	rate_node(node *node);
		int		manhattan_heuristic(node *node);
		int		hamming_heuristic(node *node);
		int 	euclidean_heuristic(node *node);
		void	getCurrentPos(node *node, int *current_x, int *current_y, int to_find);
		void	getGoalPos(node *node, int *goal_x, int *goal_y, int to_find);
		node	*best_move(std::list<node *> & open_list, std::list<node *> & closed_list);
		std::list<node *>	get_path(node *current);

		std::list<node *>	possible_movements;

		bool	_isInOpenList;
		bool	_isInClosedList;
		std::string heuristicType;

		/* GETTERS */

		/* SETTERS */

	private:
		// Astar(void);
};

#endif
