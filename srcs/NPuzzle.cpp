/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 14:08:25 by gmp               #+#    #+#             */
/*   Updated: 2015/03/26 23:35:39 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzle.hpp"

using namespace std;

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

void		NPuzzle::check_if_space_exist(void){
	for (int y = 0; y < this->_size; y++){
		for (int x = 0; x < this->_size; x++){
			// std::cout << this->parser_map[y][x] << std::endl;
			if (this->parser_map[y][x] == 0)
				return ;
		}
	}
	throw NPuzzle::puzzle_exception("Invalid Map : No empty tile, need one");
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
		this->check_if_space_exist();
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

// void	print_it(node *node){
// 	std::cout << "================" << std::endl;
// 	std::cout << "RATE = ";
// 	std::cout << node->_rate << std::endl;
// 	node->print_state();
// }

/*
**	void	NPuzzle::rezolve(char *)
*/


void NPuzzle::rezolve(char *file){

        if(!this->parse(file))
        {
            cout << "unable to read input file" << endl;
            return;
        }

        node *current = new node(this->parser_map, this->_size);

        current->print_state();

        algo.rate_node(current);
        this->open_list.push_back(current);
	this->success = false;

        while (success != true){
                current = this->algo.best_move(this->open_list, this->closed_list);
                if (algo.is_solution(current) == true)
			success = true;
                this->algo.search_moves(current, this->open_list, this->closed_list);
		this->open_list.insert(this->open_list.end(), algo.tmp.begin(), algo.tmp.end());
		if (this->open_list.empty()){
			std::cout << "NO SOLUTION" << std::endl;
			exit(0);
		}
                current->_generation += 1;
                if (current->_rate < 3){
                        std::cout << "Rate = " << current->_rate << std::endl;
                        current->print_state();
		}
		//for_each(this->open_list.begin(), this->closed_list.end(), print_it);
	}
        algo.get_path(current);
	std::cout << "FIND ONE" << std::endl;
	// current->print_state();
 }
