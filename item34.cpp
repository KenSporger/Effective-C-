#include<iostream>
using namespace std;

/* 总结：
* 1.非private的接口一定会被继承，但非private的实现则可能不会被继承
* 2.任何可能会被继承的类都有若干virtual函数（认定不会被继承的类除外）
* 3.pure virtual只继承接口（实现可有可无，有的话也可以自定义），基类中可以有关于该函数的定义，可以为impure virtual提供更安全的缺省的实现
* 4.impure virtual可以继承接口和缺省实现（可以采用基类的缺省实现，也可以自定义）
* 5.non virtual 要求强制性实现继承
*/

// abstract class 
class Bird
{
    public:
        // pure virtual函数（赋值0）
        virtual void chirp() const = 0;
        // impure virtual
        virtual void goToDestination(){
            cout << "fly to Destination" << endl;
        }
        // none virtual
        void setName(const string& name){_name = name;};
        const string getName() const {return _name;};
    protected:
        string _name;
};

// 可以为pure virtual提供定义
void Bird::chirp() const
{
    cout <<"jiu~jiu~" << endl;    
}


class Sparrow : public Bird
{
    public:
        //必须重写pure virtual函数
        void chirp() const
        {
            cout <<"jiu~jiu~" << endl;
        }
        // impure virtual可以缺省实现
        // none virtual不应被派生类重写
};

class Crow : public Bird
{
    public:
        void chirp() const
        {
            cout <<"ya~ya~" << endl;
        }
};



class Penguin : public Bird
{
    public:
        void chirp() const
        {
            cout <<"ga~ga~" << endl;
        }
        // impure virtual的危险性
        // 由于goToDestination属于impure virtual，如果不小心采用了缺省实现，则企鹅变成了会飞的鸟
};


// 使用pure virtual+默认实现来实现更安全的impure virtual
class BirdSafe : Bird
{
    public:
        //只继承接口，而没有实现
        virtual void chirp() const = 0;
        virtual void goToDestination() const = 0;
    protected:
        void defaultGoToDestination() const
        {
            cout << "swim to Destination" << endl;
        }
};

void BirdSafe::goToDestination() const
{
    cout << "swim to Destination" << endl;
}

// 两次继承
class PenguinSafe : public BirdSafe
{
    public:
        void chirp() const
        {
            cout <<"ga~ga~" << endl;
        }
        void goToDestination() const
        {
            // 方式1：defaultGoToDestination对外部不可见
            //defaultGoToDestination();
            // 方式2：BirdSafe::goToDestination对外界可见（public）
            BirdSafe::goToDestination();
        }
};

int main()
{
    // 抽象类不能实例化
    //Bird b1 = Bird();
    Bird* b1 = new Sparrow();
    b1->setName("jack");
    b1->chirp();
    b1->goToDestination();


    Bird* b2 = new Crow();
    // 使用派生类自己的实现
    b2->chirp();
    // 使用基类的实现
    b2->Bird::chirp(); 

    
    BirdSafe* b3 = new PenguinSafe();
    b3->chirp();
    b3->goToDestination();

    delete b1,b2,b3;
}