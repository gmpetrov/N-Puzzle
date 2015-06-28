/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 17:25:49 by gmp               #+#    #+#             */
/*   Updated: 2015/06/28 22:04:06 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "node.hpp"


node::node(int **state, int size) : _parent(NULL), cost(0){
	this->init_state(state, size);
	this->_generation = 0;
}

node::node(const node & src){

	init_state(src._state, src._size);

	_parent = src._parent;
	_rate = src._rate;
	_generation = src._generation;
}

node::~node(void){

	for(int j = 0; j < _size; ++j) {
		delete[] _state[j];
	}

	delete[] _state;
}

std::ostream & 	operator<<(std::ostream & o, node const & i){
	return o << "node : { _rate = " << i._rate << ";" << " parent._rate = " << i._parent->_rate << ";" << " }" << std::endl;
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

	if(this->_size != rhs._size)
		return false;

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

	_size = size;

	_state = new int*[size];
	for(int j = 0; j < size; ++j) {
		_state[j] = new int[size];
		for(int i = 0; i < size; ++i) {
			_state[j][i] = state[j][i];
		}
	}
}

void	node::print_state(void){
	for(int j = 0; j < this->_size; j++){
		for(int i = 0; i < this->_size; i++)
		{
			if(this->_state[j][i]<10)
				std::cout << this->_state[j][i] << "  ";
			else
				std::cout << this->_state[j][i] << " ";
		}
		std::cout << std::endl;
	}
}


node &	node::operator=(node const & rhs){
	this->_parent = rhs.getParent();
	this->cost = rhs.getCost();

	// MAYBE NOT NECESSARY
	init_state(rhs._state, rhs._size);

	this->_rate = rhs._rate;
	this->_generation = rhs._generation;
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
