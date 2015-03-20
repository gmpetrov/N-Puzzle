/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 14:08:25 by gmp               #+#    #+#             */
/*   Updated: 2015/03/20 18:06:24 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzle.hpp"

NPuzzle::NPuzzle() : parser_map(NULL){
	this->_size = -42;
}

NPuzzle::NPuzzle(int size) : parser_map(NULL), _size(size){
}

NPuzzle::NPuzzle(const NPuzzle & src){
	*this = src;
}

NPuzzle::~NPuzzle(void){

}

NPuzzle &	NPuzzle::operator=(NPuzzle const & rhs){
	this->_size = rhs.getSize();
	return *this;
}

void		NPuzzle::ft_usage(void){
		std::cout << "[USAGE] - ./npuzzle [map] or ./npuzzle" << std::endl;
}

void		NPuzzle::parser_save_line(std::string line){
	char	**tab;
	// if (!this->current){
	// 	this->current = new node(this->_size);
	// }
	if (!this->parser_map){
		this->parser_map = (int **)malloc(sizeof(int *) * this->_size);
		for (int k = 0; k < this->_size; k++)
			this->parser_map[k] = (int *)malloc(sizeof(int) * this->_size);
	}
	tab = ft_strsplit(line.c_str(), ' ');
	for (int i = 0; tab[i] != NULL; i++){

	}
	this->free_tab(tab);
}

void		NPuzzle::parser_check_line_size(char **tab){
	int		i;

	for (i = 0; tab[i] != NULL; i++)
		if (tab[i][0] == '#'){
			break ;
		}
	if (i != this->_size){
		this->free_tab<char **>(tab);
		throw NPuzzle::puzzle_exception("Invalid size for row");
	}
}

void		NPuzzle::parser_check_line(std::string line){
	char	**tab;

	tab = ft_strsplit(line.c_str(), ' ');
	if (this->_size != -42 && this->_size >= 3)
		parser_check_line_size(tab);
	for (int j = 0; tab[j] != NULL; j++){
		for (int i = 0; tab[j][i] != 0; i++){
			if (!ft_isdigit(tab[j][i]))
				throw NPuzzle::puzzle_exception("Invalid Map");
		}
	}
	if (tab[0] && !tab[1]){
		this->_size = ft_atoi(tab[0]);
		if (this->_size < 3)
		{
			this->free_tab<char **>(tab);
			throw NPuzzle::puzzle_exception(static_cast<std::string>("Size of Map is too small, given : ") + static_cast<std::string>(std::to_string(this->_size)));
		}
	}
	this->free_tab<char **>(tab);
}

bool		NPuzzle::parse(char *file_to_parse){
	std::string line;
	std::ifstream file(file_to_parse);

	if (file.is_open()){
		while (getline(file, line)){
			if (line.c_str()[0] == '#')
				continue ;
			else{
				this->parser_check_line(line);
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
template<typename T>
void		NPuzzle::free_tab(T tab){
	for (int j = 0; tab[j] != NULL; j++){
		free(tab[j]);
	}
	free(tab);
}

/*
**	Exceptions
*/

NPuzzle::puzzle_exception::puzzle_exception(std::string const & str) throw() : error(str){

}

NPuzzle::puzzle_exception::puzzle_exception(NPuzzle::puzzle_exception const & src) throw() : error(src.error){
		*this = src;
}

NPuzzle::puzzle_exception & NPuzzle::puzzle_exception::operator=(NPuzzle::puzzle_exception const &rhs) throw(){
	(void)rhs;
	return *this;
}

NPuzzle::puzzle_exception::~puzzle_exception() throw(){
}

const char		*NPuzzle::puzzle_exception::what() const throw(){
	return this->error.c_str();
}