#include <map>
#include <string>
#include <iostream>

/**
 * Reads console input and counts all words. Number of word occurrences is stored per-word in a map.
 *
 * Console input is read after "Enter" key is pressed.
 */

int main() {
	std::string word;
	std::map<std::string, int> wordcnt;

	// Scan for words in line until next character is new line character.
	while (!(std::cin.peek() == '\n')) {
		// ">>" operator reads all characters until whitespace.
		std::cin >> word;

		wordcnt[word]++;
	}

	// Iterate over wordcnt map and print each pair
	for (auto const& p : wordcnt) {
		std::cout << p.first << ":" << p.second << std::endl;
	}

	return 0;
}
