#include <iostream>
#include <vector>
using namespace std;

// 二分查找，查找数字target在nums.begin---nums.end之中的位置
// target刚好小于等于nums[return int] 
int findTargetPositionInNums(vector<int>& nums, int begin, int end, int target) {
    // 如果区间为空，直接返回
    if (begin == end)  return begin; 
    
    int mid = (end + begin) / 2;
    
    while (1) {
        // 区间长度小于1，进行比较 
        if (end <= begin + 1)
            if (target > nums[mid])  return end;
            else  return begin;
        
        // nums[mid - 1] <= nums[mid] < target 
        if (target > nums[mid])  begin = mid + 1;
        // nums[mid - 1] < target <= nums[mid]，返回结果 
        else if (target > nums[mid - 1])  return mid;
        // target <= nums[mid - 1] <= nums[mid]
        else  end = mid;
        
        mid = (end + begin) / 2;
    }
}

// 根据总数返回中位值，其中value1 < value2
double getMedian(int value1, int value2, bool isEven) {
    return isEven ? (double)(value1 + value2) / 2 : value2;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int sumSize = nums1.size() + nums2.size();     // 总数 
    bool isEven = sumSize % 2 == 0;                // 判断中位数数量 
    
    // 当数量太小 
    if (sumSize <= 2) {
        nums1.insert(nums1.end(), nums2.begin(), nums2.end());
        if (isEven)  return (double)(nums1[0] + nums1[1]) / 2;
        return nums1[0];
    }
    
    // 当其中一个数组为空 
    if (nums1.empty())
        return getMedian(nums2[nums2.size() / 2 - 1], nums2[nums2.size() / 2], isEven);
    else if (nums2.empty())
        return getMedian(nums1[nums1.size() / 2 - 1], nums1[nums1.size() / 2], isEven);
    
    // 正常数组
    // 如果是偶数，去掉最小值，使中位数只有一个 
    if (isEven) {
        if (nums1[0] < nums2[0])  nums1.erase(nums1.begin());
        else  nums2.erase(nums2.begin());
        sumSize--;
    }
    
    
    
    int begin1 = 0; 
    int end1 = nums1.size();
    int begin2 = 0;
    int end2 = nums2.size();               // 用于递归的值 
    int medianPosInSum = sumSize / 2 + 1;  // 中位数在总数组中第几大，一开始为sumSize/2+1
    int posInBig;                          // 某数在大数组中的位置 
    int posInSmall;                        // 某数在小数组中的位置 
    int posInSum;                          // 某数在总数组中的位置 
    int isInNums1;                         // 判断最后得到的中位值在nums1还是nums2 
       
    while (1) {
        if (end1 - begin1 > end2 - begin2) {
            // 从大数组中取一个可能的位置，为了降低时间复杂度，取比例位置 
            posInBig = (float)medianPosInSum / sumSize * (end1 - begin1) + begin1;
            // 在小数组中找到相应的位置 
            posInSmall = findTargetPositionInNums(nums2, begin2, end2, nums1[posInBig]);
            // 求出该数在总数组的位置
            posInSum = (posInBig - begin1 + 1) + (posInSmall - begin2);
            
            // 将posInSum和medianPosInSum比较 
            // posInSum < medianPosInSum，砍掉左半部分 
            if (posInSum < medianPosInSum) {
                medianPosInSum -= posInSum;
                begin2 = posInSmall;
                begin1 = posInBig + 1;
            }
            // posInSum > medianPosInSum，砍掉右半部分 
            else if (posInSum > medianPosInSum) {
                end2 = posInSmall;
                end1 = posInBig;
            }
            // posInSum == medianPosInSum，得到结果，跳出循环
            else {
                isInNums1 = true; 
                break;
            } 
        }
        // 对称 
        else {
            posInBig = (float)medianPosInSum / sumSize * (end2 - begin2) + begin2;
            posInSmall = findTargetPositionInNums(nums1, begin1, end1, nums2[posInBig]);
            posInSum = (posInBig - begin2 + 1) + (posInSmall - begin1);
            if (posInSum < medianPosInSum) {
                medianPosInSum -= posInSum;
                begin1 = posInSmall;
                begin2 = posInBig + 1;
            }
            else if (posInSum > medianPosInSum) {
                end1 = posInSmall;
                end2 = posInBig;
            }
            else {
                isInNums1 = false; 
                break;
            } 
        }
    }
    
    // 求出中位值和中位值的前一个值
    int median = isInNums1 ? nums1[posInBig] : nums2[posInBig];
    int preMedian = isInNums1 ? max(nums1[posInBig - 1], nums2[posInSmall - 1])
               : max(nums2[posInBig - 1], nums1[posInSmall - 1]);
    
    return getMedian(preMedian, median, isEven);
}

void addTestData(vector<int>& test, int& target) {
    int data1[100] = {1, 2, 3, 4, 5, 6, 6, 6, 9, 10};
    int n = 10;
    for (int i = 0; i < n; i++)
        test.push_back(data1[i]);
        
    target = 6;
}

void addTestData(vector<int>& test1, vector<int>& test2) {
    int data1[100] = {1, 2};
    int n = 2;
    for (int i = 0; i < n; i++)
        test1.push_back(data1[i]);
    
    int data2[100] = {3, 4};
    n = 2;
    for (int i = 0; i < n; i++)
        test2.push_back(data2[i]);
}

void showOutput(double output) {
    cout << output << endl;
}


int main() {
    vector<int> test1;
    vector<int> test2;
    addTestData(test1, test2);
    showOutput(findMedianSortedArrays(test1, test2));
}
