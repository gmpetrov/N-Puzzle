/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:43 by gmp               #+#    #+#             */
/*   Updated: 2015/03/15 17:26:54 by gmp              ###   ########.fr       */
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
		node(void);
		node(const node & src);
		~node(void);
		node &	operator=(node const & rhs);

		/* GETTERS */

		/* SETTERS */
	private:
};

#endif