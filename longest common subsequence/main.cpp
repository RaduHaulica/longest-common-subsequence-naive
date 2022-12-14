#include <SFML/Graphics.hpp>

#include <iostream>
#include <format>

bool findStringInString(std::string substr, std::string location)
{
    if (substr.size() > location.size())
        return false;
    for (int i = 0; i < location.size(); i++)
    {
        bool found = true;
        for (int j = 0; j < substr.size(); j++)
        {
            if (location[i + j] != substr[j])
            {
                found = false;
                break;
            }
        }
        if (found)
            return true;
    }
    return false;
}

std::vector<std::string> getSubstrings(std::string s)
{
    std::vector<std::string> results;
    std::string currentString;
    for (int i = 0; i < s.size(); i++)
    {
        currentString = "";
        for (int j = i; j < s.size(); j++)
        {
            currentString += s[j];
            results.push_back(currentString);
        }
    }
    return results;
}

void printStringVector(std::vector<std::string> strings)
{
    for (auto el : strings)
    {
        std::cout << el << ", ";
    }
    std::cout << '\n';
}

void filterSubstringsInString(std::vector<std::string>& substrings, std::string newString)
{
    //std::cout << "FUNCTION: filterSubstringsInString\n";
    //std::cout << "Filtering substrings:\n";
    //printStringVector(substrings);
    //std::cout << "In string: " << newString << "\n";
    for (int i = 0; i < substrings.size(); i++)
    {
        if (!findStringInString(substrings[i], newString))
        {
            substrings.erase(substrings.begin() + i);
            i--;
        }
    }
    //std::cout << "END\n\n";
}

std::string longestCommonSubstringSimple(std::string s1, std::string s2)
{
    int maxLength = 0;
    std::string solution = "";

    for (int i = 0; i < s1.size(); i++)
    {
        for (int j = 0; j < s2.size(); j++)
        {
            int currentLength = 0;
            int currentIndex = 0;
            std::string currentSolution = "";
            while ((i + currentIndex < s1.size()) && (j + currentIndex < s2.size()) && s1[i + currentIndex] == s2[j + currentIndex])
            {
                currentIndex++;
                currentLength++;
                currentSolution += s1[i + currentIndex];
            }
            if (currentLength > maxLength)
            {
                maxLength = currentLength;
                solution = currentSolution;
            }
        }
    }

    return solution;
}

template <class T>
auto infiniteCommonSubstrings(std::vector<std::string>& substring, T location)
{
    filterSubstringsInString(substring, location);
}

template <class T, class... TParams>
auto infiniteCommonSubstrings(std::vector<std::string>& substrings, T first, TParams... rest)
{
    infiniteCommonSubstrings(substrings, first);
    infiniteCommonSubstrings(substrings, rest...);
}

std::string maxSubstring(std::vector<std::string> substrings)
{
    std::string result = "";
    for (auto el : substrings)
        if (el.size() > result.size())
            result = el;
    return result;
}

template <class First, class... TParams>
std::string longestCommonSubstring(First first, TParams... rest)
{
    std::vector<std::string> results = getSubstrings(first);
    infiniteCommonSubstrings(results, rest...);
    return maxSubstring(results);
}

// =============================================
//      NOTHING TO SEE HERE MOVE ALONG
// =============================================

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::string s1 = "ABABAC";
    std::string s2 = "BABACA";
    std::string s3 = "ABCBABACA";
    std::string s4 = "CABACB";

    // =============================
    // testing the functions
    // =============================
    //std::cout << std::format("Found string ABC in string BCABCBC? : {}\n", findStringInString("ABC", "BCABCBC"));
    //std::vector<std::string> substrings = getSubstrings("ABC");
    //std::cout << "ABC substrings:\n";
    //printStringVector(substrings);
    //filterSubstringsInString(substrings, "BCA");
    //std::cout << "Filtering...\n";
    //printStringVector(substrings);

    std::cout << std::format("Largest overlap: {} /\ {} = {}\n", s1, s2, longestCommonSubstringSimple(s1, s2));

    std::vector < std::string> result = getSubstrings(s1);
    infiniteCommonSubstrings(result, s1, s2, s3, s4);
    printStringVector(result);
    std::cout << "Longest common substring: " << maxSubstring(result) << "\n";
    std::string common = longestCommonSubstring(s1, s2, s3, s4);
    std::cout << "Longest common substring (fancy): " << common << "\n";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}