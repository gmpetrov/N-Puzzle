/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 14:08:25 by gmp               #+#    #+#             */
/*   Updated: 2015/03/22 15:26:18 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzle.hpp"

NPuzzle::NPuzzle() : parser_map(NULL){
	this->_size = -42;
	this->parser_line_counter = 0;
}

NPuzzle::NPuzzle(int size) : parser_map(NULL), _size(size){
	this->parser_line_counter = 0;
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

void		NPuzzle::parser_save_tile(int nb, int x, int y){
	if (!this->parser_map){
		this->parser_map = (int **)malloc(sizeof(int *) * this->_size);
		for (int k = 0; k < this->_size; k++)
			this->parser_map[k] = (int *)malloc(sizeof(int) * this->_size);
	}
	// std::cout << "DEBUG " << "size : " << this->_size << " x : " << x << " y : " << y << " nb : " << nb << std::endl;
	if (x < this->_size && y < this->_size)
		this->parser_map[y][x] = nb;
	else
		throw NPuzzle::puzzle_exception("Invalid Map : parser_save_tile()");
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
		if (this->parser_is_map == true)
			this->parser_save_tile(std::atoi(tab[j]), j, this->parser_line_counter);
	}
	if (this->parser_is_map == true)
		this->parser_line_counter += 1;
	if (tab[0] && !tab[1]){
		this->_size = ft_atoi(tab[0]);
		this->parser_is_map = true;
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
		for (int j = 0; j < this->_size; j++){
			for (int i = 0; i < this->_size; i++){
				std::cout << this->parser_map[j][i] << "    ";
			}
			std::cout << std::endl;
		}
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