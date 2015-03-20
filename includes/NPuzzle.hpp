/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 14:04:53 by gmp               #+#    #+#             */
/*   Updated: 2015/03/19 16:57:16 by gmp              ###   ########.fr       */
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


		/* GETTERS */
		int			getSize(void) const;

		/* SETTERS */
		void		setSize(int size);

		bool		parse(char *);
		void		parser_check_line(std::string line);
		std::vector<node>	map;
		std::vector<node>	open_list;
		std::vector<node>	closed_list;
		void		free_tab(char **tab);

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
	private:
		int			_size;
};

#endif