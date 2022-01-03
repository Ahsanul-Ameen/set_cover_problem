#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define     endl               "\n"
#define     unsync_io          ios::sync_with_stdio(false);
#define     all(x)             begin(x), end(x)
#define     debug(x)           cerr <<"Line "<< __LINE__ <<" : "<< #x " = "<< x <<endl;
 
template<typename T, typename TT>
ostream& operator<<(ostream &os, const pair<T, TT> &t) { return os<<"("<<t.first<<", "<<t.second<<")"; }
template<typename T>
ostream& operator<<(ostream& os, const vector<T> &t) { for(const auto& i: t) os<<i<<" "; return os; }
 

class SetCover {
	const int UNIVERSE_SIZE = 30;
	const int INF = 1e8+37;
	
	int n, m;
	vector<int> universe, cost;
	vector<vector<int>> family, solution;

private:
	// O(n) time | O(1) space
	int updateMask(int mask, int j) {
		for (const int& item : family[j]) {
			// clear the (item - 1) th bit of mask
			mask &= ~(1 << (item - 1));
		}
		return mask;
	}
	
	void generateSolution(vector<vector<pair<int, bool>>>& dp) {
		const int NSETS = (1 << n) - 1;
		
		int s_upto = m, mask = NSETS;
		
		while (s_upto and mask) {
			if (dp[s_upto][mask].second) {
				// item taken
				solution.push_back(family[s_upto - 1]);
				mask = updateMask(mask, s_upto - 1);
			}
			s_upto -= 1;
		}
	}
	
public:
	SetCover(int _n, int _m) 
		: n(_n), m(_m) {
			
		assert(n < UNIVERSE_SIZE);
		// n elements of universe
		universe.resize(n);
		for (int& item : universe) {
			cin >> item;
		}
		
		// m costs of family
		cost.resize(m);
		for (int& c : cost) {
			cin >> c;
		}
		
		// m sets of family
		family.resize(m);
		for (auto& s : family) {
			int n_elements = 0;
			cin >> n_elements; // size of current set
			
			s.resize(n_elements);
			for (int& item : s) {
				cin >> item;
			}
		}	
	}
	
	// O(m * 2^n * n) time | O(m * 2^n) space
	int dpSolver() {
		const int NSETS = (1 << n) - 1;

		vector<vector<pair<int, bool>>> dp(m + 1, vector<pair<int, bool>>(NSETS + 1, {INF, false}));
		
		for (int s_upto = 0; s_upto <= m; ++s_upto) {
			for (int mask = 0; mask <= NSETS; ++mask) {
				if (!s_upto) {
					dp[s_upto][mask] = {!mask? 0 : INF, false};
				} else {
					int with = dp[s_upto - 1][updateMask(mask, s_upto - 1)].first + cost[s_upto - 1];
					int without = dp[s_upto - 1][mask].first;
					dp[s_upto][mask] = {min(with, without), with < without};
				}
			}
		}
		
		// generate solution
		generateSolution(dp);
		
		return dp[m][NSETS].first;
	}
	
	void printSets() {
		cout << "---------------------" << endl;
		cout << "n = " << n << endl;
		cout << "universe : { " << universe << "}" << endl;
		cout << "m = " << m << endl;
		for (int i = 0; i < m; ++i) {
			cout << "len : " << family[i].size() << ", cost : " << cost[i] << ", set = { " << family[i] << "}" << endl;
		}
		cout << "---------------------" << endl;
	}
	
	void printSolution() {
		sort(all(solution));
		cout << "Minimum sets : " << solution.size() << endl;
		for (const auto& s : solution) {
			cout << "\t{ " << s << "}" << endl;
		}
	}
	
};


void test_case(int nt) {
	/// write your code here...
	
	int n, m;
	cin >> n >> m;
	
	SetCover st(n, m);
	
	cout << "\n#Case : " << nt << " ..." << endl;
	
	st.printSets();
	
	cout << "cost : " << st.dpSolver() << endl;
	
	st.printSolution();
	
	cout << endl;
	
}


int main(int argc, char** argv) {
    //unsync_io
    //cin.tie(nullptr);
	
	
    int T = 1;	// default
	cin >> T;	
    for(int nt = 1; nt <= T; ++nt) {	
		test_case(nt);
    }
    
    return 0;
}


/**
 * Sample test case
    2
    
	13 5
	1 2 3 4 5 6 7 8 9 10 11 12 13
	1 1 1 1 1 
	2  1 2
	4  2 3 4 5
	8  6 7 8 9 10 11 12 13
	7  1 3 5 7 9  11 13
	7  2 4 6 8 10 12 13
	
	5 3
	1 2 3 4 5
	5 10 3
	3  4 3 1
	2  2 5
	4  1 4 3 2 
	
 * */
