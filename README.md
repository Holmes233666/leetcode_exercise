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

但是上面的解法中，对于k=0的情况，会将$sums[i] = sums[i]-k$这种情况算入最终的答案（即nums={1,2,3},k=0时结果返回值为3，结果应该为0），即答案错误地中包含了为空的子数组。还存在另外一种情况，如果sums[i] = -2, sums[j] = -5，假如j>i,且target=3，那么错误的区间[j,i]也会被计算进去，造成错误。所以前缀和的使用应该在一轮遍历中进行，不能预先计算完所有的前缀和。

我们模仿两数之和的做法，边遍历边放入哈希表，并在将自身放入哈希表之前查找哈希表，这样就可以避免上述两种情况：

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

### 路径总和III

![image-20240910190149443](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240910190149443.png)

法1：不难想到可以对每个结点进行一次深搜，每个结点作为输入，搜索这个结点往下的子树是否存在满足条件的路径，并记录。但是这种方法毫无疑问，时间复杂会比较高：$O(n^2)$

需要熟悉前缀和的方法：（1）使用哈希表记录<前缀和-出现次数>；（2）使用前缀和的关系：`ump.find(tempSum-target)!=umap.end()`；

这种在数组中扫描一次，用tempSum记录的优势在深搜的树中优势表现得更加明显：每个结点结尾的前缀和只会考虑一次，不会造成重复，直到到达路径的叶子节点后，依次弹栈，tempSum依次减去当前值，然后在分支处考虑别的结点。时间复杂度为$O(n)$，代码实现如下：

```cpp
class Solution {
public:
    unordered_map<long, int> ump;
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;
        // long表示和，int表示有该和的路径的个数
        ump[0] = 1;
        int res = 0;
        long tempSum = 0;
        DFS(root, targetSum, tempSum, res);
        return res;

    }

    void DFS(TreeNode* root, long target, long& tempSum, int& res) {
        if (root != nullptr) {
            tempSum += root->val;
            // umap中有该值
            if (ump.find(tempSum-target) != ump.end()) {
                res += ump[tempSum-target];
            }
            ump[tempSum]++;
            // 分别对左右节点进行深搜
            // 左节点进行深搜
            DFS(root->left, target, tempSum, res);
            // 深搜结束，从umap中去掉tempSum-root->val的值的频次
            if (root->left != nullptr) {
                ump[tempSum]--;
                tempSum -= root->left->val;
            }
            // 右节点进行深搜
            DFS(root->right, target, tempSum, res);
            if (root->right != nullptr) {
                ump[tempSum]--;
                tempSum -= root->right->val;
            }
        }
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

### 搜索二维矩阵II

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

**快慢指针+哑结点**：定位结点使用快慢指针，利用哑节点能够减少对临界条件的判断。代码如下：

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *pre = new ListNode();
        ListNode *res = head->next;
        ListNode *p = head, *q = head->next;
        while (p!=nullptr && q!= nullptr) {
            p->next = q->next;
            pre->next = q;
            q->next = p;
            pre = p;
            p = p->next;
            q = q->next;
        }
        return res;
    }
};
```

**快慢指针**：仅仅使用快慢指针，不使用哑节点也能完成：

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *first = head, *second = head, *third = head;
		// 首指针先走n步 
		while(n--){
			first = first->next;
		} 
     if(first == NULL){
       return second->next;
     }
		while(first->next != NULL){
			first = first->next;
			second = second->next;
		}
		second->next = second->next->next;
		return third;
    }
};
```

### 两两交换链表中的节点

![image-20240809091908832](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240809091908832.png)

**迭代法**：迭代解决链表的结点的交换问题是直接的思路，由于需要的是两两交换，这意味着在处理上一组交换结果和下一组待交换的结点时，需要记录前一组已经交换的结点的尾部节点，这里使用`pre`记录上一组的末尾节点，初始化为`nullptr`。那么一轮的交换过程可以很简单表示为：

代码1：需要进行尾部处理（保证不会出现环，以及对奇数和偶数结点分开两种条件）：

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *currNode = head, *nextNode, *pre = new ListNode(), *res = currNode->next;
        // 如果是没有后续结点的单个节点就不用交换了， 因此终止条件设置为：
        while(currNode != nullptr && currNode->next != nullptr) {
            cout << currNode->val << " ";
            // 准备好下一个带交换的一组的头
            nextNode = currNode->next->next;
            // 本轮交换
            pre->next = currNode->next;
            currNode->next->next = currNode;
            pre = currNode;
            currNode = nextNode;
        }
        if (currNode == nullptr) {
            pre->next = nullptr;
        }else{
            pre->next = currNode;
        }
        return res;
    }
};
```

代码2：这种交换方法不用进行尾部处理，因为中间步骤不会产生环形链：

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *pre = new ListNode();
        ListNode *res = head->next;
        ListNode *p = head, *q = head->next;
        while (p!=nullptr && q!= nullptr) {
            p->next = q->next;
            pre->next = q;
            q->next = p;
            pre = p;
            p = p->next;
            if (p == nullptr) return res;
            q = p->next;
        }
        return res;
    }
};
```

### K个一组翻转链表

![image-20240809101855076](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240809101855076.png)

![image-20240809102110797](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240809102110797.png)

k个一组翻转链表可以基于反转链表[反转链表](##反转链表)一题进行处理：给定一个链表的head和tail，调用反转链表的处理，直到构不成完整的k个节点为止。每次调用反转链表后需要返回新的head和tail，以便连接：因为新的head需要和上一个链表的tail连接，新的tail需要等待待翻转的下一个链表的head，进行连接；但是注意对于尾部的特别处理实现代码如下。尾部特别处理见28 29行。

```cpp
class Solution2 {
public:
    // 返回新的头结点和尾结点
    pair<ListNode*, ListNode*> reverseLinkNodeK(ListNode* head, ListNode* tail) {
        ListNode *pre = new ListNode(), *currNode = head, *tailNext = tail->next;
        pre->next = head;
        while(currNode != tailNext) {
            ListNode *nextNode = currNode->next;
            currNode->next = pre;
            pre = currNode;
            currNode = nextNode;
        }
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *currTermHead = head, *currTermTail = head, *res = head;
        ListNode *preTail = new ListNode();
        for (int i = 0; ; i++) {
            int term = k;
            currTermTail = currTermHead;
            while(currTermTail != nullptr && --term) {
                currTermTail = currTermTail->next;
            }
            if (currTermTail == nullptr) {
                // 不足k个或者刚好就是完整的一组的末尾
                // 上一组的尾巴连上当前的头
                preTail->next = currTermHead;
                return res;
            }
            if (i == 0) res = currTermTail;
            // 保存下一个头
            ListNode *tempNode = currTermTail->next;
            // 根据currTermHead和currTermTail以及k反转链表
            auto [newHead, newTail] = reverseLinkNodeK(currTermHead, currTermTail);
            // 重新连接新的头到上一个链表的尾
            preTail->next = newHead;
            preTail = newTail;
            currTermHead = tempNode;
        }
    }
};
```

上面的想法给出了一个直观的想法，下面给的代码是另一种思路：需要额外遍历链表记录要进行翻转的次数，反转链表函数每次返回的是尾部节点和尾部节点的下一个节点，然后在主函数中进行连接：（这种方法省一点循环的时间）

```cpp
class Solution {
public:
    // 返回尾结点和尾结点的下一个节点
    vector<ListNode*> reverseLinkNodeK(ListNode* head, ListNode* pre, int k) {
        vector<ListNode*> ListVec;
        ListNode *currNode = head, *nextNode;
        while(k--) {
            nextNode = currNode->next;
            currNode->next = pre;
            pre = currNode;
            currNode = nextNode;
        }
        ListVec.push_back(pre);
        ListVec.push_back(nextNode);
        return ListVec;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        int len = 0;
        ListNode *p = head, *res;
        // 首先记录链表的长度和要返回的头
        while (p!=nullptr) {
            len++;
            if (len == k) res = p;
            p=p->next;
        }
        // 一共要进行几轮旋转
        int term = len / k;
        // 初始化辅助指针pre
        ListNode *currHead = head, *pre = new ListNode();
        while (term--) {
            vector<ListNode*> vec = reverseLinkNodeK(currHead, pre, k);
            pre->next = vec[0];
            pre = currHead;
            currHead->next = vec[1];
            currHead = currHead->next;
        }
        return res;
    }
};
```

## 树的处理（递归）

### 从前序与中序遍历构造二叉树

![image-20240910190241409](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240910190241409.png)

从前序和中序构造关键在于**根据root节点划分左右子树**，然后**左右子树递归构造**即可：每次构造的时候先判断子树的root节点（依据前序，前序的第一个即为子树的root），创建root节点。然后根据root的下标（这时候为了快速根据前序的值判断中序的下标，需要使用**哈希表**），划分为左右子树。递归调用，分别传入左右子树的下标范围以及对应的前序的第一个位置：对于左子树来说，他的前序的第一个位置即为当前的root在pre+1，对于右子树来说，他的前序位置为当前root在pre中位置+左子树的节点数量（左边界到root的距离）。具体代码如下：

```cpp
class Solution {
public:
    unordered_map<int, int> ump;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;
        TreeNode* rootFather = new TreeNode(-1);
        // 将所有中序的元素放入哈希表: 值：下标
        for (int i = 0; i < inorder.size(); i++) {
            ump.emplace(inorder[i], i);
        }
        createBasedInorder(preorder, inorder, rootFather->left, 0, inorder.size()-1, 0);
        return rootFather->left;
    }

    // 基于中序，然后查询前序去构造二叉树
    void createBasedInorder(vector<int>& preorder, vector<int>& inorder, TreeNode* &newNode,
        int startInorder, int endInorder, int startPre) {
        // 如果end >= start，那么递归继续，否则递归终止
        if (endInorder >= startInorder) {
            // 先根据前序找到root结点的值和位置
            int rootVal = preorder[startPre];
            int rootIndex = ump[rootVal];
            int leftLength = rootIndex-startInorder;
            newNode = new TreeNode(rootVal);
            // 然后构造左右子树
            createBasedInorder(preorder, inorder, newNode->left, startInorder, rootIndex-1,
                startPre+1);
            createBasedInorder(preorder, inorder, newNode->right, rootIndex+1, endInorder,
                startPre+leftLength+1);
        }
    }
};
```

### 二叉树的最近公共祖先

![image-20240910210742517](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240910210742517.png)

如何找二叉树的最近公共祖先：遍历每个子树，当左右子树返回的都不是空节点时，那么这个结点是最近的公共祖先。

- 先判断在不在左子树
- 再判断在不在右子树

返回的是自下往上第一个满足组右子树都满足非空的结点（一定一个是p，一个是q），所以该结点一定是LCA

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return LCA(root, p, q);
    }

    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode* leftNode = LCA(root->left, p, q);
        TreeNode* rightNode = LCA(root->right, p, q);
        if (leftNode == nullptr) return rightNode;
        if (rightNode == nullptr) return leftNode;
        return root;
    }
};
```

## 图论算法

### 拓扑排序和环检测

拓扑排序的前提是图中没有环。

#### 环检测

环检测的实例：编译器的包依赖关系

关键：除了一般的`visited`数组外，增加一个`onpath`数组：记录目前正在递归栈中的元素，如果正在递归栈中的元素再次被访问到了：那说明含环；而在深搜中`visited`数组起的作用是防止重复深搜（深搜针对的对象是【结点】，针对结点扫描邻接节点），这么看的话，不考虑时间限制的话，其实可以不用`visited`。

![image-20240912194516913](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240912194516913.png)

```cpp
class Solution {
public:
    // 数组实现邻接表
    vector<vector<int>> grid;
    vector<int> visted;
    vector<int> onpath;
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        grid = vector<vector<int>> (numCourses, vector<int>());
        visted = vector<int> (numCourses, 0);
        onpath = vector<int> (numCourses, 0);
        bool flag = true;
        // 创建邻接表
        for (int i = 0; i < prerequisites.size(); i++) {
            int sour = prerequisites[i][1], to = prerequisites[i][0];
            grid[sour].push_back(to);
        }
        // 遍历所有的结点，进行深搜
        for (int i = 0; i < numCourses; i++) {
            if (visted[i] == 0) flag = DFS(i);
            if (flag) return (!flag);
        }
        return (!flag);
    }

    // 深度优先搜索
    bool DFS(int currNode) {
        onpath[currNode] = 1;
        visted[currNode] = 1;
        bool flag = false;  // 默认不含环
        for (int i = 0; i < grid[currNode].size(); i++) {
            int to = grid[currNode][i];
            if (onpath[to] == 1) {
                return true;    // 含有环
            }
            if (visted[to] == 1) {   // 访问过，不用继续深搜这个路线返回true
                continue;
            }else if (visted[to] == 0) {   // 没访问过，需要继续深搜
                flag = DFS(to);
                if (flag) break;
            }
        }
        onpath[currNode] = 0;
        return flag;
    }
};
```

### 前缀树

![image-20240912202047055](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240912202047055.png)

一个直观的方法是使用哈希表实现，哈希表中存入已经插入的单词，然后再判断有无该前缀的时候遍历哈希表，依次判断是否存在该前缀。但是该方法时间复杂度很高。代码如下：

```cpp
class Trie {
public:
    vector<Trie*> child;
    bool isEnd;
    Trie() {
        child = vector<Trie*>(26);
        isEnd = false;
    }

    void insert(string word) {
        Trie* t = this;
        int index = 0;
        while (index < word.length()) {
            int i = word[index++] - 'a';
            if (t->child[i] == nullptr) {
                t->child[i] = new Trie();
            }
            t = t->child[i];
        }
        t->isEnd = true;
    }

    bool search(string word) {
        // 从首字母开始依次向下搜索
        int index = 0;
        Trie* t = this;
        while (index < word.length()) {
            int i = word[index] - 'a';
            if (t->child[i] == nullptr) return false;
            t = t->child[i];
            index++;
        }
        if (t->isEnd == false) return false;
        return true;
    }

    bool startsWith(string prefix) {
        // 从首字母开始依次向下搜索
        int index = 0;
        Trie* t = this;
        while (index < prefix.length()) {
            int i = prefix[index] - 'a';
            if (t->child[i] == nullptr) return false;
            t = t->child[i];
            index++;
        }
        return true;
    }
};
```

另一个方式是使用指针数组：`vector<Tire*> child`，该数组初始化时即拥有26个位置，分别对应26个小写字母，该位置是否为空表示是否有字母存在。每个指针数组可以当做`Tire`类的属性，可使用循环迭代创建。同时，由于会有很多前缀单词，所以使用`isEnd`布尔量表征是否到达了单词末尾：在搜索时，如果到达了单词末尾，那么就成功匹配了；否则找到的是一个前缀。代码如下：

```cpp
class Trie {
public:
    vector<Trie*> child;
    bool isEnd;
    Trie() {
        child = vector<Trie*>(26);
        isEnd = false;
    }

    void insert(string word) {
        Trie* t = this;
        int index = 0;
        while (index < word.length()) {
            int i = word[index++] - 'a';
            if (t->child[i] == nullptr) {
                t->child[i] = new Trie();
            }
            t = t->child[i];
        }
        t->isEnd = true;
    }

    bool search(string word) {
        // 从首字母开始依次向下搜索
        int index = 0;
        Trie* t = this;
        while (index < word.length()) {
            int i = word[index] - 'a';
            if (t->child[i] == nullptr) return false;
            t = t->child[i];
            index++;
        }
        if (t->isEnd == false) return false;
        return true;
    }

    bool startsWith(string prefix) {
        // 从首字母开始依次向下搜索
        int index = 0;
        Trie* t = this;
        while (index < prefix.length()) {
            int i = prefix[index] - 'a';
            if (t->child[i] == nullptr) return false;
            t = t->child[i];
            index++;
        }
        return true;
    }
};
```



如果不将指针数组定义为`vector<Tire*> child`，定义为其他数据结构，比如``vector<LinkNode*> child``应该也是可以的。（尝试下）

```cpp
struct LinkNode{
  bool isEnd;
  vector<LinkNode*> child;
}
```

实现的代码：

```cpp
```

### 多源广度优先算法

#### 腐烂的橘子

![image-20240916170746815](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240916170746815.png)

直观的方法：直接模拟上述腐烂的过程，每一轮依次扫描矩阵，对于每个本轮没有访问过的腐烂的橘子（本轮没有访问过是为了保证新腐烂的橘子不会作为源点）进行对四个方向的腐蚀操作。另外，需要使用一个变量记录剩下的好的橘子的数量，这样的腐烂过程持续到所有的橘子都腐烂了，或者连续两轮剩余的好的橘子数量不变。代码如下：

```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int currLastOrange = 0, preLastOrange = 1, t = 0;
        // 记录一共有多少个橘子
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) currLastOrange++;
            }
        }
        // 访问记录数组，防止本轮被传染的句子传染别的橘子
        vector<vector<int>> visted = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(),0));

        preLastOrange = currLastOrange + 1;
        while((preLastOrange != currLastOrange)) {
            if (currLastOrange == 0) break;
            preLastOrange = currLastOrange;
            for (int i = 0; i < grid.size(); i++) {
                for (int j = 0; j < grid[i].size(); j++) {
                    // 是个坏橘子，且没被访问过
                    if (grid[i][j] == 2 && visted[i][j] == 0) {
                        currLastOrange = searchFourDir(grid, visted, i, j, currLastOrange);
                    }
                }
            }
            // 重置visted;
            visted = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(),0));
            t++;
        }
        if (currLastOrange != 0) return -1;
        return t;
    }

    int searchFourDir(vector<vector<int>>& grid, vector<vector<int>>& visted, int currI, int currJ, int currLastOrange) {
        visted[currI][currJ] = 1;
        vector<vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        for (int i = 0; i < directions.size(); i++) {
            int nextI = currI + directions[i][0], nextJ = currJ + directions[i][1];
            if (nextI >= 0 && nextJ >= 0 && nextI < grid.size() && nextJ < grid[0].size() && grid[nextI][nextJ] == 1) {
                currLastOrange--;
                grid[nextI][nextJ] = 2;
                visted[nextI][nextJ] = 1;
            }
        }
        return currLastOrange;
    }
};
```

上述方法在枚举每个腐烂橘子的时候时间复杂度较高。如果能够提前获取这些腐烂的橘子，进行广度优先搜索，那么将不会浪费遍历的过程。

**多源广度优先搜索算法**：该方法假设有一个超级源点橘子，在第0轮的时候感染了那些题中的初始的坏橘子，将他们放入感染队列中，那么对该队列进行广度优先搜索，并记录搜索的层数，那么就能够完成题目的要求。记录搜索的层数可以将在队列中存储的元素换为`pair<pair<int,int>,int>`，也可以初始化一个初始值为`-INT_MAX`的时间数组`times[][]`，用来记录每个单元格被腐蚀的时间，如果当前被腐蚀的时间与上一层腐蚀的时间不同，那么说明已经到了新的一轮。代码如下：

```cpp
class Solution3 {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int currLastOrange = 0, preLastOrange = 1, t = 0;
        queue<pair<int, int>> q;
        vector<vector<int>> times = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), -INT_MAX));
        vector<vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        // 记录一共有多少个好橘子，将坏橘子放进队列中
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) currLastOrange++;
                if (grid[i][j] == 2) {
                    q.emplace(i,j);
                    times[i][j] = 0;
                }
            }
        }
        // 进行广度优先搜索
        while (!q.empty()) {
            pair<int, int> p = q.front();
            int currI = p.first, currJ = p.second;
            if (times[currI][currJ] != t) {
                t++;
                if (currLastOrange == 0) break;
            }
            for (int i = 0; i < directions.size(); i++) {
                int nextI = currI + directions[i][0], nextJ = currJ + directions[i][1];
                if (nextI < grid.size() && nextI >=0 && nextJ < grid[0].size() && nextJ >= 0 && grid[nextI][nextJ] == 1) {
                    q.emplace(nextI, nextJ);
                    grid[nextI][nextJ] = 2;
                    times[nextI][nextJ] = t+1;
                    currLastOrange--;
                }
            }
            q.pop();
        }
        return currLastOrange == 0 ? t : -1;
    }
};
```

### 深度优先搜索

#### 岛屿的数量

![image-20240916172907055](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240916172907055.png)

对于每个为1的没有访问的点，进行深度优先搜索即可，记录这样的源点的数量即可，代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> direction = {{0,1},{1,0}, {0,-1}, {-1,0}};  // 右-下-左-上
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<char>> visted = grid;
        int res = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1') {
                    DFS(grid, visted, i, j);
                    res++;
                }
            }
        }
        return res;
    }

    void DFS(vector<vector<char>>& grid, vector<vector<char>>& visted, int currI, int currJ) {
        // 将当前位置标记为已经搜索
        visted[currI][currJ] = '0';
        for (int dirIndx = 0; dirIndx < direction.size(); dirIndx++) {
            int newI = currI + direction[dirIndx][0], newJ = currJ + direction[dirIndx][1];
            // 位置正确，且值是1，那么需要深搜。
            if (ifValidPos(grid, newI, newJ) && visted[newI][newJ] == '1') {
                DFS(grid, visted, newI, newJ);
            }
        }

    }
    bool ifValidPos(vector<vector<char>>& grid, int i, int j) {
        if (i >= 0 && i <= grid.size() && j >= 0 && j <= grid[0].size()-1) return true;
        return false;
    }

};
```

## 回溯

### 全排列

![image-20240913134147103](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240913134147103.png)

全排列问题每个数字都需要出现在结果中，且不同顺序的数字组合是不同的结果。一种直观的方法是DFS暴力搜索，不难发现，递归的终止条件是当前的结果数组中包含了所有的数字。可以使用一个栈保存目前正在递归中的所有的元素，所有元素都访问完后进行弹栈，代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        unordered_map<int, int> umap;
        for (int i = 0; i < nums.size(); i++) {
            // 求解以每个数字为首的全排列
            vector<int> resi;
            DFS(nums, resi, umap, i);
            umap.clear();
        }
        return res;
    }

    // 每次遍历不在栈中的元素，栈使用一个哈希表维护
    void DFS(vector<int>& nums, vector<int> resi, unordered_map<int, int> umap, int currIndex) {
        umap[nums[currIndex]]++;
        resi.push_back(nums[currIndex]);
        // 形成全排列
        if (umap.size() == nums.size()) {
            res.push_back(resi);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i != currIndex && umap.find(nums[i]) == umap.end()) {
                DFS(nums, resi, umap, i);
            }
        }
    }
};
```

上面的代码存在的一个比较大的问题是使用的传值，而不是传引用，虽然传值直接减少了显式地去写回溯的操作，但是，传值开销较大。

实际上`vector`也提供了回溯的方法：**`pop_back()`弹出数组的最后一个元素**。另外，对于记录元素是否访问过，直接使用`visited`数组+下标即可，不需要使用哈希表。更新后的代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> visited = vector<bool> (nums.size(), false);
        vector<int> resi;
        DFS(nums, resi, visited);
        return res;
    }

    // 每次遍历不在栈中的元素，栈使用一个哈希表维护
    void DFS(vector<int>& nums, vector<int>& resi, vector<bool>& visited) {
        // 形成全排列
        if (resi.size() == nums.size()) {
            res.push_back(resi);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i] == false) {
                visited[i] = true;
                resi.push_back(nums[i]);
                DFS(nums, resi, visited);
                resi.pop_back();
                visited[i] = false;
            }
        }
    }
};
```

### 子集

![image-20240913160937075](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240913160937075.png)

子集问题和全排列不一样，每个元素可以在集合中中也可以不在集合中，且集合是无序的，不同于全排序。所以在进行子集判断时，需要依次对数组中的每个后续元素进行放入和不放入的判断，而不存在全排列中的`for`循环的过程，否则会造成结果的重复。代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> currRes;
        DFS(-1, nums, currRes, res);
        return res;
    }

    void DFS(int currIndex, vector<int>& nums, vector<int>& currRes, vector<vector<int>>& res) {
        if (currIndex == nums.size()-1) {
            // 最后一个数了，不需要向后枚举
            res.push_back(currRes);
            return;
        }
        // 对于之后的每一个数，都有放入集合和不放入集合两种选择
        currRes.push_back(nums[currIndex+1]);
        DFS(currIndex+1, nums, currRes, res);
        currRes.pop_back();
        DFS(currIndex+1, nums, currRes, res);
    }
};
```

### 分割回文串

![image-20240916212950109](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240916212950109.png)

该题是典型的分治，不难发现要想得到一个满足条件的串集合需要进行的：对于一个完整的串，首先判断得到一个回文串`currStr = s[0...i]`，然后对于后面的`s[i+1,...end]`进行递归判断得到后面的回文串，依次加入`currVec`，直到`i+1`超过串的末尾。要获得所有满足条件的串集合则需要进行回溯：对于每一轮递归寻找过程，当找到了满足条件的`currStr = s[i...j]`还不够，我们还需要进一步判断`s[i...j+1]`……是不是回文串，因此，等到递归结束时，还需要对当前的串`currStr`继续加上后面的字符，继续递归处理。当然，如果一个串不是回文串，那么不能进行递归处理，需要一直添加字符，直到是回文串为止。代码如下：

```cpp
class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> partition(string s) {
        vector<string> currRes;
        int start = 0;
        DFS(currRes, start, s);
        return res;
    }

    void DFS(vector<string>& currRes, int start, string& s) {
        // 到最后一个字符了
        if (start == s.size()) {
            res.push_back(currRes);
            return;
        }
        if (start <= s.size()-1) {
            string tempString = "";
            for (int i = start; i < s.size(); i++) {
                tempString.push_back(s[i]);
                if (!judge(tempString)) continue;
                currRes.push_back(tempString);
                DFS(currRes, i+1, s);
                currRes.pop_back();
            }
        }
    }

    bool judge(string& s) {
        // 判断是不是回文串
        int left = 0, right = s.size()-1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

```

对于这一题，其实特别需要注意的是**重复的回文串判定过程**，正常的回文串判定过程就像上面的`judge()`函数所示，但是每次这样判断需要大量的时间，而对于一个串`s`的任意子串`s[i...j]`，判断是不是回文串有下面的状态转移方程：
$$
f(i,j)=\begin{cases}\text{True,}&\quad i\geq j\\f(i+1,j-1)\wedge(s[i]=s[j]),&\quad\text{otherwise}&\end{cases}
$$
因此，可以在正式递归处理之前对回文串进行预处理。完整的代码如下：

```cpp
class Solution {
public:
    vector<vector<string>> res;
    vector<vector<bool>> f;
    vector<vector<string>> partition(string s) {
        vector<string> currRes;
        f = vector<vector<bool>> (s.size(), vector<bool>(s.size(), true));
        // 回文串的预判断，注意边界条件
        for (int i = s.size()-2; i >= 0; i--) {
            for (int j = i + 1; j < s.size(); j++) {
                f[i][j] = f[i+1][j-1] && (s[i] == s[j]);
            }
        }
        int start = 0;
        DFS(currRes, start, s);
        return res;
    }

    void DFS(vector<string>& currRes, int start, string& s) {
        // 到最后一个字符了
        if (start == s.size()) {
            res.push_back(currRes);
            return;
        }
        if (start <= s.size()-1) {
            string tempString = "";
            for (int i = start; i < s.size(); i++) {
                tempString.push_back(s[i]);
                if (!f[start][i]) continue;
                currRes.push_back(tempString);
                DFS(currRes, i+1, s);
                currRes.pop_back();
            }
        }
    }
};
```

## 二分查找

### 搜索二维矩阵

![image-20240917171404087](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240917171404087.png)



与搜索二维矩阵II不同，这里多了一个条件：每一行的第一个整数大于前一行的最后一个整数——这使得我们不需要再进行z字型查找。只需要进行两次二分查找：

- 第一次对第一列进行二分查找，确定小于等于target的行
- 第二次对该行进行二分查找，确定该数

代码如下：

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // 首先对列进行二分查找
        vector<int> col;
        for (int i = 0; i < matrix.size(); i++) {
            col.push_back(matrix[i][0]);
        }
        int rowIdx = binarySearch(target, 0, col.size()-1, col);
        if (rowIdx < 0 || rowIdx >= matrix.size()) return false;
        // 对第colIdx行进行检索
        int colIdx = binarySearch(target, 0, matrix[rowIdx].size()-1, matrix[rowIdx]);
        if (colIdx < 0) return false;
        if (matrix[rowIdx][colIdx] == target) return true;
        return false;
    }
    int binarySearch(int target, int start, int end, vector<int>& nums) {
        if (start > end) {
            if (nums[start] <= target) return start;
            if (nums[start] > target) return start-1;
        }
        
        int mid = (start + end) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) return binarySearch(target, start, mid-1, nums);
        return binarySearch(target, mid+1, end, nums);
        
    }
};
```

### lowerbound与upperbound的实现

![image-20240918165540195](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240918165540195.png)

这题其实就是C++的STL中的`upperbound`和`lowerbound`的一种实现（并不完全一样，这两个函数找不到时不是返回-1）。这里二分查找的过程的关键在于对相等情况的处理：具体来说，对于`lowerbound`，对`=`部分的处理和`>`部分相同，应该在区间`[start, mid-1]`区间内进行递归；对于`upperbound`来说，对`=`部分的处理和`<`部分相同，应该在区间`[mid+1, end]`区间内进行递归。（反向思考一下，如果正好相反，那么会找不到相应的边界，或者先想一下两种情况下对于等于怎么处理，即单独拎出来等于的情况，然后和大于和等于的哪种相同，进行合并，这种想法会直观些）。

另一个关键点在于最后没找到的话怎么办？原先的代码给出了下面的处理方式（感觉比较难以理解）：

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0) return {-1,-1};
        int lb = getLowerBound(target, 0, nums.size()-1, nums);
        if (lb == -1) return {-1,-1};
        int ub = getUpperBound(target, 0, nums.size()-1, nums);
        return {lb,ub};
    }

    int getLowerBound(int target, int start, int end, vector<int>& nums) {
        if (start > end) {
            return -1;
        }
        int mid = (start + end) / 2;
        if (nums[mid] < target) return getLowerBound(target, mid + 1, end, nums);
        int res =  getLowerBound(target, start, mid-1, nums);
        if (res == -1) {
            // 如果没找到，那么看看mid
            if (nums[mid] == target) return mid;
            return -1;
        }
        return res;
    }

    int getUpperBound(int target, int start, int end, vector<int>& nums) {
        if (start > end) {
            return -1;
        }
        int mid = (start + end) / 2;

        if (nums[mid] > target) {
            return getUpperBound(target, start, mid-1, nums);  // 递归左半部分
        }
        int res =  getUpperBound(target, mid+1, end, nums);
        if (res == -1) {
            // 如果没找到，那么看看mid
            if (nums[mid] == target) return mid;
            return -1;
        }
        return res;
    }
};
```

在理解了[搜索旋转排序数组](###搜索旋转排序数组)一节对pivot的记录方法后，想到了另一种直接的写法，其实本质上和第一种方式一样，只是直接用引用，避免了复杂的return判断过程。以及这种逼近的思想能够很容易地写出相应的递归部分的代码。代码如下：

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0) return {-1,-1};
        int lb = -1;
        getLowerBound(target, 0, nums.size()-1, nums, lb);
        if (lb == -1) return {-1,-1};
        int ub = -1;
        getUpperBound(target, 0, nums.size()-1, nums, ub);
        return {lb,ub};
    }

    void getLowerBound(int target, int start, int end, vector<int>& nums, int& lb) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] >= target) {
                if (nums[mid] == target) lb = mid;
                getLowerBound(target, start, mid-1, nums, lb);
            }
            if (nums[mid] < target) getLowerBound(target, mid + 1, end, nums, lb);
        }
    }

    void getUpperBound(int target, int start, int end, vector<int>& nums, int& ub) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] <= target) {
                if (nums[mid] == target) ub = mid;
                getUpperBound(target, mid + 1, end, nums, ub);
            }
            if (nums[mid] > target) getUpperBound(target, start, mid-1, nums, ub);
        }
    }
};
```

### 部分有序数组的二分

#### 搜索旋转排序数组

![image-20240918163414065](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240918163414065.png)

首先给出一种直观的想法：如果我们知道数组中原本的**第一个元素的位置`pivotIndex`**，那么根据该位置，可以将数组**划分为两个有序部分**，每个部分进行一次二分查找即可实现对目标`target`的寻找。但是如何在`O(logn)`时间内找到该下标是关键。

可以利用**二分的过程找到`pivot`**。如下图所示，我们以nums[0]为参考点，pivot及其右侧的元素都小于nums[0]，而pivot左侧（除了nums[0]）的元素都大于nums[0]，那么二分查找的过程可以即为：

- 当`nums[mid]>nums[0]`时（参考index = q的情况），应该在区间[mid + 1, end]内进行二分查找，以逐渐逼近pivot
- 当`nums[mid]<nums[0]`时（参考index = p的情况），应该在区间[start, mid-1]内进行二分查找，以逐渐逼近pivot；同时由于已经进入了后半区间，只是不知道是否是pivot，所以此时应该将mid记录

查找pivot的二分的终止过程与一般二分的终止过程相同：`start > end`即终止递归。

![image-20240918164039144](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240918164039144.png)

找到`pivot`后分别对`pivot`两侧的有序数组进行二分查找即可。完整的实现代码如下：

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 首先二分寻找pivot
        int start = 1, end = nums.size()-1, pivotIdx = -1;
        searchPivot(nums, start, end, pivotIdx);
        // 然后对pivot两边进行两次二分查找
        int idxLeft = binarySearch(target, 0, pivotIdx, nums);
        if (idxLeft == -1) {
            int idxRight = binarySearch(target, pivotIdx + 1, end, nums);
            return idxRight == -1 ? -1 : idxRight;
        }
        return idxLeft;
    }

    // 搜索比nums[0]小的最小的数
    void searchPivot(vector<int>& nums, int start, int end, int& minIdx) {
        if (start <= end) {
            int mid = (start + end) / 2;
            // 没有等于的情况，每个数都是不同的
            if (nums[0] > nums[mid]) {
                minIdx = mid;   // mid比nums[0]小的时候，记录min的下标
                searchPivot(nums, start, mid - 1, minIdx);
            }
            searchPivot(nums, mid + 1, end, minIdx);
        }
    }

    int binarySearch(int target, int start, int end, vector<int>& nums) {
        if (start > end) return -1;
        int mid = (start + end) / 2;    // 不越界的写法：end + (start - end) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) return binarySearch(target, start, mid - 1, nums);
        return binarySearch(target, mid + 1, end, nums);
    }
};
```

方法2是直接利用二分的过程求解，其思想可以概括为：

- 将数组一分为二。（其中有一个一定是有序的；另一个则是有序或部分有序的）
- 此时如果target在有序部分里，则用二分法查找。
- 否则进入无序部分查找，返回1。

其中，有序无序的判断可以根据子数组的首元素和末尾元素的大小判断。根据上述思想，实现的代码如下：

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 一个数组一定有有序和无序两个部分：
        return whereTarget(nums, 0, nums.size()-1, target);
    }

    int whereTarget(vector<int>& nums, int start, int end, int target) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] == target) return mid;
            // 先找到有序的那个部分，判断target在不在有序的那部分中
            if (nums[mid] >= nums[start]) {  // 这一段是有序的，一定要加等于，mid可能等于start，即区间只有一个数，是有序的
                if (target >= nums [start] && target < nums[mid]) {
                    // 进行二分查找
                    return binarySearch(target, start, mid - 1, nums);
                }else { // 在无序的那一段中
                    return whereTarget(nums, mid + 1, end, target);
                }
            }else { // 这一段是无序的
                // 先在有序段中进行二分查找
                if (target >= nums [mid] && target <= nums[end]) {
                    return binarySearch(target, mid + 1, end, nums);
                }else {// 在无序的那一段中
                    return whereTarget(nums, start, mid - 1, target);
                }
            }
        }
        return -1;
    }

    int binarySearch(int target, int start, int end, vector<int>& nums) {
        if (start > end) return -1;
        int mid = (start + end) / 2;    // 不越界的写法：end + (start - end) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) return binarySearch(target, start, mid - 1, nums);
        return binarySearch(target, mid + 1, end, nums);
    }
};
```

#### 寻找旋转排序数组中的最小值

![image-20240918171913574](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240918171913574.png)

基于[搜索旋转排序数组](####搜索旋转排序数组)中的第一种做法，本题也可以从寻找`pivot`的角度出发直接求解：因为最小值就是上一题中的`pivot`。代码如下：

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int pIdx = -1;
        searchPivot(nums, 1, nums.size()-1, pIdx);
        return pIdx == -1 ? nums[0] : nums[pIdx];
    }

    void searchPivot(vector<int>& nums, int start, int end, int& pIdx) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] < nums[0]) {
                pIdx = mid;
                searchPivot(nums, start, mid - 1, pIdx);
            }else {
                searchPivot(nums, mid + 1, end, pIdx);
            }
        }
    }
};
```

假如本题是要找到排序数组中的最大值，那么`pIdx`只需要在`nums[mid] > nums[0]`时进行更新即可，这样能通过不断记录比`nums[0]`大的元素，逐渐逼近最大的那个。代码如下：

```cpp
void searchPivot(vector<int>& nums, int start, int end, int& pIdx) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] < nums[0]) {
                searchPivot(nums, start, mid - 1, pIdx);
            }else {
                pIdx = mid;
                searchPivot(nums, mid + 1, end, pIdx);
            }
        }
    }
```

