#include <iostream>
#include <vector>
using namespace std;

// ���ֲ��ң���������target��nums.begin---nums.end֮�е�λ��
// target�պ�С�ڵ���nums[return int] 
int findTargetPositionInNums(vector<int>& nums, int begin, int end, int target) {
    // �������Ϊ�գ�ֱ�ӷ���
    if (begin == end)  return begin; 
    
    int mid = (end + begin) / 2;
    
    while (1) {
        // ���䳤��С��1�����бȽ� 
        if (end <= begin + 1)
            if (target > nums[mid])  return end;
            else  return begin;
        
        // nums[mid - 1] <= nums[mid] < target 
        if (target > nums[mid])  begin = mid + 1;
        // nums[mid - 1] < target <= nums[mid]�����ؽ�� 
        else if (target > nums[mid - 1])  return mid;
        // target <= nums[mid - 1] <= nums[mid]
        else  end = mid;
        
        mid = (end + begin) / 2;
    }
}

// ��������������λֵ������value1 < value2
double getMedian(int value1, int value2, bool isEven) {
    return isEven ? (double)(value1 + value2) / 2 : value2;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int sumSize = nums1.size() + nums2.size();     // ���� 
    bool isEven = sumSize % 2 == 0;                // �ж���λ������ 
    
    // ������̫С 
    if (sumSize <= 2) {
        nums1.insert(nums1.end(), nums2.begin(), nums2.end());
        if (isEven)  return (double)(nums1[0] + nums1[1]) / 2;
        return nums1[0];
    }
    
    // ������һ������Ϊ�� 
    if (nums1.empty())
        return getMedian(nums2[nums2.size() / 2 - 1], nums2[nums2.size() / 2], isEven);
    else if (nums2.empty())
        return getMedian(nums1[nums1.size() / 2 - 1], nums1[nums1.size() / 2], isEven);
    
    // ��������
    // �����ż����ȥ����Сֵ��ʹ��λ��ֻ��һ�� 
    if (isEven) {
        if (nums1[0] < nums2[0])  nums1.erase(nums1.begin());
        else  nums2.erase(nums2.begin());
        sumSize--;
    }
    
    
    
    int begin1 = 0; 
    int end1 = nums1.size();
    int begin2 = 0;
    int end2 = nums2.size();               // ���ڵݹ��ֵ 
    int medianPosInSum = sumSize / 2 + 1;  // ��λ�����������еڼ���һ��ʼΪsumSize/2+1
    int posInBig;                          // ĳ���ڴ������е�λ�� 
    int posInSmall;                        // ĳ����С�����е�λ�� 
    int posInSum;                          // ĳ�����������е�λ�� 
    int isInNums1;                         // �ж����õ�����λֵ��nums1����nums2 
       
    while (1) {
        if (end1 - begin1 > end2 - begin2) {
            // �Ӵ�������ȡһ�����ܵ�λ�ã�Ϊ�˽���ʱ�临�Ӷȣ�ȡ����λ�� 
            posInBig = (float)medianPosInSum / sumSize * (end1 - begin1) + begin1;
            // ��С�������ҵ���Ӧ��λ�� 
            posInSmall = findTargetPositionInNums(nums2, begin2, end2, nums1[posInBig]);
            // ����������������λ��
            posInSum = (posInBig - begin1 + 1) + (posInSmall - begin2);
            
            // ��posInSum��medianPosInSum�Ƚ� 
            // posInSum < medianPosInSum��������벿�� 
            if (posInSum < medianPosInSum) {
                medianPosInSum -= posInSum;
                begin2 = posInSmall;
                begin1 = posInBig + 1;
            }
            // posInSum > medianPosInSum�������Ұ벿�� 
            else if (posInSum > medianPosInSum) {
                end2 = posInSmall;
                end1 = posInBig;
            }
            // posInSum == medianPosInSum���õ����������ѭ��
            else {
                isInNums1 = true; 
                break;
            } 
        }
        // �Գ� 
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
    
    // �����λֵ����λֵ��ǰһ��ֵ
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
