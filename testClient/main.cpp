#include <iostream>
using namespace std;
extern "C" int  clnt(int);

int main(int argc, char *argv[])
{
  int   x = argv[1] ? atoi(argv[1]) : 100;
  int   y = 0;
        y = clnt(x);
        std::cout << y << std::endl;
	std::cout << "End tester" << std::endl;
        return 0;
}

