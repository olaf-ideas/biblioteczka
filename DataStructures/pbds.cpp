#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using __gnu_pbds;

template <class T, class M=null_type>
typedef tree<T,M,less<T>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int main() {
  ordered_set<int> x;
  
  x.insert(123);
  x.insert(213);
  x.insert(321);
  x.insert(1232);
  x.insert(23);

  cout << *x.find_by_order(2137) << '\n'; // get 0-indexed k-th element
  cout << x.order_of_key(420) << '\n';    // get 0-indexed index of element k
}
