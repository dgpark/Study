data = input()
if len(data)>100:
    print("data length is too long")
else :
    lst = [-1 for i in range(26)]
    for i in range(0,len(data)):
        if lst[ord(data[i])-97] == -1:
            lst[ord(data[i])-97] = i
    for i in range(len(lst)):
        print(lst[i], end = " ")
