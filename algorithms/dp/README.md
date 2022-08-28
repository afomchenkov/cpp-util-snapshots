# 1 Minimum (Maximum) Path to Reach a Target

### _Statement_
 - Given a target find minimum (maximum) cost / path / sum to reach the target.
### _Approach_
 - Choose minimum (maximum) path among all possible paths before the current state, then add value for the current state.

```cpp
routes[i] = min(routes[i-1], routes[i-2], ... , routes[i-k]) + cost[i]
```
> Generate optimal solutions for all values in the target and return the value for the target.

```cpp
// top-down
for (int j = 0; j < ways.size(); ++j) {
    result = min(result, topDown(target - ways[j]) + cost/ path / sum);
}
return memo[/*state parameters*/] = result;
```

```cpp
// bottom-up
for (int i = 1; i <= target; ++i) {
   for (int j = 0; j < ways.size(); ++j) {
       if (ways[j] <= i) {
           dp[i] = min(dp[i], dp[i - ways[j]] + cost / path / sum) ;
       }
   }
}
 
return dp[target]
```
# 2 Distinct Ways

### _Statement_
 - Given a target find a number of distinct ways to reach the target.
### _Approach_
 - Sum all possible ways to reach the current state.

```cpp
routes[i] = routes[i-1] + routes[i-2], ... , + routes[i-k]
```

> Generate sum for all values in the target and return the value for the target.

```cpp
// top-down
for (int j = 0; j < ways.size(); ++j) {
    result += topDown(target - ways[j]);
}
return memo[/*state parameters*/] = result;
```
```cpp
// bottom-up
for (int i = 1; i <= target; ++i) {
   for (int j = 0; j < ways.size(); ++j) {
       if (ways[j] <= i) {
           dp[i] += dp[i - ways[j]];
       }
   }
}
 
return dp[target]
```

# 3 Merging Intervals

### _Statement_
 - Given a set of numbers find an optimal solution for a problem considering the current number and the best you can get from the left and right sides.
### _Approach_
 - Find all optimal solutions for every interval and return the best possible answer.

> Get the best from the left and right sides and add a solution for the current position. 

```cpp
// from i to j
dp[i][j] = dp[i][k] + result[k] + dp[k+1][j]
```

```cpp
// top-down
for (int k = i; k <= j; ++k) {
    result = max(result, topDown(nums, i, k-1) + result[k] + topDown(nums, k+1, j));
}
return memo[/*state parameters*/] = result;
```
```cpp
// bottom-up
for(int l = 1; l<n; l++) {
   for(int i = 0; i<n-l; i++) {
       int j = i+l;
       for(int k = i; k<j; k++) {
           dp[i][j] = max(dp[i][j], dp[i][k] + result[k] + dp[k+1][j]);
       }
   }
}
 
return dp[0][n-1];
```

# 4 DP on Strings
> General problem statement for this pattern can vary but most of the time you are given two strings where lengths of those strings are not big

### _Statement_
 - Given two strings s1 and s2, return some result.
### _Approach_
 - Most of the problems on this pattern requires a solution that can be accepted in O(n^2) complexity.

 ```cpp
// i - indexing string s1
// j - indexing string s2
for (int i = 1; i <= n; ++i) {
   for (int j = 1; j <= m; ++j) {
       if (s1[i-1] == s2[j-1]) {
           dp[i][j] = /*code*/;
       } else {
           dp[i][j] = /*code*/;
       }
   }
}
 ```
> If you are given one string s the approach may little vary

```cpp
for (int l = 1; l < n; ++l) {
   for (int i = 0; i < n-l; ++i) {
       int j = i + l;
       if (s[i] == s[j]) {
           dp[i][j] = /*code*/;
       } else {
           dp[i][j] = /*code*/;
       }
   }
}
```

```cpp
// longest common subsequence
for (int i = 1; i <= n; ++i) {
   for (int j = 1; j <= m; ++j) {
       if (text1[i-1] == text2[j-1]) {
           dp[i][j] = dp[i-1][j-1] + 1;
       } else {
           dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
       }
   }
}
```

```cpp
// palindromic substring
for (int l = 1; l < n; ++l) {
   for (int i = 0; i < n-l; ++i) {
       int j = i + l;
       if (s[i] == s[j] && dp[i+1][j-1] == j-i-1) {
           dp[i][j] = dp[i+1][j-1] + 2;
       } else {
           dp[i][j] = 0;
       }
   }
}
```

# 5 Decision Making

> The general problem statement for this pattern is forgiven situation decide whether to use or
> not to use the current state. So, the problem requires you to make a decision at a current state.

### _Statement_
 - Given a set of values find an answer with an option to choose or ignore the current value.
### _Approach_
 - If you decide to choose the current value use the previous result where the value was ignored; vice-versa, if you decide to ignore the current value use previous result where value was used.

```cpp
// i - indexing a set of values
// j - options to ignore j values
for (int i = 1; i < n; ++i) {
   for (int j = 1; j <= k; ++j) {
       dp[i][j] = max({dp[i][j], dp[i-1][j] + arr[i], dp[i-1][j-1]});
       dp[i][j-1] = max({dp[i][j-1], dp[i-1][j-1] + arr[i], arr[i]});
   }
}
```
