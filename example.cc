// c++ hello world
// Author: Felix (scsfsa)
// Date: Oct 2018

#include <iostream>
#include <cstdlib>		// For clearing Screen

int createRepo();


int museBreak(){
	std::cout << "\n\n\n Press ENTER to continue...\n";
	system("read");

}

int clear(){
	system("clear");
}


int listConfig(){
	clear();
	std::cout << "\n List Configuration";
	museBreak();

}



int configRepo(){
	clear();
	std::cout << "\n Configure Repository";
	museBreak();

}



int listCommit(){
	clear();
	std::cout << "\n List Commits";
	museBreak();

}



int createRepo(){
	clear();
	std::cout << "\n Your git repository";
	std::cout << "\n	c list config";
	std::cout << "\n	e configure repository";
	std::cout << "\n	l list commits";
	std::cout << "\n	q quit\n\n";

	char choice;
	std::cin >> choice;
	switch(choice) {
        case 'c':
			listConfig();
			createRepo();
			break;
		case 'e':
			configRepo();
			createRepo();
			break;
		case 'l':
			listCommit();
			createRepo();
			break;
        case 'q':
			museBreak();
			break;
    }
}


int main(){
	clear();
	std::cout << "\n\n	Create new empty repository?\n";
	std::cout << "\n	y yes";
	std::cout << "\n	no, quit\n\n";
	char yn;
	std::cin >> yn;

	if (yn=='y'){
		createRepo();
	}
}
