#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

int open_file(std::string name, std::ifstream& fstream){
		fstream.open(name);
		if (fstream.is_open())
			return 1;
		else
			return 0;
}

main (){

    std::ifstream meminfo_file;
    std::string line;
    std::string memsize;
	if (open_file("/proc/meminfo", meminfo_file)) {
		const std::string key = "MemTotal:";
		std::size_t found;

		while (getline(meminfo_file, line)) {
			found = line.find(key);
			if (found!=std::string::npos) {
                std::string value = line.substr(found+key.length(), line.length()-(found+key.length()+3));
                remove_copy(value.begin(), value.end(), std::back_inserter(memsize), ' ');
                std::cout << memsize << std::endl;
			}
		}
	}


    std::cout << "unknown" << std::endl;

}
