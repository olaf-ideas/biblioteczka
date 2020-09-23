#include <bits/stdc++.h>

using namespace std;

#include <bits/extc++.h>

template <typename K, typename V, typename Comp = std::less<K>> using ordered_map = __gnu_pbds::tree<K, V, Comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <typename K, typename Comp = std::less<K>>             using ordered_set = ordered_map<K, __gnu_pbds::null_type, Comp>;

int main() {
    ordered_set<int> s;
    s.insert(420);
    s.insert(2137);
    s.insert(69);
    cout << s.order_of_key(70) << '\n'; // count smaller than x
    cout << *s.find_by_order(0) << '\n'; // element with index x
}
