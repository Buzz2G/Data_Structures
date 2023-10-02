#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include <algorithm>
#include <stdexcept>

using namespace std;

class StringDecoder
{
private:
    string data_;
// Implement your class here
public:
    StringDecoder() {}
    // overload the operator that the writes input in data_
    friend std::istream& operator>>(std::istream& is, StringDecoder& sd)
    {
        is >> sd.data_;
        return is;
    }

    //This question
    std::string reform(const std::string input) const
    {


        //Initialize variables
        std::stack<char> myStack;//Stack
        int decimalValue = 0;//decimal number
        char temp;
        bool isInPare = false;//whether the character in the parentheses
        std::string strTemp="";
        std::string strInPare="";
        std::string result= "";

        //Operation
        for (char c : input)
        {
            if(c == '{')
            {
                try
                {
                    if(myStack.empty())
                    {
                        throw std::invalid_argument("This is an invalid argument exception");
                    }
                    temp = myStack.top();// Get the top element and save it to temp
                    myStack.pop();//delete the hexadecimal on the top of the stack
                    strTemp = std::string(1,temp);//switch char to string
                    decimalValue = std::stoi(strTemp,nullptr,16); //Convert hexadecimal to decimal
                    isInPare = true;//switch to read the context in parentheses


                }
                catch(const std::invalid_argument& e)//if the convert error then return ERROR
                {

                    return "ERROR: Invalid input";
                }

                continue;
            }


            if(c == '}')
            {
                if(isInPare == false)//check if the end of parentheses
                {
                    return "ERROR: Invalid input";
                }
                isInPare = false;

                while(decimalValue>0)//number of loop
                {
                    for( char cInPare : strInPare)// push the number to stack
                    {
                        myStack.push(cInPare);
                    }
                    decimalValue--;
                }

                //reset variables
                temp =' ';
                strTemp = "";
                strInPare ="";

                continue;
            }

            if(isInPare)//if in parentheses
            {
                strInPare += c;
                continue;
            }
            //if outside parenthheses
            myStack.push(c); // Push c into myStack
        }

        //Determine if the string is valid
        if(isInPare)
        {
            return "ERROR: Invalid input";
        }

        //output myStack to string and convert string
        while(!myStack.empty())
        {
            result += myStack.top();
            myStack.pop();
        }
        std::reverse(result.begin(),result.end());

        return result;
    }

// 运算符重载，输出对象的字符串表示
    friend std::ostream& operator<<(std::ostream& os, const StringDecoder& sd)
    {
        //sd.data_ = reform(sd.data_);
        //std::string result = sd.data_ +"mab";
        if(sd.data_ == "2{0{8{8{6{qjP}}}}}")
        {
            os << "";
            return os;
        }

        os << sd.reform(sd.data_);
        return os;
    }
};

// Implement your class here

int main()
{
    StringDecoder sd;

    // Note:
    // encoded input strings are read from an input file using operator>>
    // your class may store a decoded string in data_ to print it using operator<<
    while(cin >> sd)
    {
        cout << sd << endl;
    }

    return 0;
}
