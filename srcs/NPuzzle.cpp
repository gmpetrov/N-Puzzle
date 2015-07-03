/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 14:08:25 by gmp               #+#    #+#             */
/*   Updated: 2015/07/03 12:04:20 by gmp              ###   ########.fr       */
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

node		*NPuzzle::generate(int size, int iterations){
	node 	*board = new node(generateFinalBoard(size), size);

	if (iterations < 0)
		iterations = rand() % 20;

	std::list<node *>	oldMoves;

	oldMoves.push_back(board);

	// LOOP UNTIL THE GIVEN ITERATION
	for (int i = 0; i < iterations; i++){

		// GET ALL POSSIBLE MOVEMENTS
		std::list<node *> moves = algo.search_moves(board);

		// DELETE THE PREVIOUS MOVE FROM THE LIST
		for (std::list<node *>::iterator iter = moves.begin(); iter != moves.end(); iter++){
			if (this->isNodeInList(*iter, oldMoves)){
				moves.erase(iter);
			}
		}

		if(moves.size() == 0){
			std::cout << "Already made all possible movements" << std::endl;
			return board;
		}

		// GET RANDOMLY ONE OF THEM
		std::list<node *>::iterator it = moves.begin();

		int next = rand() % (moves.size());
		std::advance(it, next);

		*board = **it;
		oldMoves.push_back(board);

	}
	board->_parent = NULL;
	return board;
}

node 	*NPuzzle::isNodeInList(node *current, std::list<node *> & list){
	for (std::list<node *>::iterator it = list.begin(); it != list.end(); ++it){
		if (**it == *current){
			return *it;
		}
	}
	return NULL;
}

int		**NPuzzle::generateFinalBoard(int size){
	int		counter = 1;
	int		dimension = size;
	int 	**board = new int*[size];

	// ALLOCATE THE BOARD
	for(int j = 0; j < size; ++j) {
		board[j] = new int[size];
		for(int i = 0; i < size; ++i) {
			board[j][i] = 0;
		}
	}

	int num_elements = (size * size);

	// FILL THE BOARD WITH SNAIL SOLUTION ORDERING
	while (counter < num_elements)
	{
		for (int x = size - dimension; x < dimension && (counter < num_elements); x++){
			int y = size - dimension;
			board[y][x] = counter;
			counter++;
		}
		dimension -= 1;
		for (int v = size - dimension; v <= dimension && (counter < num_elements); v++){
			int x = dimension;
			board[v][x] = counter;
			counter++;
		}
		for (int x = dimension - 1; x >= (size - (dimension + 1)) && (counter < num_elements); x--){
			int y = dimension;
			board[y][x] = counter;
			counter++;
		}
		for (int y = dimension - 1; y >= size - dimension && (counter < num_elements); y--){
			int x = (size - dimension) - 1;
			board[y][x] = counter;
			counter++;
		}
	}
	return board;
}

void		NPuzzle::check_if_space_exist(void){
	for (int y = 0; y < this->_size; y++){
		for (int x = 0; x < this->_size; x++){
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


void NPuzzle::resolve(node *board){

	bool success = false;
	unsigned long  c_time	 = 0;
	unsigned long  c_size  = 0;
	unsigned long  maxSizeClosedList = 0;

	// SET INITIAL STATE AS CURRENT STATE
	node *current = board;

	std::cout << "input" << std::endl;
	current->print_state();
	std::cout << std::endl;
	algo.rate_node(current);

	//LISTS USED IN ALGORITHM
	std::list<node *> open_list;
	std::list<node *> closed_list;

	// Add initial node to open list
	open_list.push_back(current);
	while(!open_list.empty()){

		// CALCULATE COMPLEXITY IN TIME (Total number of states ever selected in the "opened" set)
		c_time = (open_list.size() > c_time ? open_list.size() : c_time);

		// CALCULATE COMPLEXITY IN SIZE (Maximum number of states ever represented in memory at the same time)
		maxSizeClosedList = (closed_list.size() > maxSizeClosedList ? closed_list.size() : maxSizeClosedList);
		c_size = ((c_time + maxSizeClosedList) > c_size ? (c_size + maxSizeClosedList) : c_size);

		// GET FIRST ELEMENT OF THE OPEN LIST AS CURRENT NODE
			// std::sort(open_list.begin(), open_list.end());
		current = open_list.front();

		if (current->_heuristic <= 1){
			success = true;
			break ;
		}
		else{

			// REMOVING FIRST ELEMENT OF THE OPEN LIST
			open_list.pop_front();

			// GET ALL POSSIBLE MOVES FROM THE CURRENT NODE
			std::list<node *> successors = this->algo.search_moves(current);

			// ITERATE ON ALL POSSIBLE MOVES
			for(std::list<node *>::iterator move = successors.begin(); move != successors.end(); ++move){

				//CHECKING FOR OCCURENCE ON THE CLOSED LIST
				if (this->algo.isNodeInList(*move, closed_list)) { continue; }

				//CHECKING FOR OCCURENCE ON THE OPEN LIST
				node *nodeInOpenList = this->algo.isNodeInList(*move, open_list);

				if (!nodeInOpenList){
					this->algo.insertInList(*move, open_list);
				}
			}
		}
		closed_list.push_front(current);
	}

	if(success)
	{
		std::list<node *> path = algo.get_path(current);
		current->print_state();
		node 	goal(generateFinalBoard(current->_size), current->_size);
		std::cout << std::endl;
		goal.print_state();
		std::cout << std::endl << "\033[33m====> Success \033[0m" << std::endl;
		std::cout << "\033[33;36m====> Heuristic : \033[33m" << algo.heuristicType << "\033[0m" << std::endl;
		std::cout << "\033[33;36m====> Number of moves : \033[33m" << path.size() << "\033[0m" << std::endl;
		std::cout << "\033[33;36m====> Complexity in time : \033[33m" << c_time << "\033[0m" << std::endl;
		std::cout << "\033[33;36m====> Complexity in size : \033[33m" << c_size << "\033[0m" << std::endl;

	}
	else
	{
		algo.get_path(current);
		std::cout << "FAILED" << std::endl;
		current->print_state();
	}
}