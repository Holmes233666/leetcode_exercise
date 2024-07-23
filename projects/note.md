# 力扣刷题记录

## 哈希表

### 两数之和

![image-20240722113741768](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240722113741768.png)

#### 暴力想法

最直接的想法是枚举所有i和所有j，找到和为target的两个数，这样做的时间复杂度无疑是$O(n^2)$。代码如下：

```c++
for(int i = 0; i < nums.size(); i++) {
  for(int j = i + 1; j < nums.size(); j++) {
    if (nums[i] + nums[j] == target) return {i, j};
  }
}
```

#### 哈希表

上述代码主要的问题在于我们获得一个数nums[i]后需要遍历一遍数组，判断有没有nums[j]在数组中，这个查找的过程是$O(n)$的，如果可以将这个过程的时间复杂度降为$O(1)$，那么时间复杂度当然可以下降。降低查找的时间复杂度可以简单想到哈希表：如果将每个数放入哈希表中，那么查找一个目标的时间复杂度即可下降。代码如下：

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        // 将元素放入哈希表，key为元素值，value为元素的下标
        for (int i = 0; i < nums.size(); i++) {
            hash_map[nums[i]] = i;
        }

        // 遍历数组，查找target - nums[i]是否在哈希表中
        for(int i = 0; i <nums.size(); i++) {
            int temp = target - nums[i];
            if (hash_map.count(temp) && hash_map[temp] != i) {
                return {i, hash_map[temp]};
            }
        }
        return {};
    }
};
```

上述的过程仍可以进一步优化，关键在于将初始化哈希表和查找目标数值的过程在一次循环中完成：每次在哈希表中查找$target - nums[i]$在不在哈希表中，如果找不到，那么$nums[i]$放入哈希表；否则找到了就可以直接返回，代码如下：

```c++
// 提升版本 只进行一次循环
class improvedSolution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        for (int i = 0; i < nums.size(); i++) {
            auto it = hash_map.find(target - nums[i]);
            if (it != hash_map.end()) {
                return {it->second, i};
            }
            hash_map[nums[i]] = i;
        }
        return {};
    }
};
```

## 前缀和

### 和为K的子数组

![image-20240722113658243](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240722113658243.png)

**前缀和**：对于nums[i]，其前缀和为从数组第一个元素nums[0]开始，以nums[i]结尾的子数组中所有元素的和。假设记做sums[i]。那么对于数组中从下标$i$到$j$的任意一段子数组，其和可以由下式计算：
$$
sums[i]-sums[j] + nums[j] = sums[i]-sums[j-1]
$$
检查有没有和为k的子数组即找到一组$i$和$j-1=l$，使得$sums[i]-sum[l]=k$，那么简单变形可知，对于任一个前缀和$sums[i]$，判断有没有一个前缀和$sums[l]$可以与之配成一个和为k的子数组即找到下面的前缀和：
$$
sums[l] = sums[i]-k;
$$
一种直接的想法是不妨先计算所有的前缀和，即遍历$l$计算所有的$sums[l]$，然后进行第二次遍历的时候，对于$sums[i]$和$k$，我们查询预先计算的前缀和中有没有满足条件的$sums[l]=sums[i]-k$。不难想到，预先计算的时候可以将前缀和作为哈希表的key，将该前缀和出现的次数作为哈希表的value，由此进行时间复杂度为$O(1)$的查找，又因为整体只进行了一次遍历，在遍历中进行的是时间复杂度为$O(1)$的查找，所以整体的时间复杂度为$O(n)$。这种想法下，代码如下：

```cpp
// 力扣解法：前缀和 + 哈希表，错误版本：对于k=0的情况，会记录下为空的子数组
class Solution3 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        // 遍历一遍数组，使用sums[i]表示以i为结尾的从序号0开始的子数组的和
        vector<int> sums(nums.size(), 0);
        unordered_map<int, int> umap;
        umap[0] = 1;
        umap[nums[0]] = 1;
        sums[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            sums[i] = sums[i-1] + nums[i];
            // 记录频次
            umap[sums[i]] += 1;
        }

        // j - i段子数组的和为 sums[i] - sums[j] + nums[j] = sums[i] - sums[j-1]
        for (int i = 0; i < nums.size(); i++) {
            // 等于 k 的段满足：sums[j-1] = sums[i] - k
            if (umap.find(sums[i] - k) != umap.end()) {
                res += umap[sums[i]-k];
            }
        }
        return res;
    }
};
```

但是上面的解法中，对于k=0的情况，会将$sums[i] = sums[i]-k$这种情况算入最终的答案（即nums={1,2,3},k=0时结果返回值为3，结果应该为0），即答案错误地中包含了为空的子数组。但是由于哈希表中无法缓存前缀和的序号（可以实现但是很麻烦），我们不妨模仿两数之和的做法，边遍历边放入哈希表，并在将自身放入哈希表之前查找哈希表，这样就可以避免将自身作为待减去的前缀和的情况。代码如下：

```cpp
// 前缀和+哈希表
class Solution4 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        int tempSum = 0;
        unordered_map<int, int> umap;
        umap[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            tempSum += nums[i];
            // 试图找到一个子数组，tempSum减去这个子数组就等于k
            if (umap.find(tempSum - k) != umap.end()) {
                res += umap[tempSum - k];
            }
            umap[tempSum]++;
        }
        return res;
    }
};

```

## 滑动窗口

### 最小覆盖子串

![image-20240723193558399](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240723193558399.png)

![image-20240723193618138](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240723193618138.png)

#### 滑动窗口基础解法

一个基本的想法是：

- 将所有的字符作为key，字符在t中出现的次数作为value，先存储在哈希表umap中；
- 设置两个指针，left和right，通过right指针不断向前，记录区间中出现的字符及其出现的次数（记录在副本哈希表umap_cpy中）
- 如果副本哈希表中的每一个字符出现的次数都比umap中对应字符出现的次数要多，那么即完成匹配。

而在完成匹配后如何移动窗口是一个重要的问题。

如果要找到一个最小覆盖的子串，那么在完成一个匹配时，应该尝试将**窗口缩小**到最小，有两个问题：

- 移动left还是移动right？一定是移动left，因为right处是刚好完成一个匹配的位置，少了就构不成匹配的串。
- 如何移动left？
  - 依次移动。对在map中的单词进行umap_cpy的递减处理
  - 直接跳到下一个匹配的字符处。【使用队列】

缩小到最小的窗口后，left再向前移动一个位置，因为易知，后面的更短的串肯定是不需要当前恰好构成一个窗口的s[left]的（不然他一定不是最小的覆盖），然后再从当前位置进行right递增的匹配。直到匹配到，再进行窗口的缩小。

在上述过程中，不能每次都使用substr创建一个新的子串，否则会内存溢出！

Note: 在记录子串时，最好都采用记录起始位置和长度的方式，避免出现爆内存的情况。

这里给出上面两种基础的想法的代码：

- 不使用队列

```cpp
// 滑动窗口 + umap： 去掉队列，left逐个移动，不进行快速定位下一个
class Solution {
public:
    unordered_map<char, int> c_umap;
    unordered_map<char, int> c_umap_cpy;

    bool matches() {
        for (const auto &p: c_umap) {
            if (c_umap_cpy[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t) {
        // 特殊情况处理
        if (t.size() > s.size()) return "";

        // 先把所有待匹配字母放进数组
        for (char c : t) {
            c_umap[c]++;
        }
        
        int minLen = INT_MAX;
        string str;
        int start = 0;
        for (int left = 0, right = left; right < s.size(); right++) {
            // 是待匹配的字母
            if (c_umap.count(s[right])) {
                c_umap_cpy[s[right]]++;
            }else{
                continue;
            }

            // 如果是匹配的串
            // 尝试收缩串，直到有字母不满足umap中的数值，此时，right++
            while (matches()) {
                // 如果是更短的子串
                if (minLen > right - left + 1) {
                    start = left;
                    minLen = right - left + 1;
                }
                if (c_umap_cpy.count(s[left])) c_umap_cpy[s[left]]--;
                left++;
            }
        }
        return str = minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};
```

- 使用队列

```cpp
class Solution {
public:
    unordered_map<char, int> c_umap;
    unordered_map<char, int> c_umap_cpy;
    // 辅助函数来检查c_umap_cpy是否满足c_umap的
    bool matches() {
        for (const auto &p: c_umap) {
            if (c_umap_cpy[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        // 特殊情况处理
        if (t.size() > s.size())
            return "";
        // 一般情况处理
        queue<pair<char, int>> q;

        // 先把所有待匹配字母放进数组
        for (char c : t) {
            c_umap[c]++;
        }
        string str;
        int minLen = INT_MAX;
        for (int left = 0, right = left; right < s.size(); right++) {
            // 是待匹配的字母
            if (c_umap.count(s[right])) {
                c_umap_cpy[s[right]]++;
                q.push(make_pair(s[right], right));
                left = q.front().second;
            }else{
                continue;
            }

            // 如果是匹配的串
            // 尝试收缩串，直到有字母不满足umap中的数值，此时，right++
            while (matches()) {
                // 如果是更短的子串
                if (minLen > right - left + 1) {
                    str = s.substr(left, right - left + 1);
                    minLen = right - left + 1;
                }
                c_umap_cpy[q.front().first]--;
                q.pop();
                left = q.front().second;
            }
        }
        return str;
    }
};
```

#### 优化

优化这个问题的关键在于哈希表的比较，每次都需要遍历整个哈希表，得到这窗口中的串是不是满足条件的串，这是复杂的。我们可以直接维护一个cnt计数器，记录此时满足匹配数量的字母的数量。如果cnt的大小和umap一样大，那么一定是匹配上了，否则没有。

- 使用队列的优化：

```cpp
class Solution3 {
public:
    unordered_map<char, int> c_umap;
    unordered_map<char, int> c_umap_cpy;

    string minWindow(string s, string t) {
        // 特殊情况处理
        if (t.size() > s.size())
            return "";
        // 一般情况处理
        queue<pair<char, int>> q;

        // 先把所有待匹配字母放进数组
        for (char c : t) {
            c_umap[c]++;
        }

        string str;
        int minLen = INT_MAX;
        int cnt = 0;
        int start = 0;

        for (int left = 0, right = left; right < s.size(); right++) {
            // 是待匹配的字母
            if (c_umap.count(s[right])) {
                c_umap_cpy[s[right]]++;
                q.emplace(s[right], right);
                left = q.front().second;
                if (c_umap_cpy[s[right]] == c_umap[s[right]]) cnt++;
            }else{
                continue;
            }

            // 如果是匹配的串
            // 尝试收缩串，直到有字母不满足umap中的数值，此时，right++
            while (cnt == c_umap.size()) {
                // 如果是更短的子串
                if (minLen > right - left + 1) {
                    start = left;
                    minLen = right - left + 1;
                }
                c_umap_cpy[q.front().first]--;
                if (c_umap_cpy[q.front().first] < c_umap[q.front().first]) {
                    cnt--;
                }
                q.pop();
                left = q.front().second;
            }
        }
        return str = minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};
```

- 不使用队列的优化

```cpp
```

## 动态规划
