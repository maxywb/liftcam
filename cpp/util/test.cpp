#include <iostream>
#include <boost/thread.hpp>
#include "util.hpp"

#ifdef QUEUE_TEST
int main(){
  boost::mutex mutex;
  SafeQueue<int> q(2,&mutex);
  cout << "pop empty:" << q.pop() << endl;
  cout << "isFull() - false: " << q.isFull() << endl;
  cout << "push(2) - true: " << q.push(2) << endl;
  cout << "pop - 2: " << q.pop() << endl;
  cout << "fill it" << endl;
  q.push(2);
  q.push(2);
  cout << "isFull() - true: " << q.isFull() << endl;
  cout << "push(2) - false: " << q.push(2) << endl;
  return 0;
}
#endif
