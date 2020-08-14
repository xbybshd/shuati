//notify_one()（随机唤醒一个等待的线程）
//notify_all()（唤醒所有等待的线程）
//Create By@herongwei 2019/09/10

#include <bits/stdc++.h>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

std::mutex data_mutex;            //互斥锁
std::condition_variable data_var; //条件变量
bool flag = true;
void printfA()
{
    int i = 1;
    while (i <= 100)
    {
        //休息1秒
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> lck(data_mutex);
        data_var.wait(lck, [] { return flag; }); //等待flag=true才打印奇数
        std::cout << "A " << i << endl;
        i += 2;
        flag = false;
        data_var.notify_one();
    }
}

void printfB()
{
    int i = 2;
    while (i <= 100)
    {
        std::unique_lock<std::mutex> lck(data_mutex);
        data_var.wait(lck, [] { return !flag; }); //等待flag=false才打印偶数
        std::cout << "B " << i << endl;
        i += 2;
        flag = true;
        data_var.notify_one();
    }
}
int main()
{
    // freopen("in.txt","r",stdin);
    std::thread tA(printfA);
    std::thread tB(printfB);
    tA.join();
    tB.join();
    return 0;
}