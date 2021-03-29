#include <list>
#include <string>
#include <iostream>

/**
 * Reads all words from console input and sorts alphabetically.
 *
 * Console input is read after "Enter" key is pressed.
 */

int main() {
	std::string word;
	std::list<std::string> words;

	// Scan for words in line until next character is new line character.
	while (!(std::cin.peek() == '\n')) {
		// ">>" operator reads all characters until whitespace character is found.
		std::cin >> word;

		words.push_back(word);
	}

	// Sort words alphabetically and print them.
	words.sort();

	// Iterate over words list and print each element
	for (auto const& i : words) {
		std::cout << i << std::endl;
	}

	return 0;
}
