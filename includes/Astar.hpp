/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:40:28 by gmp               #+#    #+#             */
/*   Updated: 2015/03/26 23:35:56 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_HPP
# define ASTAR_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <algorithm>
# include "node.hpp"

void	print_it(node *node);

class Astar
{
	public:
		Astar();
		Astar(const Astar & src);
		~Astar(void);
		Astar &	operator=(Astar const & rhs);

		void	search_moves(node *current, std::vector<node *> & open_list, std::vector<node *> & closed_list);
		void	search_moves_case_1(node *current, int x, int y);
		void	search_moves_case_2(node *current, int x, int y);
		void	search_moves_case_3(node *current, int x, int y);
		void	search_moves_case_4(node *current, int x, int y);
		void	remove_or_update_if_already_in_open_list(std::vector<node *>& open_list);
		void	remove_if_already_in_closed_list(std::vector<node *>& closed_list);

		void	find_blank(node *current, int *x, int *y);
		int		**copy_state(int **state, int size);
		bool	is_solution(node *current);
		void	rate_node(node *node);
		int		manhattan_heuristic(node *node);
		int		hamming_heuristic(node *node);
		void	getCurrentPos(node *node, int *current_x, int *current_y, int to_find);
		void	getGoalPos(node *node, int *goal_x, int *goal_y, int to_find);
		node	*best_move(std::vector<node *> & open_list, std::vector<node *> & closed_list);
		void	get_path(node *current);

		std::vector<node *>	tmp;

		/* GETTERS */

		/* SETTERS */

	private:
		// Astar(void);
};

#endif