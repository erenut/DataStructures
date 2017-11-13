#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

	// define the state
    bool state = true;
    int failIndex = 0;

	// Define the stack
    std::stack <Bracket> opening_brackets_stack;
    
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket new_element(next,position);
            opening_brackets_stack.push(new_element);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()) {
            	state = false;
            	failIndex = position;
            	break;
			}
			// if the stack is not empty then it will pop the last element
			Bracket top_element = opening_brackets_stack.top();
			opening_brackets_stack.pop();
			if (!top_element.Matchc(next)){
				state = false;
				failIndex = position;
				break;
			}

        }
    }

    // Printing answer, write your code here
    if (state && opening_brackets_stack.empty())
    	std::cout << "Success" << std::endl;
	else{
		std::cout << (failIndex+1) << std::endl;
		//std::cout << state << opening_brackets_stack.empty() << std::endl;
	}

    return 0;
}
