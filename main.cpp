#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using std::vector;
using std::stack;
using std::pair;

class NestedInteger {
public:
  NestedInteger(int a_int)
    : my_int(a_int), isInt(true) {
  }

  NestedInteger(const vector<NestedInteger> & nested)
    : my_vec(nested), isInt(false) {
  }

  bool isInteger() const {
    return isInt;
  }

  int getInteger() const {
    if (isInt)
      return my_int;
  }

  const vector<NestedInteger> & getList() const {
    if (!isInt)
      return my_vec;
  }

private:
  bool isInt;
  int my_int;
  vector<NestedInteger> my_vec;
};

// class NestedIterator {
// public:
//   NestedIterator(const vector<NestedInteger> & nestedList, size_t curr = 0) {
//     idx = curr;
//     iter = nestedList.begin()+idx;
//     end = nestedList.end();
//   }

//   int next() {
//     int result;
//     if (iter->isInteger()) {
//       result = iter->getInteger();
//       ++iter;
//       idx = 0;
//     }
//     else {
//       if (iter->getList().size() > idx) {
// 	NestedIterator it(iter->getList(), idx);
// 	if (it.iter->isInteger()) {
// 	  result = it.iter->getInteger();
// 	  idx++;
// 	}
// 	else {
// 	  if (it.iter != it.end) {
// 	    result = it.next();
// 	    idx++;
// 	    if (idx == iter->getList().size()) {
// 	      idx = 0;
// 	      iter++;
// 	    }
// 	  }
// 	}
//       }
//       // else if (iter->getList().size() == idx){
//       // 	++iter;
//       // 	idx = 0;
//       // 	if (iter->isInteger()) {
//       // 	  result = iter->getInteger();
//       // 	  ++iter;
//       // 	}
//       // 	else {
//       // 	  NestedIterator it(iter->getList(), idx);
//       // 	  if (it.iter != it.end) {
//       // 	    result = it.next();
//       // 	    idx++;
//       // 	  }
//       // 	  else {
//       // 	    ++iter;
//       // 	    idx = 0;
//       // 	  }
//       // 	}
//       // }
//     }
//     return result;
//   }

//   bool hasNext() {
//     return iter!=end;
//   }

// private:
//   vector<NestedInteger>::const_iterator iter;
//   vector<NestedInteger>::const_iterator end;
//   size_t idx;
// };

class NestedIterator {
public:
  NestedIterator(const vector<NestedInteger> & nestedList) {
    iters.push(make_pair(nestedList.begin(), nestedList.end()));
  }

  int next() {
    int result;
    if (!iters.empty()) {
      auto curr = iters.top();
      iters.pop();
      if (curr.first != curr.second) {
	if (curr.first->isInteger()) {
	  result = curr.first->getInteger();
	  ++(curr.first);
	  if (curr.first != curr.second)
	    iters.push(curr);
	}
	else {
	  NestedIterator it(curr.first->getList());
	  result = it.next();
	  stack<pair<vector<NestedInteger>::const_iterator, vector<NestedInteger>::const_iterator>> temp;
	  while (!it.iters.empty()) {
	    temp.push(it.iters.top());
	    it.iters.pop();
	  }

	  while (!temp.empty()) {
	    iters.push(temp.top());
	    temp.pop();
	  }
	}
      }
    }
    
    return result;
  }

  bool hasNext() const {
    
  }

private:
  stack<pair<vector<NestedInteger>::const_iterator, vector<NestedInteger>::const_iterator>> iters;
};

int main() {
  vector<NestedInteger> nested;
  // nested.push_back(NestedInteger(vector<NestedInteger>{NestedInteger(1), NestedInteger(1)}));
  // nested.push_back(NestedInteger(2));
  // nested.push_back(NestedInteger(vector<NestedInteger>{NestedInteger(3), NestedInteger(3)}));

  nested.push_back(NestedInteger(1));
  vector<NestedInteger> temp{NestedInteger(4), vector<NestedInteger>{NestedInteger(6)}};
  nested.push_back(temp);

  NestedIterator it(nested);
  while (it.hasNext())
    std::cout << it.next() << " ";
  std::cout << std::endl;
}
