// John McCormack
// 17/04/2019
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

bool check(vector<char>, int);
int realCheck(vector<char>);
int findEndBracket(vector<char>);

int main()
{
    //Test Data & the values they should equal to
    vector<char> buf1 = {'1', '+', '2', '+', '3', ')'}; // fail
    vector<char> buf2 = {'1', '+', '2'}; //3
    vector<char> buf3 = {'1', '+', ' ', '2'}; //3
    vector<char> buf4 = {'1', '+', '(', '3', '+', '2', ')', '+', '2'}; //8
    vector<char> buf5 = {'1', '+', '(', '1', '+', '(', '8', '*', '2', ')', '*', '2', ')'}; //35
    vector<char> buf6 = {'7', '*', '2', '+', '5'}; //19
    vector<char> buf7 = {'8', '*', '8'}; // 64
    vector<char> buf8 = {'8', '/', '2'}; // 4
    vector<char> buf9 = {'8', '*', '8', '*', '8'}; // 512
    vector<char> buf10 = {'1', '2', '*', '3'}; // 36
    vector<char> buf11 = {'2', '*', '1', '8'}; // 36
    vector<char> buf12 = {'1', '0', '*', '1', '1'}; //110
    vector<char> buf13 = {'1', '0', '0', '*', '2'}; //200
    cout << check(buf9, 512);
}

//High level check function in the example format
bool check(vector<char> myVector, int myResults)
{
    int check_val = 0;

    //Quick check to see if vector has equal number of open & close brackets
    for (int i = 0; i < (int)myVector.size(); i++)
    {
        if ((int)myVector[i] == 40)
            check_val++;
        else if ((int)myVector[i] == 41)
            check_val--;
    }
    //Return false if case
    if (check_val != 0)
        return false;

    //If equal number of open/close brackets, call the more detailed check function
    if (myResults == realCheck(myVector))
        return true;

    return false;
}

//realCheck - given a vector containing only numbers & operators this function will
//return the sum/subtraction/multiplication/division.
//If nested brackets are detected the function will be called recursively
int realCheck(vector<char> myVector)
{
    vector<char> vector2;
    int total = 0;

    //This for loop will iterate through the vector
    //When it encounters a number or digit it will add to the new vector - vector2
    //If a bracket is encountered the  realCheck is called again
    for (int i = 0; i < (int)myVector.size(); i++)
    {
        if ((myVector[i] >= 48 && myVector[i] < 57) || (myVector[i] == 42 || myVector[i] == 43 || myVector[i] == 45 || myVector[i] == 47))
            vector2.push_back(myVector[i]);
        if (myVector[i] == 40)
        {
            int k = findEndBracket(myVector); // find the closing bracket for this opening bracket
            vector<char> tempV(myVector.begin() + (i + 1), myVector.begin() + k);
            i = k; //move position in vecotr to skip subvector just calculated 
            vector2.push_back('0' + realCheck(tempV)); //add the value of the recursive call to vector2
        }
    }

    string temp_s = "";
    char current_c = '0', next_c = '0';
    int arg1;

    //this loop will iterate through vector2,
    //vector2 should only contain numbers and operators
    for (int j = 0; j < (int)vector2.size(); j++)
    {

        //This while loop will create any multi digit numbers and also find the next operator to use
        while (isdigit(vector2[j]))
        {
            temp_s += vector2[j]; //add digits to string
            j++;
            if (j < (int)vector2.size() && !isdigit(vector2[j])) //if not digit then is an operator
                next_c = vector2[j]; //set operator
        }
        arg1 = stoi(temp_s); //convert string to int
        temp_s = "";
        //if total = 0 then then first arg it total
        if (total == 0)
        {
            total = arg1;
            current_c = next_c; //if first arg the operator is next operator
        }
        else
        {
            //check what the operator is that perfom it on the total & new arg
            if ((int)current_c == 42)
                total = arg1 * total;
            if ((int)current_c == 43)
                total = arg1 + total;
            if ((int)current_c == 45)
                total = arg1 - total;
            if ((int)current_c == 47)
                total = total / arg1;
            //set current operator from next
            current_c = next_c;
        }
    }

    return total; //return value of vector / subvector calculated
}

//Simple function to find the position of the last closing bracket in a vector
int findEndBracket(vector<char> myVector)
{
    for (int i = myVector.size() - 1; i >= 0; i--)
        if (myVector[i] == 41)
            return i;

    return -1;
}
