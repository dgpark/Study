def ConvertToS(line):
    timeList = line[1].split(":")
    finishTime = int(timeList[0])*3600 + int(timeList[1])*60 + float(timeList[2])
    startTime = round(finishTime - float(line[2][:-1]) + 0.001, 3)
    
    return [startTime, finishTime]

def solution(lines):
    answer = 0
    inputList = []
    timeLog = []
    
    for i in range(0,len(lines)):
        inputList.append([])
        inputList[i] = lines[i].split(' ')
        
    for i in range(0,len(inputList)):
        timeLog.append([])
        timeLog[i] = ConvertToS(inputList[i])
    
    for i in range(0, len(lines)):
        count=1
        for j in range(i+1,len(lines)):
            if (timeLog[i][1]+1>timeLog[j][0]):
                count+=1
        if (answer < count) :
            answer = count
            
    return answer

# https://programmers.co.kr/learn/courses/30/lessons/17676?language=python3
