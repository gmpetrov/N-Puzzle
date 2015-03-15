/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/03/15 17:27:38 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "node.hpp"

node::node(){
}

node::node(const node & src){
	*this = src;
}

node::~node(void){

}

node &	node::operator=(node const & rhs){
	(void)rhs;
	return *this;
}
