#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 200005;
const ll  INF = (1LL<<60LL);

int n, m;
vector<pair<int, ll>> adj[N];
ll d[n];

void dijkstra(int s){
	fill(d, d+n, INF);
	set<pair<ll, int>> q;
	q.insert({0, s});
	while(q.size()){
		int u = q.begin()->second;
		ll  w = q.begin()->first;
		q.erase(q.begin());
		for(const pair<ll, int>& v : adj[u]){
			if(d[v.first] > d[u] + w){
				q.erase({d[v.first], v.first});
				d[v.first] = d[u] + w;
				q.insert({d[v.first], v.first});
			}
		}
	}
}

int main(){

}
