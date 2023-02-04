#include <new>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>
#include <future>
#include <utility>
#include <tuple>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>
#include <functional>
#include <regex>
#include <bitset>
#include <iostream>

using namespace std;

struct Edge {
  int from;
  int to;
};

// Recall that a graph, G, is a tree iff the following two conditions are met:
// - G is fully connected. In other words, for every pair of nodes in G, there is a path between them.
// - G contains no cycles. In other words, there is exactly one path between each pair of nodes in G.

// ==================================================================
// Approach 1: Graph Theory + Iterative Depth-First Search
// ==================================================================

bool check_valid_graph(vector<Edge>& edges, int n) {
  // Adjacency list is where we have a list of sub-lists, where each sub-list is the list
  // of the immediate neighbours for the i'th node.
  //
  // The other 2 choices:
  // - adjacency matrix (if we know that the number of edges is substantially higher than the number of nodes)
  // - linked representation (where you make actual nodes objects)

  // Create a new list of lists.
  vector<vector<int>> adjacencyList;
  // Initialise an empty list for each node.
  for (int i = 0; i < n; i++) {
      adjacencyList.push_back(vector<int>{});
  }
  // Go through the edge list, populating the adjacency list.
  for (auto edge : edges) {
    adjacencyList[edge.from].push_back(edge.to);
    adjacencyList[edge.to].push_back(edge.from);
  }

  // - iterative DFS
  // Use a stack to keep track of unexplored nodes.
  stack<int> st;
  st.push(0);
  // Use a set to keep track of already seen nodes to avoid infinite looping. 
  set<int> seen;
  seen.insert(0);

  // While there are nodes remaining on the stack...
  while (!st.empty()) {
    int node = st.top(); // Take one off to visit.
    st.pop();

    // Check for unseen neighbours of this node:
    for (int neighbour : adjacencyList[node]) {
      if (seen.count(neighbour)) {
        continue; // Already seen this node.
      }
      // Otherwise, put this neighbour onto stack
      // and record that it has been seen.
      st.push(neighbour);
      seen.insert(neighbour);
    }
  }
  // - There are several strategies of detecting whether or not an undirected graph
  // contains cycles, while excluding the "trivial cycles".
  // - Most rely on the idea that a depth-first search should only go along
  // each edge once, and therefore only in one direction.
  // 1. The first strategy is to simply delete the opposite direction edges from the adjacency list. 
  //    In other words, when we follow an edge A → B, we should lookup Bs adjacency list and delete A
  //    from it, effectively removing the opposite edge of B → A.
  
  // While there are nodes remaining on the stack...
  while (!st.empty()) {
    int node = st.top(); // Take one off to visit.
    st.pop();
    // Check for unseen neighbours of this node:
    
    for (auto neighbour : adjacencyList[node]) {
      // Check if we've already seen this node.
      if (seen.count(neighbour)) {
        return false;
      }
      // Otherwise, put this neighbour onto stack
      // and record that it has been seen.
      st.push(neighbour);
      seen.insert(neighbour);
      // Remove the link that goes in the opposite direction.
      adjacencyList[neighbour].erase(node);
    }
  }

  // The second strategy is, instead of using a seen set, to use a seen map that also
  // keeps track of the "parent" node that we got to a node from.
  //
  // Use a map to keep track of how we got into each node.
  map<int, int> parent;
  parent[0] = -1;

  // While there are nodes remaining on the stack...
  while (!st.empty()) {
    int node = st.top(); // Take one off to visit.
    st.pop();
    
    // Check for unseen neighbours of this node:
    for (int neighbour : adjacencyList[node]) {
      // Don't look at the trivial cycle.
      if (parent[node] == neighbour) {
        continue;
      }
      // Check if we've already seen this node.
      if (parent.count(neighbour)) {
        return false; // There must be a cycle.
      }
      // Otherwise, put this neighbour onto stack
      // and record that it has been seen.
      st.push(neighbour);
      parent[neighbour] = node;
    }
  }

  // The best strategy for this problem is probably the second one, because it doesn't 
  // require modifying the adjacency list. For more complex graph problems, the first 
  // strategy can be useful though.


  // Return true if the DFS discovered ALL nodes.
  return seen.size() == n;
}

bool iterative_dfs(vector<Edge>& edges, int n) {
  vector<vector<int>> adjacencyList;

  for (int i = 0; i < n; i++) {
    adjacencyList.push_back(vector<int>{});
  }
  for (auto edge : edges) {
    adjacencyList[edge.from].push_back(edge.to);
    adjacencyList[edge.to].push_back(edge.from);
  }
  
  map<int, int> parent;
  parent[0] = -1;
  stack<iny> st;
  st.push(0);

  while (!st.empty()) {
    int node = st.top();
    st.pop();

    for (int neighbour : adjacencyList[node]) {
      if (parent[node] == neighbour) {
        continue;
      }

      if (parent.count(neighbour)) {
        return false;
      }

      st.push(neighbour);
      parent[neighbour] = node;
    }
  }
  
  return parent.size() == n;   
}


// Recursive solution
// The recursive approach is more elegant, but is considered inferior to the iterative version 
// in some programming languages, such as Python. This is because the space used by run-time 
// stacks vary between programming languages.
struct RecursiveDFS {
  vector<vector<int>> adjacencyList;
  set<int> seen;


  bool validTree(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) return false;
    
    for (int i = 0; i < n; i++) {
      adjacencyList.push_back(vector<int>{});
    }
    for (auto edge : edges) {
      adjacencyList[edge[0]].push_back(edge[1]);
      adjacencyList[edge[1]].push_back(edge[0]);
    }
    
    // We return true if no cycles were detected, AND the entire graph has been reached.
    return dfs(0, -1) && seen.size() == n;   
  }

  bool dfs(int node, int parent) {
    if (seen.count(node)) {
      return false;
    }

    seen.insert(node);
    for (int neighbour : adjacencyList[node]) {
      if (parent != neighbour) {
        bool result = dfs(neighbour, node);

        if (!result) {
          return false;
        }
      }
    }

    return true;
  }
}

// Iterative BFS
bool validTree(int n, vector<vector<int>>& edges) {       
  vector<vector<int>> adjacencyList;

  for (int i = 0; i < n; i++) {
    adjacencyList.push_back(vector<int>{});
  }
  for (auto edge : edges) {
    adjacencyList[edge[0]].push_back(edge[1]);
    adjacencyList[edge[1]].push_back(edge[0]);
  }
  
  map<int, int> parent;
  parent[0] = -1;
  queue<int> q;
  q.push_back(0);

  while (!q.empty()) {
    int node = q.front();
    q.pop_front();

    for (int neighbour : adjacencyList[node]) {
      if (parent[node] == neighbour) {
        continue;
      }

      if (parent.count(neighbour)) {
        return false;
      }

      q.push_back(neighbour);
      parent[neighbour] = node;
    }
  }
  
  return parent.size() == n;   
}

/**
 * Complexity Analysis
 * Let E be the number of edges, and N be the number of nodes.
 * - Time Complexity : O(N+E)
 *    Creating the adjacency list requires initialising a list of length N, 
 *    with a cost of O(N), and then iterating over and inserting E edges,
 *    for a cost of O(E). This gives us O(E)+ O(N) = O(N+E).
 * 
 * Each node is added to the data structure once. This means that the outer loop will run N times. 
 * For each of the N nodes, its adjacent edges is iterated over once. In total, 
 * this means that all E edges are iterated over once by the inner loop. This, therefore,
 * gives a total time complexity of O(N+E).
 * 
 * Because both parts are the same, we get a final time complexity of O(N+E).
 * 
 * - Space Complexity : O(N+E)
 *    The adjacency list is a list of length N, with inner lists with lengths that add to 
 *    a total of E. This gives a total of O(N+E) space.
 *    In the worst case, the stack/ queue will have all N nodes on it at the same time,
 *    giving a total of O(N) space.
 * 
 * In total, this gives us O(E+N) space.
 */


// ==================================================================
// Approach 2: Advanced Graph Theory + Iterative Depth-First Search
// ==================================================================
//
// For the graph to be a valid tree, it must have exactly n - 1 edges. Any less, and it can't 
// possibly be fully connected. Any more, and it has to contain cycles. Additionally, if the
// graph is fully connected and contains exactly n - 1 edges, it can't possibly contain a 
// cycle, and therefore must be a tree!

// Going by this definition, our algorithm needs to do the following:
// - Check whether or not there are n - 1 edges. If there's not, then return false.
// - Check whether or not the graph is fully connected. Return true if it is, false if otherwise
//
// We can can check for connectivity using recursive depth-first search, iterative depth-first search,
// or iterative breadth-first search. We still need to use a seen set to prevent the algorithm getting
// caught in an infinite loop if there are indeed cycles (and to prevent looping on the trivial cycles).

// iterative DFS approach 
bool validTree1(int n, vector<vector<int>>& edges) {
  if (edges.length != n - 1) {
    return false;
  }
  
  // Make the adjacency list.
  vector<vector<int>> adjacencyList;
  for (int i = 0; i < n; i++) {
    adjacencyList.push_back(vector<int>{});
  }
  for (auto edge : edges) {
    adjacencyList[edge[0]].push_back(edge[1]);
    adjacencyList[edge[1]].push_back(edge[0]);
  }
  
  stack<int> st;
  set<int> seen;
  st.push(0);
  seen.insert(0);
  
  while (!st.empty()) {
    int node = st.top();
    st.pop();
    
    for (int neighbour : adjacencyList[node]) {
      if (seen.count(neighbour)) {
        continue;
      }
      seen.insert(neighbour);
      stack.push(neighbour);
    }
  }
  
  return seen.size() == n;   
}

struct RecursiveDFS1 {
  vector<vector<int>> adjacencyList;
  set<int> seen;
  
  bool validTree(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) return false;
    
    // Make the adjacency list.
    for (int i = 0; i < n; i++) {
      adjacencyList.push_back(vector<int>{});
    }

    for (auto edge : edges) {
      adjacencyList[edge[0]].push_back(edge[1]);
      adjacencyList[edge[1]].push_back(edge[0]);
    }
    
    // Carry out depth first search.
    dfs(0);
    // Inspect result and return the verdict.
    return seen.size() == n;   
  }
  
  void dfs(int node) {
    if (seen.count(node)) {
      return;
    }

    seen.insert(node);
    for (auto neighbour : adjacencyList[node]) {
      dfs(neighbour);
    }
  }
}

// Iterative BFS
bool validTree(int n, vector<vector<int>>& edges) {
  if (edges.size() != n - 1) return false;
  
  // Make the adjacency list.
  vector<vector<int>> adjacencyList;

  for (int i = 0; i < n; i++) {
    adjacencyList.push_back(vector<int>{});
  }

  for (auto edge : edges) {
    adjacencyList[edge[0]].push_back(edge[1]);
    adjacencyList[edge[1]].push_back(edge[0]);
  }
  
  queue<int> q;
  set<int> seen;
  q.push(0);
  seen.insert(0);
  
  while (!q.empty()) {
    int node = queue.poll();

    for (int neighbour : adjacencyList.get(node)) {
      if (seen.contains(neighbour)) continue;
      seen.add(neighbour);
      queue.offer(neighbour);
    }
  }
  
  return seen.size() == n;   
}

// Complexity Analysis
// Let E be the number of edges, and N be the number of nodes.
// - Time Complexity : O(N)
// - Space Complexity : O(N)

// ==================================================================
// Approach 3: Advanced Graph Theory + Union Find
// ==================================================================

// For the graph to be a valid tree, it must have exactly n - 1 edges. Any less, and it can't possibly 
// be fully connected. Any more, and it has to contain cycles. Additionally, if the graph is fully connected 
// and contains exactly n - 1 edges, it can't possibly contain a cycle, and therefore must be a tree.

// Another way we could approach the problem is by considering each connected component to be a set of nodes.
// When an edge is put between two separate connected components, they are merged into a single connected component.

struct UnionFind {
  vector<int> parent;
  
  // For efficiency, we aren't using makeset, but instead initialising
  // all the sets at the same time in the constructor.
  UnionFind(int n) {
    parent = vector<int>(n);
    for (int node = 0; node < n; node++) {
      parent[node] = node;
    }
  }
  
  // The find method, without any optimizations. It traces up the parent
  // links until it finds the root node for A, and returns that root.
  int find(int A) {
    while (parent[A] != A) {
      A = parent[A];
    }
    return A;
  }

  // The unionise method, without any optimizations. It returns True if a
  // merge happened, False if otherwise.
  bool unionise(int A, int B) {
    // Find the roots for A and B.
    int rootA = find(A);
    int rootB = find(B);
    // Check if A and B are already in the same set.
    if (rootA == rootB) {
      return false;
    }
    // Merge the sets containing A and B.
    parent[rootA] = rootB;
    return true;
  } 
}

struct Solution1 {
  bool validTree(int n, vector<vector<int>>& edges) {
    // Condition 1: The graph must contain n - 1 edges.
    if (edges.size() != n - 1) return false;
    
    // Condition 2: The graph must contain a single connected component.
    // Create a new UnionFind object with n nodes. 
    UnionFind* unionFind = new UnionFind(n);
    // Add each edge. Check if a merge happened, because if it 
    // didn't, there must be a cycle.
    for (int[] edge : edges) {
      int A = edge[0];
      int B = edge[1];
      
      if (!unionFind.unionise(A, B)) {
        return false;
      }
    }
    
    // If we got this far, there's no cycles!
    return true;
  }
}

struct UnionFindCompressed {
  vector<int> parent;
  vector<int> size; // We use this to keep track of the size of each set.
  
  // For efficiency, we aren't using makeset, but instead initialising
  // all the sets at the same time in the constructor.
  UnionFindCompressed(int n) {
    parent = vector<int>(n);
    size = vector<int>(n);
    
    for (int node = 0; node < n; node++) {
      parent[node] = node;
      size[node] = 1;
    }
  }
  
  // The find method, with path compression. There are ways of implementing
  // this elegantly with recursion, but the iterative version is easier for
  // most people to understand!
  int find(int A) {
      // Step 1: Find the root.
      int root = A;
      while (parent[root] != root) {
          root = parent[root];
      }
      // Step 2: Do a second traversal, this time setting each node to point
      // directly at A as we go.
      while (A != root) {
          int oldRoot = parent[A];
          parent[A] = root;
          A = oldRoot;
      }
      return root;
  }

  // The unionise method, with optimization union by size. It returns True if a
  // merge happened, False if otherwise.
  bool unionise(int A, int B) {
    // Find the roots for A and B.
    int rootA = find(A);
    int rootB = find(B);
    // Check if A and B are already in the same set.
    if (rootA == rootB) {
        return false;
    }
    // We want to ensure the larger set remains the root.
    if (size[rootA] < size[rootB]) {
        // Make rootB the overall root.
        parent[rootA] = rootB;
        // The size of the set rooted at B is the sum of the 2.
        size[rootB] += size[rootA];
    } else {
        // Make rootA the overall root.
        parent[rootB] = rootA;
        // The size of the set rooted at A is the sum of the 2.
        size[rootA] += size[rootB];
    }

    return true;
  } 
}

class Solution2 {
  bool validTree(int n, vector<vector<int>>& edges) {
    // Condition 1: The graph must contain n - 1 edges.
    if (edges.size() != n - 1) return false;
    
    // Condition 2: The graph must contain a single connected component.
    // Create a new UnionFind object with n nodes. 
    UnionFind* unionFind = new UnionFind(n);
    // Add each edge. Check if a merge happened, because if it didn't, there must be a cycle.
    for (auto edge : edges) {
      int A = edge[0];
      int B = edge[1];
      
      if (!unionFind.union(A, B)) {
        return false;
      }
    }
    
    // If we got this far, there's no cycles!
    return true;
  }
}

int main()
{
  return 0;
}