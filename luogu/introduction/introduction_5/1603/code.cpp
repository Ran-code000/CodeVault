#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

int main()
{
    std::map<std::string, int> m = 
    {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
        {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}, 
        {"eleven", 11}, {"twelve", 12}, {"thirteen", 13}, {"fourteen", 14}, {"fifteen", 15}, 
        {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19}, {"twenty", 20} ,
        {"a", 1}, {"another", 1}, {"first", 1}, {"second", 2}, {"third", 3}, {"both", 2} 
    };

    std::string s;
    std::getline(std::cin, s);

    std::stringstream l(s);
    std::string str;
    std::vector<std::string> vec;

    while(l >> str)
    {
        vec.push_back(str);
    }

    std::vector<int> a;

    int flag = 1;

    for(const auto &val : vec)
    {
        auto it = m.find(val);
        if(it != m.end())
        {
            flag = 0;
            a.push_back(it->second * it->second);
        }
    }

    if(flag)
    {
        std::cout << 0;
        return 0;
    }

    std::sort(a.begin(),a.end());

    a.erase(std::remove(a.begin(), a.end(), 0), a.end());
    //std::remove(a.begin(), a.end(), 0)是在向量a中移动所有不等于0的元素到向量的前面，
    //并返回一个指向“新末尾”（即第一个被移动元素的位置）的迭代器
    //a.erase(new_end, a.end())删除从new_end（std::remove返回的新“逻辑”末尾迭代器）
    //到a.end()（原始末尾）之间的所有元素


    /*int k = 1;
    while(a[k] < 10)
    {
        std::string ss = "0" + std::to_string(a[k]);
        a[k] = stoi(ss);

        k++;
    }//补零？不对,stoi转换时不会保留前导零
    */

    for(int i=0; i<a.size(); i++)
    {
        if(i!=0 && a[i]<10)
        {
            std::cout << 0;
        }
        std::cout << a[i];
    }

    return 0;
}