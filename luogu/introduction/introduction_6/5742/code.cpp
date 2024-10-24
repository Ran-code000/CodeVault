#include <iostream>

class Student
{
public:
    Student(int score1, int score2)
    {
        this->score1 = score1;
        this->score2 = score2;
    }

    ~Student() = default;

    int getScore1(void)
    {
        return score1;
    }

    int getScore2(void)
    {
        return score2;
    }

    bool isExcellent(int c1, int c2)
    {
        if((c1 * 7 + c2 * 3 >= 800) && (c1 + c2) > 140)
        // 为了避免精度丢失， 将c1 * 0.7 + c2 * 0.3 与 80 比较转化为 c1 * 7 + c2 * 3 与800比较
        {
            return true;
        }

        return false;
    }
private:
    int score1;
    int score2;
};

int main()
{
    int num;
    std::cin >> num;

    for(int i = 0; i < num; i++)
    {
        int id, a, b;
        std::cin >> id >> a >> b;
        Student student(a, b);

        if(student.Student::isExcellent(a, b))
        {
            std::cout << "Excellent" << std::endl;
        }else
        {
            std::cout << "Not excellent" << std::endl;
        }
    }
}