// git program
// Author: sc17jhd
// Date: Oct 2018

#include <iostream>
#include <cstdlib>		// For clearing Screen
#include "gitpp5.h"

void yourRepo();


void museBreak(){
	std::cout << "\n\n\n Press ENTER to continue...\n";
	system("read");

}

void clear(){
	system("clear");
}


void listConfig(){
	clear();
	std::cout << "\n List Configuration";
	museBreak();

}



void configRepo(){
	clear();
	std::cout << "\n Configure Repository";
	museBreak();

}



void listCommit(){
	clear();
	std::cout << "\n List Commits";
	museBreak();

}



void yourRepo(){
	clear();
	std::cout << "\n Your git repository";
	std::cout << "\n	c list config";
	std::cout << "\n	e configure repository";
	std::cout << "\n	l list commits";
	std::cout << "\n	q quit\n\n";

	char choice;
	std::cin >> choice;
	// if (choice!='c'||choice!='e'||choice!='l'||choice!='q'){
	// }
	switch(choice) {
        case 'c':
			listConfig();
			yourRepo();
			break;
		case 'e':
			configRepo();
			yourRepo();
			break;
		case 'l':
			listCommit();
			yourRepo();
			break;
        case 'q':
			museBreak();
			break;
		default: // code to be executed if n doesn't match any constant
			std::cout << "\n Invalid arguments supplied. Please try again.";
			break;
    }
}

int repoExists(){
	return 1;
}

void createRepo(){
	clear();
	std::cout << "\n\n	Create new empty repository?\n";
	std::cout << "\n	y yes";
	std::cout << "\n	no, quit\n\n";
	char yn;
	std::cin >> yn;

	if (yn=='y'){
		yourRepo();
	}
}

void commitHistory(){
	clear();
	std::cout << "Show a page with the first ten commits in the history, similar to the output of git log";
	museBreak();
	yourRepo();
}



int main(){
	if (!repoExists()){
		createRepo();
	}else{
		commitHistory();
	}
}