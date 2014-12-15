#!/usr/bin/env python
#-*- encoding=utf-8 -*-
import sys

def readmap(filename):
	graph={}
	with open(filename,'r') as mapfile:
		line=mapfile.readline()
		directed=int(line[:-1])
		line=mapfile.readline()
		nodes=line[:-1].split(' ')
		for node in nodes:
			graph[int(node)]=[]
		for line in mapfile:
			node1,node2=line[:-1].split('\t')
			graph[int(node1)].append(int(node2))
			if not directed:
				graph[int(node2)].append(int(node1))
	return graph

def dfs(map,prevnode,startnode,nexttable,prevtable,visited,record,tag):
	if visited[startnode]:
		#prevnode->startnode 1
		record[(prevnode,startnode)]=1
		if (startnode,prevnode) in record:
			if startnode in prevtable:
				prevtable[startnode].append(prevnode)
			else:
				prevtable[startnode]=[]
				prevtable[startnode].append(prevnode)
		return
	#print startnode,'!'
	tag[startnode]=len(tag)+1
	visited[startnode]=1
	if prevnode!=-1:
		if prevnode in nexttable:
			nexttable[prevnode].append(startnode)
		else:
			nexttable[prevnode]=[]
			nexttable[prevnode].append(startnode)
	for neibor in map[startnode]:
		dfs(map,startnode,neibor,nexttable,prevtable,visited,record,tag)

def suffix(node,prevtable,nexttable,value,tag):
	if node in nexttable:
		for inode in nexttable[node]:
			suffix(inode,prevtable,nexttable,value,tag)
	numv=tag[node]
	numw,low=100,100
	if node in prevtable:
		for prev in prevtable[node]:
			if tag[prev]<numw:
				numw=tag[prev]
	if node in nexttable:
		for neibor in nexttable[node]:
			if value[neibor][1]<low:
				low=value[neibor][1]
	lowofme=min(numv,numw,low)
	value[node]=(tag[node],lowofme)

def dfs_tree(map):
	nexttable={}
	prevtable={}
	record={}
	startnode,prevnode=0,-1
	visited={}.fromkeys(map.keys(),0)
	tag={}
	dfs(map,prevnode,startnode,nexttable,prevtable,visited,record,tag)

	#print prevtable
	#print nexttable
	#print tag
	value={}.fromkeys(map.keys(),None)
	
	suffix(startnode,prevtable,nexttable,value,tag)

	return nexttable,value

def check(nexttable,value):
	cutnodes=[]
	for node in nexttable:
		if node==0:#root
			if len(nexttable[node])>1:
				cutnodes.append(node)
		else:
			for neibor in nexttable[node]:
				if value[neibor][1]>=value[node][0]:
					cutnodes.append(node)
	return cutnodes

if __name__ == '__main__':
	map=readmap(sys.argv[1])
	nexttable,value=dfs_tree(map)
	cutnodes=check(nexttable,value)
	print cutnodes