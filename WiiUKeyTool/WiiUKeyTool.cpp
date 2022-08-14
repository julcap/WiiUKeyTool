#include <fstream>
#include <ctime>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;
using namespace std;


map<string, string> read_key_file(char* file_path, char delimiter, map<string, string>& storage) {
	string line, key, comment;
	ifstream file(file_path);

	while (getline(file, line)) {
		if (line == "") continue;
		key = line.substr(0, line.find(delimiter));
		comment = line.substr(line.find(delimiter), line.length());
		trim(key);
		trim(comment);
		if (key != "" && storage.count(key) == 0) {
			storage.insert({ key,comment });
		}
	}

	file.close();
	return storage;
}

void save_keys_file(multimap<string, string> data) {
	string line;
	ofstream file("merged_keys.txt");
	for (auto const& x : data) {
		line = x.second + ' ' + x.first + '\n';
		file.write(line.c_str(), line.size());
	}
	file.close();
}

int main(int argc, char** argv) {
	char delimiter = '#';
	map<string, string> parsed_data;
	multimap<string, string> sorted_data;

	for (int i = 1; i < argc; i++) {
		read_key_file(argv[i], delimiter, parsed_data);
	}

	// Invert map to multimap
	for (auto const& x : parsed_data) {
		sorted_data.insert({ x.second,x.first });
	}

	save_keys_file(sorted_data);

	return 0;
}
