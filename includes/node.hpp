/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:43 by gmp               #+#    #+#             */
/*   Updated: 2015/03/25 15:44:44 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>
# include <fstream>
# include <string>

class node
{
	public:
		node(int  **state, int size);
		node(int **state, int size,node *parent);
		node(const node & src);
		~node(void);
		node &	operator=(node const & rhs);

		node	*_parent;
		int		cost;
		int		**_state;
		int		_rate;
		int		_generation;
		int		_size;

		bool	is_equal(const node & rhs) const;
		bool	is_not_equal(const node & rhs) const;
		void	init_state(int **state, int size);
		void	print_state(void);

		template<typename T>
		void		free_tab(T tab);
		bool		operator<(const node & rhs) const;
		bool		operator==(const node & rhs) const;
		bool		operator!=(const node & rhs) const;

		/* GETTERS */
		int		getCost(void) const;
		node	*getParent(void)  const;
		/* SETTERS */

	private:
		node(void);
};

#endif