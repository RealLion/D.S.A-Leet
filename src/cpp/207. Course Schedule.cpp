/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
click to show more hints.

Hints:
This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
Topological sort could also be done via BFS.
*/
#include <common.hpp>
using std::unordered_set;
using std::pair;

class Solution
{
public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<int> indegrees = cal_indegree(graph);

        for (int i = 0; i < numCourses; i++)
        {
            // 所有顶点的indegree都不为0，则所有顶点一起构成一个圈
            int j = 0;
            for (; j < numCourses; j++)
                if (!indegrees[j])
                    break;
            if (j == numCourses)
                return false;

            // 顶点j的indegree为0，可作为拓扑排序的第一个顶点，也即第一门上的课
            indegrees[j] = -1;
            for (int neigh : graph[j])
                indegrees[neigh]--;
        }
        return true;
    }

private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        //Adjacency lists
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre.second].insert(pre.first);
        return graph;
    }
    vector<int> cal_indegree(vector<unordered_set<int>> &graph)
    {
        vector<int> indegrees(graph.size(), 0);
        for (auto neighbors : graph)
            for (int neigh : neighbors)
                indegrees[neigh]++;
        return indegrees;
    }
};

/*
输入的prerequisites表示一个graph
ref 拓扑排序 http://blog.csdn.net/changyuanchn/article/details/17067349

bfs 
将prerequisites构造成一个图，看这个图是否能完成拓扑排序。有圈的图无法完成拓扑排序。
！！！但是这和bfs有什么关系？
*/