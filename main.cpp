#include <bits/stdc++.h>
using namespace std;


vector<string> readFile( string& filename) {
    vector<string> lines;
    ifstream file(filename);

    if(!file.is_open()) {
        cout<<"Error: Cannot open "<<filename<<endl;
        return lines;
    }

    string line;
    while(getline(file,line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}


vector<vector<int>> LCS(vector<string>& a, vector<string>& b) {
    int n = a.size();
    int m = b.size();

    vector<vector<int>> dp(n+1,vector<int>(m+1,0));

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp;
}

void print(vector<string>& oldFile, vector<string>& newFile, vector<vector<int>>& dp) {
    int i = oldFile.size();
    int j = newFile.size();

    vector<string> output;

    while(i>0 || j>0) {
        // both lines are same
        if(i>0 && j>0 && oldFile[i-1] == newFile[j-1]) {
            output.push_back("  "+oldFile[i-1]);
            i--;
            j--;
        }

        // New line was added
        else if (j>0 && (i==0 || dp[i][j-1] >= dp[i-1][j])) {
            output.push_back( "+ "+newFile[j-1]);
            j--;
        }

        // Old line was removed
        else {
            output.push_back("- "+ oldFile[i-1]);
            i--;
        }
    }
    reverse(output.begin(), output.end());

    for(string line : output) {
        if (line[0]=='+') cout << "\033[32m" << line << "\033[0m" << endl;
        else if (line[0]=='-') cout << "\033[31m" << line << "\033[0m" << endl;
        else cout << line << endl;
    }
}

int main(int n, char* v[]) {

    if(n != 3) {
        cout << "Usage: ./main <file1> <file2>" << endl;
        return 1;
    }

    string file1 = v[1];
    string file2 = v[2];

    vector<string> oldFile = readFile(file1);
    vector<string> newFile = readFile(file2);

    vector<vector<int>> dp =  LCS(oldFile, newFile);

    cout << endl;
    cout << "========== DIFFERENCE ==========" << endl;
    cout << endl;

    print(oldFile, newFile, dp);

    cout << endl;
    cout << "=================================" << endl;

    int lcs = dp[oldFile.size()][newFile.size()], total = oldFile.size() + newFile.size();
    double similarity = 100.0;

    if (total != 0) similarity = (2.0 * lcs / total) * 100.0;
    cout << "Similarity: "<< similarity<< "%" << endl;

    return 0;
}