/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:43 by gmp               #+#    #+#             */
/*   Updated: 2015/03/20 17:25:38 by gmp              ###   ########.fr       */
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
		node(int size);
		node(int size,node *parent);
		node(const node & src);
		~node(void);
		node &	operator=(node const & rhs);

		node	*_parent;
		int		cost;
		int		**state;
		int		_size;

		/* GETTERS */
		int		getCost(void) const;
		node	*getParent(void)  const;
		/* SETTERS */

	private:
		node(void);
};

#endif