/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/03/25 16:56:11 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "node.hpp"

node::node(int **state, int size) : _parent(NULL), cost(0), _size(size){
	// this->init_state(state, size);
	this->_state = state;
	this->_generation = 0;
}

node::node(int **state, int size, node *parent) : _parent(parent), _size(size){
	// this->init_state(state, size);
	this->_state = state;
	if (parent){
		this->cost = parent->getCost();
		this->_generation = parent->_generation;
	}
}

node::node(const node & src){
	*this = src;
}

node::~node(void){
	// if (this->_state)
	// 	this->free_tab<int **>(this->_state);
}

bool	node::operator<(const node & rhs) const{
	return this->_rate < rhs._rate;
}

bool	node::operator==(const node & rhs)const{
	return this->is_equal(rhs);
}

bool	node::operator!=(const node & rhs)const{
	return this->is_not_equal(rhs);
}

bool	node::is_equal(const node & rhs) const{
	for (int y = 0; y < this->_size; y++){
		for (int x = 0; x < this->_size; x++){
			if (this->_state[y][x] != rhs._state[y][x])
				return false;
		}
	}
	return true;
}

bool	node::is_not_equal(const node & rhs) const{
	for (int y = 0; y < this->_size; y++){
		for (int x = 0; x < this->_size; x++){
			if (this->_state[y][x] != rhs._state[y][x])
				return true;
		}
	}
	return false;
}

void	node::init_state(int **state, int size){
	this->_state = (int **)malloc(sizeof(int *) * size);
	for (int j = 0; j < size; j++){
		this->_state[j] = (int *)malloc(sizeof(int) * size);
		for (int i = 0; i < size; i++){
			this->_state[j][i] = state[j][i];
		}
	}
}

void	node::print_state(void){
	for(int j = 0; j < this->_size; j++){
		for(int i = 0; i < this->_size; i++)
			std::cout << this->_state[j][i] << " ";
		std::cout << std::endl;
	}
}

node &	node::operator=(node const & rhs){
	this->_parent = rhs.getParent();
	this->cost = rhs.getCost();
	this->_state = rhs._state;
	return *this;
}

template<typename T>
void		node::free_tab(T tab){
	for (int j = 0; tab[j] != NULL; j++){
		free(tab[j]);
	}
	free(tab);
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