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



void yourRepo(int invalid){
	clear();
	if (invalid){
		std::cout << "\n\n Invalid arguments supplied. Please try again.\n\n";
	}
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
			yourRepo(0);
			break;
		case 'e':
			configRepo();
			yourRepo(0);
			break;
		case 'l':
			listCommit();
			yourRepo(0);
			break;
        case 'q':
			museBreak();
			break;
		default: // code to be executed if n doesn't match any constant
			yourRepo(1);
			break;
    }
}

int repoExists(){
	try{
		GITPP::REPO r;

		// auto c=r.config();
		// GITPP::CONFIG::ITEM N=c["user.name"];
		return 1;
	}catch(GITPP::EXCEPTION_CANT_FIND const& e){
		return 0;
	}

}



void createRepo(){
	clear();
	std::cout << "\n\n	Create new empty repository?\n";
	std::cout << "\n	y yes";
	std::cout << "\n	no, quit\n\n";
	char yn;
	std::cin >> yn;

	if (yn=='y'){
		// Begin creation of repository
		std::string path=".";
		try{
			GITPP::REPO r(path.c_str());
		}catch(GITPP::EXCEPTION_CANT_FIND const&){
			GITPP::REPO r(GITPP::REPO::_create, path.c_str());
		}

		GITPP::REPO r(path.c_str());
		r.commits().create("test created from git_create.cc");

		for(auto i : r.commits()){
			std::cout << i << " " << i.signature().name() << " " << i.message() << "\n";
		}

		yourRepo(0);
	}
}

void commitHistory(){
	clear();
	std::cout << "Show a page with the first ten commits in the history, similar to the output of git log";
	museBreak();
	yourRepo(0);
}



int main(){
	if (!repoExists()){
		createRepo();
	}else{
		commitHistory();
	}
}
