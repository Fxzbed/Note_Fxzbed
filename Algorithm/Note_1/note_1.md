### *输入输出流与前缀和*

#### *1. 输入*

在取消同步流的情况下，一般会比scanf更快。

```c++
ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
```

最好不要写

```c++
cout << "..." << endl;
```

写成

```c++
cout << "..." << '\n';
```

使用endl会强制刷新缓冲区，导致运行速度减慢

---

#### *2. 前缀和*

主要用于区间求和中，对于一个区间 i 到 j 都有一个前缀和数组对应 

$ prefix[i] = num[i] + num[i - 1] + num[i - 2] + ..... $

从而可得一个区间 $[l, r]$

$res_{[l,r]} = prefix[r] - prefix[l - 1]$

模板：

````c++
#include <iostream>

using namespace std;
using ll = long long;

const int N = 1e5 + 10;

ll num[N], prefix[N];

int main(void) {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n; cin >> n;
    
    for (int i = 1; i <= n; i ++) cin >> num[i];
    for (int i = 1; i <= n; i ++) prefix[i] = num[i] + prefix[i - 1];

    int q; cin >> q;
    for (int i = 0; i < q; i ++) {
        int l, r;
        cin >> l >> r;
        cout << prefix[r] - prefix[l - 1] << '\n';
    }
    
    return 0;
}
````

---

#### *3. 差分*

对于每一个差分数组都有

$d[i] = a[i] - a[i - 1]$

求和可得

$\sum_{j = 1} ^ {i}d[j] = a[1] - a[0] + a[2] - a[1] + ... + a[i - 1] - a[i - 2] + a[i] - a[i - 1]$

最终会剩下 $a[i]$

$d[i] = a[i] - a[i - 1]$

- 通过前缀还原成$a[i]$

- 进行后缀的区间修改

	对于后缀数组$d$ 如果$d[2] + 1$，此时的差分数组还原后，区间$d_{[2,last]}$都被加上1，如果进行区间	$[l,r]$的修改，可以写成$d[l] + x$和$d[r + 1] - x$

	使用差分区间修改的题目中，一定是==先修改完后再询问==。

模板：

```c++
#include <iostream>

using namespace std;
using ll = long long;

const int N = 1e5 + 10;

ll num[N], prefix[N], diff[N];

int main(void) {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n; cin >> n;
    
    for (int i = 1; i <= n; i ++) cin >> num[i];
    for (int i = 1; i <= n; i ++) diff[i] = num[i] - num[i - 1];

    int m; cin >> m;
    for (int i = 0; i < m; i ++) {
        int l, r, x;
        cin >> l >> r >> x;
        diff[l] += x, diff[r + 1] -= x;
    }

    for (int i = 1; i <= n; i ++) num[i] = diff[i] + num[i - 1];
    for (int i = 1; i <= n; i ++) prefix[i] = num[i] + prefix[i - 1];

    int q; cin >> q;
    for (int i = 0; i < q; i ++) {
        int l, r;
        cin >> l >> r;
        cout << prefix[r] - prefix[l - 1] << '\n';
    }
    
    return 0;
}
```

$diff$ 		拥有良好的==修改性==

$prefix$ 	    拥有良好的==查询性==

---

#### *4. 二维前缀和*

将原先的一维前缀和扩展至二维时

| $num[0][0]$ | $num[0][1]$ | $num[0][2]$ |
| :---------- | ----------- | ----------- |
| $num[1][0]$ | $num[1][1]$ | $num[1][2]$ |
| $num[2][0]$ | $num[2][1]$ | $num[2][2]$ |

$prefix[1][1] = num[0][0] + num[0][1] + num[1][0] + num[1][1]$

以此类推...

 $prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + num[i][j]$

对于一块对角线定点分别为$[i][j]$和$[a][b]$的矩形有：

$result_{[i][j]-[a][b]} = prefix[a][b] - prefix[a][j - 1] - prefix[i - 1][b] + prefix[i - 1][j - 1]$

---

#### *5. 二维差分*

对于二维的差分数组，我们不直接通过原数组求$diff$而是把差分数组全部赋为0，在diff修改以达到差分的性质，如下：

```c++
for (int i = 1; i <= n; i ++) 
	for (int j = 1; j <= m; j ++) {
		d[i][j] += num[i][j];
		d[i + 1][j] -= num[i][j];
		d[i][j + 1] -= num[i][j];
		d[i + 1][j + 1] += num[i][j];
	}
```

对二维的$diff$数组做前缀和，我们可以得到$num[i][j]$

$num[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + diff[i][j]$

对于一块$l,r$与$i,j$为顶点的一块矩形，对矩形内的元素整体修改可以写成：

```c++
diff[l][r] += x;
diff[i + 1][j + 1] += x;
diff[l][j + 1] -= x;
diff[i][r + 1] -= x;
```