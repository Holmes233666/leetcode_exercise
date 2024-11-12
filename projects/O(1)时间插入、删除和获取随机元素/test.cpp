#include<vector>
#include<unordered_map>

using namespace std;

class RandomizedSet {
public:
    unordered_map<int, int> umap;   // value-index in vector
    vector<int> vec;
    RandomizedSet() {

    }
    // 不存在时，向集合中插入该项，并返回 true ；否则，返回 false
    bool insert(int val) {
        // 首先判断umap中的元素是不是存在
        if (umap.find(val) == umap.end()) { // 如果没有这个元素，那么插入
            umap[val] = vec.size();
            vec.push_back(val);
            return true;
        }else {
            return false;
        }
    }

    // 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
    bool remove(int val) {
        if (umap.find(val) == umap.end()) { // 如果没有这个元素，那么直接返回false;
            return false;
        }
        // 问题：数组中怎么快速找到元素并且移出？
        // 关键：直接将数组最后一个元素放入当前元素的位置，然后pop最后一个位置的元素
        vec[umap[val]] = vec[vec.size()-1];
        vec.pop_back();
        // 从集合中移出
        umap.erase(val);
        return true;

    }

    // 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
    int getRandom() {
        int idx = rand() % vec.size();
        return vec[idx];
    }
};
