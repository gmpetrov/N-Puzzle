/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 14:08:25 by gmp               #+#    #+#             */
/*   Updated: 2015/03/19 16:55:36 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzle.hpp"

NPuzzle::NPuzzle(){
	// std::cout << "CONSTRUCTOR CALLED" << std::endl;
}

NPuzzle::NPuzzle(int size) : _size(size){
	// std::cout << "CONSTRUCTOR CALLED : NPUZZLE OF SIZE " << size << " CONSTRUCTED" << std::endl;
}

NPuzzle::NPuzzle(const NPuzzle & src){
	*this = src;
}

NPuzzle::~NPuzzle(void){
	// std::cout << "NPUZZLE DESTRUCTOR CALLED" << std::endl;
}

NPuzzle &	NPuzzle::operator=(NPuzzle const & rhs){
	this->_size = rhs.getSize();
	return *this;
}

void		NPuzzle::ft_usage(void){
		std::cout << "[USAGE] - ./npuzzle [map] or ./npuzzle" << std::endl;
}

bool		NPuzzle::parse(char *file_to_parse){
	char	**tab;
	std::string line;
	std::ifstream file(file_to_parse);

	if (file.is_open()){
		while (getline(file, line)){
			// std::cout << line << std::endl;
			if (line.c_str()[0] == '#')
				continue ;
			else{
				tab = ft_strsplit(line.c_str(), ' ');
				for (int j = 0; tab[j] != NULL; j++)
					std::cout << tab[j] << std::endl;
				std::cout << "end" << std::endl;
				this->free_tab(tab);
			}
		}
		file.close();
		return true;
	}
	else{
		std::cout << "Can't open " << file_to_parse << std::endl;
		return false;
	}
}

int			NPuzzle::getSize(void) const{
	return this->_size;
}

void		NPuzzle::setSize(int size){
	this->_size = size;
}

void		NPuzzle::free_tab(char **tab){
	for (int j = 0; tab[j] != NULL; j++){
		free(tab[j]);
	}
	free(tab);
}