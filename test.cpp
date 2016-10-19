#include <iostream>
#include <string>
#include <fstream>

int open_file(std::string name, std::ifstream& fstream){
		fstream.open(name);
		if (fstream.is_open())
			return 1;
		else
			return 0;
}

int main() {
    std::ifstream cpuinfo_file;
    std::string line;
	if (open_file("/proc/cpuinfo", cpuinfo_file)) {
		const std::string key = "model name";
		std::size_t found;

		while (getline(cpuinfo_file, line)) {
			found = line.find(key);
			if (found!=std::string::npos) {
                
				/*line=(line.substr(found+key.length()+1,
								   // remove key and quotes at the beginning
								   line.length()-(found+key.length()+1)-1));
								   // remove quotes at the end*/
                found = line.find(":");
				line=line.substr(found+2);
								   // remove ':' and space at the beginning
                std::cout << line << std::endl;
                break;
			}
		}
	}


    std::cout << "unknown" << std::endl;
}
