#include <iostream>
using namespace std;

long long a, b, ans = 1;

int main()
{
    cin >> a >> b;
    while(a < b && ans) {
        ans *= ++a;
        ans %= 10;
    }
    cout << ans;
    return 0;
}