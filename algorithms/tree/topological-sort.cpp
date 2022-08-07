/**
 * @file topological-sort.cpp
 * @author Aliaksandr Famchankou (afamchankou@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
 * 1. Identify all nodes with no incoming edges and add those nodes to topological sort
 *   - create queue 'order', which will store the topological sort
 *   - create queue 'processNext', this will store the next nodes to process
 *   - count the number of incoming edges of each node and set instance node.inbound
 * 2. While traversing dfs tree, remove them from the tree and add to result
 *   - walk through the nodes again and add to 'processNext' any node where x.bound == 0
 *   - while 'processNext' is not empty, do the following:
 *     * remove first node from 'processNext'
 *     * for each edge(n, x) decrement x.inbound, if x.inbound == 0, append x to 'processNext'
 *     * append it to 'order'
 * 3. Repeat step untill all done
 *   if 'order' contains all the nodes, then it has succeeded, otherwise it failed due to cycles
 */