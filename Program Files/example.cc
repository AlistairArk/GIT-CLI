// git program
// Author: sc17jhd
// Date: Oct 2018

#include <iostream>
#include <cstdlib>        // For clearing Screen
#include "gitpp5.h"
#include <cstdlib>
#include <sstream>        //convert to string?
#include <typeinfo>     // Debugging variable types

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
    GITPP::REPO r;
    auto c=r.config();

    std::string mycwd(getenv("PWD"));
    // char username = ;
    std::cout << "\n Your git repository in <" << mycwd << ">\n" <<std::endl;
    GITPP::CONFIG::ITEM name=c["user.name"];
    std::cout << "1. name:                          <" << name.value() << ">\n";
    GITPP::CONFIG::ITEM email=c["user.email"];
    std::cout << "2. email:                         <" << email.value() << ">\n";
    GITPP::CONFIG::ITEM pushDef=c["push.default"];
    std::cout << "3. push default:                  <" << pushDef.value() << ">\n";
    GITPP::CONFIG::ITEM bare=c["core.bare"];
    std::cout << "4. bare:                          <" << bare.value() << ">\n";
    GITPP::CONFIG::ITEM filemode=c["core.filemode"];
    std::cout << "5. filemode:                      <" << filemode.value() << ">\n";
    GITPP::CONFIG::ITEM repFmtVer=c["core.repositoryformatversion"];
    std::cout << "6. repository format version:     <" << repFmtVer.value() << ">\n";
    GITPP::CONFIG::ITEM logallrefupdates=c["core.logallrefupdates"];
    std::cout << "7. log all ref updates:           <" << logallrefupdates.value() << ">\n";
    museBreak();

}



void listCommit(){
    clear();
    std::cout << "\n Your Commits: \n\n";

    GITPP::REPO r;

    int counter=0;
    for(auto i : r.commits()){
        counter+=1;
        std::cout << counter << ". ";
        // std::cout << git_commit_message(i);
        std::cout << "<"<< i << "> <" << i.signature().name() << "> <" << i.message() << ">\n";
    }
    museBreak();

}

void listBranch(){
    GITPP::REPO r;

    // Display string for use in option selection
    char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l', 'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    std::cout << "\n    select a branch to display commits\n\n";
    int branchCounter=-1; // Index of current branch
    for(GITPP::BRANCH i : r.branches()){
        branchCounter+=1;
        std::cout << "    " << alphabet[branchCounter] << ". " << i << "\n";
    }
    if (branchCounter){
        // If more than one branch, take input for choice
        char choice;
        std::cin >> choice;


        branchCounter = -1;         // Reset branchCounter

        std::string out_string;

        // Loop through choices until desired branch is found
        for(GITPP::BRANCH i : r.branches()){
            branchCounter+=1;
            if (choice == alphabet[branchCounter]){
                // std::cout << "Switching to branch "<< i.name();
                r.checkout(i.name());             // Switch to branch
                listCommit();                     // Now list commits in this branch
                break;
            }
        }

    }else{
        listCommit(); // Only master branch exists, thus display that
    }

}





void yourRepo(int invalid){
    clear();
    if (invalid){
        std::cout << "\n\n Invalid arguments supplied. Please try again.\n\n";
    }
    std::cout << "\n Your git repository";
    std::cout << "\n    c list config";
    std::cout << "\n    e configure repository";
    std::cout << "\n    l list commits";
    std::cout << "\n    q quit\n\n";

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
            listBranch();
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
        GITPP::REPO r; // If repo exists return 1
        return 1;

    }catch(GITPP::EXCEPTION_CANT_FIND const& e){
        return 0;
    }

}



void createRepo(){
    clear();
    std::cout << "\n\n    Create new empty repository?\n";
    std::cout << "\n    y yes";
    std::cout << "\n    no, quit\n\n";
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
        r.commits().create("First Commit!");

        listCommit();

        yourRepo(0);
    }
}

void commitHistory(){
    clear();
    listCommit(); // Maybe hand an argument specifying to show only up to 10
    // std::cout << "Show a page with the first ten commits in the history, similar to the output of git log";

    // museBreak();
    yourRepo(0);
}



int main(){

    if (!repoExists()){
        createRepo();
    }else{
        commitHistory();
    }
}
