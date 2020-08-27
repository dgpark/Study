'''
#Best Method

result = 0
for i in range(int(input())):
    word = input()
    # key=word.find -> sorted by character order which is found in word
    if list(word) == sorted(word, key=word.find):
        result += 1
print(result)

'''

#myMethod
#myMethod Point : 문자열의 알파벳 덩어리 순서대로 dictionary key 값을 1로 변경
#만약 문자열에서 group number가 아닌 떨어져 있는 알파벳이 나올 경우, dictionary 값이 이미 1로 저장되어 있기 때문에 group number가 아님을 확인 가능.

def CheckGroupWord(list,N):

    sum = len(list)
    for i in range(N):
        #change list to set
        checkSet = set(list[i])
        #change set to dictionary
        checkSet = dict.fromkeys(checkSet,0)
        for j in range(len(list[i])) :
            if j == 0 :
                checkSet[list[i][j]] += 1
            elif list[i][j-1] != list[i][j] :
                if checkSet[list[i][j]] == 0 :
                    checkSet[list[i][j]] += 1
                else :
                    sum -= 1
                    break
    return sum


N = int(input())

strings = list()

for i in range(N):
    strings.append(input())

print(CheckGroupWord(strings,N))
