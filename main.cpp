#include <iostream>
#include <vector>
using namespace std;

// report[i][j] = 晶片 i 對晶片 j 的判斷
// true  表示 i 說 j 是好晶片
// false 表示 i 說 j 是壞晶片

class ChipTester {
private:
    vector<vector<bool>> report;

public:
    ChipTester(const vector<vector<bool>>& r) : report(r) {}

    // 回傳一顆好晶片的索引；若無法找到則回傳 -1
    int findGoodChip(vector<int> chips) {
        while (true) {
            int n = chips.size();

            // 1. 若只剩一顆晶片
            if (n == 1) {
                return chips[0];
            }

            // 2. 第一顆作為候選 A
            int A = chips[0];

            // 3. 設 V = 0
            int V = 0;

            // 4. 與其他晶片互測
            for (int i = 1; i < n; i++) {
                int B = chips[i];

                if (report[A][B] && report[B][A]) {
                    V++;
                }
            }

            // 5. 若支持數夠多，回傳 A
            if (V >= n / 2) {
                return A;
            }

            // 6. 否則刪除 A
            chips.erase(chips.begin());

            // 保險檢查（理論上不會發生）
            if (chips.empty()) {
                return -1;
            }
        }
    }
};

int main() {
    // 範例：6 顆晶片
    vector<vector<bool>> report = {
        // 0    1    2    3    4    5
        {true, true, true, false, true, false},
        {true, true, true, false, true, false},
        {true, true, true, false, true, false},
        {true, false, true, true, false, true},
        {true, true, true, false, true, false},
        {false, true, false, true, true, true}
    };

    ChipTester tester(report);

    vector<int> chips = {0, 1, 2, 3, 4, 5};

    int goodChip = tester.findGoodChip(chips);

    if (goodChip != -1) {
        cout << "Found a good chip: chip " << goodChip << endl;
    } else {
        cout << "No good chip found." << endl;
    }

    return 0;
}
