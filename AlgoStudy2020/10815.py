''' #Method1
N = int(input())
nCard = set(map(int, input().split()))
M = int(input())
mCard = list(map(int, input().split()))

for i in range(0,M):
    num = mCard[i]
    if num in nCard:
        print(1, end = " ")
    else :
        print(0, end = " ")
'''

#method2
def binary_search(list, m):
    l = 0
    r = len(list)-1

    while(l<=r):
        mid = int((l+r)/2)
        if list[mid] == m:
            return 1
        elif list[mid] > m:
            r = mid - 1
        else :
            l = mid + 1

    return 0

N = int(input())
nCard = list(map(int, input().split()))
M = int(input())
mCard = list(map(int, input().split()))

nCard = sorted(nCard)

for i in range(M):
    print(binary_search(nCard, mCard[i]), end = " ")
