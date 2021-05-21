#include <iostream>

std::string getLeftPart(std::string number)
{
    std::string leftPart;
    bool firstNonZeroIsFound = false;
    char sign = '+';
    for (int i = 0; i < number.length(); i++)
    {
        if (number[i] == '.')
        {
            if (i == 0 || i == 1 && (number[0] == '-' || number[0] == '+')) return "+0";
            else break;
        }
        else if (i == 0 && number[i] == '-') sign = '-';
        else if (i == 0 && number[i] == '+') sign = '+';
        else if (number[i] == '0' & !firstNonZeroIsFound) continue;
        else if (number[i] >= '0' && number[i] <= '9')
        {
            leftPart += number[i];
            firstNonZeroIsFound = true;
        }
        else return "ERROR";
    }
    if (!firstNonZeroIsFound) return "+0";
    else return sign + leftPart;
}

std::string cutZerosFromTheEnd(std::string rightPart)
{
    std::string cutRightPart;
    int zerosAtTheEnd = 0;
    for (int i = rightPart.length() - 1; rightPart[i] == '0' && i >= 1; i--)
    {
        zerosAtTheEnd++;
    }

    for (int i = 0; i < rightPart.length() - zerosAtTheEnd; i++)
    {
        cutRightPart += rightPart[i];
    }
    return cutRightPart;
}

std::string getRightPart(std::string number)
{
    std::string rightPart;
    bool dotIsFound = false;

    for (int i = 0; i < number.length(); i++)
    {
        if (number[i] == '.')
        {
            if (!dotIsFound) dotIsFound = true;
            else return "ERROR";

            if (i == number.length() - 1) return "0";
        }
        else if (dotIsFound) {
            if (number[i] >= '0' && number[i] <= '9') rightPart += number[i];
            else return "ERROR";
        }
    }
    if (!dotIsFound) return "0";
    else return cutZerosFromTheEnd(rightPart);
}

std::string compareNumbers(std::string number_1, std::string number_2)
{
    std::string RESULT_LESS = "is LESS than";
    std::string RESULT_GREATER = "is GREATER than";
    std::string RESULT_EQUALS = "EQUALS to";

    std::string leftPart_1 = getLeftPart(number_1);
    std::string rightPart_1 = getRightPart(number_1);
    std::string leftPart_2 = getLeftPart(number_2);
    std::string rightPart_2 = getRightPart(number_2);

    if (leftPart_1[0] != leftPart_2[0])
    {
        if (leftPart_1[0] == '-') return RESULT_LESS;
        else return RESULT_GREATER;
    }
    else if (leftPart_1.length() > leftPart_2.length()) return RESULT_GREATER;
    else if (leftPart_1.length() < leftPart_2.length()) return RESULT_LESS;
    else
    {
        int length = leftPart_1.length();
        for (int i = 0; i < length; i ++)
        {
            if (leftPart_1[i] > leftPart_2[i]) return RESULT_GREATER;
            else if (leftPart_1[i] < leftPart_2[i]) return RESULT_LESS;
            else continue;
        }

        int longestLength = rightPart_1.length() > rightPart_2.length() ?
                rightPart_1.length() : rightPart_2.length();
        for (int i = 0; i < longestLength; i++)
        {
            char charToCompare_1, charToCompare_2;
            if (rightPart_1.length() - 1 < i) charToCompare_1 = '0';
            else charToCompare_1 = rightPart_1[i];

            if (rightPart_2.length() - 1 < i) charToCompare_2 = '0';
            else charToCompare_2 = rightPart_2[i];

            if (charToCompare_1 > charToCompare_2) return RESULT_GREATER;
            else if (charToCompare_1 < charToCompare_2) return RESULT_LESS;
            else continue;
        }
    }
    return RESULT_EQUALS;
}


int main() {
    std::string number_1;
    std::string number_2;

    std::cout << "Please enter two numbers for comparison:\n";
    std::cin >> number_1 >> number_2;

    std::cout << "You've entered following numbers:\n";
    std::cout << getLeftPart(number_1) << "." << getRightPart(number_1) << "\n";
    std::cout << getLeftPart(number_2) << "." << getRightPart(number_2) << "\n";

    std::cout << "---------------------------------\n";
    std::cout << "First number " << compareNumbers(number_1, number_2) << " second number.\n";

    return 0;
}
