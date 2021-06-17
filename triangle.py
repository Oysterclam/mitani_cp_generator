import scipy
from tkinter import Tk, Canvas, Frame, BOTH
from random import seed
from random import random
from scipy.spatial import Delaunay
import numpy as np
import math
from functools import cmp_to_key

seed()

scale = 300
offset_x = 10
offset_y = 10

non_edge_points = 5
edge_random_multiplier = 1

def rotation_ordered_neighbors(G,points,s):
    neighbors = [points[i] for i in range(0,len(G)) if G[s][i]==1 and not i == s]
    return sorted(neighbors, key=lambda p : math.atan2(p[0] - points[s][0], p[1] - points[s][1]))

def bfs(G,s):
    #returns a list of lists. 
    #list[i] is a list which contains the vertices traversed to get to vertex i
    #list[i] includes s but not i
    V = len(G)
    visited = [0 for x in G]
    prev = [-1 for x in G]
    dist = [math.inf for x in G]
    tovisit = []

    visited[s]=1
    for i in range(V):
        if G[s][i] == 1:
            tovisit.append(i)
            prev[i]=s
            dist[i]=1
    prev[s]=-1
    dist[s]=0
    while not tovisit == []:
        i = tovisit.pop(0)
        if visited[i]==0:
            visited[i]=1
            for j in range(V):
                if G[i][j] == 1:
                    if visited[j]==0:
                        if dist[j] >= dist[i] + 1:
                            tovisit.append(j)
                            prev[j]=i
                            dist[j]=dist[i] + 1
    paths = []
    for i in range(len(prev)):

        path = []
        j = i
        while not prev[j]==-1:
            j = prev[j]
            path.append(j)
        path.reverse()
        paths.append(path)

    return paths


def order_tuple(lst):
	if lst[0] <= lst[1]:
		return lst		
	else:
		return [lst[1],lst[0]]

def triangulation_to_lines(tri):
    #list of triplets of lines to a list of lines
	lines = []
	for triangle in tri:
		lines.append([triangle[0],triangle[1]])
		lines.append([triangle[1],triangle[2]])
		lines.append([triangle[2],triangle[0]])
	return lines

class crease_pattern(Frame):

    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):
    	#initialization I copied
        self.master.title("Square")
        self.pack(fill=BOTH, expand=5)
        canvas = Canvas(self)

        #the square
        square = [[offset_x,offset_y],
                    [scale+offset_x,offset_y],
                    [scale+offset_x,scale+offset_y],
                    [offset_x,scale+offset_y]]

        #initializing points
        points = []
        points.extend(square)
        for i in range(0,non_edge_points):
            points.append([random()*scale+offset_x,random()*scale+offset_y])
        for i in range(0,1+int(random()*edge_random_multiplier)):
            points.append([offset_x,random()*scale+offset_y])
        for i in range(0,1+int(random()*edge_random_multiplier)):
            points.append([scale+offset_x,random()*scale+offset_y])
        for i in range(0,1+int(random()*edge_random_multiplier)):
            points.append([random()*scale+offset_x,offset_y])
        for i in range(0,1+int(random()*edge_random_multiplier)):
            points.append([random()*scale+offset_x,scale+offset_y])

        #initializing graph adjacency matrix
        graph = []
        for i in range(len(points)):
            row = []
            for j in range(len(points)):
                row.append(0)
            graph.append(row)
            graph[i][i]=1

        #triangulating 
        tri = Delaunay(np.array(points)).simplices  

        #removing duplicate line references in triangulation
        lines = []
        # [lines.append(x) for x in [order_tuple(x) for x in triangulation_to_lines(tri)] if x not in lines]
        [lines.append(x) for x in triangulation_to_lines(tri)]
        
        #initializing adjacency matrix
        for line in lines:
            graph[line[0]][line[1]]=1
            graph[line[1]][line[0]]=1
        
        #for comaparison before editing lines
        points1 = [[x[0]+scale+offset_x,x[1]] for x in points]
        for i in range(len(points1)):
            canvas.create_oval(points1[i][0], points1[i][1], points1[i][0], points1[i][1], width = 5, fill = 'green')
            canvas.create_text(points1[i][0], points1[i][1], fill="green",font="Times 20 italic bold",text=str(i))
        for i in range(len(graph)):
            for j in range(len(graph)):
                if graph[i][j]==1:
                    canvas.create_line(points1[i][0], points1[i][1], points1[j][0], points1[j][1])
        #draw square
        for i in range(0,4):
            canvas.create_line(square[i][0]+scale+offset_x, square[i][1], square[(i+1)%4][0]+scale+offset_x, square[(i+1)%4][1])


        #calculating degree of each vertex
        #ignore the corners and edges of square using non_edge_points counter
        degrees = []
        for i in range(4,non_edge_points+4):
            deg = 0
            for j in range(len(graph)):
                if graph[i][j]==1:
                    deg+=1  
            degrees.append(deg-1)

        #brute bfs for path distance between all points
        paths = []
        for i in range(len(graph)):
            paths.append(bfs(graph,i))
        
        #printing 
        print(degrees)
        # print(points)
        # print(lines)
        # for i in range(len(graph)):
        #     for j in range(len(graph)):
        #         print(graph[i][j], end = ' ')
        #     print()
        # for i in range(len(paths)):
        #     for j in range(len(paths)):
        #         print(paths[i][j], end = ' ')
        #     print()

        #get
        odd = [i for i in range(0,len(degrees)) if degrees[i]%2==1]
        print(odd)

        #delete paths between odd vertices, paired in order
        #we use the bfs created shortest paths to achieve this
        for i in range(0,int(len(odd)/2)):
            s=odd[2*i]
            t=odd[2*i+1]
            path = paths[s][t]
            path.reverse()
            for p in path:
                graph[p][t]=0
                graph[t][p]=0
                t=p
        # for i in range(len(graph)):
        #     for j in range(len(graph)):
        #         print(graph[i][j], end = ' ')
        #     print()

        degrees = []
        for i in range(len(graph)):
            deg = 0
            for j in range(len(graph)):
                if graph[i][j]==1:
                    deg+=1
            degrees.append(deg-1)
        
        print(degrees)
        test = rotation_ordered_neighbors(graph,points,0)
        print(rotation_ordered_neighbors(graph,points,0))

        #doing angles 
        #note: kind of broken for reflexive angles
        angle_list = []
        for i in range(len(graph)):
            rotation_ordered = rotation_ordered_neighbors(graph,points,i)
            angles = []
            neighbors = len(rotation_ordered)
            for j in range(neighbors):
                x1 = rotation_ordered[j][0]-points[i][0]
                y1 = rotation_ordered[j][1]-points[i][1]
                x2 = rotation_ordered[(j+1)%neighbors][0]-points[i][0]
                y2 = rotation_ordered[(j+1)%neighbors][1]-points[i][1]

                norm1 = math.pow(x1*x1+y1*y1,0.5)
                norm2 = math.pow(x2*x2+y2*y2,0.5)
                dot_prod_norm = min((x1*x2+y1*y2)/norm1/norm2,1)
                dot_prod_norm = max(dot_prod_norm,-1)
                angles.append(math.acos(dot_prod_norm)*180/math.pi)
            angle_list.append(angles)
        print(angle_list)
        for i in range(4,non_edge_points+4):
            print(sum(angle_list[i]))

        #drawing all lines and points
        for i in range(len(points)):
            canvas.create_oval(points[i][0], points[i][1], points[i][0], points[i][1], width = 5, fill = 'green')
            canvas.create_text(points[i][0], points[i][1], fill="green",font="Times 20 italic bold",text=str(i))
        for i in range(len(test)):
            canvas.create_oval(test[i][0], test[i][1], test[i][0], test[i][1], width = 5, fill = 'green')
            canvas.create_text(test[i][0], test[i][1], fill="red",font="Times 40 italic bold",text=str(i))
        for i in range(len(graph)):
            for j in range(len(graph)):
                if graph[i][j]==1:
                    canvas.create_line(points[i][0], points[i][1], points[j][0], points[j][1])
        #draw square
        for i in range(0,4):
            canvas.create_line(square[i][0], square[i][1], square[(i+1)%4][0], square[(i+1)%4][1])

        canvas.pack(fill=BOTH, expand=1)

def main():
    root = Tk()
    ex = crease_pattern()
    root.geometry("630x320+500+300")
    root.mainloop()

main()