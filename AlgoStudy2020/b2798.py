N, M = map(int, input().split())
card = list(map(int, input().split()))

card = sorted(card)
max = 0
sum=0


for i in range(N-1, 1, -1):
    if card[i] + card[1] + card[0] > M:
        continue
    for j in range(i-1, 0, -1):
        #if card[i] + card[j] + card[0] > M:
        #    continue
        for k in range(j-1, -1, -1):
            sum = card[i] + card[j] + card[k]
            if sum == M:
                max = sum
            elif max < sum < M:
                max = sum

print(max)
