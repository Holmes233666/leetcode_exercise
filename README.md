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

### 字母异位词分组

![image-20241125142852052](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241125142852052.png)

【排序+哈希表】：经过排序后异位词就是相同的一个词了，可以使用该词作为哈希表的key，要返回的未排序过的词构成的数组作为value，在遍历的过程中，不断往key对应的数组中加入值。最后提取哈希表中所有的value即可。时间复杂度为$O(nklogk)$，其中$k$为单词的最大长度，$n$是单词的数量。代码如下：

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> umap;
        vector<vector<string>> res;
        int n = strs.size();
        for (int i = 0; i < n; i++) {
            string temp = strs[i];
            sort(strs[i].begin(), strs[i].end());
            umap[strs[i]].push_back(temp);
        }
        for (auto it : umap) {
            res.push_back(it.second);
        }
        return res;
    }
};
```

【计数】：利用每个异位词的词频相同，将词频作为哈希表的key，相应的异位词构成的数组作为value。额外的开销是每次对于一个单词都要记录他的每次字母出现的频率。代码如下：

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        unordered_map<string, vector<string>> resMap;
        vector<vector<string>> resVec;
        // 先给所有的单词做字母统计，然后放入特定的value中
        for (int i = 0; i < n; i++) {
            vector<int> count(26, 0);
            for (int j = 0; j < strs[i].size(); j++) {
                count[strs[i][j]-'a']++;    // 统计词频
            }
            // 遍历统计结果，查找哈希表
            string key;
            for (int j = 0; j < 26; j++) {
                key.push_back(j + 'a');
                key.push_back(count[j] + '0');
            }
            resMap[key].push_back(strs[i]);
        }
        // 遍历哈希表，提取结果
        for (auto it : resMap) {
            resVec.push_back(it.second);
        }
        return resVec;
    }
};
```

题解省去了创建string的过程，自定义了一个array<int, 26>类型的哈希函数，即直接使用数组作为key，代码如下：

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 自定义对 array<int, 26> 类型的哈希函数
        auto arrayHash = [fn = hash<int>{}] (const array<int, 26>& arr) -> size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (string& str: strs) {
            array<int, 26> counts{};
            int length = str.length();
            for (int i = 0; i < length; ++i) {
                counts[str[i] - 'a'] ++;
            }
            mp[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};
```

### 最长连续序列

![image-20241126161150144](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241126161150144.png)

【暴力想法】：暴力想法是将所有的数放入哈希表中，然后遍历数组元素`nums[i]`，尝试找出`nums[i]+1, nums[i]+2, ..., nums[i]+ n`。该方法的时间复杂度是$O(n^2)$。

【哈希表+判断序列第一个数字】：上述暴力的方法主要的时间花在了重复的操作：因为使用`nums[i]`判断后，如果存在`nums[i+x]==nums[i]+1`，遍历到`nums[i+x]`时又会重新进行一次寻找后续数值的过程，但这个结果不会比`nums[i]`更优。因此，每次查找是否有后续数时应该保证该数字是序列的第一个元素，即如果哈希表中存在`nums[i]`的前序数字`nums[i]-1`，那么不对该数进行后续数的查找遍历。保证了每个数仅遍历一次，时间复杂度为$O(n)$，空间复杂度也为$O(n)$。代码如下：

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        unordered_set<int> uset;
        for (int i = 0; i < nums.size(); i++) {
            uset.insert(nums[i]);
        }
        int maxLen = 1;
        for (auto it : uset) {
            int len = 0;
            if(uset.find(it-1) == uset.end()) { // 没有前序，那么他是序列的第一个数
                int num = it;
                while(uset.find(num) != uset.end()) {
                    len++;
                    num++;
                }
            }
            maxLen = max(maxLen, len);
        }
        return maxLen;
    }
};
```

### 存在重复元素II

![image-20241126161534451](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241126161534451.png)

【哈希表】：顺序扫描，哈希表中只存储目前最大的index即可，如果该下标不满足，那么其他的比index更小的之前的下标更不可能满足$abs(i - j) <= k$。代码如下：

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> umap;   // key: 数值，value：为该数值的最新的索引
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (umap.find(nums[i]) != umap.end()) { // 集合里有这个数
                if (abs(umap[nums[i]] - i) <= k) {
                    return true;
                }
                umap[nums[i]] = i;
            }else { // 集合里没有这个数
                umap[nums[i]] = i;
            }
        }
    }
};
```

### 快乐数

![image-20241126161909798](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241126161909798.png)

【哈希表】：直观的方法是直接使用哈希表判断是否有重复数字或者到达了1，下面的代码使用了字符串，额外增加了空间开销，但是时间开销能降低。代码如下：

```cpp
class Solution {
public:
    bool isHappy(int n) {
        // 使用字符串存储n，方便提取数字
        string currNumStr = to_string(n);
        sort(currNumStr.begin(), currNumStr.end());
        unordered_map<string, bool> umap;
        umap[currNumStr] = true;
        while(true) {
            string newStr;
            int accumulateNum = 0, len = currNumStr.size();
            for (int i = 0; i < len; i++) {
                accumulateNum += pow(currNumStr[i] - '0', 2);
            }
            if (accumulateNum == 1) return true;
            newStr = to_string(accumulateNum);
            // 对newStr排序
            sort(newStr.begin(), newStr.end());
            if (umap.find(newStr) != umap.end()) {  // 已经有这个数字了
                return false;
            }
            umap[newStr] = true; // 没有这个数
            currNumStr = newStr;
        }
        return false;
    }
};
```

【快慢指针】：快慢指针的思想类似于在链表中判断链表是否含环的问题，关键思路在于：如果有重复数就意味着形成了一个数环，只要存在环，那么快指针和慢指针一定会在成环的位置相遇，如果是归于1，那么就在1处相遇，否则在别的位置相遇。代码如下：

```cpp
class Solution {
public:
    bool isHappy(int n) {
        int fast = getNext(n), slow = n;
        while (fast != slow && fast != 1) {
            slow = getNext(slow);                  // 每次走一步
            fast = getNext(getNext(fast));     // 每次走两步
        }
        return fast == 1;
    }

    int getNext(int n) {
        int res = 0;
        while(n > 0) {
            int d = n % 10;
            n = n / 10;
            res += d * d;
        }
        return res;
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

### 合并两个有序数组

![image-20241011213453819](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241011213453819.png)

**双指针：**合并两个有序数组的直接做法是使用额外空间的数组，使用双指针+扫尾即可。这种实现的代码如下：

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> sorted = nums1;
        int p0=0, p1=0, p=0;
        while (p < m+n) {
            if (m != 0 && n != 0 && nums1[p0] <= nums2[p1]) {
                sorted[p++] = nums1[p0++];
            }else if (m != 0 && n != 0 && nums1[p0] > nums2[p1]){
                sorted[p++] = nums2[p1++];
            }

            if (p0 == m) {  // 扫尾只剩下p1
                while (p1 < n) {
                    sorted[p++] = nums2[p1++];
                }
            }else if (p1 == n) {
                while (p0 < m) {
                    sorted[p++] = nums1[p0++];
                }
            }
        }

        // 拷贝回nums1
        for (int i = 0; i < sorted.size(); i++) {
            nums1[i] = sorted[i];
        }
    }
};
```

**排序：**另一种方法是直接合并，然后排序，这种方法的时间复杂度会比双指针的时间复杂度更高一些。

**逆向双指针：**在双指针的方法中使用了额外的空间，而不是进行原地操作（因为原地操作回覆盖数组1中的数）。在数组1的大小为`m+n`时，如果进行逆向扫描，那么可以直接原地完成两个数组的合并，代码如下：

```cpp
class Solution2 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int end1 = m-1, end2 = n-1, end = m + n -1;
        while (end1 >= 0 || end2 >= 0) {
            if (end1 >= 0 && end2 >= 0) {
                if (nums1[end1] > nums2[end2]) {
                    nums1[end--] = nums1[end1--];
                }else {
                    nums1[end--] = nums2[end2--];
                }
            }else if (end1 >= 0) {
                nums1[end--] = nums1[end1--];
            }else if (end2 >= 0) {
                nums1[end--] = nums2[end2--];
            }
        }
    }
};
```

### 移除元素

![image-20241017161031084](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241017161031084.png)

在处理移除元素怎么做前，我们处理过：使用一个pivot将数组分成左右两个部分，一部分大于这个pivot，一部分小于这个pivot。这是快速排序中的场景。这里要求原地删除所有数值等于pivot的数，且其检查的方法只扫描数组的前若干个元素，并不真的完全扫描完数组，所以类似的，可以使用快速排序中的双指针+pivot的做法：可以选择`val`为pivot，利用双指针将数组右边的数设置为`val`，左边的数不等于`val`。具体地，我们遇到值不等于pivot时，就将其换到前方；否则位置不变。这样最后数组中的前若干个数即为不需要删除的元素。代码如下：

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // 双指针：其中一个指针后面都是不等于val的数，一个指针负责前进，进行交换
        int right = -1, left = 0;
        while (left < nums.size()) {
            if (nums[left] != val) {
                right++;
                swap(nums[left], nums[right]);
            }
            left++;
        }
    }
};
```

### 删除有序数组中的重复项

![image-20241017162658626](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241017162658626.png)

本题要求原地删除，即不能使用额外的一个数组。双指针的实现比较符合直观的想法：两个指针，一个向前走（fast），一个不动（slow），fast指针一直向前走，直到遇到不等于slow指针指向的元素，此时slow++，nums[slow]赋值为nums[fast]。fast指针扫完数组，那么重复的元素也就全部删除了。代码如下：

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size(), slow = 0, fast = 0;
        while (fast < n) {
            if (nums[slow] == nums[fast]) {
                fast++;
            }else { // 不相等
                slow++;
                nums[slow] = nums[fast];
            }
        }
        return slow+1;
    }
};
```

### 删除有序数组中的重复项II

![image-20241017163503716](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241017163503716.png)

**双指针+计数**：如果直接仿真，那么采取的措施仍基于双指针，slow指针不动，fast指针向前直到找到不同于slow指针所指元素的位置，同时记录有多少个重复元素。如果slow所指元素不重复（fast只比上次所在的位置多走了1步），那么`nums[slow] = nums[fast-1]`，然后`slow++`即可；否则如果有多个元素重复，`nums[slow] = nums[fast-1], nums[++slow]=nums[slow-1]，slow+=1`；由于快慢指针最多只走完整个数组，即`2n`，所以时间复杂度为`O(n)`。完成代码如下：

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, fast = 0, n = nums.size(); // slow记录的始终是第一个待更改的数
        while (fast < n) {
            int temp = nums[fast];
            while(fast < n && nums[fast] == temp) { // 找到第一个与当前下标不同的元素
                fast++;
                steps++;
            }
            nums[slow] = nums[fast-1];
            if (steps > 1) {    // 不止一个数，那么保留两个
                nums[slow+1] = nums[slow];
                slow += 2;
            }else {
                slow++;
            }
        }
        return slow;
    }
};
```

### 三数之和

![image-20250116183040010](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250116183040010.png)

【双指针+排序】：三数之和可以效仿两数之和，首先固定一个数，然后内层执行两数之和，但是由于题目要求不能包含重复的结果，这种解法去重比较复杂（使用set也会引入额外的时间复杂度）；另一种容易想到的方式是先进行排序，然后遍历数组，固定一个数，内循环使用双指针求解，这种方法给去重提供了简化手段。需要注意两个地方的去重：

- 内循环，双指针内部的去重：在满足三数之和时，如果left指针right指针的后一个数与自己相同，那么需要跳过这些数，防止加入重复答案。
- 外循环：如果nums[i]和nums[left]相同，那么如果在枚举完nums[i]后接着枚举nums[left]，也会产生重复解，因此在每个外部循环要结束时，需要进行一次跳过重复元素的操作

详细代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        cout << endl;
        for (int i = 0; i < n; ) {
            int right = n - 1, left = i + 1;
            while (left < right) {
                if (nums[i] + nums[left] + nums[right] == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    // 跳过所有相同的数
                    while (left < right && (nums[left] == nums[left+1])) left++;
                    if (left == right) break;
                    while (left < right && nums[right] == nums[right-1]) right--;
                    if (left == right) break;
                    left++;
                  	right--;
                }else if (nums[i] + nums[left] + nums[right] > 0) {
                    right--;
                }else{
                    left++;
                }
            }
            while (i+1 < n && nums[i] == nums[i+1]) {
                i++;
            }
            i++;
        }
        return res;
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

【逆序放入】：第二次刷时利用的是等式`sums[j] - sums[i] == k`转变成的等式`sums[j] == k + sums[i]`，即每次遍历到`sums[i]`时，寻找数`sums[i]+k`在不在哈希表中，此时要保证找到的`j`一定比`i`大，所以可以逆序遍历`sums`数组，检查并放入哈希表，这样找到的`nums[j]`的下标`j`一定是比`i`大的有效子数组。详细代码如下：

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> umap;
        vector<int> preSum(n+1, 0);
        // umap[nums[0]]++;
        preSum[0] = 0;
        // 前缀和放入哈希表
        for (int i = 0; i < n; i++) {
            preSum[i+1] = preSum[i] + nums[i];
        }
        int res = 0;
        for (int i = n; i >= 0; i--) {
            if (umap.find(k+preSum[i]) != umap.end()) {
                res += umap[k+preSum[i]];
            }
            umap[preSum[i]]++;
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

### 长度最小的子数组

![image-20241128103820137](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241128103820137.png)

### 找到字符串中所有字母异位词

![image-20250121151008963](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250121151008963.png)

【滑动窗口模板】：使用基础的滑动窗口模板即可，模板参见[无重复字符最长子串](###无重复字符最长子串)

```cpp
class Solution2 {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> res;
        unordered_map<char, int> umap;
        // 记录p的字典
        for (int i = 0; i < m; i++) {
            umap[p[i]]++;
        }
        int charNum = umap.size();
        unordered_map<char, int> currMap;
        // 滑动窗口
        for (int left = 0, right = 0; right < n; right++) {
            // 当前字符
            char currChar = s[right];
            while(right-left+1 > m) {  // 扩展左边界
                currMap[s[left]]--;
                if (currMap[s[left]] == umap[s[left]]-1) charNum--;
                left++;
            }
            // 扩展右边界
            currMap[currChar]++;
            if (currMap[currChar] == umap[currChar]) {
                charNum--;
            }
            if (charNum == 0) {
                res.push_back(left);
            }
        }
        return res;
    }
};
```

### 无重复字符最长子串

![image-20241128103923154](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241128103923154.png)

【滑动窗口】：基本的做法就是使用滑动窗口的模板，标准模板如下：

```cpp
//外层循环扩展右边界，内层循环扩展左边界
for (int l = 0, r = 0 ; r < n ; r++) {
	//当前考虑的元素
	while (l <= r && check()) {//区间[left,right]不符合题意
        //扩展左边界
    }
    //区间[left,right]符合题意，统计相关信息
}
```

套用模板，本题写法如下：

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
      int n = 
        set<char> myset;
    }
};
```

【滑动窗口：右扩+左缩】：

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size(), maxLen = 0;
        int left = 0, right = 1;
        unordered_map<char, int> umap;
        umap[s[left]] = 1;
        while(left < n) {
            // 右边扩张
            for (; right <= n; right++) {
                if (right == n || umap.find(s[right]) != umap.end()) {    // 有重复字符
                    if (right < n) umap[s[right]] = 2;  // 特殊标记
                    maxLen = max(right-left, maxLen);
                    break;
                }
                umap[s[right]] = 1;
            }
            // 左边收缩
            while(left < right) {
                if (umap[s[left]] == 1) {
                    umap.erase(s[left++]);
                }else{
                    umap[s[left++]] = 1;
                    break;
                }
            }
            right++;
        }
        return maxLen;
    }
};
```



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

- 不使用队列的优化：使用滑动窗口的模板

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> umap, currMap;
        int n = s.size(), m = t.size();
        // 记录t的词典
        for (int i = 0; i < m; i++) {
            umap[t[i]]++;
        }
        // 记录总共的字母数量
        int totChars = umap.size();
        int start = 0, len = s.size()+1;
        for (int left = 0, right = 0; right <= n; right++) {
            while(left < right && totChars == 0) {
                if (right - left < len) {
                    start = left;
                    len = right - left;
                }
                currMap[s[left]]--;
                if (umap.find(s[left]) != umap.end() && currMap[s[left]] == umap[s[left]]-1) { // 是目标字母，且达不到要求了
                    totChars++;
                }
                left++;
            }
            if (right == n) break;
            currMap[s[right]]++;
            if (umap.find(s[right]) != umap.end() && currMap[s[right]] == umap[s[right]]) {
                totChars--;
            }
        }
        return len == s.size()+1 ? "" : s.substr(start, len);
    }
};
```

### 串联所有单词的子串

![image-20250124202955026](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250124202955026.png)

【滑动窗口】：这题与[找到字符串中所有字母异位单词](####找到字符串中所有字母异位词)相似，只不过本题将字母换为了单词。换为单词后如果还使用滑动窗口+哈希表，带来的主要问题是：按照字母的滑窗会导致整个窗口内的所有词发生变化，导致每移动一个字母，整个窗口的哈希表需要重置；如果按照单词为单词进行滑窗，那么可能会漏掉某个单词内的起始索引。

前者可以实现，但是时间复杂度较高。后者可以进行优化：在按照单词进行滑窗的外层再加一层循环，遍历每个位置，即：

```cpp
for (int i = 0; i + win_size < slen; i++) {	// 外层套循环，避免漏掉单词内部的位置
  for (int left = i, right = i; right < slen; right++) {	// 以单词为单位进行滑窗
    
  }
}
```

但是这样做的时间复杂度相比于第一种做法只是少了重置哈希表的时间，观察到：由于每次都已单词为单位进行滑窗，所以外层的`i`在`[i, word[0].size()-1]`区间的滑窗结果会和`[i-word[o].size(), 2word[0].size()-1]`……区间的滑窗结果重合，即有：

![image-20250124205154283](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250124205154283.png)

因此外层循环不用到`i + win_size < slen`，遍历到`i < word[0].size() && i + win_size() <= slen`即可。这样能够避免大量的重复滑动结果。详细代码如下：

```cpp
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = words.size(), m = words[0].size();
        int slen = s.size();
        int win_size = m * n;
        if (slen < win_size) return {};
        vector<int> res;
        unordered_map<string, int> umap;
        for (int i = 0; i < n; i++) {
            umap[words[i]]++;
        }
        for (int i = 0; i < m && i + win_size <= slen; i++) {
            unordered_map<string, int> currMap;
            // 记录新窗口内的单词
            int wordNum = umap.size();
            for (int start = i, end = i; end < start + win_size; end += m) {
                string currStr = s.substr(end, m);
                currMap[currStr]++;
                if (umap.find(currStr) != umap.end() && umap[currStr] == currMap[currStr]) {
                    wordNum--;
                }
            }
            if (wordNum == 0) res.push_back(i);
            // 滑动窗口
            for (int right = i, left = i + win_size - 1; left + m < slen; right += m, left += m) {
                string moveStr = s.substr(right, m);
                string inStr = s.substr(left + 1, m);
                currMap[moveStr]--;
                currMap[inStr]++;
                if (umap.find(inStr) != umap.end() && currMap[inStr] == umap[inStr] && inStr != moveStr) wordNum--;
                if (umap.find(moveStr) != umap.end() && currMap[moveStr] == umap[moveStr]-1 && inStr != moveStr) wordNum++;
                if (wordNum == 0) res.push_back(right + m);
            }
            // 上一段的逻辑简化：
            // for (int right = i, left = right + win_size - 1; left + m < slen; right += m, left += m) {
            //     string moveStr = s.substr(right, m);
            //     string inStr = s.substr(left + 1, m);
            //     currMap[moveStr]--;
            //     if (umap.find(moveStr) != umap.end() && currMap[moveStr] == umap[moveStr]-1) wordNum++;
            //     currMap[inStr]++;
            //     if (umap.find(inStr) != umap.end() && currMap[inStr] == umap[inStr]) wordNum--;
            //     if (wordNum == 0) res.push_back(right + m);
            // }
        }
        return res;
    }
};
```

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

**暴力解法**：暴力的想法是对于每个位置使用双指针，分别向左和向右找到最高的柱子，然后记录当前位置能接的水。这种情况下的时间复杂度是$O(n^2)$。代码省略。

**单调栈类似模拟**：仍然使用双指针，但是不是对于每个位置都进行双指针，而是每次都找到一个降序位置，这样的降序位置构成一个能够接水的坑，然后找下一个坑。具体来说，首先跳过一开始的升序情况（升序情况无法接水），然后开始从第一个降序开始接雨水。详细代码如下：

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int tot = 0;
        int start = 0; 
        // 跳过最开始的非降序情况
        while(start < height.size() - 1 && height[start+1] >= height[start]) {
            start++;
        }
        // 从第一个降序开始尝试接雨水
        for (int left = start; left < height.size() - 1; ) {
            // 对于紧密的右侧低于left的情况是可以构成盛水的容器的，那么不断右移right指针，直到找到第一个高于等于左指针的height
            int right = left + 2;
            int minus_squ = height[left+1];
            int notfindhigh_squ = minus_squ;
            int maxHeightIndex = left + 1;

            // 寻找右指针位置
            while (right < height.size() && height[right] < height[left]) {
                minus_squ += height[right];
                // 为找不到比left更高的柱子做准备：记录中间过程中最高的柱子
                maxHeightIndex = height[maxHeightIndex] > height[right] ? maxHeightIndex : right;
                right++;
            }

            // 成功接到雨水：找到更高的
            if (right < height.size() && height[right] >= height[left]) {
                tot += (right - left - 1) * height[left] - minus_squ;
                // 移动指针位置
                while(right < height.size() - 1 && height[right+1] > height[right]) {
                    right++;
                }
                left = right;
                continue;
            }
            // 成功接到雨水：找到最后一个都没找到更高的，那么期间最高的一个就作为一个承接点
            if (right == height.size() && right - left > 1) {
                int minus = 0;
                for (int k = left+1; k < maxHeightIndex; k++) {
                    minus += height[k];
                }
                tot += height[maxHeightIndex] * (maxHeightIndex - left - 1) - minus;
                left = maxHeightIndex;
                continue;
            }
            left++;
        }
        return tot;
    }
};
```

**动态规划**：以上代码过于复杂，实际上在暴力想法的基础上进行优化，只需要找到左边和右边的最高的柱子即可。可以分别从左向右和从右向左扫描一遍数组，提前记录右边和左边的最大值（包括自己的位置）。最后对于某个位置能够接到的雨水：`min(leftMax[i], rightMax[i])-heights[i]`。详细代码如下：

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> leftMax(n, height[0]), rightMax(n, height[n-1]);
        // 分别找到每个柱子左边和右边的最高的柱子
        for (int i = 1, j = n-2; i < n && j >= 0; i++, j--) {
            leftMax[i] = max(height[i], leftMax[i-1]);
            rightMax[j] = max(height[j], rightMax[j+1]);
            // cout << leftMax[i] << " " << rightMax[i] << endl;
        }
        // 根据柱子的高度计算当前位置能接多少水，并累加
        int water = 0;
        for(int i = 0; i < n; i++) {
            water += min(leftMax[i], rightMax[i]) - height[i];
        }
        return water;
    }
};
```

## 数组/字符串的处理

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
  - 记录已经输出的数的下标，每次打印一个数字前判断该数是否已经打印，已经打印的话不进行输出，否则输出，并记录已经打印的数。（记录方式可以使用visit数组或者使用map记录）
  - 定义上下左右四个边界，输出完第一行，应该upper++；输出完最后一列，应该right--……

后者的空间复杂度更小，而且不用查询，两种方式的代码如下：

- 使用基于记录的方式：

```cpp
// *************************** 使用map记录 *****************************
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

// ************************** 使用visited数组 ******************************
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<vector<int>> dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        vector<int> res;
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<char>> visited(n, vector<char>(m, '0'));  // 初始标记为都没有访问过
        int num = n * m;
        int i = 0, j = 0;
        int k = 0;
        while (num--) {
            res.push_back(matrix[i][j]);
            visited[i][j] = '1';
            int nextI = i + dir[k % 4][0], nextJ = j + dir[k % 4][1];
            if (nextI < 0 || nextI >= n || nextJ < 0 || nextJ >= m || visited[nextI][nextJ] == '1') {    // 无效单元格
                k++;
                i += dir[k % 4][0];
                j += dir[k % 4][1];
            }else {
                i = nextI;
                j = nextJ;  
            }
        }
        return res;
    }
};
```

- 使用边界重定义的方式：

```cpp
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

### 生命游戏

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241119152617974.png" alt="image-20241119152617974" style="zoom: 50%;" />

因为细胞的死活是同时发生的，不能使用已经更新的状态对判断别的细胞。新词，如果不对数组进行拷贝，那么原地处理的方式需要引入额外的状态：比如可以使用2表示死细胞变活，使用-2表示活细胞变死。在判断细胞死活时根据额外的状态判断，并在最后将对应的额外状态映射到标准的状态即可，代码如下：

```cpp
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        vector<vector<int>> dir = {{-1,-1}, {-1,0}, {-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        // 用2表示死细胞变活，用-2表示活细胞变死
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int currCeil = board[i][j];
                int aroundLive = 0, aroundDead = 0;
                for (int k = 0; k < 8; k++) {
                    int newI = i + dir[k][0], newJ = j + dir[k][1];
                    if (newI >=0 && newI < n && newJ >= 0 && newJ < m) {    // 合法位置
                        int ifAlive = board[newI][newJ];
                        if (ifAlive == 2 || ifAlive == 0) aroundDead++;
                        if (ifAlive == -2 || ifAlive == 1) aroundLive++;
                    }
                }
                if (currCeil == 1) {    // 是活细胞
                    if (aroundLive < 2 || aroundLive > 3) {
                        board[i][j] = -2;
                    }
                }else { // 是死细胞
                    if (aroundLive == 3) {
                        board[i][j] = 2;
                    }
                }
            }
        }
        // 更新整个矩阵的状态
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 2) {
                    board[i][j] = 1;
                }else if (board[i][j] == -2) {
                    board[i][j] = 0;
                }
            }
        }
    }
};
```

### 有效的数独

![image-20241119152720021](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241119152720021.png)

最直接的想法是直接按照题目给出的规则进行检验：先检验行，再检验列，最后检验每个小矩阵。但是这样每个元素会被检查3次，即需要扫描3次矩阵。

可以预先将所有的检查矩阵创建出来（类似DFS中的visisted矩阵），在对矩阵进行逐行扫描的时候根据行、列下标信息进行标记，重复标记返回错误即可，这样只需要扫描一次矩阵。另外需要注意数字是从1开始的，不是从0开始。代码如下：

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<char>> row(9, vector<char>(9, '0'));
        vector<vector<char>> line(9, vector<char>(9, '0'));
        vector<vector<vector<char>>> matrixs(9, vector<vector<char>>(3, vector<char>(9, '0')));

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char currChar = board[i][j];
                if (currChar == '.') continue;
                // 检查行
                if (row[i][currChar-'0'-1] != '1') {
                    row[i][currChar-'0'-1] = '1';
                }else {
                    return false;
                }
                // 检查列
                if (line[j][currChar-'0'-1] != '1') {
                    line[j][currChar-'0'-1] = '1';
                }else {
                    return false;
                }
                // 检查矩阵
                int matRowIdx = ceil(i/3), matLineIdx = ceil(j/3);
                if (matrixs[matRowIdx][matLineIdx][currChar-'0'-1] != '1') {
                    matrixs[matRowIdx][matLineIdx][currChar-'0'-1] = '1';
                }else {
                    return false;
                }
            }
        }
        return true;
    }
};
```



### 分发糖果

![image-20241112164706151](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241112164706151.png)

直观的想法是对于每个孩子，向左和向右进行比较，然后调整他的糖果值。但是对于下一个孩子，他进行调整后是可能影响上一个孩子的结果的。比如样例`[1,2,87,87,87,2,1]`，在对最后一个2进行调整后，上一个87的结果将会不对。即，从左向右的遍历只能保证从左向右的结果一定是对的，但是无法保证从右向左的结果是对的。补上一次从右向左的遍历后即可实现完整的功能，代码如下：

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size(), number = n;
        vector<int> res(n, 1);
        // 从左向右扫描，保证如果right比left大，那么一定有res[right] > res[left]
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i-1] && res[i] <= res[i-1]) {
                number++;
                res[i]++;
            }
        }
        // 从右向左扫描，保证如果left比right大，那么一定有res[left] > res[right]
        for (int i = n-2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1] && res[i] >= res[i+1]) {
                number++;
                res[i]++;
            }
        }
        return number;
    }
};
```

### O(1)时间插入、删除和获取随机元素

![image-20241113194850281](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241113194850281.png)

**哈希表+可变长数组**：哈希表能够快速地定位一个元素、移出一个元素。但是随机返回一个元素，比较方便的还是通过数组随机下标的方式获取元素。因此比较方便的是将哈希表与数组结合：哈希表中key为元素，value为该元素在数组中的下标。插入元素时间复杂度O(1)，随机返回时获取数组的长度设置随机数返回对应下标的元素即可，时间复杂度也是O(1)。

但是题目还涉及到元素的移出，哈希表中移出一个元素很容易，但是在数组中移出某个下标中的位置同时又要保证随机获取元素时可以借助数组的长度是困难的：一个元素移出数组，数组中的所有的元素都要向前移动，然后依次改变他们在哈希表中的下标，最差的时间复杂度是O(n)，不满足题目的要求。

给出一种方式：每次移出时，将数组尾部的元素改放到移出的位置，只改变这个元素在数组中的位置以及其哈希表对应的value值即可。这样就能实现时间复杂度为O(1)的所有操作。代码如下：

```cpp
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
        umap[vec[vec.size()-1]] = umap[val];
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
```

### 验证回文串

![image-20241114153306819](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241114153306819.png)

需要记住的只有一个问题：`A`的ASCII码比`a`小32。代码如下：

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        for(int i = 0, j = n-1; i <= j; ) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                s[i] = s[i] + 32;
            }
            if (s[j] >= 'A' && s[j] <= 'Z') {
                s[j] = s[j] + 32;
            }

            // 如果不是字母/数字，那么应该跳过
            if ((s[i] < 'a' || s[i] > 'z') && (s[i] < '0' || s[i] > '9')) {
                i++;
                continue;
            }
            if ((s[j] < 'a' || s[j] > 'z') && (s[j] < '0' || s[j] > '9')) {
                j--;
                continue;
            }
            if (s[i] != s[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};
```

### 找出字符串中第一个匹配项的下标

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241125170424954.png" alt="image-20241125170424954" style="zoom:50%;" />

【KMP算法】：使用KMP算法实现的主要思想是利用最长相同前后缀跳过暴力解法中的对某些位置的比较，保证匹配串（长串）的指针$i$永远只进行后移，而不会进行回溯，而只对模式串（短串）的指针$j$进行后回溯。回溯的位置使用next数组决定。

算法的关键在于如何以$O(n)$时间复杂度完成对next数组的计算：

- 首先：next数组中`next[j]`含义是在匹配串中j处不匹配时，应该将匹配串的指针j移动到`next[j]`位置处，即跳过`next[j]`个字符的比较，直接比较`next[j]`处是否相同

- 其次：`next[0]`将其初始化为0，表示在第一个位置就不同，那么直接移动到第一个位置

- 最后：下面详细说明next数组的计算过程，该过程巧妙利用了之前的计算的next数组结果

  - 维护一个匹配的串的长度`prefix_len`，表示到当前字符之前为止，最长的匹配的公共前后缀长度，初始化为0。

  - 使用指针i遍历模式串，如果：

    - `needle[prefix_len] == needle[j]`：那么直接看上一位，将其记为`next[j]=++prefix_len`

      ![image-20241125201604375](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241125201604375.png)

    - 如果二者不等，那么看下图：

      ![image-20241125201630573](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241125201630573.png)
      
      需要利用前面已经算好的结果，看看有没有可能有更短的前后缀。左边的ABA和右边的ABA在之前的比较中知道是相同的，那么在上图中，相当于把B放到C的位置，看看ABAB的最长公共前后缀，将prefix_len更新为next[prefix_len-1]=1，即A处的值（这是一个递归的过程，需要体会一下），然后再接着比较……

得到next数组后，可以代入主流程中。注意，主流程的结束条件是

- 主串到了末尾（一直没找到模式串）
- j指针到末尾了（找到了模式串）

上述KMP详细实现的代码如下：

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        vector<int> next;
        int m = haystack.size(), n = needle.size();
        getNext(needle, next);
        for (int i = 0, j = 0; i < m; ) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }else if (j > 0) {  // 不匹配
                j = next[j-1];
            }else { // 不匹配
                i++;
            }
            if (j == n) return i-j; // 如果到末尾都不匹配呢？
        }
        return -1;
    }

    void getNext(string& needle, vector<int>& next) {
        int n = needle.size();
        next.push_back(0);  // next[0] = 0;
        int prefix_len = 0;
        for(int i = 1; i < n; ) {
            if (needle[i] == needle[prefix_len]) {
                prefix_len++;
                next.push_back(prefix_len);
                i++;
            }else {
                if (prefix_len == 0) {
                    next.push_back(0);
                    i++;
                }else {
                    prefix_len = next[prefix_len - 1];  // 看看有没有更短的前后缀
                }
            }
        }
    }
};
```

【调库】：在C++中，串匹配的函数为`haystack.find(needle)`，如果找不到会返回一个特殊符号`haystack.npos`。直接调用的代码如下：

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        int res = haystack.find(needle);
        return res == haystack.npos ? -1 : res;
    }
};
```

### 排序

#### 计数排序

##### H指数

![image-20241113150556765](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241113150556765.png)

**计数排序：**首先类似计数排序的处理：遍历数字，记录每个引用次数下有多少篇论文，记在数组中。假设记录的数组为`nums`，那么`nums[i]`的值表示引用为$i$的论文有多少篇。

基于上述确定H指数是多少可以从数组末尾开始向前遍历，并累积一个currCite值（`currCite += nums[i]`），直到currCite值超过i为止。时间复杂度和空间复杂度都是$O(n)$，代码如下：

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int maxCite = *max_element(citations.begin(), citations.end());
        vector<int> nums(maxCite+1, 0);
        // 计数排序，得到引用i次的文章有多少篇的数组
        for (int i = 0; i < citations.size(); i++) {
            nums[citations[i]]++;
        }
        int currNum = 0;
        for (int i = maxCite; i >= 0; i--) {
            // 记录引用大于等于i的文章有多少篇
            currNum += nums[i];
            if (currNum >= i) {
                return i;
            }
        }
        return 0;
    }
};
```

**排序**：另一种方式是对数组进行排序，然后从大到小遍历。具体来说，首先初始化$h$值为0，如果`citations[i]>h`，那么`h++`，直到h不变为止（保证了至少有h篇论文的引用是超过h的）。时间复杂度为$O(n\log n)$。代码如下：

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int h = 0;
        for (int i = citations.size()-1; i >= 0; i--) {
            if (citations[i] > h) {
                h++;
            }else {
                break;
            }
        }
        return h;
    }
};
```

**二分查找**：H指数是最大的那个满足“至少有h篇论文的引用指数大于h”的h值。所以如果H指数是h，那么所有小于h的值`x`也一定满足至少有`x`篇论文的引用指数大于`x`。因此可以进行二分查找，遍历每一种h的可能，然后在每种可能中进行检查：是否满足“至少有h篇论文的引用指数大于h”。代码如下：

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size(), left = 0, right = n;

        return binarySearchIfH(citations, left, right);
    }

    int binarySearchIfH(vector<int>& citations, int start, int end) {
        if (start <= end) {
            int mid = (start + end) / 2;
            int cnt = 0;
            for (int i = 0; i < citations.size(); i++) {
                if (citations[i] >= mid) {
                    cnt++;
                }
            }
            if (cnt < mid) {   // 说明mid需要更小，那么end改为mid-1
                return binarySearchIfH(citations, start, mid - 1);
            }else {
                return binarySearchIfH(citations, mid + 1, end);
            }
        }
        return end;
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

### 反转链表



### 反转链表II

![image-20241209142644099](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241209142644099.png)



### 删除排序链表中的重复元素

![image-20241209160123959](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241209160123959.png)

【一个`pre`指针】：如果删除重复元素但每个元素保留一个，那么可以使用一个`pre`指针+一个`current`指针，`current`指针不断向前扫，直到找到与`pre`指针不同的元素，然后进行next关系的建立。代码如下：

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // 使用pre指针和current指针
        if (head == nullptr) return head;
        for (ListNode *current = head->next, *pre = head; current != nullptr; ) {
            if (current->val != pre->val) {
                pre = current;
                current = current->next;
            }else { // 如果current指针在和pre相同，那么current一直前进，直到二者不相同或者curr = nullptr
                while (current != nullptr && current->val == pre->val) {
                    current = current->next;
                }
                pre->next = current;
                pre = current;
                if (current == nullptr) break;
                current = current->next;
            }
        }
        return head;
    }
};
```

但是现在不希望保留任何相同的元素，此时，仍使用一个结点`pre`来建立`next`关系，但是`curr`的值需要记录下来，跳过所有满足与`curr`值相同的节点：`current`在跳过时令`current = current->next`，不断检验是不是与当前值相同，直到找到与当前值不同的`current`结点。具体代码如下所示。需要额外体会的是next关系记录的时刻是15行，而不在13行后建立next关系：出现`2->2->2->3->3->3`中`current`指向第一个`3`，但是`3`仍然是重复值的情况。

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        // 使用pre，current和next指针
        ListNode *pre = new ListNode(0, head), *current = head;
        ListNode *res = pre;
        while (current != nullptr) {
            if (current->next != nullptr && current->val == current->next->val) {
                int currentVal = current->val;
                while (current != nullptr && current->val == currentVal) {
                    current = current->next;
                }
            }else {
                pre->next = current;
                pre = current;
                current = current->next;
            }
        }
        pre->next = current;
        return res->next;
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

第二次刷的时候写的更直接了，代码如下：

```cpp
class Solution {
public:
    pair<ListNode*, ListNode*> reversReturn(ListNode* head, ListNode* tail) { // 返回新的头和尾
        ListNode *pre = nullptr, *currNode = head;
        while (currNode != tail) {
            ListNode *nextNode = currNode->next;
            currNode->next = pre;
            pre = currNode;
            currNode = nextNode;
        }
        currNode->next = pre;
        return {tail, head};    // 返回新的头和尾
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *p = head, *pre = new ListNode(0, head), *res = pre;
        while (p != nullptr) {
            int term = k;
            ListNode *currTail = p;
            while (--term && currTail != nullptr) {
                currTail = currTail->next;
            }
            if (currTail != nullptr) {  // 足以进行一组翻转
                ListNode *nextNode = currTail->next;
                pair<ListNode*, ListNode*> resTwoNodes = reversReturn(p, currTail);
                pre->next = resTwoNodes.first;
                resTwoNodes.second->next = nextNode;
                p = nextNode;
                pre = resTwoNodes.second;
            }else {
                break;
            }
        }
        return res->next;
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

### 随机链表的复制

![image-20241209140336066](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241209140336066.png)

【哈希表】：最直接的方式是建立原节点到新创建结点之间的映射，即`original Node ---> new Node`。第一遍循环建立一般的`next`关系和该映射，第二遍循环通过第一轮建立的映射关系通过`umap[currHead->random]`补全新链表的随机关系即可。代码实现如下：

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // 使用哈希表：original Node ---> new Node
        unordered_map<Node*, Node*> umap;
        Node *newHead = new Node(0), *currHead = head;    // 设置哑结点
        // 构建从 original node ---> new Node的链表
        for (Node *tail = newHead; currHead != NULL; tail = tail->next, currHead = currHead->next) {
            Node *newNode = new Node(currHead->val);
            umap[currHead] = newNode;
            tail->next = newNode;
        }

        // 访问原链表中的random信息，将映射的random信息填入
        for (Node *newNode = newHead->next, *currHead = head; currHead != NULL; currHead = currHead->next, newNode = newNode->next) {
            if (currHead->random != NULL) {
                newNode->random = umap[currHead->random];
            }else{
                newNode->random = NULL;
            }
        }
        return newHead->next;
    }
};
```

### LRU缓存

![image-20241212141315432](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241212141315432.png)

【双向链表 + 哈希表】：该题有两个方面的$O(1)$时间复杂度的需求：（a）需要快速查找/更新值；（b）`put`操作需要隐式维护一个访问的排序：从最新访问到最久没有访问。第一个需求不难联想到哈希表。第二个需求需要提取元素并且排序，两种选择：数组和链表。数组无法实现$O(1)$时间的元素移动；考虑用链表实现，但是链表也无法直接定位到需要移动的结点——需要遍历整个链表？可以将哈希表与链表结合：哈希表中不直接存储题中的key对应的value，而是存储节点的指针，这样就能直接定位到要移动的结点是哪个，并且通过指针访问对应的`value`。但是使用链表还有一个问题：

为什么使用双向链表？因为使用哈希表定位到该节点对应的指针后，该结点需要移动到头部/尾部，从而维持一个访问顺序，但是该结点的前序节点和后继节点还需要建立连接关系。如果使用单链表，直接访问到该结点对应的指针无法实现获得前序节点，该连接关系无法建立，还是需要扫描链表，无法满足时间复杂度的要求。而双向链表可以解决这个问题。

详细代码实现如下：

```cpp
struct LNode {
    int key;
    int val;
    LNode *pre;
    LNode *next;
    LNode () : key(-1), val(-1), pre(nullptr), next(nullptr) {};
    LNode (int key, int val) : key(key), val(val), pre(nullptr), next(nullptr) {};
    LNode (int key, int val, LNode *pre, LNode *next) : key(key), val(val), pre(pre), next(next) {};
};

class LRUCache {
public:
    unordered_map<int, LNode*> umap;  // key ---> LNode*
    int capacity;
    LNode *head = new LNode(), *q = head; // 尾插法

    LRUCache(int cap) {
        capacity = cap;
    }
    
    int get(int key) {
        if (umap.find(key) != umap.end()) { // 在哈希表中
            // 移动该结点到链表最后
            LNode *currNode = umap[key];
            if (currNode->next == nullptr) return currNode->val;    // 已经是最新访问的结点了，不需要移动到末尾
            currNode->pre->next = currNode->next;
            currNode->next->pre = currNode->pre;
            currNode->next = q->next;
            currNode->pre = q;
            q->next = currNode;
            q = currNode;
            return currNode->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (umap.find(key) != umap.end()) {
            if (get(key) != value) umap[key]->val = value;
        }else{  // 不在哈希表中，直接在尾部插入元素
            if (umap.size() == capacity) {
                // 移出头部元素
                LNode *removeNode = head->next;
                if (q == removeNode) q = head;
                umap.erase(removeNode->key);
                if (head->next != nullptr) {
                    head->next = removeNode->next;
                    if (head->next != nullptr) head->next->pre = head;
                }
                delete removeNode;
            }
            // 在尾部插入元素
            LNode *currNode = new LNode(key, value, q, nullptr);
            umap[key] = currNode;
            q->next = currNode;
            q = currNode;
        }
    }
};
```



## 树的处理

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

【递归】：核心思想是由底向上传递每个子树的状态：

- 递归终止条件：
  - 如果一个节点是`p`或者是`q`，那么该节点返回这个结点本身，即`p`或者`q`
  - 如果一个节点是空节点，那么返回空指针，表示不可能是最近公共祖先
  - 如果一个节点的左子树和右子树都返回了非空的结果，那么说明他的左子树和右子树分别含有`p`或`q`，该结点是最近公共祖先
- 进一步递归条件：
  - 搜索左子树：得到空指针或者非空指针
  - 搜索右子树：得到空指针或者非空指针

特别地，当`p`是两个公共节点的最近公共祖先或者`q`是两个结点的最近公共祖先时，`p`会一直沿着递归栈返回，因为另一侧子树的结果永远都是`nullptr`。

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return LCA(root, p, q);
    }

    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q || !root) return root;       // 自底向上传递当前结点的状态
        TreeNode* leftRes = LCA(root->left, p, q);
        TreeNode* rightRes = LCA(root->right, p, q);
        // 在左子树和右子树分别找到了需要的结点，那么这个结点就是最终的最近公共祖先
        if (leftRes != nullptr && rightRes != nullptr) return root;
        if (leftRes == nullptr) return rightRes;
        if (rightRes == nullptr) return leftRes;
        return nullptr;
    }
};
```

### 基于树的层序遍历的问题

#### 填充每一个节点的下一个右侧节点指针II

![image-20241215211902292](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241215211902292.png)

【基于队列的层序遍历】：如果通过递归建立相邻结点的之间的`next`关系通常是复杂的，比较直接的方法是层序遍历，使用队列存储层序遍历过程中的结点。进一步地，每次的遍历应该是以层为单位的：层内节点的`next`则是队首节点；但是在一层遍历完时，最后一个节点的`next`是`nullptr`。因此，在层序遍历中有必要对层进行维护，以便对下一个节点是`nullptr`的情况进行处理。维护层数的方式很简单：外层循环在弹出一个结点前获取当前队列中的元素数量，当前队列中有几个节点该层就有几个节点。使用内层循环依次对该层的这些节点进行遍历：压入左右指针、建立`next`关系即可。建立`next`关系时注意对最后一个节点的特殊护理。详细代码如下：

```cpp
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) return root;
        queue<Node*> t_queue;
        t_queue.push(root);
        while (!t_queue.empty()) {
            Node* currNode = t_queue.front();
            int num = t_queue.size();   // 记录目前队列中有多少个结点，即这一层的节点数
            for (int i = 0; i < num; i++) {
                t_queue.pop();
                if (currNode->left != nullptr) t_queue.push(currNode->left);
                if (currNode->right != nullptr) t_queue.push(currNode->right);
                if (i != num-1) {   // 如果不是最后一个节点，那么next指针指向队列的第一个元素
                    currNode->next = t_queue.front();
                }else { // 如果是这一层的最后一个节点，那么next结点应该指向nullptr
                    currNode->next = nullptr;
                }
                currNode = t_queue.front();
            }
        }
        return root;
    }
};
```

#### 二叉树的右视图

![image-20241218154724258](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241218154724258.png)



### 二叉树展开为链表

![image-20241216124608676](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241216124608676.png)

【前序遍历+新建二叉树】：基于前序遍历将数值存储在数组中，然后根据数组中的值重构二叉树是一个直接的方法。此方法的时间复杂度和空间复杂度都是`O(n)`。详细代码如下：

```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        vector<int> res;
        preTravel(root, res);
        // 根据res中的内容修改root节点
        modifyTree(root, res, 0);
    }

    void preTravel(TreeNode* root, vector<int>& res) {
        if (root != nullptr) {  // 进行先序遍历
            res.push_back(root->val);
            preTravel(root->left, res);
            preTravel(root->right, res);
        }
    }

    void modifyTree(TreeNode* &root, vector<int>& res, int idx) {
        if (idx <= res.size()-1) {
            if (root == nullptr) {
                root = new TreeNode(res[idx++]);
            }else{
                root->val = res[idx++];
            }
            if (root->left != nullptr) root->left = nullptr;
            modifyTree(root->right, res, idx);
        }
    }
};
```

在上面的代码中，由于函数列表中`Tree* &root`使用的引用传入，以修改树，创建新的节点，但是如果是空指针传入，后面可能会引发未知的问题。

【前序遍历+数组直接存储指针】：上述的做法需要重新开辟空间建立树节点，但是如果在数组中直接存储指针，那么就不需要重新开辟空间了。此时由于还是需要用到数组，所以时间复杂度和空间复杂度还都是`O(n)`。详细代码如下：

```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        vector<TreeNode*> res;
        preTravel(root, res);
        TreeNode* pre = res[0];
        for (int i = 1; i < res.size(); i++) {
            TreeNode* curr = res[i];
            pre->left = nullptr;
            pre->right = curr;
            pre = curr;
        }
    }

    void preTravel(TreeNode* root, vector<TreeNode*> &res) {
        if (root != nullptr) {
            res.push_back(root);
            preTravel(root->left, res);
            preTravel(root->right, res);
        }
    }
};
```

【寻找前驱结点】：找到前驱结点指的是在先序遍历中，遍历的顺序是根-左-右，要展开为链表即要将右子树的结点都放在左子树之后，找的前驱是右子树的前驱。因此寻找前驱结点来展开二叉树为链表可以分为下面的步骤：

- 对于当前结点，分为两种情况：
  - 如果左子树为空，那么左子树不会被展开，当前节点直接变为当前节点的右子树的结点
  - 如果左子树不为空，那么左子树是需要展开的，右子树需要跟在左子树的【先序遍历的最后一个节点】后面，即这里的【前驱】指的是右子树的前驱。具体来说：
    - 找到左子树中的右子树前驱
    - 将右子树置为该前驱结点的右子树
    - 将整合后的左子树整体移动到当前结点的右子树上
    - 当前结点的左子树置为空
- 遍历下一个节点

此时，代码的时间复杂度是$O(n)$，但空间复杂度上，如果寻找右子树的前驱过程时间复杂度是$O(1)$的，那么，整体的空间复杂度可以下降到$O(1)$，所以关键是如何以`O(1)`复杂度找到右子树的前驱。

详细代码如下：

```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* currNode = root;
        while (currNode != nullptr) {
            if (currNode->left != nullptr) {    // 如果左子树不为空
                TreeNode* left_pre = findPre(currNode->left);
                left_pre->right = currNode->right;
                currNode->right = currNode->left;
                currNode->left = nullptr;
            }   // 如果左子树是空指针，直接进入下一个节点
            currNode = currNode->right;
        }
    }

    TreeNode* findPre(TreeNode* root) { // 由主函数flatten输入的root一定不是空指针
        if (root->right != nullptr) {
            return findPre(root->right);
        }
        if (root->left != nullptr){ // 右子树为空，那么从左子树找
            return findPre(root->left);
        }
        return root;
    }
};
```

### 完全二叉树的节点个数

![image-20241218205907509](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241218205907509.png)

【基于遍历/二分+位运算】：如果不考虑完全二叉树的特点，直接搜索也能求得节点的个数，时间复杂度为$O(n)$。如果考虑完全二叉树的特点，可知最后一层如果有节点，那么最左侧的节点一定有节点。因此可以先确定层数$h$。然后根据层数以及完全二叉树的特点确定最后一层的节点数量范围。在该数据量范围内做二分查找。

如何做二分查找？

![image-20241218210853659](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241218210853659.png)

代码如下：

```cpp
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int level = 0;
        TreeNode* node = root;
        while (node->left != nullptr) {
            level++;
            node = node->left;
        }
        int low = 1 << level, high = (1 << (level + 1)) - 1;
        while (low < high) {
            int mid = (high - low + 1) / 2 + low;
            if (exists(root, level, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }

    bool exists(TreeNode* root, int level, int k) {
        int bits = 1 << (level - 1);
        TreeNode* node = root;
        while (node != nullptr && bits > 0) {
            if (!(bits & k)) {
                node = node->left;
            } else {
                node = node->right;
            }
            bits >>= 1;
        }
        return node != nullptr;
    }
};
```



### 二叉树中的最大路径和

![image-20241217214821668](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241217214821668.png)

【深搜】：**递归边界：**对于该问题的最小问题：对于一个空节点来说，那么这棵树的最大路径一定是0。

**问题分解（分治处理）：**对于二叉树中的任意一个节点 root，我们需要计算以该节点为根的最大路径和。这个值的计算需要综合考虑以下几种情况：

1. 左子树的最大路径和（以左子树根节点为起点）。
2. 右子树的最大路径和（以右子树根节点为起点）。
3. 仅包含当前节点的路径和。
4. 包含当前节点，以及左、右子树的路径和。

假设当前节点的值为 `currVal`，左子树的最大路径和为 `leftMax`，右子树的最大路径和为 `rightMax`，那么以当前节点为根的最大路径和可以表示为：
$$
connectSum=currVal+leftMax+rightMax
$$
这里的 `connectSum` 表示当前节点连接左右子树的路径和。

此外，针对以当前节点为起点的路径和，我们需要向上传递一个值供父节点使用。这个值应该是以下三者中的最大值：

1. 当前节点值 `currVal`，
2. 当前节点值加上左子树路径和 `currVal + leftMax`，
3. 当前节点值加上右子树路径和 `currVal + rightMax`。

**优化思路：**在更新最大路径和时，如果要对四种情况进行比较是很复杂的。为了简化计算，我们可以先对 `leftMax` 和 `rightMax` 进行预处理：如果某个子树的最大路径和小于 0，那么这条路径对最终结果没有贡献，可以直接将其置为 0。这样，路径和的计算会更加简洁。

预处理代码如下：

```cpp
if (leftMax < 0) leftMax = 0;
if (rightMax < 0) rightMax = 0;
```

经过上述处理后，我们只需要考虑以下两种情况：

1. 当前节点连接左右子树的路径和（`currVal + leftMax + rightMax`）。
2. 当前节点作为路径终点的路径和（`currVal` 或 `currVal + leftMax` 或 `currVal + rightMax`）。

**递归设计：**在递归过程中，我们需要完成以下两件事：

1. **更新全局最大值**：记录当前节点连接左右子树的路径和是否超过全局最大值。
2. **向上传递路径和**：返回以当前节点为起点的最大路径和，供父节点计算。

**完整代码如下：**

```cpp
class Solution {
public:
    // 以一个结点往下的最大路径和的四种情况：左子树路径、右子树路径、左+根、右+根、左+右+根
    // 自底向上进行计算
    int maxPathSum(TreeNode* root) {
        int maxNum = -INT_MAX;
        getMaxSum(root, maxNum);
        return maxNum;
    }

    int getMaxSum(TreeNode* root, int& maxNum) {  
        if (!root) return 0;
        int leftMax = max(getMaxSum(root->left, maxNum), 0);
        int rightMax = max(getMaxSum(root->right, maxNum), 0);
        int connectSum = root->val + leftMax + rightMax;
        maxNum = max(maxNum, connectSum);
        return max(leftMax+root->val, rightMax+root->val);
    }
};
```

### 验证二叉搜索树

![image-20241224191023068](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241224191023068.png)

【中序遍历】：根据二叉搜索树的性质，使用中序搜索会得到一个递增序列，所以可以先对二叉搜索树进行中序遍历，并在遍历的过程中判断是不是比上一个元素大，时间复杂度和空间复杂度都是`O(n)`。代码如下：

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int> nums;
        midTravel(root, nums);
        if (nums.size() == 0) return true;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] <= nums[i-1]) return false;
        }
        return true;
    }

    void midTravel(TreeNode* root, vector<int>& vec) {
        if (root != nullptr) {
            midTravel(root->left, vec);
            vec.push_back(root->val);
            midTravel(root->right, vec);
        }
    }
};
```

【自上而下判断】：对于某个结点位置处，判断是否为二叉搜索树需要三个条件：

- 当前节点的左节点小于当前结点，右节点大于当前节点
- 左子树是二叉搜索树
- 右子树是二叉搜索树

后面两个条件需要递归判断，但是需要携带对上层节点的信息：`[minNum, maxNum]`。详细代码如下：

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long maxNum = INT_MAX+1, minNum = -INT_MAX-1;
        return check(root, maxNum, minNum);
    }

    bool check(TreeNode* root, long maxNum, long minNum) {
        if (root != nullptr) {
            if (maxNum < root->val || minNum > root->val) return false;
            return check(root->left, root->val, minNum) && check(root->right, maxNum, root->val);
        }
    }
};
```

### 建立四叉树

![image-20250109144944151](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250109144944151.png)

【暴力递归】：暴力递归只需要结合判断函数`judge`判断四个区域的值是不是都是0或者都是1，然后根据判断结果递归建树即可。详细代码如下：

```cpp
#include<vector>

using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};


class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();
        Node* currNode;
        createTree(0, n-1, 0, n-1, grid, currNode);
        return currNode;
    }

    void createTree(int startI, int endI, int startJ, int endJ, vector<vector<int>>& grid, Node* &currNode) {
        if (startI <= endI && startJ <= endJ) {
            currNode = new Node(false, false);
            if (!judge(startI, endI, startJ, endJ, grid)) { // 不是叶子结点，需要继续递归
                createTree(startI, (startI+endI)/2, startJ, (startJ+endJ)/2, grid, currNode->topLeft);
                createTree(startI, (startI + endI)/2, (startJ+endJ)/2+1, endJ, grid, currNode->topRight);
                createTree((startI+endI)/2+1, endI, startJ, (startJ+endJ)/2, grid, currNode->bottomLeft);
                createTree((startI+endI)/2+1, endI, (startJ+endJ)/2+1, endJ, grid, currNode->bottomRight);
            }else { // 是叶子结点
                currNode->val = grid[startI][startJ];
                currNode->isLeaf = true;
            }
        }else {
            currNode = nullptr;
        }
    }

    bool judge(int startI, int endI, int startJ, int endJ, vector<vector<int>>& grid) {
        int cmp = grid[startI][startJ];
        for (int i = startI; i <= endI ; i++) {
            for (int j = startJ; j<= endJ; j++) {
                if (grid[i][j] != cmp) return false;    // 是不是叶子结点，需要继续递归
            }
        }
        return true;    // 是叶子结点
    }
};
```

【前缀和优化】：在暴力递归中最耗费时间的是对每个二维数组小块进行遍历，判断是否需要递归创建。可以使用前缀和对这部分进行优化。需要特别注意的是为了后续边界处理更加方便前缀和数组比grid数组多一个第0行和第0列，同时以`grid[i][j]`结尾的前缀和需要映射到前缀和数组的`pre[i+1][j+1]`。详细代码入下：

```cpp
class Solution {
public:
    vector<vector<int>> pre;
    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();
        Node* currNode;
        pre = vector<vector<int>>(n+1, vector<int>(n+1, 0));   // n+1是为了方便i==0和j==0的检查函数
        // 进行pre数组计算
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                pre[i][j] = pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1] + grid[i-1][j-1];
            }
        }
        createTree(0, n-1, 0, n-1, grid, currNode);
        return currNode;
    }

    void createTree(int startI, int endI, int startJ, int endJ, vector<vector<int>>& grid, Node* &currNode) {
        if (startI <= endI && startJ <= endJ) {
            currNode = new Node(false, false);
            int prefixNum = pre[endI + 1][endJ + 1] - pre[endI + 1][startJ] - pre[startI][endJ+1] + pre[startI][startJ];
            int square = (endI - startI + 1) * (endJ - startJ + 1);
            if (prefixNum != square && prefixNum != 0) { // 不是叶子结点，需要继续递归
                createTree(startI, (startI+endI)/2, startJ, (startJ+endJ)/2, grid, currNode->topLeft);
                createTree(startI, (startI + endI)/2, (startJ+endJ)/2+1, endJ, grid, currNode->topRight);
                createTree((startI+endI)/2+1, endI, startJ, (startJ+endJ)/2, grid, currNode->bottomLeft);
                createTree((startI+endI)/2+1, endI, (startJ+endJ)/2+1, endJ, grid, currNode->bottomRight);
            }else { // 是叶子结点
                currNode->val = grid[startI][startJ];
                currNode->isLeaf = true;
            }
        }else {
            currNode = nullptr;
        }
    }
};
```

## 图论算法

### 拓扑排序和环检测

拓扑排序的前提是图中没有环。

#### 环检测

环检测的实例：编译器的包依赖关系

##### 课程表

![image-20240912194516913](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240912194516913.png)

关键：除了一般的`visited`数组外，增加一个`onpath`数组：记录目前正在递归栈中的元素，如果正在递归栈中的元素再次被访问到了：那说明含环；而在深搜中`visited`数组起的作用是防止重复深搜（深搜针对的对象是【结点】，针对结点扫描邻接节点）（这么看的话，不考虑时间限制的话，其实可以不用`visited`）。

对每个节点进行包括`onpath`处理的深搜，同时使用引用变量`ifcircle`标记是否可以提前结束对每个节点的处理。详细代码如下：

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        vector<int> onpath(numCourses, 0);
        vector<int> visited(numCourses, 0);
        vector<vector<int>> matrix = vector<vector<int>> (numCourses, vector<int>());
        for (int i = 0; i < n; i++) {
            matrix[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        for (int i = 0; i < n; i++) {
            if (visited[prerequisites[i][0]] == 0) {    // 没有访问过
                onpath[prerequisites[i][0]] = 1;
                bool ifcircle = dfs(prerequisites[i][0], matrix, onpath, visited);
                if (ifcircle) return false;
                onpath[prerequisites[i][0]] = 0;
            }
        }
        return true;
    }

    bool dfs(int currNode, vector<vector<int>>& matrix, vector<int>& onpath, vector<int>& visited) {
        visited[currNode] = 1;
        for (int i = 0; i < matrix[currNode].size(); i++) {
            int nextNode = matrix[currNode][i];
            if (onpath[nextNode] == 1) return true;    // 含有环
            if (visited[nextNode] == 0) {
                onpath[nextNode] = 1;
                bool ifonpath = dfs(nextNode, matrix, onpath, visited);
                if (ifonpath) return true;  // 含有环
                onpath[nextNode] = 0;
            }
        }
        return false;   // 所有的深搜结果都没有环，返回false;
    }
};
```

##### 课程表II

![image-20250107152347710](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250107152347710.png)

在课程表1的基础上需要保存可行路径，那么仍是基于课程表1对每个课程进行深搜的基础，增加一个保存路径的过程（数组引用）。而对于没有在依赖关系中的结点，需要额外补充一个加入结果数组的过程。

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        vector<int> res;
        vector<int> onpath(numCourses, 0);
        vector<int> visited(numCourses, 0);
        vector<vector<int>> matrix = vector<vector<int>> (numCourses, vector<int>());
        for (int i = 0; i < n; i++) {
            matrix[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        for (int i = 0; i < n; i++) {
            if (visited[prerequisites[i][0]] == 0) {    // 没有访问过
                onpath[prerequisites[i][0]] = 1;
                bool ifcircle = dfs(prerequisites[i][0], matrix, onpath, visited, res);
                if (ifcircle) return {};
                res.push_back(prerequisites[i][0]);
                onpath[prerequisites[i][0]] = 0;
            }
        }
        // 将所有没有在依赖关系中的结点加入数组
        for(int i = 0; i < numCourses; i++) {
            if (visited[i] == 0) {
                res.push_back(i);
            }
        }
        return res;
    }

    bool dfs(int currNode, vector<vector<int>>& matrix, vector<int>& onpath, vector<int>& visited, vector<int>& res) {
        visited[currNode] = 1;
        for (int i = 0; i < matrix[currNode].size(); i++) {
            int nextNode = matrix[currNode][i];
            if (onpath[nextNode] == 1) return true;    // 含有环
            if (visited[nextNode] == 0) {
                onpath[nextNode] = 1;
                bool ifonpath = dfs(nextNode, matrix, onpath, visited, res);
                if (ifonpath) return true;  // 含有环
                onpath[nextNode] = 0;
                res.push_back(nextNode);    // 如果已经访问过，那么不用深搜，也不用加入res数组。
            }
        }
        return false;   // 所有的深搜结果都没有环，返回false;
    }
};
```



### 前缀树

#### 数据结构的实现

##### 前缀树

![image-20240912202047055](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240912202047055.png)

【哈希表实现】：一个直观的方法是使用哈希表实现，哈希表中存入已经插入的单词，然后再判断有无该前缀的时候遍历哈希表，依次判断是否存在该前缀。但是该方法时间复杂度很高。代码如下：

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

【前缀树】：另一个方式是使用指针数组：`vector<Tire*> child`，该数组初始化时即拥有26个位置，分别对应26个小写字母，该位置是否为空表示是否有字母存在。每个指针数组可以当做`Tire`类的属性，可使用循环迭代创建。同时，由于会有很多前缀单词，所以使用`isEnd`布尔量表征是否到达了单词末尾：在搜索时，如果到达了单词末尾，那么就成功匹配了；否则找到的是一个前缀。代码如下：

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

如果不将指针数组定义为`vector<Tire*> child`，定义为其他数据结构，比如``vector<LinkNode*> child``应该也是可以的。

```cpp
struct LinkNode{
  bool isEnd;
  vector<LinkNode*> child;
}
```

实现的代码：

```cpp
class Node {
public:
    vector<Node*> children;
    bool isEnd;

    Node() {
        children = vector<Node*>(26, nullptr);
        isEnd = false; // 默认不是单词的结尾，如果是的话需要修改标记位。
    }

    Node(char val) {
        children = vector<Node*>(26, nullptr);
        children[val - 'a'] = new Node();
        children[val - 'a']->isEnd = false;
        isEnd = false;
    }
};

class Trie {
public:
    Node* head;

    Trie() {
        head = new Node();
    }

    void insert(string word) {
        int n = word.size();
        Node *currNode = head;
        for (int i = 0; i < n; i++) {
            if (currNode->children[word[i]-'a'] == nullptr){    // 存在这个结点，但是之前没字母。（不会对等于2的情况进行修改）
                currNode->children[word[i]-'a'] = new Node();
            }
            if (i == n-1) {
                currNode->children[word[i]-'a']->isEnd = true;   // 有到该字母为止的单词
            }
            currNode = currNode->children[word[i] - 'a'];
        }
    }

    bool search(string word) {
        // 对head开始进行向下检索
        int n = word.size();
        Node* currNode = head;
        for (int i = 0; i < n; i++) {
            if (currNode->children[word[i]-'a'] == nullptr) return false;
            if (i == n-1 && currNode->children[word[i]-'a']->isEnd == true) {
                return true;
            }
            currNode = currNode->children[word[i] - 'a'];
        }
        return false;
    }

    bool startsWith(string prefix) {
        // 对head开始进行向下检索
        int n = prefix.size();
        Node* currNode = head;
        for (int i = 0; i < n; i++) {
            if (currNode->children[prefix[i]-'a'] == nullptr) return false;
            if (i == n-1 && currNode->children[prefix[i]-'a'] != 0){
                return true;
            }
            currNode = currNode->children[prefix[i]-'a'];
        }
        return false;
    }
};
```

#### 前缀树数据结构的应用

##### 添加与搜索单词-数据结构设计

![image-20250108161300296](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250108161300296.png)

【DFS+Tire树】在Tire树数据结构的基础上，在出现`.`的情况下需要对树进行深搜，详细代码入下：

```cpp
class WordDictionary {
public:
    WordDictionary* w;
    vector<WordDictionary*> child;
    bool isEnd;

    WordDictionary() {
        child = vector<WordDictionary*>(26);
        isEnd = false;
    }

    void addWord(string word) {
        int n = word.size();
        WordDictionary* curr = this;
        for (int i = 0; i < n; i++) {
            int idx = word[i] - 'a';
            if (curr->child[idx] == nullptr) {
                curr->child[idx] = new WordDictionary();
            }
            curr = curr->child[idx];
        }
        curr->isEnd = true;
    }

    bool search(string word) {
        return dfs(0, word, this);
    }

    bool dfs(int idx, string& word, WordDictionary* curr) {
        if (idx == word.size() && curr->isEnd == true) {
            return true;
        }
        if (idx == word.size() && curr->isEnd == false) {
            return false;
        }
        if (word[idx] == '.') { // 进行深搜
            // 尝试每个字母
            for (int i = 0; i < 26; i++) {
                // 任意一个单词非空，进行深搜
                if (curr->child[i] != nullptr) {
                    bool flag = dfs(idx+1, word, curr->child[i]);
                    if (flag) return true;
                }
            }
            return false;
        }else { // word[idx] 是一个单词
            int i = word[idx] - 'a';
            if (curr->child[i] == nullptr) return false;
            return dfs(idx+1, word, curr->child[i]);
        }
        return false;
    }
};
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
        // 访问记录数组，防止本轮被传染的橘子传染别的橘子
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

#### 除法求值

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250103112619229.png" alt="image-20250103112619229" style="zoom: 67%;" />

【邻接表 + 深度优先搜索】：本题需要注意的是含权邻接表的建立方式，如果不是含权的邻接表可以直接使用`vector<vector<int>>`的方式定义。含权的邻接表建立可以用`vector<list<pair<int, double>>>`的方式定义，也可以使用`vector<vector<pair<int, double>>>`的方式定义（第一个`int`代表结点的序号，在本题中，结点编号是使用`string`实现的）。定义邻接表后，对边进行插入，注意两项的权重互为倒数即可。

在邻接表上进行深度优先搜索，注意终止条件还要加上一个不存在节点即可。

```cpp
class Graph {
public:
    int vertices; // 图的顶点数量
    unordered_map<string, int> ump;     // 由string映射到邻接表的数组下标
    vector<list<pair<string, double>>> adjList; // 邻接表，存储 <目标顶点, 权重>

    // 构造函数，初始化图
    Graph(int v, unordered_map<string, int>& umap) {
        vertices = v;
        adjList.resize(v);
        ump = umap;
    }

    // 添加带权边（有向图）
    void addEdge(string src, string dest, double weight) {
        adjList[ump[src]].emplace_back(dest, weight);
        adjList[ump[dest]].emplace_back(src, 1/weight);
    }
};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int n = equations.size(), k = 0;
        unordered_map<string, int> umap;
        vector<double> resVec;
        // 建图，遍历得到顶点个数
        for (int i = 0; i < n; i++) {
            if (umap.find(equations[i][0]) == umap.end()) {
                umap[equations[i][0]] = k++;
            }
            if (umap.find(equations[i][1]) == umap.end()) {
                umap[equations[i][1]] = k++;
            }
        }
        vector<int> visited(k, 0);
        // k为顶点个数
        Graph g = Graph(k, umap);
        // 添加边
        for (int i = 0; i < n; i++) {
            g.addEdge(equations[i][0], equations[i][1], values[i]);
        }

        // 对每个查询进行深搜
        for (int i = 0; i < queries.size(); i++) {
            double res = -1.0;
            dfs(g, queries[i][0], queries[i][1], visited, 1, res);
            resVec.push_back(res);
            visited = vector<int>(k, 0);
        }
        return resVec;
    }

    void dfs(Graph& g, string& currNode, string& dest, vector<int>& visited, double val, double& res) {
        if (g.ump.find(currNode) == g.ump.end()) {
            return;
        }
        int idx = g.ump[currNode];
        list<pair<string, double>> l = g.adjList[idx];
        visited[idx] = 1;
        // 递归终止条件
        if (currNode == dest) {
            res = val;
            return;
        }
        for (auto it = l.begin(); it != l.end(); it++) {
            string nextNode = it->first;
            int nextIdx = g.ump[nextNode];
            if (visited[nextIdx] == 0) {    // 进行深搜
                dfs(g, nextNode, dest, visited, val*(it->second), res);
            }
        }
    }
};
```

#### 克隆图

![image-20250107153749237](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250107153749237.png)

【深搜】：本题的关键在于对「引用、容器等的理解」。克隆图需要对图进行搜索，此处是基于深搜实现的。参考数据结构的实现，不难看出是基于邻接表的图，即需要对邻接表进行深度优先搜索，然后克隆图。需要注意以下细节：

- 首先，传入的待复制结点的参照需要传入的是值：`Node *`【因为不需要对这个结点的地址进行修改】，但是由于需要对节点进行复制，即对一个指针变量的地址进行赋值，所以待创建结点需要传入的是引用，即`Node* &`。

- 深搜过程中需要建立邻居关系。

  - 如果结点没有创建，那么需要进行深度优先搜索，创建结点。然后将深搜后的结点加入邻居列表中。
  - 如果有些节点已经创建过了，需要将其加入到当前结点的邻接表中需要利用结点的序号关系：利用序号定位到该结点。

  不管有没有创建，都要为下次可能再通过其他结点访问该结点做准备。不难想到哈希表可以建立序号与结点之间的映射，同时建立邻居关系时需要使用哈希表建立。代码如下：

  ```cpp
  if (umap.find(currNextVec[i]->val) == umap.end()) { // 没找到
      Node* nextNode;
      dfs_create(currNextVec[i], nextNode, umap);
      newNode->neighbors.push_back(nextNode);
  }else{
      newNode->neighbors.push_back(umap[currNextVec[i]->val]);
  }
  ```

上述思路下详细代码如下：

```cpp
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


// 深度优先搜索
class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<int, Node*> ump;
        Node* res = nullptr;
        dfs_create(node, res, ump);
        return res;
    }

    // newNode应该在搜索完成结束后加入数组中，否则没法在数组中访问到
    void dfs_create(Node* orignNode, Node* &newNode, unordered_map<int, Node*>& umap) {
        if (orignNode != nullptr) {
            newNode = new Node(orignNode->val);
            umap[newNode->val] = newNode;
            vector<Node*> currNextVec = orignNode->neighbors;
            for (int i = 0; i < currNextVec.size(); i++) {
                if (umap.find(currNextVec[i]->val) == umap.end()) { // 没找到
                    Node* nextNode;
                    dfs_create(currNextVec[i], nextNode, umap);
                    umap[newNode->val]->neighbors.push_back(nextNode);
                }else{
                    umap[newNode->val]->neighbors.push_back(umap[currNextVec[i]->val]);
                }
            }
        }
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

### 单词搜索

![image-20250109132810488](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250109132810488.png)

【回溯】：典型的搜索题目，但是本题需要注意的有三点：

- 传值与传引用：首先尽量是都选择传引用，虽然传值可以减少回溯的开销，但是传值的时间太长，容易超过时间复杂度。
- **每个起点**后visisted要置空：由于visited数组使用传值会超时，所以必须使用传引用，但是传引用不要忽视回溯操作，重新置0。
- 深搜内部也需要回溯（当然如果visited传值就不需要了）

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        vector<vector<char>> visited(n, vector<char>(m, '0'));
        vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == word[0] && visited[i][j] == '0') {
                    bool flag = dfs(visited, board, word, 0, dir, i, j);
                    if (flag) return true;
                }
                visited = vector<vector<char>>(n, vector<char>(m, '0'));
            }
        } 
        return false;
    }

    bool dfs(vector<vector<char>>& visited, vector<vector<char>>& board, string& word, int currIdx, vector<vector<int>>& dir, int currI, int currJ) {
        if (currIdx == word.size()-1) {
            return true;
        }
        visited[currI][currJ] = '1';
        int n = board.size(), m = board[0].size();
        for (int i = 0; i < 4; i++) {
            int nextI = currI + dir[i][0], nextJ = currJ + dir[i][1];
            if (nextI >= 0 && nextI < n && nextJ >= 0 && nextJ < m && visited[nextI][nextJ] == '0' && board[nextI][nextJ] == word[currIdx+1]) {
                bool flag = dfs(visited, board, word, currIdx+1, dir, nextI, nextJ);
                visited[nextI][nextJ] = '0';
                if (flag) return true;
            }
        }
        return false;
    }
};
```

### 括号生成

![image-20250107224156365](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250107224156365.png)

【深搜】：本题的关键在于在括号匹配失败时进行剪枝，减少时间复杂度。因此可以维护一个回溯可用的栈（参考括号匹配题目，栈里只放左括号，不放右括号），在往结果串中放入括号前使用栈进行判断是否可以放入当前括号，不能放入的情况只有两种：

- 已经放入了n个括号，新放入的括号还是`(`：已经放入足够多的左括号了
- 栈空，放入的括号是`)`

其余情况都是可以放入任意括号的。

**特别注意递归终止条件**：

- 结果串的括号数量达标且【栈空】

详细代码如下：

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        stack<char> bra_s;
        vector<string> res;
        vector<char> brackets = {'(', ')'};
        string currStr = "";
        dfs(2*n, currStr, res, brackets, bra_s);
        return res;
    }

    void dfs(int n, string& currStr, vector<string>& res, vector<char>& brackets, stack<char>& bra_s) {
        if (n == currStr.size() && bra_s.empty()) {
            res.push_back(currStr);
            return;
        }else if (n == currStr.size()) {
            return;
        }
        for (int i = 0; i < brackets.size(); i++) {
            // 尝试放入括号
            if (judgeSta(brackets[i], bra_s, n/2)) {
                currStr.push_back(brackets[i]);
                if (brackets[i] == '(') {
                    bra_s.push('(');
                }else{
                    bra_s.pop();
                }
                dfs(n, currStr, res, brackets, bra_s);
                currStr.pop_back();
                if (brackets[i] == '(') {
                    bra_s.pop();
                }else{
                    bra_s.push('(');
                }
            }
        }
    }

    bool judgeSta(char bracket, stack<char>& bra_s, int n) {
        if (bra_s.size() == n && bracket == '(') return false;
        if (bra_s.empty() && bracket == ')') return false;
        return true;
    }
};
```

### 电话号码的字母组合

记录本题是想记录下哈希表的初始化方式，即用大括号的方式`{key, value}`进行初始化。详细代码如下：

```cpp
class Solution {
public:
    unordered_map<int, vector<char>> umap = {
        {'1', {}},
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}
    };
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        if (n == 0) return {};
        vector<string> res;
        string currStr = "";
        dfs(res, currStr, 0, n, digits);
        return res;
    }
    
    void dfs(vector<string>& res, string& currStr, int currIdx, int n, string& digits) {
        if (currStr.size() == n) {
            res.push_back(currStr);
            return;
        }
        vector<char> vec = umap[digits[currIdx]];
        int m = vec.size();
        for (int i = 0; i < m; i++) {
            // 尝试加入
            currStr.push_back(vec[i]);
            dfs(res, currStr, currIdx+1, n, digits);
            // 回溯
            currStr.pop_back();
        }
    }
};
```



## 二分查找

### 搜索插入位置

![image-20250114114423947](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250114114423947.png)

二分本身的逻辑很简单，关键是找不到的情况如何处理。这里分为两种大情况，分别对应递归搜索的两个if分支：

- 如果是因为`mid-1`导致上限一直向左缩短，最终区间不成立（`start > end`），那么会有两种子情况：
  - `mid-1<0`，即`end<0`，那么返回的值为0（其实即为start）
  - `mid-1>=0`，即`end>=0`（根据二分的思路，此时`nums[end]`只会是<0，不会是其他情况），那么应该返回`start`
- 如果是因为`mid+1`导致下限一直向右缩短，最终区间不成立，那么不论`start>=nums.size()`，插入的位置就都是`start`本身。

因此详细代码如下：

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return binarySearch(0, nums.size()-1, nums, target);
    }

    int binarySearch(int start, int end, vector<int>& nums, int target) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) return binarySearch(start, mid-1, nums, target);
            if (nums[mid] < target) return binarySearch(mid+1, end, nums, target);
        }
        return start;
    }
};
```

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

### 寻找峰值

![image-20250115153422194](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250115153422194.png)

【扫描】：扫描需要`O(n)`时间复杂度实现。

【二分】：当start < end时，直观地二分需要考虑四种情况，使用线段表示数组趋势，顶点从左到右分别代表`mid-1,mid,mid+1`，下面是四种情况：

- `/\`：那么mid就是峰值，直接返回即可；
- `\/`：左侧和右侧都有可能出现峰值，左右任意顺序递归；
- `/`：递增，那么一定存在一个峰值在[mid+1, end]中，向右递归；
- `\`：递减，那么一定存在一个峰值在[start, mid-1]中，向左递归；

此时，start == end是递归终止条件，此时start一定是峰值。但是需要注意递减的情况中的递归写法，递归的区间应该是[start, mid]，而不是[start, mid-1]，因为mid-1本身可能是峰值，向下取整后永远无法再考虑到mid-1这个峰值了。详细代码如下：

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        return binarySearch(nums, 0, nums.size()-1);
    }

    int binarySearch(vector<int>& nums, int start, int end) {
        if (start < end) {
            int mid = (start + end) / 2;
            if (mid > 0 && nums[mid] > nums[mid+1] && nums[mid] > nums[mid-1]) return mid;
            if (mid == 0 && nums[mid] > nums[mid+1]) return mid;
            if (mid == 0 && nums.size() == 2 && nums[mid+1] > nums[mid]) return mid+1;
            if (mid > 0 && nums[mid] > nums[mid-1] && nums[mid] < nums[mid+1]) {    // 递增
                return binarySearch(nums, mid+1, end);
            }
            if (mid > 0 && nums[mid] < nums[mid-1] && nums[mid] > nums[mid+1]) {    // 递减
                return binarySearch(nums, start, mid);
            }
            if (mid > 0 && nums[mid] < nums[mid-1] && nums[mid] < nums[mid+1]) {
                return binarySearch(nums, start, mid);
            }
        }
        return start; 
    }
};
```

【二分简化】：简化来说只要考虑两个数的比较即可：

- 如果`nums[mid] < nums[mid+1]`，那么递归区间[mid+1, end]，因为右区间一定有一个峰值
- 反之，递归区间[start, mid]，因为mid也可能是峰值

当区间中只有一个数时达到终止条件，此时该数就是峰值。详细代码如下：

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        return binarySearch(nums, 0, nums.size()-1);
    }

    int binarySearch(vector<int>& nums, int start, int end) {
        if (start == end) return start;
        if (start < end) {
            int mid = (start + end) / 2;
            if (nums[mid] < nums[mid+1]) return binarySearch(nums, mid+1, end);
            return binarySearch(nums, start, mid);
        }
        return -1;
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

【二分，不进行是否有序的递归】：第二次刷的时候给出了下面的解法，其实更简单，分类讨论下就行了：

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(0, nums.size()-1, target, nums);
    }

    int binarySearch(int start, int end, int target, vector<int>& nums) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) {
                if (nums[mid] < nums[start]) {
                    return binarySearch(start, mid-1, target, nums);
                }
                int idx = binarySearch(start, mid-1, target, nums);
                if (idx != -1) return idx;
                return binarySearch(mid+1, end, target, nums);
            }else { // mid < target
                if (nums[mid] > nums[start]) return binarySearch(mid+1, end, target, nums);
                int idx = binarySearch(mid+1, end, target, nums);
                if (idx != -1) return idx;
                return binarySearch(start, mid-1, target, nums);
            }
        }
        return -1;
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

### 寻找两个正序数组的中位数

![image-20240919195326467](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240919195326467.png)

如何从分治的角度思考查找中位数？首先，根据数组长度和为奇数还是偶数划分，中位数是两个数组中的第`(m+n)/2+1`个数或者第`(m+n)/2+1`和第`(m+n)/2`个数的平均数。因此，问题转换为了找到两个数组中的第K大的数，其中$K=(m+n)/2$或$K=(m+n)/2+1$。直接找到目标数并不容易，但是该问题的一个**最小的问题是，找到第1小的数**：直接比较两个数组的首元素，哪个小返回即可。所以分治的目标即是将第K大的元素通过规模减小，逐渐减小到找到第1小的元素。

另一方面，`O(log(m+n))`的时间复杂度直接提示该题使用二分：二分能够帮助排除区间的一部分长度，直到K为1为止。由于有两个数组，本题应该选择的`pivot`是`K/2-1`位置上的数，比较两个数组该位置上的数字的大小有三种情况：

- `nums1[pIdx]<nums2[pIdx]`：那么`nums1[pIdx]`位置处的元素一定不是第K大的数，因为它至多比`K-2`个数大，加上`nums1[pIdx]`，即他至多是是第K-1大的元素；因此nums1的前`K/2-1`个数可以排除，在后续的结果中递归寻找第`K-(K/2-1 + 1)`个数。
- `nums1[pIdx]>nums2[pIdx]`，类比第一类可以排除得到结果
- `nums1[pIdx]==nums2[pIdx]`，如果相等，也可以排除，参考第一类即可。

另外，有一种特殊的情况，如果该轮次的开始元素+`K/2-1`大于数组长度了，那么可以选择数组的最后一个元素，最后去除的时候去除实际去除的元素即可。

实现代码如下：

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 数组长度为偶数，返回中间两数和的平均
        if ((nums1.size() + nums2.size()) % 2 == 0) {
            int k1 = (nums1.size() + nums2.size()) / 2;
            int k2 = k1 + 1;
            return (getKth(nums1, nums2, k1, 0, 0) + getKth(nums1, nums2, k2, 0, 0)) / 2.0;
        }else {
            int k = (nums1.size() + nums2.size()) / 2 + 1;
            return getKth(nums1, nums2, k, 0, 0);
        }
    }

    double getKth(vector<int>& nums1, vector<int>& nums2, int K, int left1, int left2) {
        if (left1 == nums1.size()) return nums2[left2 + K - 1];
        if (left2 == nums2.size()) return nums1[left1 + K - 1];
        if (K == 1) return min(nums1[left1], nums2[left2]);
        // 如果有越界的情况：
        int pivotIdx1 = left1 + K/2 - 1 >= nums1.size() ? nums1.size() - 1 : left1 + K/2 - 1;
        int pivotIdx2 = left2 + K/2 - 1 >= nums2.size() ? nums2.size() - 1 : left2 + K/2 - 1;
        if (nums1[pivotIdx1] <= nums2[pivotIdx2]) {
            int newK = K - ((K/2 - 1) + 1);
            if (left1 + K/2 - 1 >= nums1.size()){
                newK = K - (nums1.size() - 1 - left1 + 1);
            }
            return getKth(nums1, nums2, newK, pivotIdx1+1, left2);
        }else {
            // 如果数组2没有越界：排除nums2前k/2-1个个元素以及nums1[left1 + K/2 - 1]
            int newK = K - ((K/2 - 1) + 1);
            if (left2 + K/2 - 1 >= nums2.size()){
                newK = K - (nums2.size() - 1 - left2 + 1);
            }
            return getKth(nums1, nums2, newK, left1, pivotIdx2+1);
        }
    }
};
```

## 栈

### 字符串解码

![image-20240920144149311](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240920144149311.png)

不难看出，最关键的问题在于如何处理嵌套式的编码，比如：`3[a2[b4[ab]]]`；如果是直观写法的话，应该先处理最内层的编码，然后由内而外进行处理。由内而外的处理过程提示我们之前扫描过的字符需要暂存；而一组闭合的`[]`提示一层编码结束了，形成了一个字符串，新的字符串也需要暂存（因为可能是某个内嵌的字符串，需要\*n处理的）。`[]`前面必有数字，这些数字也应该得到暂存，\*n处理的过程以及由内而外处理的过程提示我们暂存的结果最好以栈的形式进行存取（队列的话不方便由内）。

具体处理方法：分两个栈：数字栈，符号栈

- 遇到数字，一直i++，获取完整的数字后压栈
- 遇到符号
  - 扫描`[`：压字符栈`[`
  - 扫描字母：压字符栈
  - 扫描`]`：弹字符栈，直到遇到`[`，表示形成一个字母串。弹栈`[`，然后与数字栈顶的数字形成*n的串，弹出数字栈顶元素，最后形成的新的字符串压字符栈
- 扫描完毕，从栈中取出字符串逆序连接。

代码如下：

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<int> nums;
        stack<string> strs;
        for (int i = 0; i < s.size();) {
            int tempNum = 0;
            if (s[i] >= '0' && s[i] <= '9') {
                while (s[i] >= '0' && s[i] <= '9') {
                    tempNum = tempNum * 10 + s[i] - '0';
                    i++;
                }
                nums.emplace(tempNum);
            }else {
                string tempStr;
                if (s[i] == '[') {
                    tempStr.push_back('[');
                    strs.emplace(tempStr);
                    i++;
                }else if (s[i] == ']') {
                    while (!strs.empty() && strs.top() != "[") {
                        tempStr = strs.top() + tempStr;
                        strs.pop();
                    }
                    // 弹出'['
                    if (!strs.empty()) strs.pop();
                    // tempStr要重复num次
                    int num = nums.top();
                    nums.pop();
                    string newStr = tempStr;
                    while (--num) {
                        newStr += tempStr;
                    }
                    // 新的字符串压栈
                    strs.emplace(newStr);
                    i++;
                }else { // 遇到的是字符，直接压栈
                    string tempStr;
                    tempStr.push_back(s[i]);
                    strs.emplace(tempStr);
                    i++;
                }
            }
        }
        // 获得了所有的字符后，将字符串取出，进行连接。
        string res;
        while (!strs.empty()) {
            res = strs.top() + res;
            strs.pop();
        }
        return res;
    }
};
```

### 单调栈

#### 每日温度

![image-20240920161919322](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240920161919322.png)

#### 接雨水

在双指针一节中，接雨水使用了动态规划的方式求解，

#### 柱状图中最大的矩形

![image-20240924133014452](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240924133014452.png)

暴力的想法：

- 枚举宽度：对于每个柱子，向右遍历，记录当前的最低高度，并不断更新该高度，遍历到每一个柱子时，记录下此时的面积，不断更新最大面积
- 枚举高度：对于一个柱子，我们向左/右分别寻找比他高度小的第一个柱子，然后枚举面积。

枚举宽度的做法对于每个柱子都要向右枚举，时间复杂度为$O(n^2)$，代码如下（超时）：

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        for (int left = 0; left < heights.size(); left++) {
            if (heights[left] == 0) continue;
            int miniHeight = heights[left];
            res = max(res, heights[left]);
            for (int right = left + 1; right < heights.size(); right++) {
                miniHeight = min(heights[right], miniHeight);
                res = max(miniHeight * (right - left + 1), res);
            }
        }
        return res;
    }
};
```

对于枚举高度的做法， 向左向右寻找第一个更小的值的过程，使用两次$O(n)$的循环+单调栈实现，最后再计算面积，代码如下：

```cpp
class Solution2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<pair<int, int>> numStack;
        numStack.push({heights[0],0});
        vector<int> rightFirLow = vector<int>(heights.size(), heights.size()-1);
        vector<int> leftFirLow = vector<int>(heights.size(), 0);
        int res = 0;
        // 先从右到左，求解每个位置的下一个最小值出现的位置
        for (int i = 1; i < heights.size(); i++) {
            while (!numStack.empty() && heights[i] < numStack.top().first) {
                rightFirLow[numStack.top().second] = i-1;
                numStack.pop();
            }
            numStack.push({heights[i], i});
        }

        stack<pair<int, int>> numStack2;
        numStack2.push({heights[heights.size()-1], heights.size()-1});
        // 然后从左到右，求解每个位置的下一个最小元素出现的位置
        for (int i = heights.size()-2; i >= 0; i--) {
            while (!numStack2.empty() && heights[i] < numStack2.top().first) {
                leftFirLow[numStack2.top().second] = i+1;
                numStack2.pop();
            }
            numStack2.push({heights[i], i});
        }
        // 求解完左边和右边的第一个比当前元素的下标（包括当前元素），然后对每个矩形求解其能构成的最大面积
        for (int i = 0; i < heights.size(); i++) {
            res = max(heights[i] * (rightFirLow[i] - leftFirLow[i] + 1), res);
        }
        return res;
    }
};
```

上述的代码使用了两个循环记录，但其实在从左向右寻找右侧第一个最小值时，对于栈顶元素：`stack.top()`，他找到了右侧的第一个比它小的值`i`；而对于正好遍历到的元素`i`，待弹栈过程结束时，他找到了左侧第一个比它小的值；即代码可以优化如下：

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<pair<int, int>> numStack;
        numStack.push({heights[0],0});
        vector<int> rightFirLow = vector<int>(heights.size(), heights.size()-1);
        vector<int> leftFirLow = vector<int>(heights.size(), 0);
        int res = 0;
        // 先从右到左，求解每个位置的下一个最小值出现的位置
        for (int i = 1; i < heights.size(); i++) {
            while (!numStack.empty() && heights[i] < numStack.top().first) {
                rightFirLow[numStack.top().second] = i-1;
                numStack.pop();
            }
            leftFirLow[i] = numStack.empty() ? 0 : numStack.top().second + 1;
            numStack.push({heights[i], i});
        }

        // 求解完左边和右边的第一个比当前元素的下标（包括当前元素），然后对每个矩形求解其能构成的最大面积
        for (int i = 0; i < heights.size(); i++) {
            res = max(heights[i] * (rightFirLow[i] - leftFirLow[i] + 1), res);
        }
        return res;
    }
};
```

### 最小栈

![image-20241129150105746](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241129150105746.png)

本题的关键在于在常数时间内找到最小元素，除了该要求外，其他的需求都能直接使用一个栈进行模拟。考虑到常数时间内的元素检索，需要使用两个栈对最小栈进行模拟：

- 一个栈（`allNumStack`）正常对所有元素进行入栈、出栈操作，不对最小元素进行特别处理
- 一个栈（`miniStack`）只维护后续**可能称为最小元素**的元素：如果新入栈的元素比当前的最小元素（`miniStack.top()`）更大，那么该元素是不可能在后续的`pop/push`操作后成为最小的元素的：因为他不可能比目前的`minStack.top()`更小。可以看出`miniStack`是一个单调递减栈，元素是保持不严格降序的，因此栈顶始终是最小的元素，可以在尝试时间内返回最小的元素。

代码如下：

```cpp
class MinStack {
public:
    stack<int> allStack, minNumS;
    MinStack() {

    }
    
    void push(int val) {
        allStack.emplace(val);
        if (minNumS.empty() || val <= minNumS.top()) {
            minNumS.emplace(val);
        }
    }
    
    void pop() {
        if (!allStack.empty()) {    // 只要allStack不空，minNumS一定也不空
            int val = allStack.top();
            allStack.pop();
            if (val == minNumS.top()) {
                minNumS.pop();
            }
        }
    }
    
    int top() {
        return allStack.top();
    }
    
    int getMin() {
        return minNumS.top();
    }
};
```

官方题解中的最小栈对每个元素对应的最小值都进行了存储，其实没有必要。

### 简化路径

![image-20241129154234929](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241129154234929.png)

【`stringstream`+可变长数组模拟栈】：简化路径的关键在于首先将字符串`path`按照`/`进行分割。单个字符（`char`）的遍历会比较麻烦。而使用可变长数组（`vector`）模拟栈的原因是按照`/`进行分割后会出现以下四种情况，依次处理如下：

- 空字符串：`stringstream`的分割结果如果是连续的`///`那么会出现空字符串，直接跳过即可
- `.`：当前目录，跳过
- `..`：父目录，当栈非空的时候需要弹栈，弹出`/`和上一个目录；如果是根目录了（即栈空），跳过
- 其他情况：当做正常目录压栈，（除了是最后一个目录外）然后压一个`/`，用以分割。

最后当输出完毕的时候，如果末尾还是`/`，还需要抹除最后的`/`。代码如下：

```cpp
class Solution {
public:
    string simplifyPath(string path) {
        // 首先对path进行按照/的划分
        stringstream ss(path);
        vector<string> stringVec;
        string segment;
        while (getline(ss, segment, '/')) {
            stringVec.push_back(segment);
        }
        int n = stringVec.size(), currIdx = 1;
        vector<string> resPath = {"/"}; // 结果存在vec中，方便正向读取连接最终结果
        while (currIdx < n) {
            while (currIdx < n && stringVec[currIdx] == "") {
                currIdx++;
            }
            if (currIdx >= n) break;
            if (stringVec[currIdx] == ".") {    // 当前目录，直接跳过
                currIdx++;
            }else if (stringVec[currIdx] == "..") {
                if (resPath.size() != 1) {  // 如果不是根目录
                    resPath.pop_back(); // 弹出 “/"
                    resPath.pop_back(); // 弹出字符
                }
                currIdx++;
            }else { // 其他字符直接当做正常字符处理
                resPath.push_back(stringVec[currIdx]);
                if (currIdx != n-1) {
                    resPath.push_back("/");
                }
                currIdx++;
            }
        }
        // 遍历数组，合并产生正确的结果
        string res;
        for (int j = 0; j < resPath.size(); j++) {
            if (j == resPath.size()-1 && resPath[j] == "/" && resPath.size() != 1) break;
            res += resPath[j];
        }
        return res;
    }
};
```

### 基本计算器

![image-20241224132425308](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241224132425308.png)

【括号击穿+栈】：该题可以现将式子转换为逆波兰表达式，然后使用栈进行处理。但是这样的做法比较复杂。在有限的时间内能够快速实现的方法是括号击穿+栈。由于本题中不包含乘法和除法，只有括号和加减，因此在去掉括号后，只要能够正确判断符号的变化，完全可以实现从左到右的依次计算。

符号的变化参照下面的例子：

```cpp
1 + (2 - (3 - 4))
```

里面的 `3` 的符号直接由减号 `-` 决定，但括号里的 `-4` 也被外层的 `-` 翻转为 `+4`。

括号击穿的主要思想是将每个括号括起来的部分看做一个作用域，暂存括号外的符号，从而进行变号：比如括号外是`-`，那么当前在遇到`+`时，应该变号为`-`；如果当前遇到为`-`，那么应该编号为`+`。具体地，在上述例子中，2外符号为`+`，3外符号为`-`。

这种符号的结果应该被保存起来，方便根据前一个域的符号进行变号。而当离开一个作用域后，能够快速地判断前一个域的符号，进行变号。

这种括号域的符号暂存的实现的方式是使用栈：

- 当遇到`(`时，保存当前累计的符号：压栈；
- 当遇到`)`时，弹出栈顶，当前符号变为新的栈顶符号；

当前符号可以直接使用一个值为`{-1,1}`的数`sign`表示累计变化的结果。对于`sign`的变化：

- 遇到`+`，`sign`为栈顶符号
- 遇到`-`，`sign`变为栈顶符号的相反数

详细代码如下：

```cpp
class Solution {
public:
    int calculate(string s) {
        stack<int> ops;
        ops.push(1);    // 初始符号为正号
        int res = 0, sign = 1;            // 最后结果，和初始符号位
        for (int i = 0; i < s.size(); ) {
            if (s[i] == '(') {
                ops.push(sign);
                i++;
            }else if (s[i] == ')') {
                ops.pop();
                sign = ops.top();
                i++;
            }else if (s[i] == '+') {
                sign = ops.top();
                i++;
            }else if (s[i] == '-') {
                sign = -ops.top();
                i++;
            }else if (s[i] == ' '){
                i++;
            }else {
                long currNum = 0;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                    currNum = currNum * 10 + s[i] - '0';
                    i++;
                }
                res += sign * currNum;
            }
        }
        return res;
    }
};
```

## 堆

### 数组中的第K个最大元素

![image-20250117204234437](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250117204234437.png)

【Partition，lomute分区法】：使用快排中的partition操作能够有效选择出数组中的第K个最大元素。其中Lomute分区法是常用且容易理解的方法。需要注意的是该方法执行后最终的i的位置应该是指向最后一个小于等于pivot的位置，即`nums[i+1]>pivot`。代码如下：

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return select(nums, 0, n-1, n - k + 1);
    }

    int select(vector<int>& nums, int start, int end, int k) {
        if (start < end) {
            int pivot = nums[end];
            int i = start-1, j = start;
            while(j <= end) {
                if (nums[j] <= pivot) {
                    i++;
                    if(i != j) swap(nums[i], nums[j]);
                }
                j++;
            }
            int sortedNum = i - start + 1;
            if (k == sortedNum) return nums[i];
            if (k < sortedNum) return select(nums, start, i-1, k);
            return select(nums, i+1, end, k - sortedNum);
        }
        return 0;
    }
};
```

但是上述的分区方法在重复元素很多时会超时。本题能通过的是下面的分区算法：

【Partition，Hoare分区法】：注意do while的写法以及该分区法的本质：任何一侧都有可能存在等于pivot的元素，划分不会严格区分等于pivot的元素。另外，该方法调用的函数入口是要找的元素在数组中的索引，所以传入的是`n-k`而不是`n-k+1`，且之后的调用也不用改变，因为索引下标始终不变。详细代码如下：

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return select(nums, 0, n-1, n - k);
    }

    int select(vector<int>& nums, int start, int end, int k) {
        if (start == end) return nums[start];
        int pivot = nums[start];
        int i = start-1, j = end + 1;
        while(i < j) {
            do i++; while(nums[i] < pivot);
            do j--; while(nums[j] > pivot);
            if (i < j) swap(nums[i], nums[j]);
        }
        if (k <= j) return select(nums, start, j, k);
        return select(nums, j+1, end, k);
    }
};
```

### IPO

![image-20250118210600409](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250118210600409.png)

【大顶堆】：要想获得最大的利润，对于k次项目选择中任意一次项目选择都是在启动资金小于等于w的项目集合中挑选出利润最大的那个。而每次做完一个项目，收获的资本将使w变大，因此资金小于等于w的项目集合将是一个大小变化的集合，这符合“堆”的使用场景：在元素变换频繁的场景中维护最大/小值。

具体设计为：动态维护一个堆，堆中放入所有启动资金小于当前w的项目的利润，等到所有满足条件的项目都被放入后，取出目前利润最大的项目执行。然后重复上述过程，直到选到k个项目或者堆为空（最多k个项目，k可能大于满足条件的项目数）。详细代码入下：

```cpp
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<pair<int, int>> arr;
        priority_queue<int> pq;
        int n = profits.size();
        for (int i = 0; i < n; i++) {
            arr.push_back({capital[i], profits[i]});
        }
        sort(arr.begin(), arr.end());   // 升序排列
        int curr = 0;
        for (int i = 0; i < k; i++) {
            while(curr < n && arr[curr].first <= w) {
                pq.emplace(arr[curr].second);
                curr++;
            }
            if (!pq.empty()) {
                w += pq.top();
                pq.pop();
            }else {
                break;
            }
        }
        return w;
    }
};
```

### 数据流的中位数

![image-20240925183705630](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240925183705630.png)

【大顶堆 + 小顶堆】：小顶堆`qMax`中放大于等于中位数的那一半，大顶堆`qMin`中放小于中位数的那一半。那么当数据总数为奇数时，小顶堆堆顶元素即为中位数；否则，为两个堆的堆顶元素的平均值。

为了维护上述的数据结构能够正确返回中位数，关键在于保证“小顶堆`qMax`中放大于等于中位数的那一半，大顶堆`qMin`中放小于中位数的那一半”这个性质成立。因此在加数的时候需要满足：

- 当目前两个堆中元素个数和为偶数时：多的数是一定要放入小顶堆的（因为小顶堆放的元素要多于大顶堆），但是新加的数`num`可能不是大于等于中位数的，所以需要先将`num`放入小顶堆中，取出小顶堆堆顶的元素，钙元素一定是大于等于中位数，将其放入`qMax`中。
- 当目前两个堆中元素个数和为奇数时：需要加的数放入大顶堆（维持两个堆中数的平衡），但是新加的数`num`可能不是小于中位数的，所以先加入小顶堆，然后从小顶堆中取出最小的数加入大顶堆。


满足上述两个条件的`addNum`即可实现中位数的获取。详细代码如下：

```cpp
class MedianFinder {
public:
    priority_queue<int, vector<int>, greater<int>> qMax; // 小顶堆，放大于等于中位数的那一半
    priority_queue<int> qMin;               // 大顶堆，放小于中位数的那一半
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if ((qMax.size() + qMin.size()) % 2 == 0) {
            qMin.emplace(num);
            int topNum = qMin.top();
            qMin.pop();
            qMax.emplace(topNum);
        }else{
            qMax.emplace(num);
            int topNum = qMax.top();
            qMax.pop();
            qMin.emplace(topNum);
        }
    }
    
    double findMedian() {
        if ((qMax.size() + qMin.size()) % 2 == 0) return (qMax.top() + qMin.top())/2.0;
        return qMax.top();
    }
}
```

### 查找和最小的K对数字

![image-20250124210921388](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250124210921388.png)

【堆 + 标记】：暴力的方法是将所有的数对放入堆中，然后找出和最小的k对。但当加入元素索引对`[a1, b1]`时，下一个比`[a1, b1]`大的数一定是`[a1+1, b1]`或者是`[a1, b1+1]`。因此其实不需要将所有的数对都放入堆中。

初始化时将`[a0, b0]`放入堆中，并将其作为结果数组的第一个元素。然后每次需要放入时（结果数组中元素数量不足k个），都从堆中找一个最小的索引组`[ai,bi]`，然后将其弹出堆，加入`[a_{i+1}, bi]`和`[a_i, b_{i+1}]`，并标记已经放入堆的元素，避免重复加入，直到结果数组元素满足要求。详细代码如下：

```cpp
// 法1：堆 + 使用标记数组
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        // 使用 lambda 表达式捕获 nums1 和 nums2
        auto cmp = [&nums1, &nums2](const vector<int>& a1, const vector<int>& a2) {
            return nums1[a1[0]] + nums2[a1[1]] > nums1[a2[0]] + nums2[a2[1]]; // 小顶堆
        };

        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        vector<vector<int>> res;
        set<pair<int, int>> has_pushed;

        pq.emplace(vector<int>{0, 0});
        has_pushed.insert({0,0});
        int currNum = 0;

        while (!pq.empty() && currNum < k) {
            vector<int> currMinIdx = pq.top();
            pq.pop();
            res.push_back({nums1[currMinIdx[0]], nums2[currMinIdx[1]]});
            int nextidx1_1 = currMinIdx[0] + 1, nextidx1_2 = currMinIdx[1];
            if (nextidx1_1 < n && has_pushed.find({nextidx1_1, nextidx1_2}) == has_pushed.end()) {
                pq.emplace(vector<int>{nextidx1_1, nextidx1_2});
                has_pushed.insert({nextidx1_1, nextidx1_2});
            }
            int nextidx2_1 = currMinIdx[0], nextidx2_2 = currMinIdx[1] + 1;
            if (nextidx2_2 < m && has_pushed.find({nextidx2_1, nextidx2_2}) == has_pushed.end()) {
                pq.emplace(vector<int>{nextidx2_1, nextidx2_2});
                has_pushed.insert({nextidx2_1, nextidx2_2});
            }
            currNum++;
        }
        return res;
    }
};
```

【堆 + 免标记】：在上面思路的基础上，避免标记的方式是从一开始就不放入重复元素：首先将(0,0), (0,1), (0,2), ..., (0,m)加入堆中，后续放入元素时，不再放入`[a_{i}, b_{j+1}]`和`[a_{i+1}, b_{j}]`两个元素，而是只放入`[a_{i+1}, b_{j}]`，详细代码如下：

```cpp
class Solution2 {
public:
    struct cmp {
        bool operator()(vector<int>& a1, vector<int>& a2) {
            return a1[0] > a2[0];
        }
    };
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
        vector<vector<int>> res;
        pq.emplace(vector<int>{0, 0, 0});
        int currNum = 0;

        // 首先将(0,0), (0,1), (0,2), ..., (0,m)加入堆中
        for (int j = 0; j < m; j++) {
            pq.emplace(vector<int>{nums1[0]+nums2[j], 0, j});
        }

        // 弹出pq，每次再选择最小的一个压入
        while (!pq.empty() && currNum < k) {
            vector<int> currMin = pq.top();
            pq.pop();
            res.push_back({nums1[currMin[1]], nums2[currMin[2]]});
            int nexti = currMin[1]+1, nextj = currMin[2];
            pq.emplace(vector<int>{nums1[nexti]+nums2[nextj], nexti, nextj});
            currNum++;
        }
        return res;
    }
};
```

## 贪心算法

### 买卖股票的最佳时机

![image-20241001123455355](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241001123455355.png)

如何做出最佳决策？对于第$i$天，如果知道后面哪一天价格最高，那么可得第$i$天的最大利润；全局的最优解即为所有可能买入时间的利润的最大值。所以问题的关键在于，**对于每一天如何知道后面哪天的价格最高**。不难想到，先从右向左记录每个元素的后续最大值：`rightMax[i] = max(price[i], rightMax[i+1])`，同时`rightMax`中的所有元素初始化为`rightMax[i] = price[end]`。此外，同时维护一个`maxPro`变量，即可在边记录时，边更新最大利润。代码如下：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxPro = 0;
        vector<int> rightMax = vector<int>(prices.size(), prices[prices.size()-1]);
        for (int i = prices.size()-2; i >= 0; i--) {
            rightMax[i] = prices[i] >= rightMax[i+1] ? prices[i] : rightMax[i+1];
            maxPro = max(maxPro, rightMax[i] - prices[i]);
        }
        return maxPro;
    }
};
```

### 加油站

![image-20241113201255600](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241113201255600.png)



### 跳跃游戏

![image-20241001150829927](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241001150829927.png)

暴力想法：遍历数组的每一个位置，将可以到达的位置都打上标记，遍历完后检查最后一个位置是否被标记了即可，此时时间复杂度为$O(n^2)$。代码如下：
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> ifJump = vector<bool>(nums.size(), false);
        ifJump[0] = true;
        for (int i = 0; i < nums.size(); i++) {
            if (ifJump[i]) {
                for (int j = 1; j < nums[i]; j++) {
                    ifJump[i+j] = true;
                }
            }
        }
        return ifJump[nums.size()-1];
    }
};
```

上述的方法的主要时间浪费在给每个可达元素做标记，其中有很多是重复的。不妨维护一个变量`maxReach`，表示目前能够跳到的最大位置，在遍历数组的过程中只更新`maxReach`（而不是给每个元素都做标记），直到`maxReach`大于等于数组的最后位置的下标，或者遍历到`maxReach`后无法向前。代码如下：

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int lastMaxIdx = nums[0];
        for (int i = 0; i <= lastMaxIdx; i++) {
            lastMaxIdx = max(i + nums[i], lastMaxIdx);
            if (lastMaxIdx >= nums.size()-1) return true;   // 提前跳出循环的重要性
        }
        return false;
    }
};
```

这样时间复杂度优化到了$O(n)$。

### 跳跃游戏II

![image-20241001155611599](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241001155611599.png)

在[跳跃游戏](###跳跃游戏)的基础上，要求记录最少的步数。在上一题第二种解法的基础上，我们需要维护一个`lastReach`变量，记录过去一轮能够够到的最远的距离，`maxReach`为当前轮次能够够到的最远距离。在遍历的过程中，当`maxReach`超过最后一个下标的时候，那么就说明目前的步数+1就是最少步数了。随着遍历中`i`逐渐递增，会达到`lastReach`（等于），这时候需要更新`lastReach`为当前的`maxReach`，同时说明步数需要增加1。数组中只有一个元素的例子需要额外特殊处理。代码如下：

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int maxStep = 0, maxReach = 0, lastReach = 0;
        for (int i = 0; i < nums.size(); i++) {
            maxReach = max(maxReach, i + nums[i]);
            if (maxReach >= nums.size()-1) {
                return maxStep+1;
            }
            if (i == lastReach) {
                maxStep++;
                lastReach = maxReach;
            }
        }
        return maxStep;
    }
};

```

### 划分字母区间

![image-20240925183525280](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20240925183525280.png)

划分字母区间要求一个字母只能在一个区间内出现，所以知道该字母出现的最后一个位置非常重要。获取：

- 比$x$大/小的最后一个数
- 比$x$大/小的下一个数
- 字母出现的下一个位置

等等，都可以采取从右向左扫描记录的方式。

对于字母的最后一个位置的记录，可以使用数组或者哈希表。（下面的两种代码分别给出了两种方式）

划分字母区间即要获取一个片段的start位置和end位置：

- 对于start处的字母，获取`s[start]`的最后一个位置，记为`end`，然后扫描`[start, end]`区间内的所有字母，获取区间内的所有字母的最后出现的位置，更新end，直到扫描到end，即获取到了一个片段。
- end + 1位置为下一个start位置，重复上述步骤。

记录方式为哈希表和数组的两种方式的代码如下：

```cpp
class Solution {
public:
    vector<int> res;
    vector<int> nextLetterLoc;
    unordered_map<char, int> umap;
    vector<int> partitionLabels(string s) {
        nextLetterLoc = vector<int>(s.size(), 0);
        for (int i = s.size()-1; i >= 0; i--) {
            if (umap[s[i]] == 0) umap[s[i]] = i;    // 第一次出现
            // 记录umap中最后一次出现的位置
            nextLetterLoc[i] = umap[s[i]];
        }
        int start = 0;
        while (start < s.size()) {
            start = getAStr(s, start) + 1;
        }
        return res;
    }

    int getAStr(string& s, int start) {
        // 找到start和start字母最后一次出现的位置之间的所有字母的下一个位置
        int nextIdxofStart = nextLetterLoc[start], end = nextIdxofStart;
        // 记录中间出现的字母的下一个最大位置，初始最大位置为start字母出现的下一个最大位置。
        for (int i = start + 1; i < end; i++) {
            end = max(end, nextLetterLoc[i]);
        }
        res.push_back(end - start + 1);
        return end;
    }
};
```

```cpp
class Solution {
public:
    vector<int> res;
    vector<int> nextLetterLoc = vector<int>(26, 0);
    vector<int> partitionLabels(string s) {
        for (int i = s.size()-1; i >= 0; i--) {
            nextLetterLoc[s[i] - 'a'] = max(nextLetterLoc[s[i]-'a'], i);
        }
        int start = 0;
        while (start < s.size()) {
            start = getAStr(s, start) + 1;
        }
        return res;
    }

    int getAStr(string& s, int start) {
        // 找到start和start字母最后一次出现的位置之间的所有字母的下一个位置
        int nextIdxofStart = nextLetterLoc[s[start]-'a'], end = nextIdxofStart;
        // 记录中间出现的字母的下一个最大位置，初始最大位置为start字母出现的下一个最大位置。
        for (int i = start + 1; i < end; i++) {
            end = max(end, nextLetterLoc[s[i]-'a']);
        }
        res.push_back(end - start + 1);
        return end;
    }
};
```

### 用最少数量的箭引爆气球

![image-20241209161104002](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241209161104002.png)

【排序+贪心】：考虑随机地射出一支箭，移动箭的位置以尽可能多的射中气球：只要保证原本射中的气球仍被射中即可，再考虑能不能射中更多的气球。参考下图，箭需要尽可能地右移，最多能右移且原本射中的气球仍被射中的位置即是某个区间的**右边界**。

因此：**一定存在一种最优（射出的箭数最小）的方法，使得每一支箭的射出位置都恰好对应着某一个气球的右边界。**

考虑所有的区间中最靠左的一个区间，按照他为标准进行射箭，能够获得一轮射中最多的气球。因此对这些区间进行参考右边界的从小到大的排序，然后遍历，直到有区间的左边界大于最小区间的有边界，那么需要的箭数量增加。更新箭的数量。

![image-20241215214312466](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241215214312466.png)

详细代码如下：

```cpp
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[1] < b[1]; // 升序排列
    }
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), cmp);
        int n = points.size(), shotNum = 0;
        for (int i = 0; i < n; ) {
            int currStart = i, nextStart = i + 1;
            while (nextStart < n && points[nextStart][0] <= points[currStart][1]) { // 直到找到一个不满足的区间
                nextStart++;
            }
            i = nextStart;
            shotNum++;
        }
        return shotNum;
    }
};
```

### 最长递增子序列

![image-20250310213735611](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250310213735611.png)

【dp做法】：如果是递增子数组，那么动态规划非常方便。但是递增子序列中，`dp[i]`：以`nums[i]`结尾的最长子序列的长度，但是可能存在`dp[0....i]`中有更长的元素，所以需要遍历之前的结果，那么时间复杂度为`O(n^2)`，详细代码如下：

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1);    // dp[i]表示长度为i的递增子序列的末尾的最小的数
        int maxLen = 1; 
        dp[1] = nums[0];
        // 对每个元素进行遍历，更新dp[i]
        for (int i = 1; i < n; i++) {
            if (nums[i] > dp[maxLen]) {
                maxLen = maxLen + 1;
                dp[maxLen] = nums[i];
            }else {
                int idx = binarySearch(1, maxLen, dp, nums[i]);
                dp[idx] = nums[i];
            }
        }
        return maxLen;
    }

    int binarySearch(int start, int end, vector<int>& nums, int target) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) return binarySearch(start, mid-1, nums, target);
            return binarySearch(mid+1, end, nums, target);
        }
        return start;
    }
};
```

【贪心+二分查找】：定义一个数组`dp[i]`表示长度为`i`的子序列的末尾的数。根据贪心的想法，如果我们希望得到最长的递增子序列，那么`dp[i]`应该增长得越慢越好。

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1);    // dp[i]表示长度为i的递增子序列的末尾的最小的数
        int maxLen = 1; 
        dp[1] = nums[0];
        // 对每个元素进行遍历，更新dp[i]
        for (int i = 1; i < n; i++) {
            if (nums[i] > dp[maxLen]) {
                maxLen = maxLen + 1;
                dp[maxLen] = nums[i];
            }else {
                int idx = binarySearch(1, maxLen, dp, nums[i]);     // idx位置 >= target
                dp[idx] = nums[i];
            }
        }
        return maxLen;
    }

    // 找到的是 >= target的index
    int binarySearch(int start, int end, vector<int>& nums, int target) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) return binarySearch(start, mid-1, nums, target);
            return binarySearch(mid+1, end, nums, target);
        }
        return start;
    }
};
```





## 动态规划

### 基本入门

#### 打家劫舍

![image-20241001231602944](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241001231602944.png)

直观的想法是，使用一个二维数组$f[0][i]$和$f[1][i]$分别表示对第$i$家是否进行偷窃获得的最大金额，在比较的过程中记录最大的偷窃金额，初始情况如下：
$$
\begin{align}f(0)=\begin{cases}nums[0],&取\\
0,&不取
\end{cases}\end{align}\\
$$

$$
\begin{align}f(1)=\begin{cases}nums[1],&取\\
nums[0],&不取
\end{cases}\end{align}
$$

对于任意$n\geq 2$，递推方程为：
$$
f(n)=\begin{align}\begin{cases}\max(\begin{cases}f(n-2),不取\\f(n-2),取\end{cases})+nums[n]\\max(f(n-1),f(n-2))\end{cases}\end{align}
$$
代码如下：

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n==1) return nums[0];
        vector<vector<int>> f = vector<vector<int>>(2, vector<int>(n, 0));  // 2个数组，0是不取，1是取
        f[0][0] = 0;    // 对于第0家，不取
        f[1][0] = nums[0];  // 对于第0家，取
        f[0][1] = nums[0];  // 对于第1家，不取
        f[1][1] = nums[1];  // 对于第1家，取
        int maxPro = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            f[0][i] = max(max(f[0][i-1], f[1][i-1]), max(f[0][i-2], f[1][i-2]));
            f[1][i] = max(f[0][i-2], f[1][i-2]) + nums[i];
            maxPro = max(f[0][i], f[1][i]);
        }
        return maxPro;
    }
};
```

注意到，其实上述的递推公式中，我们始终需要的都是取与不取中的较大值，所以设$f(n)$为考虑完第$n$家时的最大值利润，其实递推公式可以化简为：
$$
f(n) = max(f(n-2)+nums[n], f(n-1))
$$
最后返回$f(n)$即可。代码如下：

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n==1) return nums[0];
        vector<int> f = vector<int>(n, nums[0]);
        f[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            f[i] = max(f[i-2] + nums[i], f[i-1]);
        }
        return f[n-1];
    }
};
```

#### 完全平方数

![image-20241002170023344](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241002170023344.png)

对于输入$n$，设$f(n)$为输入$n$的完全平方数的最少数量，其子问题是：对于任意$j<n$，如果有$j+i^2 = n$，那么有状态转移方程：
$$
f(n) = \min_{i=1}^{int(\sqrt{n})}(f[n-i^2]+1,f(n))
$$
该状态方程表示的是，在所有的$n-i^2=j$的$j$中挑一个最小的。【注意这里的+1指的就是$n-i^2+i^2$后等于n了，即是能够构成和为n的所有情况里挑一个】

代码如下：

```cpp
class Solution {
public:
    int numSquares(int n) {
        vector<int> f = vector<int>(n+1,INT_MAX-1);
        f[0] = 1;
        for (int i = 2; i <= n; i++) {
            int SqrtI = int(sqrt(i));
            if (i == SqrtI * SqrtI) {
                f[i] = 1;
            }else{
                for (int j = 1; j <= SqrtI; j++) {
                    f[i] = min(f[i-j*j]+1, f[i]);
                }
            }
        }
        return f[n];
    }
};
```

#### 零钱兑换

![image-20241002171114780](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241002171114780.png)

与[完全平方数](###完全平方数)一题的状态转移方程类似，定义$f(n)$为和为$n$时需要的最少的硬币个数，那么有状态转移方程：
$$
f(n) = \min_{i\in coins[j]}(f(n-coins[j])+1, f(n))
$$
代码如下：

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> f = vector<int>(amount+1, INT_MAX-1);
        f[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (coins[j] <= i) {
                    f[i] = min(f[i-coins[j]] + 1, f[i]);
                }
            }
        }
        if (f[amount] == INT_MAX-1) return -1;
        return f[amount];
    }
};
```

另一种更直观的方式是进行深度优先搜索，遍历所有的方式，记录数量最少的方式。代码如下：

### 字符串处理

#### 单词拆分

![image-20241225163409995](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241225163409995.png)

使用`f[i]`表示串`s`中的前`i`个字母

#### 编辑距离

![image-20241010215732778](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241010215732778.png)

首先，需要注意到将`word1`转换为`word2`需要的最少操作次数和将`word2`转换为`word1`的最少操作次数是对称的，所以次数相等，所以我们只需要考虑将`word1`转换为`word2`的操作即可，即每次有三种选择：

- 在word1中插入字符
- 在word1中删除字符
- 在word1中替换字符

【分析子问题】：如果两个单词的末尾的单词相同，比如都是字母`e`，那么这个转换的问题一定可以推给子问题：两个单词都去掉最后一个字母后的最小转换次数，如下图：

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241011111359521.png" alt="image-20241011111359521" style="zoom:50%;" />

如果不同，以`word1=horse`，`word2=ros`为例，分别考虑三种操作下的子问题：

- 在word1中插入一个字母`s`，那么只需要比较`word1[0....n1]`和`word2[0...n2-1]`即可。（n1,n2分别是单词的总长度）

  <img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241011111545630.png" alt="image-20241011111545630" style="zoom:50%;" />

- 在word1中删除字符`e`，那么需要比较的是`word1[0,...n1]`和`word2[0...n2]`即可。

  <img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241011112259523.png" alt="image-20241011112259523" style="zoom:50%;" />

- 在word1中替换字符，将`word1`尾部的`e`替换成了`word2`尾部的`s`，那么考了的就是`word[0,....,n1-1]`和`word2[0,...,n2-1]`：

  <img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241011112433991.png" alt="image-20241011112433991" style="zoom:50%;" />

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241011112516221.png" alt="image-20241011112516221" style="zoom:50%;" />

综上，我们最终得到`word1`转换为`word2`的最少操作次数，如果他们尾部字符不相同，那么只需要在上述三种情况下选择操作次数最少的一种方法。这就是该问题的子问题。

使用`dp[i][j]`表示考虑`word1`的前`i`和字符和`word2`的前`j`个字符需要的最少转换次数，那么状态转移方程可以写成下面的形式：
$$
dp[i][j]=\begin{cases}\begin{align}&dp[i-1][j-1],& word[i] == word[j]\\
&min(dp[i][j-1], dp[i-1][j],dp[i-1][j-1])+1, & else\end{align}\end{cases}
$$
从用自下而上的方式计算，初始化矩阵为$n1+1$行$n2+1$列，矩阵的第一行和第一列都分别初始化为$0,1,2....,n2$和$0,1,2,...,n1$，表示第前0个字母如何转换为相应的结果。而每个$dp[i][j]$在计算的时候需要的结果：$dp[i-1][j]、dp[i][j-1]、dp[i-1][j-1]$都已经完成计算，可以直接使用。代码如下：

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        vector<vector<int>> dp = vector<vector<int>>(n1+1, vector<int>(n2+1, 0));
        // 首先初始化，从word1的前i个字符到word20个字符的值等于word1此时的长度
        for (int i = 1; i <= word1.size(); i++) {
            dp[i][0] = i;
        }
        // 从word2的前若干个字符到word1的前0个字符的值等于word2此时的长度
        for (int j = 1; j <= word2.size(); j++) {
            dp[0][j] = j;
        }
        // 开始填表
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                // 取：A中增加一个字符，在B中增加一个字符，更改A中的一个字符 三者中最小的
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = min(min(dp[i][j-1]+1, dp[i-1][j]+1), dp[i-1][j-1]);
                }else{
                    dp[i][j] = min(min(dp[i][j-1]+1, dp[i-1][j]+1), dp[i-1][j-1]+1);
                }
                
            }
        }
        return dp[n1][n2];
    }
};
```

#### 最长回文子串

![image-20241230153849360](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20241230153849360.png)

#### 两个字符串的最小ASCII删除和

![image-20250209115326546](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250209115326546.png)

【动态规划】：[编辑距离](###编辑距离)的改版

```cpp
#include<vector>

using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> f(n+1, vector<int>(m+1));
        for (int j = 1; j <= m; j++) {
            f[0][j] = f[0][j-1] + int(s2[j-1]);
        }
        for (int i = 1; i <= n; i++) {
            f[i][0] = f[i-1][0] + int(s1[i-1]);
        }
        // 填表
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i-1] == s2[j-1]) f[i][j] = f[i-1][j-1];
                if (s1[i-1] != s2[j-1]) f[i][j] = min(f[i][j-1] + int(s2[j-1]), f[i-1][j] + int(s1[i-1]));
            }
        }
        return f[n][m];
    }
};

```

#### 交错字符串

![image-20241230153907077](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20241230153907077.png)

【错误解法：双指针】：直观地看题意，会直接认为可以使用双指针：两个指针分别指向两个子串，如果主串的待比较字符和两个指针指向的某个字符相同，那么主串的待比较字符后移，两个子串指针中字符相同的串的指针后移。但实际上与主串字符相同的可能不只是某个子串，当两个子串的字符都与主串相同时，移动哪个子串的指针？如果随意移动一个指针，可能导致下面的情况：

- 待匹配串：`acabc`
- 子串`s1`：`abc`，子串`s2`：`ac`

假设当两个子串的字符都和待匹配串相同时（如上例所示的`a`），我们优先移动子串1的指针，即使用子串1中的字母进行匹配。那么将得出子串1和子串2无法交错形成待匹配串的结论。

【动态规划】：正确的方法是以二维动态规划的角度求解。设`f[i][j]`表示使用子串`s1`的前`i`个字符和`s2`的前`j`个字符是否能够构成主串的前`i+j`个字符（由于`i`和`j`是序数，此处`i>=1, j>=1`），故状态转移方程如下：
$$
f[i][j] = f[i-1][j]\&\&s1[i-1]==s[i+j-1] ||f[i][j-1]\&\&s2[j-1]==s[i+j-1]
$$
详细代码如下：

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 + n2 != n3) return false;
        if (n3 == 0) return true;
        vector<vector<bool>> f(n1+1, vector<bool>(n2+1, true));
        // 初始化矩阵的第一行
        for (int i = 0, j = 1; j <= n2; j++) {
            f[i][j] = f[i][j-1] && (s2[j-1] == s3[i+j-1]);
        }
        // 进行后续计算
        for (int i = 1; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                if (j == 0) {
                    f[i][j] = f[i-1][j] && (s1[i-1] == s3[i+j-1]);
                }else {
                    f[i][j] = (f[i-1][j] && (s1[i-1] == s3[i+j-1])) || (f[i][j-1] && (s2[j-1] == s3[i+j-1]));
                }
            }
        }
        return f[n1][n2];
    }
};
```

【其他想法：搜索】上述动态规划的方式本质是进行了广度优先搜索，利用了前序信息。基于深度搜索也可以实现。每个s[i]，尝试使用s1和s2中的字母，遇到不可行情况进行剪枝即可。



### 数组处理

#### 最大子数组和

![image-20250113230020388](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250113230020388.png)

【动态规划】：使用`f[i]`表示以`nums[i]`结尾的最大子数组和，那么该最大子数组和要么是只有`nums[i]`这一个元素，要么是将`nums[i]`接在前一个最大子数组`f[i-1]`所对应的最大子数组的后面。状态转移方程如下：
$$
f[i] = max(nums[i], f[i-1]+nums[i])
$$
该方法时间复杂度和空间复杂度均为`O(n)`。

【线段树】：

该方法的时间复杂度为`O(n)`，但空间复杂度为`O(log(n))`。

#### 环形最大子数组和

![image-20250113231149386](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250113231149386.png)

【动态规划】：环形子数组可以分成两种情况去求解：

- 第一种情况：计算区间$[i,j]$上的最大子数组和，其中$0 < i < j < n$，这种情况其实就是上一题中的最大子数组和
- 第二种情况：计算区间[0, i], [j, n]上的最大子数组和，其中$0 < i < j < n$。这种情况是环形数组中的特殊情况。

两种情况如下图所示：

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250113232614927.png" alt="image-20250113232614927" style="zoom: 33%;" />

第二种这种情况要在`O(n)`时间复杂度内求解不妨从后往前看：固定一个`j`，计算`nums[j:n]`（这步可以在累加的过程中完成），然后获取`[0,j-1]`区间内的最大前缀和（注意是最大前缀和，所以第一个元素一定是包括在内的），该获取最大前缀和的过程需要在`O(1)`时间内完成，才能实现整体复杂度为`O(n)`。最大前缀和的计算可以使用动态规划的思想进行预计算，动态转移方程为：
$$
maxPrefix[i] = max(maxPrefix[i-1], sum(0...i))
$$
经过上式的预处理，能够在`O(n)`时间内处理完第二种情况。然后综合第一种情况，得到最终的答案。详细代码如下：

```cpp
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int maxNum = nums[0], n = nums.size();
        // 第一种情况：计算 0 < i < j < n, 区间[i,j]上的最大子数组和
        vector<int> f(n);
        f[0] = nums[0];
        for (int i = 1; i < n; i++) {
            f[i] = max(nums[i], nums[i] + f[i-1]);
            maxNum = max(maxNum, f[i]);
        }
        // 第二种情况：计算 0 < i < j < n，区间[0, i], [j, n]上的最大子数组和
        // 首先计算区间 0 - i区间上，任意i < n-1 时的最大前缀和
        vector<int> maxPre(n);  // 多算一个
        maxPre[0] = nums[0];
        int preSum = nums[0];
        for (int i = 1; i < n; i++) {
            preSum += nums[i];
            maxPre[i] = max(maxPre[i-1], preSum);
        }
        int endSum = 0;
        for (int j = n-1; j > 0; j--) {
            endSum += nums[j];
            maxNum = max(maxPre[j-1] + endSum, maxNum);
        }
        return maxNum;
    }
};
```

### 其他

#### 分割等和子集

<img src="https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250321204343321.png" alt="image-20250321204343321" style="zoom:33%;" />

**NP难**：经典的“**子集和问题**”（Subset Sum Problem），问题的本质是：给定一个数组 `nums`，判断是否可以把这个数组分成两个和相等的子集。

根据数值类型，去除总和是奇数的情况。偶数情况如果使用回溯求解，那么时间复杂度是`O(2^n)`，即判断每个数放或者不放。代码最终超时。

【动态规划】：动态规划也针对每个数值选或者不选，但是因为有之前子问题的结果，减少了重复的子问题。主要是设计的`dp[i][j]`数组（`n x (targetSum+1)`），`i`表示`[0-i]`之间的数（都可以选或者不选）是否能构成值`j`。详细代码如下。时间复杂度`O(n * halfSum)`。

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int totSum = 0;
        for (int i = 0; i < n; i++) {
            totSum += nums[i];
        }
        if (totSum % 2 != 0) return false;
        int halfNum = totSum / 2;
        vector<vector<int>> dp(n, vector<int>(halfNum+1, false));
        dp[0][0] = true;
        for (int j = 1; j <= halfNum; j++) {
            dp[0][j] = nums[0] == j ? true : false;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= halfNum; j++) {
                if (j >= nums[i]) dp[i][j] = dp[i-1][j-nums[i]] || dp[i-1][j];    // 选或者不选
                if (j < nums[i]) dp[i][j] = dp[i-1][j]; // 只能不选
            }
        }
        return dp[n-1][halfNum];
    }
};
```



## 其他技巧

### 位运算

#### 颠倒二进制位

![image-20250121150128763](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250121150128763.png)

【位运算】：取出每一位后（移位操作 + 与操作）进行对称处理（移位操作），结果拼接（位运算中的按照位拼接使用或运算）即可，详细代码如下：

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for (int i = 0; i < 32 && n > 0; i++) {
            res |= (n & 1) << (31 - i);
            n >>= 1;
        }
        return res;
    }
};
```

#### 只出现一次的数字II

![image-20250121145811215](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250121145811215.png)

【哈希表】：使用哈希表记录每个数出现的次数，时间复杂度和空间复杂度均为`O(n)`：

```cpp
class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        unordered_map<int, int> umap;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            umap[nums[i]]++;
            if (umap[nums[i]] == 3) umap.erase(nums[i]);
        }
        auto it = umap.begin();
        return it->first;
    }
};
```

【利用余数关系】：可以按位获取答案的每一位（0或1）：由于除了答案，其他的数都是出现3次的，因此在不加上答案前，其余数的每一位的和对3取余一定为0。加上答案后，对3取余的结果即为答案的该位的值。因此，获取答案可以按位获取，对所有的数的第`j`位求和，对3取余即得到了答案的第`j`位。所有位拼凑即得到了完整的数。详细代码如下：

```cpp
class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for (int j = 0; j < 32; j++) {
            int tot = 0;
            for (int i = 0; i < n; i++) {
                // 取出第j位的数
                tot += (nums[i] >> j) & 1;
            }
            res |= tot % 3 == 0 ? (0 << j) : (1 << j);
        }
        return res;
    }
};
```

#### 数字范围按位与

![image-20250121172749345](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250121172749345.png)

【最长公共前缀】对于范围内的数字按位与，不难知道除了这些数的最长公共前缀外，后面的数肯定至少有一个零，所以在最长公共前缀后面补0即可。

最长公共前缀可以通过left和right同时右移，直到相等时得到。

详细代码如下：

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int move = 0;
        while (left != right) {
            left >>= 1;
            right >>= 1;
            move++;
        }
        // 直到找到最长公共前缀，后位补0
        while (move--) {
            left <<= 1;
        }
        return left;
    }
};
```

### 数学

#### `x`的平方根

![image-20250122173124876](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250122173124876.png)

【二分】：可以使用二分查找的方式确定该根。注意递归终止条件。详细代码如下：

```cpp
class Solution {
public:
    int mySqrt(int x) {
        return binarySearch(0, x, x);
    }

    int binarySearch(int start, int end, long x) {
        if (start <= end) {
            long mid = (start + end) / 2;
            if (mid * mid == x) return mid;
            if (mid * mid > x) return binarySearch(start, mid-1, x);
            return binarySearch(mid+1, end, x);
        }
        return end;
    }
};
```

#### Pow(x, n)

【快速幂（分治）】：快速幂其实本质是分治，分治时注意奇数、偶数的划分以及递归终止条件即可。详细代码如下：

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        return myPow(x, n);
    }
    double divide(double x, int n) {
        if (n % 2 == 0) {
            int half = n / 2;
            double halfRes = divide(x, half);
            return halfRes * halfRes;
        }
        int half = n / 2;
        double halfRes = divide(x, half);
        return halfRes * halfRes * x;
    }
};
```

#### 阶乘后的零



#### 直线上最多的点数

![image-20250126115524220](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/images/image-20250126115524220.png)

【哈希表】：对每两个点之间都进行斜率计算（使用嵌套循环`for (int i = 0;...){ for (int j = i + 1; ....)}`），存入哈希表中统计相同斜率的点的数量，记录最大的同斜率的点的数量即可。需要注意下面两点：

- 外层循环每次需要重置哈希表的数量值，因为相同斜率并不一定是一条直线上，可能两点平行
- 垂直于x轴的线需要额外统计。

详细代码如下：

```cpp
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int maxNum = 0, n = points.size();
        if (n == 1 || n == 2) return n;
        for (int i = 0; i < n; i++) {
            int localMax = 0, infty = 0;
            unordered_map<double, int> umap;
            for (int j = i+1; j < n; j++) {
                double deltax = points[i][0] - points[j][0];
                double deltay = points[i][1] - points[j][1];
                if (deltax == 0) {
                    infty++;
                    localMax = max(localMax, infty);
                }else{
                    umap[deltay/deltax]++;
                    localMax = max(umap[deltay/deltax], localMax);
                }
            }
            maxNum = max(localMax, maxNum);
        }
        return maxNum+1;
    }
};
```



### 颜色分类

![image-20241111110020938](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241111110020938.png)



### 下一个排列

![image-20241111105924271](https://cdn.jsdelivr.net/gh/Holmes233666/blogImage/img/image-20241111105924271.png)
