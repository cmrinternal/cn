import heapq

def prims_mst(graph, start):
    n = len(graph)
    visited = [False]*n
    key = [float('inf')]*n
    parent = [-1]*n
    key[start] = 0
    min_heap = [(0, start)]

    while min_heap:
        _, u = heapq.heappop(min_heap)
        if visited[u]: continue
        visited[u] = True
        for v, w in enumerate(graph[u]):
            if w and not visited[v] and w < key[v]:
                key[v], parent[v] = w, u
                heapq.heappush(min_heap, (key[v], v))

    print("\nMinimum Spanning Tree:")
    for i in range(1, n):
        print(f"Edge: {chr(parent[i]+65)} - {chr(i+65)}, Weight: {graph[i][parent[i]]}")

def broadcast(graph, current, visited):
    print(f"Node {chr(current + 65)} received the packet.")
    visited[current] = True
    for i, w in enumerate(graph[current]):
        if w and not visited[i]:
            broadcast(graph, i, visited)

n = int(input("Enter number of nodes: "))
graph = [list(map(int, input().split())) for _ in range(n)]
start = int(input(f"Enter the starting node (0 to {n-1}): "))

prims_mst(graph, start)
print("\nStarting broadcast:")
broadcast(graph, start, [False]*n)
