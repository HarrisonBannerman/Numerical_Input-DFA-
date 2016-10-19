//=======================================
//Roosevelt Bannerman
//Numerical Checking Program with DFA
//=======================================


#include <iostream>
#include <fstream>

using namespace std;

string obtainFileName();
bool checkValidity(string);

int main()
{
    ifstream inputFile;
    ofstream outputFile;

    string fileName = obtainFileName();

    inputFile.open((fileName + ".txt").c_str());

    unsigned int longest = 0;
    string current;

    while(!inputFile.eof()){
        getline(inputFile,current);
        if(current.length() > longest){
            longest = current.length();
        }
    }

    longest += 5;

    inputFile.close();
    inputFile.open((fileName + ".txt").c_str());

    fileName = fileName + "_output.txt";
    outputFile.open(fileName.c_str());

    cout << "\n\n\t1 - Opening input file.";

    string temp;
    bool isValid;

    cout << "\n\n\t1 - Checking validity.";
    cout << "\n\n\t1 - Writing to output file.";
    while(!inputFile.eof()){
        getline(inputFile,current);
        isValid = checkValidity(current);

        outputFile << current;

        string temp((longest) - current.length(),' ');
        if(isValid){
            outputFile << temp << "is a valid numeric literal" << endl;
        }
        else{
            outputFile << temp << "is NOT a valid numeric literal" << endl;
        }

    }

    inputFile.close();
    outputFile.close();
    cout << "\n\n\t4 - Operations finished." << endl;
    return 0;
}


//=======================================
//Obtains the File Name to search for
//Checks whether the file exists
//Returns the name
//=======================================
string obtainFileName(){

    bool isGood = true;
    string entry;

    do{
    cout << "\n\n\tPlease enter the file name (example.txt): ";
    getline(cin,entry);

    ifstream inFile((entry + ".txt").c_str());
    isGood = inFile.good();

    if(!isGood){
        cout << "\n\tCould not find file. Try again.";
    }

    } while(!isGood);

    return entry;


}


//=======================================
//Recieves a literal
//Checks whether the literal is a valid numeric expression
//Returns true or false
//=======================================
bool checkValidity(string arg){

    enum states{Empty,NumberInFront,OperatorInFront,PeriodInFront,
                NumberInMid,OperatorInMid,PeriodInMid,ExponentInMid,
                NumberAtEnd,NeverValid};
    const int LENGTH = arg.length();
    int currentPosition = 0;
    int currentState = Empty;

    while(true){
        if(currentState == Empty){
            if(currentPosition == LENGTH){
                return false;
            }
            else if(isdigit(arg[currentPosition])){
                currentState = NumberInFront;
            }
            else if(arg[currentPosition] == '+' || arg[currentPosition] == '-'){
                currentState = OperatorInFront;
            }
            else if(arg[currentPosition] == '.'){
                currentState = PeriodInFront;
            }
            else{
                return false;
            }
        }
        else if(currentState == NumberInFront){
            if(currentPosition == LENGTH){
                return true;
            }
            else if(isdigit(arg[currentPosition])){
                //do nothing
                //this should just go forward to next position
            }
            else if(arg[currentPosition] == '.'){
                currentState = PeriodInMid;
            }
            else if(arg[currentPosition] == 'e' || arg[currentPosition] == 'E'){
                currentState = ExponentInMid;
            }
            else{
                return false;
            }

        }
        else if(currentState == OperatorInFront){
            if(currentPosition == LENGTH){
                return false;
            }
            else if(arg[currentPosition] == '.'){
                currentState = PeriodInFront;
            }
            else if(isdigit(arg[currentPosition])){
                currentState = NumberInFront;
            }
            else{
                return false;
            }

        }
        else if(currentState == PeriodInFront){
            if(currentPosition == LENGTH){
                return false;
            }
            else if(isdigit(arg[currentPosition])){
                currentState = NumberInMid;
            }
            else {
                return false;
            }

        }
        else if(currentState == NumberInMid){
            if(currentPosition == LENGTH){
                return true;
            }
            else if(isdigit(arg[currentPosition])){
                //do nothing
            }
            else if(arg[currentPosition] == 'e' || arg[currentPosition] == 'E'){
                currentState = ExponentInMid;
            }
            else{
                return false;
            }

        }
        else if(currentState == OperatorInMid){
            if(currentPosition == LENGTH){
                return false;
            }
            else if(isdigit(arg[currentPosition])){
                currentState = NumberAtEnd;
            }
            else{
                return false;
            }

        }
        else if(currentState == PeriodInMid){
            if(currentPosition == LENGTH){
                return true;
            }
            else if(isdigit(arg[currentPosition])){
                currentState = NumberInMid;
            }
            else if(arg[currentPosition] == 'e' || arg[currentPosition] == 'E'){
                currentState = ExponentInMid;
            }
            else{
                return false;
            }

        }
        else if(currentState == ExponentInMid){
            if(currentPosition == LENGTH){
                return false;
            }
            else if(isdigit(arg[currentPosition])){
                currentState = NumberAtEnd;
            }
            else if(arg[currentPosition] == '+' || arg[currentPosition] == '-'){
                currentState = OperatorInMid;
            }
            else{
                return false;
            }


        }
        else if(currentState == NumberAtEnd){
            if(currentPosition == LENGTH){
                return true;
            }
            else if(isdigit(arg[currentPosition])){
                //do nothing
            }
            else{
                return false;
            }

        }

        currentPosition += 1;
    }

}
