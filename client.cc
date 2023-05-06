//
// daytime_client.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			cerr << "Usage: daytime_client <host> <port>" << endl;
			return EXIT_FAILURE;
		}

		tcp::iostream s(argv[1], argv[2]); //[1] == host, [2] == port
		if (!s) //Connection failed
		{
			cout << "Unable to connect: " << s.error().message() << endl;
			return EXIT_FAILURE;
		}

		string line;
		//s >> line;
		getline(s, line);
		cout << line << endl;
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
