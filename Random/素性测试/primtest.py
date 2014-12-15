#!/usr/bin/env python
#-*- encoding=utf-8 -*-

from random import randint

limits=2**16

def primtest(a,b,c):#return a**b%c
	#print c
	result=1
	while b>0:
		#print b
		if b&1:
			result*=a
		if a*a%c==1 and a!=1 and a!=c-1:
			return 0
		a=a*a%c
		b>>=1
	return result%c==1

def basemethod():
	primtable={}.fromkeys(range(1,limits),0)
	primtable[1]=1
	for i in primtable.keys()[1:]:
		if not primtable[i]:
			current=i
			while current+i<limits:
				primtable[current+i]=1
				current+=i
	return primtable

if __name__=='__main__':
	mydict=basemethod()
	primset=set([x for x in mydict if not mydict[x]])
	print len(primset)
	ferma=[]
	for i in range(1,limits):
		#status=1
		#for j in range(10):
		if primtest(randint(1,limits)%i,i-1,i):
			#	status=0
			#	break
		#if status:
			ferma.append(i)
	print len(ferma)
	fermaset=set(ferma)
	print 'shouldbe=',primset-fermaset
	print 'shouldn\'tbe=',fermaset-primset
	print 'pi=',len(fermaset-primset)#*1.0/len(fermaset)*100
