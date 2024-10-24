#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const unsigned long MOD = 1000000007;

int countChoice(std::unordered_map<int,int> &counts);

int main()
{
    int n;

    std::cin >> n;

    std::vector<int> v(n);

    for(int i=0 ;i<n ;i++)
    {
        std::cin >> v[i];
    }

    std::unordered_map<int, int> counts;

    for(int val : v)
    {
        ++counts[val];
    }

    std::cout << countChoice(counts) << std::endl;   

    
    return 0;
}



int countChoice(std::unordered_map<int,int> &counts)
{
    int sum = 0;
    
    for(auto it = counts.begin() ; it != counts.end() ; it++)
    {
        if( it->second >= 2)
        {
            int choice = (it->second*(it->second-1)/2) % MOD;

            int i;

            int way = 0;


            for(i=1 ; i<it->first-i ;i++)
            {
                way += (counts[i] * counts[it->first-i]);
                way %= MOD;
            }

            if(it->first % 2==0 && counts[i] >= 2)
            {
                way += counts[i]*(counts[i]-1)/2 % MOD;
            }
            
            way *= choice;
            sum += way;
            
        }
        
        

    }

    return sum%MOD;
}

