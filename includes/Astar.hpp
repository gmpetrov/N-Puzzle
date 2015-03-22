/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:40:28 by gmp               #+#    #+#             */
/*   Updated: 2015/03/22 17:07:09 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_HPP
# define ASTAR_HPP

# include <iostream>
# include <fstream>
# include <string>
# include "node.hpp"

class Astar
{
	public:
		Astar();
		Astar(const Astar & src);
		~Astar(void);
		Astar &	operator=(Astar const & rhs);

		void	search_moves(node *current);
		void	find_blank(node *current, int *x, int *y);

		/* GETTERS */

		/* SETTERS */

	private:
		// Astar(void);
};

#endif