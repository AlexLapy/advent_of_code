
from helper import my_helper
from itertools import permutations
import sys
import numpy as np


class Day_09():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_9/day_9.txt")
        self.mst = list()
        self.node = list()

        self.V = 0
        self.graph = list()
        self.node_enum = set()
    

    #117
    def PrintSolutionA(self):
        
        print(self.FindShortDistance(shortest = True))

    #909
    def PrintSolutionB(self):
        print(self.prims_setup())



    def FindShortDistance(self, shortest = False, longest = False):
        
        mapLocation = dict()
        locationSet = set()

        for line in self.PuzzleInput:

            (source, _, dest, _, distance) = line.split()
            locationSet.add(source)
            locationSet.add(dest)
            
            #Try_emplace 
            mapLocation.setdefault(source, dict())[dest] = int(distance)
            mapLocation.setdefault(dest, dict())[source] = int(distance)

        shortestPath = sys.maxsize
        longestPath = 0

        for items in permutations(locationSet):
            #add dist between AB-BC-CD-DE ...
            newPath = sum(map(lambda x, y: mapLocation[x][y], items[:-1], items[1:]))
            shortestPath = min(shortestPath, newPath)
            longestPath = max(longestPath, newPath)

        if (shortest):
            return shortestPath
        elif (longest):
            return longestPath

            

    
    def kruskal_setup(self):

        for line in self.PuzzleInput:
            (source, _, dest, _, distance) = line.split()
            self.node_enum.add(source)
            self.node_enum.add(dest)
        

        self.V = len(self.node_enum)
        self.node_enum = list(self.node_enum)


        for line in self.PuzzleInput:
            (source, _, dest, _, distance) = line.split()
            source_index = self.node_enum.index(source)
            dest_index = self.node_enum.index(dest)

            self.add_edge(int(source_index), int(dest_index), int(distance))
        
        

        self.graph = sorted(self.graph, key=lambda item: item[2])

        

        return self.kruskal_algo()


    def add_edge(self, u, v, w):
        self.graph.append((u, v, w))

    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])


    def apply_union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    #  Applying Kruskal algorithm
    def kruskal_algo(self):
        result = []
        i, e = 0, 0
       
        parent = []
        rank = []
        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        while e < self.V - 1:
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.apply_union(parent, rank, x, y)



        path_lengh = 0
        for _, _, weight in result:
            path_lengh += weight

        for u, v, weight in result:
            print("%d - %d: %d" % (u, v, weight))

        return path_lengh
            



    def prims_setup(self):

        for line in self.PuzzleInput:
            (source, _, dest, _, distance) = line.split()
            self.node_enum.add(source)
            self.node_enum.add(dest)
        

        self.V = len(self.node_enum)
        self.node_enum = list(self.node_enum)
        self.node_enum.sort(reverse=True)

        INF = sys.maxsize

        G = np.zeros((self.V, self.V))

        for line in self.PuzzleInput:
            (source, _, dest, _, distance) = line.split()
            source_index = self.node_enum.index(source)
            dest_index = self.node_enum.index(dest)
            
            G[source_index, dest_index] = distance
        
        selected = np.zeros((self.V))

        no_edge = 0

        selected[0] = True

        path_lenght = 0

        while (no_edge < self.V - 1):
            # For every vertex in the set S, find the all adjacent vertices
            #, calculate the distance from the vertex selected at step 1.
            # if the vertex is already in the set S, discard it otherwise
            # choose another vertex nearest to selected vertex  at step 1.
            minimum = INF
            x = 0
            y = 0
            for i in range(self.V):
                if selected[i]:
                    for j in range(self.V):
                        if ((not selected[j]) and G[i, j]):  
                            # not in selected and there is an edge
                            if minimum > G[i, j]:
                                minimum = G[i, j]
                                x = i
                                y = j
            print(str(x) + "-" + str(y) + ":" + str(G[x, y]))
            path_lenght += G[x, y]
            selected[y] = True
            no_edge += 1


        return path_lenght