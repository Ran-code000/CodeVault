#include <iostream>
#include <vector>
#include <algorithm>

bool f1(std::vector<std::vector<int>> &vec, std::vector<std::vector<int>> &ans);
bool f2(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &ans);
bool f3(std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &ans);
bool f4(std::vector<std::vector<int>> &vec, std::vector<std::vector<int>> &ans);
bool f5(std::vector<std::vector<int>> &d, std::vector<std::vector<int>> &ans);
bool f6(std::vector<std::vector<int>> &vec, std::vector<std::vector<int>> &ans);

std::vector<std::vector<int>> a, b, c, d, e, f;

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n, std::vector<int>(n, 0)), ans(n, std::vector<int>(n, 0));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            char x;
            std::cin >> x;
            int t;
            if(x == '@')
            {
                t = 1;
            }else
            {
                t = 0;
            }
            vec[i][j] = t;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            char x;
            std::cin >> x;
            int t;
            if(x == '@')
            {
                t = 1;
            }else
            {
                t = 0;
            }
            ans[i][j] = t;
        }
    }

    if(f1(vec, ans))
    {
        std::cout << 1;
    }else if(f2(a, ans))
    {
        std::cout << 2;
    }else if(f3(b, ans))
    {
        std::cout << 3;
    }else if(f4(vec, ans))
    {
        std::cout << 4;
    }else if(f5(d, ans))
    {
        std::cout << 5;
    }else if(f6(vec, ans))
    {
        std::cout << 6;
    }else
    {
        std::cout << 7;
    }

    return 0;

}

bool f1(std::vector<std::vector<int>> &vec, std::vector<std::vector<int>> &ans)
{
    a = vec;

    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < vec.size(); j++)
        {
            a[i][j] = vec[vec.size() - 1 - j][i];
        }
    }

    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < vec.size(); j++)
        {
            if(a[i][j] != ans[i][j]) return false;
        }
    }

    return true;

}
bool f2(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &ans)
{
    std::vector<std::vector<int>> t = a;
    for(int i = 0; i < t.size(); i++)
    {
        for(int j = 0; j < t.size(); j++)
        {
            t[i][j] = a[t.size() - 1 - j][i];
        }
    }
    b = t;

    for(int i = 0; i < b.size(); i++)
    {
        for(int j = 0; j < b.size(); j++)
        {
            if(b[i][j] != ans[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
bool f3(std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &ans)
{
    std::vector<std::vector<int>> t = b;
    for(int i = 0; i < t.size(); i++)
    {
        for(int j = 0; j < t.size(); j++)
        {
            t[i][j] = b[t.size() - 1 - j][i];
        }
    }
    c = t;

    for(int i = 0; i < c.size(); i++)
    {
        for(int j = 0; j < c.size(); j++)
        {
            if(c[i][j] != ans[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
bool f4(std::vector<std::vector<int>> &vec, std::vector<std::vector<int>> &ans)
{
    d = vec;
    for(int i = 0; i < d.size(); i++)
    {
        for(int j = 0; j < d.size(); j++)
        {
            d[i][j] = vec[i][d.size() - 1 - j];
        }
    }

    for(int i = 0; i < d.size(); i++)
    {
        for(int j = 0; j < d.size(); j++)
        {
            if(d[i][j] != ans[i][j])
            {
                return false;
            }
        }
    }
    return true;

}
bool f5(std::vector<std::vector<int>> &d, std::vector<std::vector<int>> &ans)
{
    e = d;
    for(int i = 0; i < e.size(); i++)
    {
        for(int j = 0; j < e.size(); j++)
        {
            e[i][j] = d[e.size() - 1 - j][i];
        }
    }
    f = e;
    for(int i = 0; i < f.size(); i++)
    {
        for(int j = 0; j < f.size(); j++)
        {
            f[i][j] = e[f.size() - 1 - j][i];
        }
    }

    if(f1(d, ans) || f2(e, ans) || f3(f, ans))
    {
        return true;
    }else
    {
        return false;
    }
}
bool f6(std::vector<std::vector<int>> &vec, std::vector<std::vector<int>> &ans)
{
    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < vec.size(); j++)
        {
            if(vec[i][j] != ans[i][j])
            {
                return false;
            }
        }
    }
    return true;
}


