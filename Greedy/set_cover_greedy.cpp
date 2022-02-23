#include <bits/stdc++.h>
using namespace std;

string set_cover_greedy(int m, set<int> U, const float costs[], set<int> subsets[])
{
    string str;
    float cost_count = 0.0;
    set<int> sets_taken;

    for(int i=0;i<m; i++)
    {
        str +='0';
    }

    while(!U.empty()){

        float cost_eff = -999.0;
        int set_no;

        for(int i=0; i<m; i++)
        {
            if(sets_taken.find(i)==sets_taken.end()){

                set<int> intersect;
                set_intersection(U.begin(), U.end(), subsets[i].begin(), subsets[i].end(),
                                 inserter(intersect, intersect.begin()));

                float temp = (float)intersect.size()/costs[i];

                if(temp > cost_eff)
                {
                    cost_eff = temp;
                    set_no = i;
                }
            }
        }

        str[set_no] = '1';
        cost_count += costs[set_no];
        sets_taken.insert(set_no);

        set<int>::iterator itr;

        for(itr = subsets[set_no].begin(); itr != subsets[set_no].end(); itr++)
        {
            if(U.find(*itr)!=U.end()){
                U.erase(*itr);
            }
        }
//        for(itr = U.begin(); itr != U.end(); itr++)
//        {
//            cout << *itr << " ";
//        }
//        cout<< "\n";

    }
    cout<< "Total Cost: "<< cost_count<< "\n";
    return str;
}

void print_sets(int m, string str, set<int> subsets[])
{
    for(int i=0; i<m; i++)
    {
        if(str[i]=='1'){

            set<int>::iterator itr;

            for(itr = subsets[i].begin(); itr != subsets[i].end(); itr++)
            {
                cout << *itr << " ";
            }
            cout<< "\n";
        }
    }
}

void test_case(int nt) {
	
	cout << "\n#Case : " << nt << " ..." << endl;
	
	int n, m;
    cin >> n >> m;
    set<int> U;
    float costs[m] ;
    set<int> subsets[m];

    for(int i=0;i<n;i++)
    {
       int x;
       cin >> x;
       U.insert(x);
    }

    for(int i=0;i<m;i++)
    {
        float x;
        cin >> x;
        costs[i]=x;
    }

    for(int i=0;i<m;i++)
    {
        int s;
        cin >> s;
        for(int j=0;j<s;j++)
        {
            int x;
            cin >> x;
            subsets[i].insert(x);
        }
    }

    string bits = set_cover_greedy(m, U, costs, subsets);
    cout<< "Output String: " << bits << endl;
    cout<< "Sets chosen: " << endl;
    print_sets(m, bits, subsets);
}

int main() {
        //unsync_io
    //cin.tie(nullptr);
	
	freopen("../test/io_cases.txt", "r", stdin); 
	
    int T = 1;	// default
	cin >> T;	
    for(int nt = 1; nt <= T; ++nt) {	
		test_case(nt);
    }
    
    return 0;

}

/**

5 4
1 2 3 4 5
1.0 3.0 5.0 2.0
3  1 2 3
2  2 4
2  3 4
2  4 5


13 5
1 2 3 4 5 6 7 8 9 10 11 12 13
1 1 1 1 1 
2  1 2
4  2 3 4 5
8  6 7 8 9 10 11 12 13
7  1 3 5 7 9 11 13
7  2 4 6 8 10 12 13

non optimal output at case 2

5 3
1 2 3 4 5
5.0 10.0 3.0
3  4 3 1
2  2 5
4  1 4 3 2
 
 * */
