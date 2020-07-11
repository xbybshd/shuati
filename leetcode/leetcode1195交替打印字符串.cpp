#include <semaphore.h>//posix信号量类型
#include <thread>//c++11线程库
#include <functional>//函数项
using namespace std;
class FizzBuzz {
private:
    int n;
    int cur;
    sem_t sem_fizz;//打印每种数字的信号量
    sem_t sem_buzz;
    sem_t sem_fizzbuzz;
    sem_t sem_number;//算每种数字的信号量

public:
    FizzBuzz(int n) {
        this->n = n;
        cur=0;
        sem_init(&sem_fizz,0,0);//初始化信号量，第一个是是否全部进程共享，第二个是初始值
        sem_init(&sem_buzz,0,0);
        sem_init(&sem_fizzbuzz,0,0);
        sem_init(&sem_number,0,1);
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(cur<=n){
            sem_wait(&sem_fizz);//P
            if(cur>15) break;
            printFizz();
            sem_post(&sem_number);//V计算数字的信号量
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(cur<=n){
            sem_wait(&sem_buzz);
            if(cur>15) break;
            printBuzz();
            sem_post(&sem_number);
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(cur<=n){
            sem_wait(&sem_fizzbuzz);
            if(cur>15) break;
            printFizzBuzz();
            sem_post(&sem_number);
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(++cur<=n){
            sem_wait(&sem_number);//P计算数字的信号量
            if(cur%3==0&&cur%5==0){
                sem_post(&sem_fizzbuzz);//V打印每种数字的信号量
            }
            else if(cur%3==0){
                sem_post(&sem_fizz);
            }
            else if(cur%5==0){
                sem_post(&sem_buzz);
            }
            else{
                printNumber(cur);
                sem_post(&sem_number);
            }
        }
        sem_post(&sem_fizz);
        sem_post(&sem_buzz);
        sem_post(&sem_fizzbuzz);


    }
};


int main(int argc, char** argv){
    FizzBuzz fizzBuzz(15);

    std::function<void()> printFizz = [](){printf(" fizz ");};//将lambda表达式转成函数对象
    std::function<void()> printBuzz = [](){printf(" buzz ");};
    std::function<void()> printFizzBuzz = [](){printf(" fizzbuzz ");};
    std::function<void(int)> printNum = [](int x){printf(" %d ", x);};

    std::thread th[4];
    th[0] = std::thread(&FizzBuzz::fizz, &fizzBuzz, printFizz);//将类的成员函数设为一个线程，第一个是函数地址，第二个是this指针，第三个是\
    成员函数的参数，就是打印函数
    th[1] = std::thread(&FizzBuzz::buzz, &fizzBuzz, printBuzz);
    th[2] = std::thread(&FizzBuzz::fizzbuzz, &fizzBuzz, printFizzBuzz);
    th[3] = std::thread(&FizzBuzz::number, &fizzBuzz, printNum);

    for(auto &ts : th) {
        if(ts.joinable()) ts.join();
    }

    return 0;
}
