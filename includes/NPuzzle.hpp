/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 14:04:53 by gmp               #+#    #+#             */
/*   Updated: 2015/03/20 17:29:57 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include "node.hpp"

extern "C" {
	#include "libft.h"
}

class NPuzzle
{
	public:
		NPuzzle(void);
		NPuzzle(int size);
		NPuzzle(const NPuzzle & src);
		~NPuzzle(void);
		NPuzzle &	operator=(NPuzzle const & rhs);
		void		ft_usage(void);

		int		**parser_map;

		/* GETTERS */
		int			getSize(void) const;

		/* SETTERS */
		void		setSize(int size);

		bool		parse(char *);
		void		parser_check_line(std::string line);
		void		parser_check_line_size(char **tab);
		void		parser_save_line(std::string str);

		std::vector<node>	open_list;
		std::vector<node>	closed_list;
		template<typename T>
		void		free_tab(T tab);

		class		puzzle_exception : public std::exception{
			public:
				puzzle_exception(std::string const &) throw();
				puzzle_exception(puzzle_exception const &src) throw();
				puzzle_exception & operator=(puzzle_exception const & rhs) throw();
				~puzzle_exception() throw();
				virtual const char *what() const throw();

				std::string			error;
			private:
				puzzle_exception() throw();
		};

		node		*current;
	private:
		int			_size;
};

#endif