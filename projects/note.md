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

## 双指针

### 移动零

![image-20240731173142001](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240731173142001.png)

**双指针**：设置一个零指针和非零指针，零指针始终指向序列中的第一个零，非零指针不断向右移动，将零与非零数进行位置交换，当非零指针移动到序列的末尾时，过程结束。代码如下：

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int num_point = 0;
        int zero_point = 0;
        while (zero_point < nums.size() && nums[zero_point] != 0) {
            zero_point++;
        }
        // 数组中没有0
        if (zero_point == nums.size()) return;
        num_point = zero_point;
        while (num_point < nums.size()) {
            // 如果数字指针指着零，那么直接右移
            if (nums[num_point] == 0) {
                num_point++; 
                continue;
            }
            // 如果数字指针指着非零，那么需要跟零指针指着的0换一下数值
            if (nums[num_point] != 0) {
                nums[zero_point] = nums[num_point];
                nums[num_point] = 0;
                // 然后零指针右移，直到遇到第一个零或者越界
                while(zero_point < nums.size() + 1 && nums[zero_point] != 0) {
                    zero_point++;
                }
            }
            // 数组里面的零已经被处理完了
            if (zero_point == nums.size() + 1) {
                break;
            }
            num_point++;
        }
    }
};
```

### 盛水最多的容器

![image-20240731174401300](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240731174401300.png)



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

## 单调栈/队列

### 滑动窗口的最大值

![image-20240724142022836](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240724142022836.png)

**优先队列**：找一个区间内的最大值，每次对这个区间只有两个数字的变化：增加一个数字，减少一个数字，不难想到，使用堆每次只调整堆中两个元素，且能够方便地得到堆中的最大值，这似乎是一个可行的方法。分析下时间复杂度：

- 在堆中增加一个元素，堆调整的时间复杂度：$O(\log(n))$
- 在堆中删除一个元素：删除需要先找到这个元素，然后删除并调整堆，综合需要的时间复杂度为$O(n)$

如果我们每次在窗口移动时，都进行元素的插入和删除的话，总的时间复杂度为$O(n)$。因此，对于整个数组而言，需要的时间复杂度为$O(n^2)$。

【关键思想：**延迟删除**】减少时间复杂度需要只能在删除元素处进行调整，如果仅仅是删除堆顶的元素，那么时间复杂度就可以降低到$O(\log n)$：不妨推迟数的删除，我们在堆中存的不仅是数，还包括该数对应的下标，如果堆顶元素（最大值）是窗口外的元素，那么才把这个元素删除。那么就可以减少一些操作。最坏情况下假设每次都要删除，那么对于一个窗口而言，增加元素+删除元素的综合的时间复杂度为$O(\log n)$。对于所有的元素而言，整体的时间复杂度为$O(n\log n)$。

代码如下：

```cpp
// 大顶堆：关键在于不急于移出离开滑动窗口的元素，延迟移出，直到这个元素到堆顶，移除的时间复杂度由O(n)降低到O(1)
class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> queue; 
        for (int i = 0; i < k; i++) {
            queue.emplace(nums[i], i);
        }
        vector<int> res;
        res.push_back(queue.top().first);
        for (int left = 1, right = k; left < nums.size(), right < nums.size(); left++, right++) {
            queue.emplace(nums[right], right);
            while (queue.top().second < left) {
                // 弹出堆顶元素
                queue.pop();
            }
            res.push_back(queue.top().first);
        }
        return res;
    }
};
```

**单调递减队列**：在窗口的滑动过程中，注意到这样一个事实：如果$j>i$，且$nums[j] > nums[i]$那么$nums[i]$在后续的窗口滑动中都不会成为最大的元素，是冗余的元素。我们将每个窗口看做一个队列，这样在下标增长的过程中，如果新进入窗口的数据比队首的元素大，那么队列需要清空：因为队列中的所有元素一定都比新进入窗口的元素要小，后续不再可能成为窗口中最大的元素；如果新进入窗口的数据比队首的元素小，那么该元素插入队尾，因为该元素可能会随着窗口的移动成为窗口中最大的元素；再这样的过程中，不难发现每个窗口中最大的元素一定是队首的元素：因为如果不是最大的元素，那么一定存在某个元素进入窗口时，该元素被清除。进一步地，可以得出队列中的元素是单调递减的。

在上述过程中，需要在队列两端插入删除元素，可以使用双端队列：deque。（内部使用双向链表实现，在两端插入和删除的时间复杂度都是$O(1)$）。

因此，分析最差情况，假设每个元素都恰好被放入一次队列，且最多被弹出一次队列，因此时间复杂度为$O(n)$.

代码实现如下：

```cpp
class Solution3 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> res;
        // 未形成完整的窗口
        for (int i = 0; i < k; i++) {
            // 是否可以直接将队列清空？
            while (!dq.empty() && nums[i] >= nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        res.push_back(nums[dq.front()]);
        // 已经形成完整的窗口
        for (int right = k; right < nums.size(); right++) {
            // 队尾元素小于窗口右侧新元素，那么队列清空
            while (!dq.empty() && nums[right] >= nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(right);
            // 如果队首的元素已经超过窗口，那么应该清除
            while (!dq.empty() && dq.front() <= right - k) {
                dq.pop_front();
            }
            // 队首元素是最大的元素
            res.push_back(nums[dq.front()]);
        }
        return res;
    }
};
```

### 接雨水

![image-20240724162316693](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240724162316693.png)



## 数组的处理

### 合并区间

区间合并的关键在于首先对于所有区间进行按照start元素大小进行的排序。按照从小到大的原则完成排序之后，依次扫描区间，进行区间合并。

区间有序后，这种扫描+合并的过程是O(n)的：每个区间要么被合并到一个区间中，要么新建了一个区间。

合并可以通过扫描到的区间start元素和当前目标区间的end元素比较得到。当前目标区间是会不断更新的，初始设置为首元素最小区间的start和end，扫描到的区间的start元素如果小于目标区间的end，那么可以合并，并进行必要的end更新；否则，扫描到的区间不在当前目标区间内，那么后续的区间也不会在当前区间内了，即完成了上一个区间的合并，应该push目标区间到结果中，并新建一个目标区间。

代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] < b[0];
        });
        vector<vector<int>> res;
        for (int i = 0; i < intervals.size();) {
            int end = intervals[i][1];
            int k = i + 1;
            while(k < intervals.size() && end >= intervals[k][0]) {
                if (end < intervals[k][1]) {
                    end = intervals[k][1];
                }
                k++;
            }
            res.push_back({intervals[i][0], end});
            i = k;
        }
        return res;
    }
};
```

### 轮转数组

**使用额外空间**：使用额外空间能直接将数组元素放到目标位置上。代码如下：

```cpp
// 我的做法
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        vector<int> res(nums.size(), 0);
        for (int i = nums.size()-1, rote_num = 0; rote_num < k; i--) {
            res[k-rote_num-1] = nums[i];
            rote_num++;
        }
        for (int i = 0; i <= nums.size() - k - 1; i++) {
            res[i+k] = nums[i];
        }
        nums = res;
    }
};

// 力扣题解，直接将所有的元素都放到： (i + k) mod n的位置
class Solution2 {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> res(nums.size(), 0);
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            res[(i + k) % n] = nums[i];
        }
        nums = res;
    }
};
```

**不使用额外空间**：原地操作使用翻转可以实现，一共要进行三次翻转。依次翻转整个数组，第二次分别对k前和k后的元素进行翻转，代码如下：

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k % n);
        reverse(nums.begin() + k % n, nums.end());
    }
};
```

### 缺失的第一个正数

![image-20240725134026407](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240725134026407.png)

**不考虑空间复杂度**：假如只考虑时间复杂度，而不考虑空间复杂度：可以从1开始向正无穷遍历，查询这些数是不是出现在了数组中即可。如果查询的时间复杂度可以在$O(1)$实现，那么整体的时间复杂度则是$O(n)$。那么不难想到关键在于实现快速的查找，使用哈希表即可：首先扫描一遍数组，将数值作为key，次数记为value，从1开始遍历的时候再进行查表，没有出现在哈希表中的就是第一个没有出现的正整数。

代码如下：

```cpp
// 哈希表+扫描两遍：不考虑O(1)的空间复杂度，只考虑O(n)的时间复杂度
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_map<int, int> umap;
        int minNum = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= 0) continue;
            if (!umap.count(nums[i])) umap[nums[i]]++;
        }
        for (int i = 1; i < INT_MAX; i++) {
            if(!umap.count(i)) return i;
        }
        return 0;
    }
};
```

上述的方法时间复杂度满足要求，但是空间复杂度为$O(n)$。瓶颈在于哈希表的实现，如果能用原来的数组达到哈希表的目的，那么就不需要额外的空间了。

**原地处理**：题解给出的方法是将原来的数组改成哈希表。这需要基于一个：

- 断言：对于一个长度为$n$的数组，没有出现的第一个正数一定在$[1,n+1]$内。
  - 证明：如果[1,n]之内的数全都出现，那么没出现的数是n+1，在区间[1, n+1]内；如果[1,n]内的数没有全都出现，即存在一些数是在该区间外，那么没出现的数也一定在区间[1,n+1]内。

这样，其实哈希表中需要存储的仅是$[1,n]$之内的数，其他的数都可以不放入哈希表。因此可以将原来的数组改为一个哈希表：

- 对原数组做预处理：将所有的不在[1,n]区间的数全改为一个统一的值，比如n+1，因为他们对于找到没有出现的第一个正整数没有影响。
- 依次扫描数组，扫描到[1,n]之内的数$x$时，将$x-1$下标处的数字$m$改为$-m$。
  - 特别地，如果扫描到的数不是n+1，且是一个负数-m，且该负数的绝对值在[1,n]内，那么说明原来此处的数字为m，应该对m-1处数字进行修改。
  - 如果发现要改为负数的位置已经是负数了，那么就不用再更改了
- 完成这个操作后，再扫描这个数组，如果m-1处的数字不是负数，那么说明m没有出现在数组中。如果数组中全是负数，那么说明n+1没有出现在数组中。

代码如下：

```cpp
class Solution2 {
public:
    int firstMissingPositive(vector<int>& nums) {
        // 更改不在区间内的数
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = (nums[i] > nums.size() or nums[i] < 1)? nums.size() + 1 : nums[i];
        }
        // 模拟哈希表
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == nums.size() + 1 or (nums[i] < 0 and nums[i] < -nums.size()) or nums[abs(nums[i]) - 1] < 0) continue;
            // 扫到一个数，如果是不是n+1且是一个正数，那么要翻转，如果是一个负数，但是其绝对值在[1,n]内，那么也要翻转，其余不用管。
            nums[abs(nums[i]) - 1] = -nums[abs(nums[i])-1];
        }
        for (int i = 0; i < nums.size(); i++) {
            if(nums[i] >= 0) return i+1;
        }
        return nums.size() + 1;
    }
};
```

### 矩阵置零

![image-20240725210248067](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240725210248067.png)

**使用标记数组**：遍历两次，第一次遍历使用一个标记数组记录需要标记为0的行和列的下标。可以用两个数组来分别记录，也可以用一个map来记录，但是需要进行额外的处理区别行号/列号（使用一个数组也是一样的，需要做额外的处理）。第二次遍历时，扫描每个元素，判断他们的index是否在map中，在的话将该元素置零。代码如下：

```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        unordered_map<int, int> umap;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 0) {
                    umap[-i-1] = 1;
                    umap[j] = 1;
                }
            }
        }

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (umap.count(-i-1) or umap.count(j)) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
```

### 螺旋矩阵

![image-20240725211011198](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240725211011198.png)

**记录路径**：解决的关键在于碰到边界之后向哪个方向走以及如何刻画由其他数构成的边界。

- 碰到边界后转向：定义右下左上四个方向数组，在一轮循环中使用是按照这个方向行走的。
- 如何定义边界：除了数组本身的边界外，碰到已经输出的数也应该转向，因此可以采取两种方案更新边界：
  - 使用map记录已经输出的数的下标，每次打印一个数字前判断该数的索引是否在map中，在的话不进行输出，否则输出，并记录该数在map中
  - 定义上下左右四个边界，输出完第一行，应该upper++；输出完最后一列，应该right--……

后者的空间复杂度更小，而且不用查询，两种方式的代码如下：

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 定义四个方向
        vector<vector<int>> directions = {{0,1}, {1,0},{0,-1},{-1,0}};   // 右，下，左，上
        unordered_set<string> uset;
        int count = 0, term = 0, last_i = 0, last_j = 0;
        int totNum = matrix.size() * matrix[0].size();
        vector<int> res;
        while(count < totNum) {
            vector<int> currDire = directions[term % 4];
            while (last_i >= 0 && last_i < matrix.size() && last_j >= 0 && last_j < matrix[0].size() && !uset.count(to_string(last_i) + "," + to_string(last_j))) {
                uset.insert(to_string(last_i) + "," + to_string(last_j));
                count++;
                res.push_back(matrix[last_i][last_j]);
                last_i += currDire[0];
                last_j += currDire[1];
            }
            // 回退一步
            last_i -= currDire[0];
            last_j -= currDire[1];
            // 改变方向
            term++;
            // 更新方向
            last_i += directions[term % 4][0];
            last_j += directions[term % 4][1];
        }
        return res;
    }
};
```



### 旋转图像

![image-20240726190200451](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240726190200451.png)

![image-20240726190214531](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240726190214531.png)

与[轮转数组](###轮转数组)：移动k个某尾的数到数组头部的翻转的方法类似，这题也可以找到规律：先reverse，然后ij序号对换。代码如下：

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        reverse(matrix.begin(), matrix.end());
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i ; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
    }
};
```

Note：注意，在有关vector图像的题目中，正序遍历数组比逆序遍历速度更快。

### 搜索二维矩阵

![image-20240727003825360](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240727003825360.png)

**二分查找**：对每一行做一次二分查找，时间复杂度是$m\log n$

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); i++) {
            auto it = lower_bound(matrix[i].begin(), matrix[i].end(), target);
            if (it != matrix.end() && *it == target) {
                return true;
            }
        }
        return false;
    }
};
```

**Z字型查找**：以$matrix[0][n-1]$为起点进行查找，规则：

- 如果$matrix[i][j] == target$，那么找到了，返回
- 如果$matrix[i][j] > target$，那么以第j列以及大于j的列都不会有target，j--
- 如果$matrix[i][j] < target$，那么i++

代码如下：

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int start_i = 0, start_j = matrix[0].size()-1;
        int currI = start_i, currJ = start_j;
        while (currI < matrix.size() && currJ >= 0) {
            int temp = matrix[currI][currJ];
            if (temp == target) return true;
            if (temp > target) {
                currJ--;
            }else {
                currI++;
            }
        }
        return false;
    }
};
```

## 链表的处理

### 相交链表

![image-20240731190506184](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240731190506184.png)

**双指针**：双指针是实现判断相交链表的一个高效手段，只要指向两个链表的指针在遍历到对应链表的尾部时，移动指针到另一个链表的表头即可，原理如图：

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240801003726538.png" alt="image-20240801003726538" style="zoom:50%;" />

实现的代码如下：

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        while (p != q) {
            if (p == nullptr && q != nullptr) {
                p = headB;
                q = q->next;
                continue;
            }
            if (q == nullptr && p != nullptr) {
                q = headA;
                p = p->next;
                continue;
            }
            p = p->next;
            q = q->next;
        }
        return p;
    }
};
```

**记录链表长度**：首先分别记录两个链表的长度分别记做$|A|$和$|B|$，然后较长的链表先向前走$|A-B|$个节点，然后两个链表共同向前移动，遇到，代码如下：

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 若其中一个为空，直接返回null
        if (headA == nullptr or headB == nullptr) return nullptr;

        //首先记录两个链表的长度
        int lenA = 1, lenB = 1;
        ListNode* p = headA;
        ListNode* q = headB;
        ListNode *p2, *q2;

        p2 = p, q2 = q;

        while (p2->next != nullptr) {
            lenA++;
            p2 = p2->next;
        }

        while (q2->next != nullptr) {
            lenB++;
            q2=q2->next;
        }

        // 长度较长的链表先走几步
        while (lenA > lenB) {
            p = p->next;
            lenA--;
        }
        while (lenB > lenA) {
            q = q->next;
            lenB--;
        }

        // 两个链表一起走，直到遇到相同的结点
        while (p != nullptr && q != nullptr && q != p ) {
            q = q->next;
            p = p->next;
        }

        if (p != nullptr && q != nullptr) return q;
        return nullptr;
    }
};
```

**哈希表**：判断有没有相交可以直接讲一个链表中的所有节点的**指针**，放入一个哈希表中，然后遍历另一个哈希表，判断有没有相同的值在哈希表中。代码如下：

```cpp
class Solution3 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        unordered_map<ListNode*, int> umap;
        while (p!=nullptr) {
            umap[p]++;
            p = p->next;
        }
        while (q!=nullptr) {
            if (umap.count(q)) return q;
            q = q->next;
        }
        return nullptr;
    }
};
```

### 反转链表

![image-20240801141223695](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240801141223695.png)

**三指针法**：使用一个指针记录当前的结点，一个记录前一个节点，一个记录后一个，三个指针辅助即可实现，代码如下：

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *curr = head, *pre = nullptr;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        return pre;
    }
};
```

这是比较直接，也是执行起来速度较快的方法。下面这种写法一定要注意设置$pre$指针的next为nullptr，否则链表会成为一个环形链表：

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        ListNode *curr = head->next, *pre = head;
        pre->next = nullptr;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        return pre;
    }
};
```

**栈**：使用栈也能翻转链表，但是速度较慢。另外注意一点，即**最后一个指针的next一定要设置为nullptr**。代码如下：

```cpp
// 方法1： 栈
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        stack<ListNode*> nodeStack; // 存储指针
        ListNode* p = head;
        // 放入栈
        while(p != nullptr) {
            nodeStack.push(p); // 存储指针
            p = p->next;
        }
        // 从栈中取出节点
        p = nodeStack.top();
        ListNode* tempNode = p;
        nodeStack.pop();
        while (!nodeStack.empty()) {
            ListNode* q = nodeStack.top();
            nodeStack.pop();
            p->next = q;
            p = q;
        }
        p->next = nullptr; // 最后一个节点的 next 设为 nullptr
        return tempNode;
    }
};
```

### 回文链表

![image-20240801160739625](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240801160739625.png)

**快慢指针+反转链表**：一种直接的写法是反转链表，栈，或者复制链表到数组中，进行双指针判断，但是这些方法的空间复杂度都是$O(n)$。空间复杂度为$O(1)$的方法可以使用**快慢指针+反转链表**：快指针一次走两步，慢指针一次走一步；快指针到达末尾时，慢指针正好到链表的一半，此时以慢指针为表头，翻转后半边的链表，然后从两头进行双指针比较即可。注意奇数节点和偶数结点的区别处理：奇数节点的中间节点应该算作前半部分的链表。代码如下：

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 首先设置快慢指针
        ListNode *fast = head, *slow = head;
        while (fast->next != nullptr) {
            fast = fast->next;
            if (fast->next != nullptr) {
                fast = fast->next;
            }else {
                break;
            }
            slow = slow->next;
        }
        // 以后面的slow指针为起点，翻转链表
        ListNode *curr = slow->next, *pre = nullptr;
        while (curr != nullptr) {
            ListNode* nextNode = curr->next;
            curr->next = pre;
            pre = curr;
            curr = nextNode;
        }
        // 反转后现在的pre是反转后链表的首节点
        ListNode *leftHead = head, *p = pre;
        while (p != nullptr) {
            if (p->val != leftHead->val) return false;
            p = p->next;
            leftHead = leftHead->next;
        }
        return true;
    }
};
```

### 环形链表

![image-20240801230800876](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240801230800876.png)

**哈希表**：参考相交链表一节，哈希表是一个简单的方式，按照哈希表进行遍历，每个结点都加入哈希表，直到遇到nullptr或者是相同的结点：前者返回不含环，后者返回含环；代码如下：

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* p = head;
        unordered_map<ListNode*, int> umap;
        while (p != nullptr) {
            if (!umap.count(p)) {
                umap[p]++;
                p = p->next;
            }else {
                return true;
            }
        }
        return false;
    }
};
```

**快慢指针**：相同的速度，如果有环，快指针一定会追上慢指针；另一方面如果快指针走到空了，那么也意味着链表不含有环。代码如下：

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr) return false;
        ListNode *fast=head->next, *slow=head;
        while (fast != slow) {
            if (fast == nullptr) return false;
            fast = fast->next;
            if (fast == nullptr) return false;
            fast = fast->next;
            slow = slow->next;
        }
        return true;
    }
};
```

### 环形链表II

![image-20240801235812175](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240801235812175.png)

**哈希表**：一种方式是直接参考[环形链表](##环形链表)中哈希表的做法，方法简单，但是空间复杂度不是$O(1)$，方法如下：

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *p = head;
        unordered_map<ListNode*, int> umap;
        while (p!=nullptr) {
            if (umap.count(p)) return p;
            umap[p]++;
            p = p->next;
        }
        return nullptr;
    }
};
```



### 合并两个有序链表

![image-20240801235501510](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240801235501510.png)

**归并排序法**：归并排序的方式+尾插法创建链表是一个直接的方法。注意与数组不同，这里对于遇到nullptr后另一个链表的处理不需要再像数组那样一个个的拷贝，直接**将newTail指针连接到非空的剩余链表即可**（line 17）。代码如下：

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *p = list1, *q = list2;
        ListNode *newHead = new ListNode(0), *newTail = newHead;
        while (p!=nullptr && q!= nullptr) {
            if (p->val <= q->val) {
                newTail->next = p;
                newTail = p;
                p = p->next;
            }else {
                newTail->next = q;
                newTail = q;
                q = q->next;
            }
        }
        newTail->next = p == nullptr? q : p;
        return newHead->next;
    }
};
```

**递归写法**：迭代的写法需要新申请一个结点作为头结点，但是递归的写法能够直接从两个链表的节点中选择较小值的那个节点作为头结点，在递归的过程中自然而然地完成next关系的延续。另外，对于尾部的处理也可以比较简单地实现，代码如下：

```cpp
class Solution2 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) {
            return list2;
        }else if (list2 == nullptr) {
            return list1;
        }else if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }else {
            list2->next = mergeTwoLists(list2->next, list1);
            return list2;
        }
    }
};
```

### 两数相加

![image-20240802121547267](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240802121547267.png)

思路很简单，两个链表都从开始加上进位相加即可，需要注意的是最后的进位。下面给出两种写法，第一种写法是将对尾部的处理单独用一个循环写，第二个写法表达上不如第一种直接，但是将尾部的处理融入，代码如下：

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(0), *tail = head;
        // 从头尾指针开始做加法，中间进位用l表示：
        ListNode *p=l1, *q=l2;
        int l = 0;
        // 共同部分的增加；
        while (p!=nullptr && q!=nullptr) {
            int sum = p->val + q->val + l;
            ListNode *nextNode = new ListNode(sum % 10);
            l = sum / 10;
            tail->next = nextNode;
            tail = nextNode;
            p = p->next;
            q = q->next;
        }
        // 判断哪个链表进入了nullptr，取非null的链表的头
        ListNode *resNode = p==nullptr? q:p;
        while (resNode!=nullptr) {
            int sum = resNode->val + l;
            ListNode *nextNode = new ListNode(sum % 10);
            resNode = resNode->next;
            tail->next = nextNode;
            tail = nextNode;
            l = sum / 10;
        }
        if (l != 0) {
            ListNode *nextNode = new ListNode(l);
            tail->next = nextNode;
        }
        return head->next;
    }
};
```

第二种写法：更加精简，运行起来时间也更快。

```cpp
class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(0), *tail = head;
        // 从头尾指针开始做加法，中间进位用l表示：
        ListNode *p=l1, *q=l2;
        int l = 0;
        // 共同部分的增加；
        while (p!=nullptr || q!=nullptr) {
            int sum = 0;
            if (p!=nullptr) {
                sum += p->val;
                p = p->next;
            }
            if (q!=nullptr) {
                sum += q->val;
                q = q->next;
            }
            sum += l;
            ListNode *nextNode = new ListNode(sum % 10);
            l = sum / 10;
            tail->next = nextNode;
            tail = nextNode;
        }
        if (l != 0) {
            ListNode *nextNode = new ListNode(l);
            tail->next = nextNode;
        }
        return head->next;
    }
};
```

### 删除链表的倒数第N个节点

![image-20240802165022892](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240802165022892.png)
