'''data = input().lower()
length = len(data)
max = 0
alpha_index = 0
multiple = False

alphabet = [0 for i in range(26)]

for i in range(0,length):
    index = ord(data[i])-97
    alphabet[index] += 1
    if alphabet[index] > max :
        max = alphabet[index]
        alpha_index = index
        multiple = False
    elif (alphabet[index] == max) and (alpha_index != alphabet[index]):
        multiple = True

if multiple == False :
    print(chr(ord('A')+alpha_index))
else :
    print("?")
'''

s,a=input().lower(),[]
for i in range(97,123):
 a.append(s.count(chr(i)))
print('?'if a.count(max(a))>1 else chr(a.index(max(a))+97).upper())
