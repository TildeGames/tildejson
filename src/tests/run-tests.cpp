
#include <dirent.h>
#include <list>

#include <fstream>
#include <sstream>
#include <iostream>

// Linux terminal colors
#define C_RED   "\033[1;31m"
#define C_GREEN "\033[1;32m"
#define C_RESET "\033[0m "

// Global constants
#define TESTS_PATH   "./tests/"
#define RESULTS_PATH "./results/"
#define TEST_EXEC    "./run-test"

int main()
{
	DIR *dir;
	struct dirent *ent;
	
	std::list<std::string> files;

	if ((dir = opendir (TESTS_PATH)) != NULL)
	{
		// Add each file name to the list
		while ((ent = readdir (dir)) != NULL)
			files.push_back(ent->d_name);

		closedir (dir);
	}
	else
	{
		std::cerr << "ERROR - Can't open tests folder." << std::endl;
		return 0;
	}

	// Remove current and parent
	files.remove(".");
	files.remove("..");

	
	int i=0;      // Number of tests
	int succ = 0; // Number of OK tests
	int fail = 0; // Number of KO tests

	std::list<std::string>::iterator it;
	std::cout << "--------------------" << std::endl;
	for (it=files.begin(); it!=files.end(); ++it)
	{
		i++;

		// Read test result
		std::string cmd = TEST_EXEC;
		cmd += " 2>&1 < "; // Redirect stderr to stdout
		cmd += TESTS_PATH + (*it);
		FILE* pipe = popen(cmd.c_str(), "r");
	    if (!pipe)
	    	return 0;
	    char buffer[128];
	    std::string result = "";
	    while(!feof(pipe))
	    	if(fgets(buffer, 128, pipe) != NULL)
	    		result += buffer;

	    // Read expected test result
		std::string rs = RESULTS_PATH + (*it);
		std::ifstream ifs(rs.c_str());
	    std::string expectedResult((std::istreambuf_iterator<char>(ifs)),
	                               (std::istreambuf_iterator<char>()));

	    // Write current test result
	    std::stringstream ss;	    
	    if (result == expectedResult)
		{
			succ++;
			ss << C_GREEN;
		}
		else
		{
			fail++;
			ss << C_RED;
		}
		ss << i;
		ss << C_RESET;
		std::cout << ss.str();
		std::cout << (*it) << std::endl;
	}

	// Write summary
	std::stringstream ssEnd;
	ssEnd << "--------------------" << std::endl;
	ssEnd << "End of tests :\n";
	ssEnd << C_GREEN << "  " << succ << C_RESET << " succed" << std::endl;
	ssEnd << C_RED << "  " << fail << C_RESET << " fail" << std::endl;
	ssEnd << "--------------------" << std::endl;
	std::cout << ssEnd.str();
		
	return 0;
}