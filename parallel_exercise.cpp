#include <future>
#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>

// function to print vector
void print_vector(std::vector<int> vec) {
 for (auto i: vec) {
  std::cout << i << ' ';
  }	 
} 

//function to return sorted vector
std::vector<int> sort_vector(std::vector<int> vec) {

 std::sort(vec.begin(), vec.end());
 return vec;

}

//function to set vector promise
void promise_vector(std::promise<std::vector<int>>&& vecPromise, std::vector<int> vec) {
 
 std::vector<int> result = sort_vector(vec); 
 vecPromise.set_value(result);	

}

int main() {
 
 //define input vectors	
 std::vector<int> v1 = {1,57,13,16,19,20};
 std::vector<int> v2 = {8,9,12,124,86,91};

 //post inputs
 std::cout << "The inputs are: " << std::endl;
 print_vector(v1);
 std::cout << std::endl;
 print_vector(v2);
 std::cout << std::endl;

 //define promises
 std::promise<std::vector<int>> v1Promise;
 std::promise<std::vector<int>> v2Promise;

 // get the futures
 std::future<std::vector<int>> v1Future = v1Promise.get_future();
 std::future<std::vector<int>> v2Future = v2Promise.get_future();

 //calculate threads
 std::thread t1 {promise_vector, std::move(v1Promise), v1};
 std::thread t2 {promise_vector, std::move(v2Promise), v2};

 //get results
 std::vector<int> res1 = v1Future.get(); 
 std::vector<int> res2 = v2Future.get();

 //terminate threads
 t1.join();
 t2.join();

 //post outputs
 std::cout << "The outputs are: " << std::endl;
 print_vector(res1);
 std::cout << std::endl;
 print_vector(res2);
 std::cout << std::endl;

}





