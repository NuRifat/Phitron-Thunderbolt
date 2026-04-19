#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'equalStacks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY h1
 *  2. INTEGER_ARRAY h2
 *  3. INTEGER_ARRAY h3
 */

int equalStacks(vector<int> h1, vector<int> h2, vector<int> h3) {
    int  height1=0, height2=0, height3=0;
    for(int x : h1){
        height1 += x;
    }
    for(int x : h2){
        height2 += x;
    }
    for(int x : h3){
        height3 += x;
    }
    
    int i=0, j=0, k=0;
    while(true){
        if(i==h1.size() || j==h2.size() || k==h3.size()) 
            return 0;
        
        if(height1==height2 && height2==height3) 
            return height1;
        
        if(height1 >= height2 && height1 >= height3){
            height1 -= h1[i];
            i++;
        }
        else if(height2 >= height1 && height2 >= height3){
            height2 -= h2[j];
            j++;
        }
        else{
            height3 -= h3[k];
            k++;
        }
        
    }

}

int main()
{
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    
    vector<int> h1(n1), h2(n2), h3(n3);
    
    for(int i=0;i<n1;i++) cin >> h1[i];
    for(int i=0;i<n2;i++) cin >> h2[i];
    for(int i=0;i<n3;i++) cin >> h3[i];
    
    int result = equalStacks(h1, h2, h3);

    cout << result << endl;

    return 0;
}
