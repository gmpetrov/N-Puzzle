/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:40:28 by gmp               #+#    #+#             */
/*   Updated: 2015/03/22 22:30:34 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_HPP
# define ASTAR_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include "node.hpp"

class Astar
{
	public:
		Astar();
		Astar(const Astar & src);
		~Astar(void);
		Astar &	operator=(Astar const & rhs);

		void	search_moves(node *current);
		void	search_moves_case_1(node *current, int x, int y);
		void	search_moves_case_2(node *current, int x, int y);
		void	search_moves_case_3(node *current, int x, int y);
		void	search_moves_case_4(node *current, int x, int y);
		void	find_blank(node *current, int *x, int *y);
		int		**copy_state(int **state, int size);

		std::vector<node *>	tmp;

		/* GETTERS */

		/* SETTERS */

	private:
		// Astar(void);
};

#endif