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

## 单调栈/队列

### 滑动窗口的最大值

![image-20240724142022836](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240724142022836.png)

**优先队列**：找一个区间内的最大值，每次对这个区间只有两个数字的变化：增加一个数字，减少一个数字，不难想到，使用堆每次只调整堆中两个元素，且能够方便地得到堆中的最大值，这似乎是一个可行的方法。分析下时间复杂度：

- 在堆中增加一个元素，堆调整的时间复杂度：$O(\log(n))$
- 在堆中删除一个元素：删除需要先找到这个元素，然后删除并调整堆，综合需要的时间复杂度为$O(n)$

如果我们每次在窗口移动时，都进行元素的插入和删除的话，总的时间复杂度为$O(n)$。因此，对于整个数组而言，需要的时间复杂度为$O(n^2)$。

【关键思想：延迟删除】减少时间复杂度需要只能在删除元素处进行调整，如果仅仅是删除堆顶的元素，那么时间复杂度就可以降低到$O(\log n)$：不妨推迟数的删除，我们在堆中存的不仅是数，还包括该数对应的下标，如果堆顶元素（最大值）是窗口外的元素，那么才把这个元素删除。那么就可以减少一些操作。最坏情况下假设每次都要删除，那么对于一个窗口而言，增加元素+删除元素的综合的时间复杂度为$O(\log n)$。对于所有的元素而言，整体的时间复杂度为$O(n\log n)$。

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







