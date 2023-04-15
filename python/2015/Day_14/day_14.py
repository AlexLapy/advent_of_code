
from helper import my_helper
from collections import defaultdict
import re


class Day_14():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_14/day_14.txt")
    

    #2640
    def PrintSolutionA(self):
        print(self.FindMaxDistance())

    #1102
    def PrintSolutionB(self):
        print(self.FindLeadingDeer())

    

    def FindMaxDistance(self):
        
        nameSet = set()
        deerMap = defaultdict(dict)
        
        for line in self.PuzzleInput:

            words = re.findall(r'\w+', line)
            numbers = re.findall(r'\d+', line)

            deerName = words[0]

            nameSet.add(deerName)
            
            deerMap[deerName]["speed"] = int(numbers[0])
            deerMap[deerName]["endurance"] = int(numbers[1])
            deerMap[deerName]["rest"] = int(numbers[2])

        distances = []
        for deer in nameSet:

            speed = deerMap[deer]["speed"]
            endu = deerMap[deer]["endurance"]
            rest = deerMap[deer]["rest"]

            time = 0
            distance = 0
            window = endu + rest
         
            while (time < 2503):
                
                if time % window < endu:
                    distance += speed

                time += 1


            distances.append(distance)



        return max(distances)
        

    def FindLeadingDeer(self):
        
        nameSet = set()
        deerMap = defaultdict(dict)
        
        for line in self.PuzzleInput:

            words = re.findall(r'\w+', line)
            numbers = re.findall(r'\d+', line)

            deerName = words[0]

            nameSet.add(deerName)
            
            deerMap[deerName]["speed"] = int(numbers[0])
            deerMap[deerName]["endurance"] = int(numbers[1])
            deerMap[deerName]["rest"] = int(numbers[2])
            deerMap[deerName]["distance"] = 0
            deerMap[deerName]["points"] = 0


        time = 0
        while (time < 2503):
            for deer in nameSet:
                speed = deerMap[deer]["speed"]
                endu = deerMap[deer]["endurance"]
                rest = deerMap[deer]["rest"]
                window = endu + rest

                if time % window < endu:
                    deerMap[deer]["distance"] += speed

            leaderName = ""
            leaderDist = 0
            for currentDeer in nameSet:
                currentDist = deerMap[currentDeer]["distance"]
                if  currentDist > leaderDist:
                    leaderName = currentDeer
                    leaderDist = currentDist
            
            deerMap[leaderName]["points"] += 1
            time += 1



        deersPoints = []
        for deer in nameSet:
            deersPoints.append(deerMap[deer]["points"])
        



        return max(deersPoints)