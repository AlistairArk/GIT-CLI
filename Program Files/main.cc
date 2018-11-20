// Git CLI Program
// Author: sc17jhd
// Date: Nov 2018

#include "hci0.h"         // getkey
#include "gitpp5.h"
#include <iostream>
#include <cstdlib>        // For clearing Screen
#include <cstdlib>
#include <sstream>        //convert to string?


const unsigned limit=10;
const char spacebar=32;
const char escape=0x1b;

class PROGRAM : public HCI_APPLICATION {

    void yourRepo();

    void museBreak(){
        std::cout << "\n\n\n Press ANY KEY to continue...\n";
        getkey();
    }



    void listConfig(){
        // Lists configuration of an existing repository
        clear();
        GITPP::REPO r;
        auto c=r.config();

        std::string mycwd(getenv("PWD")); // Get <CWD>

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
        GITPP::CONFIG::ITEM logAllRefUpdts=c["core.logallrefupdates"];
        std::cout << "7. log all ref updates:           <" << logAllRefUpdts.value() << ">\n";


    }

    int confirm(){
        // Simple function used for y/n (yes/no) cases

        std::cout << "\n Confirm changes? [y/n]";
        while(char choice=getkey()){ // Take input for what user wants to configure

            // Will not return value until either 'y' or 'n' is pressed
            if (choice=='y'){
                return(1);
            }else{
                if (choice=='n'){
                    return(0);
                }
            }
        }
        return 0;
    }





    void configRepo(int invalid){
        clear();
        listConfig(); // First list config options
        invalidMsg(invalid);


        std::cout << "\n==== esc: leave ===="; // Return case

        char choice=getkey(); // Take input for what user wants to configure

        if (choice!=escape){

            GITPP::REPO r;
            auto c=r.config();
            GITPP::CONFIG::ITEM name=c["user.name"];
            GITPP::CONFIG::ITEM email=c["user.email"];
            GITPP::CONFIG::ITEM pushDef=c["push.default"];
            GITPP::CONFIG::ITEM bare=c["core.bare"];
            GITPP::CONFIG::ITEM filemode=c["core.filemode"];
            GITPP::CONFIG::ITEM repFmtVer=c["core.repositoryformatversion"];
            GITPP::CONFIG::ITEM logAllRefUpdts=c["core.logallrefupdates"];
            std::string newValue;
            int loop = 1;

            invalid = 0; // Lower invalid flag
            switch(choice) {

                case '1':
                    clear();
                    std::cout << "\n Enter A New Name | Current Name: <" << name.value() << ">\n\n>>>";
                    std::cin >> newValue;
                    std::cout << "\n<" << name.value() << "> --> <" << newValue <<">\n";
                    if (confirm()){ // If true, then set new val, else do nothing
                        c["user.name"] = newValue;
                    }
                    break;

                case '2':
                    clear();
                    std::cout << "\n Enter A New Email | Current Email: <" << email.value() << ">\n\n>>>";
                    std::cin >> newValue;
                    std::cout << "\n<" << email.value() << "> --> <" << newValue <<">\n";
                    if (confirm()){ // If true, then set new val, else do nothing
                        c["user.email"] = newValue;
                    }
                    break;

                case '3':

                    while (loop) { // Loop until case breaking choice is made
                        clear();
                        invalidMsg(invalid);
                        std::cout << "\n Select Push Mode | Current Mode: <" << pushDef.value() << ">\n\n";
                        std::cout << "\n    1. simple";
                        std::cout << "\n    2. matching";
                        std::cout << "\n    3. upstream";
                        std::cout << "\n    4. current";
                        std::cout << "\n    5. nothing\n";
                        if (loop==2) break;

                        std::cout << "\n==== esc: leave ===="; // Return case
                        loop=2;                 // Assume loop will be broken
                        invalid=0;              // Lower invalid flag
                        choice=getkey();        // Get user input
                        switch(choice) {
                            case '1':newValue="simple";break;
                            case '2':newValue="matching";break;
                            case '3':newValue="upstream";break;
                            case '4':newValue="current";break;
                            case '5':newValue="nothing";break;
                            case escape:newValue="escape";break;

                            default: // code to be executed if n doesn't match any constant
                                loop=1;         // Invalid choice handed so set to loop again
                                invalid=1;      // Raise invalid flag
                                break;
                        }
                    }

                    if (newValue!="escape"){
                        std::cout << "\n<" << pushDef.value() << "> --> <" << newValue <<">\n";
                        if (confirm()){ // If true, then set new val, else do nothing
                            c["push.default"] = newValue;
                        }
                    }
                    break;

                case '4':


                    while (loop) { // Loop until case breaking choice is made
                        clear();
                        invalidMsg(invalid);
                        std::cout << "\n Bare | Current Mode: <" << bare.value() << ">\n\n";
                        std::cout << "\n    t TRUE";
                        std::cout << "\n    f FALSE\n";
                        if (loop==2) break;

                        std::cout << "\n==== esc: leave ===="; // Return case
                        loop=2;                 // Assume loop will be broken
                        invalid=0;              // Lower invalid flag
                        choice=getkey();        // Get user input
                        switch(choice) {
                            case 't':newValue="true";break;
                            case 'f':newValue="false";break;
                            case escape:newValue="escape";break;

                            default: // code to be executed if n doesn't match any constant
                                loop=1;         // Invalid choice handed so set to loop again
                                invalid=1;      // Raise invalid flag
                                break;
                        }
                    }

                    if (newValue!="escape"){
                        std::cout << "\n<" << bare.value() << "> --> <" << newValue <<">\n";
                        if (confirm()){ // If true, then set new val, else do nothing
                            c["core.bare"] = newValue;
                        }
                    }
                    break;

                case '5':
                    while (loop) { // Loop until case breaking choice is made
                        clear();
                        invalidMsg(invalid);
                        std::cout << "\n File Mode | Current Mode: <" << filemode.value() << ">\n\n";
                        std::cout << "\n    t TRUE";
                        std::cout << "\n    f FALSE\n";


                        if (loop==2) break;

                        std::cout << "\n==== esc: leave ===="; // Return case
                        loop=2;                 // Assume loop will be broken
                        invalid=0;              // Lower invalid flag
                        choice=getkey();        // Get user input
                        switch(choice) {
                            case 't':newValue="true";break;
                            case 'f':newValue="false";break;
                            case escape:newValue="escape";break;

                            default: // code to be executed if n doesn't match any constant
                                loop=1;         // Invalid choice handed so set to loop again
                                invalid=1;      // Raise invalid flag
                                break;
                        }
                    }

                    if (newValue!="escape"){
                        std::cout << "\n<" << filemode.value() << "> --> <" << newValue <<">\n";
                        if (confirm()){ // If true, then set new val, else do nothing
                            c["core.filemode"] = newValue;
                        }
                    }
                    break;

                case '6':
                    clear();

                    while (loop) { // Loop until case breaking choice is made
                        clear();
                        invalidMsg(invalid);
                        std::cout << "\n Repository Format Version | Current Version: <" << repFmtVer.value() << ">\n\n";
                        std::cout << "\n    0 ";
                        std::cout << "\n    1 \n";

                        if (loop==2) break;

                        std::cout << "\n==== esc: leave ===="; // Return case
                        loop=2;                 // Assume loop will be broken
                        invalid=0;              // Lower invalid flag
                        choice=getkey();        // Get user input
                        switch(choice) {
                            case '0':newValue="0";break;
                            case '1':newValue="1";break;
                            case escape:newValue="escape";break;

                            default: // code to be executed if n doesn't match any constant
                                loop=1;         // Invalid choice handed so set to loop again
                                invalid=1;      // Raise invalid flag
                                break;
                        }
                    }

                    if (newValue!="escape"){
                        std::cout << "\n<" << repFmtVer.value() << "> --> <" << newValue <<">\n";
                        if (newValue=="1"){ // Warn user before they shoot themself in the foot
                            std::cout << "\nWARNING: Only versions up to 0 are supported! ";
                            std::cout << "Changing to version to 1 will make your repository ";
                            std::cout << "incompatible with this software and may cause future issues. ";
                            std::cout << "\nAre you sure you wish to continue?\n";
                        }
                        if (confirm()){ // If true, then set new val, else do nothing
                            c["core.repositoryformatversion"] = newValue;
                        }
                    }
                    break;


                case '7':

                    while (loop) { // Loop until case breaking choice is made
                        clear();
                        invalidMsg(invalid);
                        std::cout << "\n Log All Reference Updates | Current Mode: <" << logAllRefUpdts.value() << ">\n\n";
                        std::cout << "\n    t TRUE";
                        std::cout << "\n    f FALSE\n";


                        if (loop==2) break;

                        std::cout << "\n==== esc: leave ===="; // Return case
                        loop=2;                 // Assume loop will be broken
                        invalid=0;              // Lower invalid flag
                        choice=getkey();        // Get user input
                        switch(choice) {
                            case 't':newValue="true";break;
                            case 'f':newValue="false";break;
                            case escape:newValue="escape";break;

                            default: // code to be executed if n doesn't match any constant
                                loop=1;         // Invalid choice handed so set to loop again
                                invalid=1;      // Raise invalid flag
                                break;
                        }
                    }

                    if (newValue!="escape"){
                        std::cout << "\n<" << logAllRefUpdts.value() << "> --> <" << newValue <<">\n";
                        if (confirm()){ // If true, then set new val, else do nothing
                            c["core.logallrefupdates"] = newValue;
                        }
                    }
                    break;

                default: // code to be executed if n doesn't match any constant
                    invalid=1; // Raise invalid flag
                    break;
            }
            configRepo(invalid); // Call back with invalid flag

        }
        // museBreak();
    }



    void listCommit(int maxNum){
        // maxNum = Maximum number of commits to be displayed.
        //          Set as 0 to display all commits.

        clear();
        std::cout << "\n Your Commits: \n\n";

        GITPP::REPO r;

        int counter=0;
        for(auto i : r.commits()){
            counter+=1;
            std::cout << counter << ". ";

            /*  Gets first line in commit message
                Prints line, and then breaks */
            std::istringstream f(i.message());
            std::string line;
            while (std::getline(f, line)) {
                std::cout << "<"<< i << "> <" << i.signature().name() << "> <" << line << ">\n";
                break;
            }
            if (counter==maxNum)break;
        }
        museBreak();

    }

    void invalidMsg(bool invalid){ // Displays message for unassigned key presses
        if (invalid){
            std::cout << "\n\n Unassigned key pressed. Please try again.\n\n";
        }
    }
    void listBranch(int invalid){
        clear();
        invalidMsg(invalid);
        GITPP::REPO r;
        // Display string for use in option selection
        char alphabet[] =  {'a','b','c','d','e',
                            'f','g','h','i','j',
                            'k','l','m','n','o',
                            'p','q','r','s','t',
                            'u','v','w','x','y','z'};

        std::cout << "\n    select a branch to display commits\n\n";
        int branchCounter=-1; // Index of current branch
        for(GITPP::BRANCH i : r.branches()){
            branchCounter+=1;
            std::cout << "    " << alphabet[branchCounter] << ". " << i << "\n";
        }

        if (branchCounter){ // If more than one branch, take input for choice

            std::cout << "\n==== esc: leave ===="; // Return case
            char choice=getkey();

            if (choice!=escape){

                branchCounter = -1;         // Reset branchCounter
                bool branchFound = 0;       // If Found then True

                std::string out_string;

                // Loop through choices until desired branch is found
                for(GITPP::BRANCH i : r.branches()){
                    branchCounter+=1;
                    if (choice == alphabet[branchCounter]){
                        branchFound = 1;
                        if (alphabet[branchCounter]=='z'){
                            break;
                        }else{
                            // Ensue repo is not bare before checking out
                            auto c=r.config();
                            if (c["core.bare"].value()=="true"){
                                clear();
                                std::cout << " Cannot checkout. This operation is not allowed against bare repositories.";
                                museBreak();
                                listBranch(0);
                            }else{

                                // Error check required as conflicts can prevent checkout of branches
                                try{
                                    r.checkout(i.name());   // Switch to branch
                                    listCommit(0);          // Now list commits in this branch
                                    break;
                                }catch(const std::exception& e){
                                    clear();
                                    std::cout << " The following error has occured: \n " << e.what() << "\n\n";
                                    std::cout << " Please resolve the aforementioned conflicts before trying again.\n";
                                    museBreak();
                                    listBranch(0);

                                }
                            }
                        }
                    }
                }

                if (!branchFound){ // If branch was not found
                    listBranch(1);
                }

            }// Escape handed so return without doing anything else


        }else{
            listCommit(0); // Only master branch exists, thus display that
        }

    }




    void yourRepo(int invalid){
        clear();
        invalidMsg(invalid);


        std::cout << "\n Your git repository";
        std::cout << "\n    c list config";
        std::cout << "\n    e configure repository";
        std::cout << "\n    l list commits";
        std::cout << "\n    q quit\n\n";



        char choice=getkey();


        switch(choice) {

            case 'c':
                listConfig();
                museBreak();
                yourRepo(0);
                break;

            case 'e':
                configRepo(0);
                yourRepo(0);
                break;

            case 'l':
                listBranch(0);
                yourRepo(0);
                break;

            case 'q':
                std::cout << "Goodbye!\n\n";
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
        std::cout << "\n    n quit\n\n >";

        char choice=getkey();

        if (choice=='y'){
            // Begin creation of repository
            std::string path=".";
            try{
                GITPP::REPO r(path.c_str());
            }catch(GITPP::EXCEPTION_CANT_FIND const&){
                GITPP::REPO r(GITPP::REPO::_create, path.c_str());
            }

            GITPP::REPO r(path.c_str());
            r.commits().create("First Commit!");

            listCommit(0);

            yourRepo(0);
        }else{
            std::cout << "Goodbye!\n\n";
        }
    }




public:
    void startup(){
        if (!repoExists()){
            createRepo();
        }else{
            listCommit(10); // List first 10 commits
            yourRepo(0);
        }

    }
};

int main(){
    PROGRAM m;
    m.startup();
}
