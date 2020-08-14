#include <bits/stdc++.h>

// key-value类型
template <typename K, typename V>
struct Pair
{
    Pair(const K &k = K(), const V &v = V())
        : first(k), second(v)
    {
    }
    K first;
    V second;
};

//链式哈希表
template <typename K, typename V>
class HashMap
{
public:
    HashMap(int size = 3, double loadFactor = 0.75)
        : mloadFactor(loadFactor), museBucketNum(0)
    {
        // 按照size开辟空间，并给vector添加size个list默认构造的容器
        mhashMap.resize(size);
    }

    /**
	 * 插入key-value对，如果插入的key存在，则用新的value将旧的value替换掉
	 * 在unordered_map中insert的返回类型为pair<iterator, bool>，但是由于尚未实现迭代器，故返回值类型为void
	 */
    void insert(const Pair<K, V> &pair)
    {
        double lf = museBucketNum * 1.0 / mhashMap.size();
        // cout << "lf:" << lf << endl;
        if (lf > mloadFactor) // 扩容
        {
            expand();
        }

        // idx就是桶的下标
        int idx = pair.first % mhashMap.size();
        list<Pair<K, V>> &mylist = mhashMap[idx];
        if (mylist.empty())
        {
            museBucketNum++;
        }
        else
        {
            for (auto &item : mylist)
            {
                if (item.first == pair.first)
                {
                    // key已经存在，不会重复插入
                    item.second = pair.second;
                    return;
                }
            }
        }
        mylist.push_back(pair);
    }

    /**
	 * 传入key，删除key-value对
	 */
    void erase(const K &key)
    {
        // idx就是桶的下标
        int idx = key % mhashMap.size();

        auto &mylist = mhashMap[idx];
        if (!mylist.empty())
        {
            for (auto it = mylist.begin(); it != mylist.end(); ++it)
            {
                if (it->first == key)
                {
                    mylist.erase(it);
                    if (mylist.empty())
                    {
                        // 删除后桶为空，更新已使用桶的数量
                        museBucketNum--;
                    }
                    return;
                }
            }
        }
    }

    /**
	 * 传入key，返回包含key的key-value对的迭代器pair
	 * 如果key不存在，返回nullptr
	 */
    Pair<K, V> *find(const K &key)
    {
        int idx = key % mhashMap.size();
        list<Pair<K, V>> &mylist = mhashMap[idx];

        if (!mylist.empty())
        {
            for (auto &item : mylist)
            {
                if (item.first == key)
                {
                    return &item;
                }
            }
        }
        return nullptr;
    }

    /**
	 * operator[]的功能：增加一个[key, V()],然后把V()返回进行赋值操作、覆盖旧值、查询
	 * 	
	 * 需要注意的是，map[key]当key不存在时会自动增加[key, V()]，所以不建议使用operator[]查询，只做增加或者覆盖值使用
	 */
    V &operator[](const K &key)
    {
        int idx = key % mhashMap.size();
        list<Pair<K, V>> &mylist = mhashMap[idx];

        if (mylist.empty())
        {
            // 为一个空桶
            museBucketNum++;
        }
        else
        {
            for (auto &item : mylist)
            {
                if (item.first == key)
                {
                    return item.second;
                }
            }
        }

        // 插入时调用insert方法，这样新插入元素就会适时扩容哈希表
        insert({key, V()});

        // 把mylist的尾结点的second返回（insert为尾插）
        return mylist.back().second;
    }

private:
    vector<list<Pair<K, V>>> mhashMap; // 链式哈希表结构
    double mloadFactor;                // 加载因子 0.75
    int museBucketNum;                 // 记录已经使用的桶的个数

    /**
	 * 判断是否为素数
	 * 素数的特性：恒等于 6x-1 或者 6x+1，其中 x 是大于等于1的自然数
	 * 由素数的特性可知：循环的步长可以设为 6，每次只判断 6 前后的两个数即可
	 */
    bool isprime(int num)
    {
        // 判断是不是 6x 左右的数
        if (num % 6 != 1 && num % 6 != 5)
        {
            return false;
        }

        int sq = (int)sqrt(num);
        for (int i = 5; i <= sq; i += 6)
        {
            if (num % i == 0 || num % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }

    // 哈希表扩容函数
    void expand()
    {
        vector<list<Pair<K, V>>> oldHashMap;

        // oldHashMap放的是旧哈希表的所有内容 mhashMap是空的
        mhashMap.swap(oldHashMap);

        // 扩容后的哈希表的桶的个数设置为素数
        int prime = oldHashMap.size() + 1;
        while (!isprime(prime))
        {
            prime++;
        }
        mhashMap.resize(prime);
        museBucketNum = 0;

        // 遍历oldHashMap里面每一个不空的桶，把里面的list结点splice摘下来，放入新的哈希表mhashMap中
        for (list<Pair<K, V>> &mylist : oldHashMap)
        {
            while (!mylist.empty())
            {
                Pair<K, V> &pair = mylist.front();
                int idx = pair.first % mhashMap.size();

                list<Pair<K, V>> &newlist = mhashMap[idx];
                if (newlist.empty())
                {
                    museBucketNum++;
                }
                newlist.splice(newlist.begin(), mylist, mylist.begin());
            }
        }
    }
};

// 测试代码
int main()
{
    HashMap<int, string> map;
    map.insert({1010, "wu"});
    map.insert({1020, "fan"});
    map.insert({1030, "love"});
    map.insert({1040, "yan"});
    map.insert({1050, "han"});

    cout << map[1030] << endl;
    //map.erase(1010);
    Pair<int, string> *it = map.find(1010);
    if (it == nullptr)
    {
        cout << "not find" << endl;
    }
    else
    {
        cout << it->first << endl;
    }

    return 0;
}
