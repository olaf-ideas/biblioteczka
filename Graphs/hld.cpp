#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 5e4+5;

int n,k;

vector<int> adj[MAXN], heavy[MAXN];
set<pair<int,int>> heavyEdges;
int singleChanges[MAXN], subTreeSize[MAXN], parent[MAXN];
pair<int,int> treeOverNode[MAXN];
bool vis[MAXN];

int pre[MAXN], cpre = 0, post[MAXN], cpost = 0;

struct SegTree{
	SegTree(int _base):base(_base){
		t.resize(base<<1,0);
	}

	int base;
	vector<int> t;
	unordered_set<int> includedNodes;
	int highest;

	void update(int a, int b, int val, int low = 0, int high = -1, int u = 1){
		if(high == -1)	high = base-1;
		if(a > high || b < low)	return;
		if(a <= low && high <= b){
			t[u] += val;
			return;
		}
		int mid = (low+high)>>1;
		update(a,b,val,low,mid,u<<1);
		update(a,b,val,mid+1,high,u<<1|1);
	}

	int query(int x){
		int res = 0;
		for(x += base; x > 0; x >>= 1)	res += t[x];
		return res;
	}
};

vector<SegTree> hldTrees;

void dfs(int u){
	vis[u] = true;
	pre[u] = cpre++;
	subTreeSize[u] = 1;
	
	int heaviest = -1;
	int heaviestSts;

	for(int v : adj[u]){
		if(!vis[v] && v != parent[u]){
			parent[v] = u;
			dfs(v);
			subTreeSize[u] += subTreeSize[v];
			if(heaviest == -1 || subTreeSize[v] > heaviestSts){
				heaviest = v;
				heaviestSts = subTreeSize[v];
			}
		}
	}
	if(heaviest != -1){
		heavy[heaviest].push_back(u);
		heavy[u].push_back(heaviest);
		heavyEdges.insert({u,heaviest});
		heavyEdges.insert({heaviest, u});
	}
	post[u] = cpost++;
}

int tSize;

int hldDfs(int u, unordered_set<int>* r, int nTree, int iteration = 0){
	vis[u] = true;
	tSize++;
	r->insert(u);
	treeOverNode[u] = {nTree, iteration};
	int hmax = -1;
	bool anyLeft = false;
	for(int v : heavy[u]){
		if(!vis[v]){
			anyLeft = true;
			hmax = max(hmax, hldDfs(v, r, nTree, iteration+1));
		}
	}
	if(!anyLeft)	return u;
	return hmax;
}

int jumps[MAXN][35];

void preCalcLca(){
	for(int i = 0; i < 35; i++)	jumps[0][i] = -1;
	for(int j = 1; j < n; j++) 	jumps[j][0] = parent[j];
	for(int i = 1; i < 35; i++) 
		for(int j = 1; j < n; j++){
			if(jumps[j][i - 1] == -1)	jumps[j][i] = -1;
			else 						jumps[j][i] = jumps[jumps[j][i - 1]][i - 1];
		}
}

bool isAncestor(int x, int anc){
	if(x == -1 || anc == -1)	return false;
	return pre[anc] < pre[x] && post[anc] > post[x];
}

int lca(int x, int y){
	if(isAncestor(x, y))	return y;
	if(isAncestor(y, x))	return x;
	int jumpPow = 30;
	while(true){
		if(!isAncestor(y, x) && isAncestor(y, parent[x]))	break;
		if(jumps[x][jumpPow] == -1 || isAncestor(y, jumps[x][jumpPow])) jumpPow--;
		else x = jumps[x][jumpPow];
	}	
	return parent[x];
}

void change(int x, int nParent){
	while(x != nParent){
		while(heavyEdges.find({x, parent[x]}) == heavyEdges.end() && x != nParent){
			singleChanges[x]++;
			x = parent[x];
		}
		if(x == nParent)	break;
		if(heavyEdges.find({x,parent[x]}) != heavyEdges.end()){
			SegTree* currentTree = &hldTrees[treeOverNode[x].first];
			if(currentTree->includedNodes.find(nParent) != currentTree->includedNodes.end()){
				currentTree->update(treeOverNode[x].second, treeOverNode[nParent].second-1,1);
				return;
			}else	currentTree->update(treeOverNode[x].second, currentTree->base-1, 1);
			x = parent[currentTree->highest];
		}else	x = parent[x];
	}
	return;
}

int main(){
	for(int i = 0; i < MAXN; i++)	treeOverNode[i] = {-1,-1};
	cin >> n >> k;
	for(int i = 0; i < n-1; i++){
		int a,b;
		cin >> a >> b;
		a--,b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(0);
	fill(vis,vis+MAXN,false);

	for(int i = 0; i < n; i++){
		if(vis[i])	continue;
		if(heavy[i].size() != 1)		continue;
		if(heavy[i][0] != parent[i])	continue;
		tSize = 0;
		unordered_set<int> tset;
		int chigh = hldDfs(i, &tset, (int)hldTrees.size());
		int p = 1;
		while(p < tSize)	p<<=1;
		hldTrees.emplace_back(p);
		hldTrees[hldTrees.size()-1].includedNodes = tset;
		hldTrees[hldTrees.size()-1].highest = chigh;
	}
	preCalcLca();
	for(int i = 0; i < k; i++){
		int a,b;
		cin >> a >> b;
		a--,b--;
		int u = lca(a,b);
		if(a != u)	change(a,u);
		if(b != u)	change(b,u);
		singleChanges[u]++;
	}

	int maxFlow = -1;
	for(int i = 0; i < n; i++){
		if(treeOverNode[i].first != -1)	maxFlow = max(maxFlow, singleChanges[i] + hldTrees[treeOverNode[i].first].query(treeOverNode[i].second));
		else  							maxFlow = max(maxFlow, singleChanges[i]);
	}
	cout << maxFlow << "\n";
}