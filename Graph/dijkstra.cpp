using ll = long long;

const int N = 500005;
const ll  INF = (1LL<<60LL);

int n, m;
vector<pair<int, ll>> adj[N];
ll d[N];

void dijkstra(int s){
	fill(d, d + n, INF);
  d[s] = 0;
	set<pair<ll, int>> q;
	q.insert({d[s], s});
	while(q.size()){
		int u = q.begin()->second;
		q.erase(q.begin());
		for(const pair<ll, int> & e : adj[u]){
      ll  c = e.first;
      int v = e.second;
			if(d[v] > d[u] + c){
				q.erase({d[v], v});
				d[v] = d[u] + c;
				q.insert({d[v], v});
			}
		}
	}
}
