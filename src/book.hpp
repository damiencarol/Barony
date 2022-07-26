/*-------------------------------------------------------------------------------

	BARONY
	File: book.hpp
	Desc: declarations and such for readable books

	Copyright 2013-2016 (c) Turning Wheel LLC, all rights reserved.
	See LICENSE for details.

-------------------------------------------------------------------------------*/

#pragma once

#include "main.hpp"

class Book_t
{
public:
	Book_t() {};
	std::string text = "";
	std::string name = "";
	std::vector<std::string> formattedPages;
};
extern std::vector<Book_t> allBooks;

class BookParser_t
{
	static const int MAX_FILE_LENGTH = 192000;
	const int versionJSON = 1;
public:
	bool booksRequireCompiling();
	bool readCompiledBooks();
	void writeCompiledBooks();
	void createBooks(bool forceCacheRebuild);
	void createBook(std::string filename); //Take a book filename and generate all of its pages.
	void deleteBooks();
	std::unordered_map<std::string, std::string> tempBookData;
	void readBooksIntoTemp();
	std::list<std::string> getListOfBooksAfterFiltering();
};
extern BookParser_t bookParser_t;

int getBook(std::string bookTitle);
std::string getBookNameFromIndex(int index);
extern int numbooks;

