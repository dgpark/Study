'''T = int(input())
lst = []
for i in range(0,T):
    line = input()
    R, S = line.split(" ")
    R = int(R)
    tempList=[]
    for j in range(0,len(S)):
        for k in range(0,R):
            tempList.append(S[j])
    lst.append(tempList)

for i in range(0,T):
    for j in range(0,len(lst[i])):
        print(lst[i][j], end="")
    print()
'''

T = int(input())
for i in range(T):
    a,b = input().split()
    for j in b:
        print(int(a)*j, end='')
    print()
