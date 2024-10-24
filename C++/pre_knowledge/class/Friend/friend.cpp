#include <iostream>
#include <string>
using namespace std;
class Lovers
{
public:
    Lovers(string theName);
    void kiss(Lovers *lover);
    void ask(Lovers *lover,string something);

protected:
    string name;

    friend class Others;//友元关系
};

class BoyFriend : public Lovers
{
public:
    BoyFriend(string theName);
};

class GirlFriend : public Lovers
{
public:
    GirlFriend(string theName);
};

class Others
{
public:
    Others(string theName);
    void kiss(Lovers *lover);

protected:
    string name;
};

Lovers::Lovers(string theName)
{
    name = theName;
}

void Lovers::kiss(Lovers *lover)
{
    cout << name << " kissing my" << lover->name << endl;
}

void Lovers::ask(Lovers *lover,string something)
{
    cout << "Baby " << lover->name << " help me" <<something <<endl;
}

BoyFriend::BoyFriend(string theName) : Lovers(theName)
{
    
}

GirlFriend::GirlFriend(string theName) : Lovers(theName)
{

}

Others::Others(string theName)
{
    name = theName;
}

void Others::kiss(Lovers *lover)
{
    cout << name << " kiss one time " << lover->name << endl;
}

int main()
{
    BoyFriend boyfriend("Handsome A");
    GirlFriend girlfriend("Beautiful B");

    Others others("little 3");

    girlfriend.kiss(&boyfriend);
    girlfriend.ask(&boyfriend,"washing clothes!");

    cout << "Fucking bitch coming.....\n";
    others.kiss(&girlfriend);

    return 0;
}