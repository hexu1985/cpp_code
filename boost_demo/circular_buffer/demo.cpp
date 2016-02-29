#include <iostream>
#include <limits>
#include <boost/circular_buffer.hpp>


using namespace std;
using namespace boost;


void print(const circular_buffer<int>& nums) {
  for (int i = 0; i < nums.size(); ++i) {
    cout << nums[i] << " ";
  }
  cout << endl;
}


int main(int argc, char* argv[]) {
  circular_buffer<int> nums(5);     //声明一个总容量为5的circular_buffer
  nums.push_back(1);
  nums.push_back(2);
  nums.push_back(3);
  nums.push_back(4);
  nums.push_back(5);
  print(nums);
  nums.push_back(6);
  print(nums);
  nums.push_front(8);
  print(nums);
  nums[3] = 9;
  print(nums);
  nums.pop_back();
  print(nums);
  nums.pop_front();
  print(nums);
  return 0;
}
