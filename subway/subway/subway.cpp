// subway.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void usage();

int main(int argc, char** argv)
{
	//detect the correction of args
	switch (argc)
	{
	case 1://'subway'
		ReadDataFromFile();
		StationQuery();
		break;

	case 4://'subway -b station1 staion2', or 'subway -c station1 staion2'
		if (string(argv[1]) == string("-b"))
		{
			ReadDataFromFile();
			ShortestPath(string(argv[2]), string(argv[3]), SHORTEST);
		}
		else if(string(argv[1]) == string("-c"))
		{
			ReadDataFromFile();
			ShortestPath(string(argv[2]), string(argv[3]), FEWEST_TRANSFER);
		}
		else
			usage();
		break;

	case 3://'subway -a station'
		if (string(argv[1]) == string("-a"))
		{
			ReadDataFromFile();
			TSP(string(argv[2]));
		}
		else
			usage();
		break;

	default://error
		usage();
		break;
	}
    return 0;
}

void usage()
{
	cout << "Subway route planning advisor." << endl
		 << endl
		 << "Usage: subway" << endl
		 << "       subway -b station1 station2" << endl
		 << "       subway -c station1 station2" << endl
		 << "       subway -a station1" << endl
		 << endl
		 << "Options:" << endl
		 << endl
		 << "    (no option)   Read metro line name from stdin, and print the " << endl
		 << "                  stations along the way." << endl
		 << "    -b            Print the shortest path from station1 to station2." << endl
		 << "    -c            Print the path with the fewest transfer and shortest" << endl
		 << "                  length from station1 to station2." << endl
		 << "    -a            Print the shortest path that travels every station at" << endl
		 << "                  least once, from and ended at station1." << endl;
	exit(EXIT_FAILURE);
}
