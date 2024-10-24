/*# include <iostream>
# include <string>
# include <regex>

bool isValidDate(const std::string& date)
{
    std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date,datePattern);
}

int main()
{
    std::string date;
    std::cout << "Enter a date (YYYY-MM-DD) : ";
    std::cin >> date;

    if(isValidDate(date))
    {
        std::cout << "You entered a valid date" << std::endl;
    }else
    {
        std::cout << "You entered a invalid date";
    }
    return 0;
}
*/
/*与正则表达式相关的主要类：

1.std::regex:
表示一个正则表达式。可被用来构造一个正则表达式对象，该对象可以被用于匹配,搜索,替换字符串

2.std::smatch:
这个类是std::match_results的一个特化，用于字符字符串的搜索结果。
当你在一个std::string对象中搜索正则表达式匹配时，使用这个类型来存储结果。

3.std::regex_match:
这是一个函数，用于检查一个给定的字符串是否完全匹配一个正则表达式。

4.std::regex_search:
这是一个函数，用于在给定的字符串中搜索正则表达式的匹配。
与regex_match不同,regex_search可在字符串的任意部分找到匹配,不要求整个字符串与模式完全匹配。

5.std::regex_replace:
这是一个函数，用于使用正则表达式来替换字符串中的文本。

6.std::regex_iterator 和 std::regex_token_iterator:
这些迭代器可以用来遍历字符串中所有匹配正则表达式的子串，或者是匹配的特定部分。

7.std::regex_error:
如果在处理正则表达式时发生错误（例如，正则表达式的语法不正确），会抛出这个异常类的对象。*/

#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text = "The C++11 standard introduced regex support.";
    std::regex pattern(R"(\b(\w+)\b)"); // 匹配单词边界之间的所有单词

    std::smatch matches; // 用于存储匹配结果

    // 使用 regex_search 查找第一个匹配
    if (std::regex_search(text, matches, pattern)) {
        std::cout << "Found word: " << matches[0] << '\n';
    }

    // 使用 regex_iterator 遍历所有匹配
    std::sregex_iterator it(text.begin(), text.end(), pattern);
    std::sregex_iterator end;
    while (it != end) {
        std::cout << "Found word: " << it->str() << '\n';
        ++it;
    }

    // 使用 regex_replace 替换字符串中的文本
    std::string replaced = std::regex_replace(text, pattern, "[$&]");
    std::cout << "Replaced Text: " << replaced << '\n';

    return 0;
}