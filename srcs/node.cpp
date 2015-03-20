/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/03/20 17:16:01 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "node.hpp"

node::node(int size) : _parent(NULL), cost(0), _size(size){
}

node::node(int size, node *parent) : _parent(parent), _size(size){
	if (parent)
		this->cost = parent->getCost();
}

node::node(const node & src){
	*this = src;
}

node::~node(void){

}

node &	node::operator=(node const & rhs){
	this->_parent = rhs.getParent();
	this->cost = rhs.getCost();
	this->state = rhs.state;
	return *this;
}

/*
**	Getters & Setters
*/

int		node::getCost(void) const{
	return this->cost;
}

node	*node::getParent(void) const{
	return this->_parent;
}