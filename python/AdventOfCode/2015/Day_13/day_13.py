

from helper import my_helper
from collections import defaultdict
from itertools import permutations
import re


class Day_13():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_13/day_13.txt")
    

    #618
    def PrintSolutionA(self):
        print(self.FindMaxHappiness(False))

    #601
    def PrintSolutionB(self):
        print(self.FindMaxHappiness(True))

    

    def FindMaxHappiness(self, addingMe):
        
        mapHappiness = defaultdict(dict)
        nameSet = set()

        for line in self.PuzzleInput:

            words = re.findall(r'\w+', line)
            amount = int(re.findall(r'\d+', line)[0])

            sign = -1 if words[2] == "lose" else 1
            amount *= sign
            
            person1 = words[0]
            person2 = words[-1]
          
            nameSet.add(person1)

            #Try_emplace 
            mapHappiness[person1][person2] = int(amount)
            

        if addingMe:
            for person in nameSet:
                mapHappiness["me"][person] = 0
                mapHappiness[person]["me"] = 0

            nameSet.add("me")

            

        overAllAmount = []

        for items in permutations(nameSet):
            #add dist between AB-BC-CD-DE ...
            startToEndClockwise = sum(map(lambda x, y: mapHappiness[x][y], items[:-1], items[1:]))
            EndToStartClockwise = mapHappiness[items[-1]][items[0]]

            startToEndAntiClockwise = sum(map(lambda x, y: mapHappiness[y][x], items[:-1], items[1:]))
            EndToStartAntiClockwise = mapHappiness[items[0]][items[-1]]
            
            totalClockwise = startToEndClockwise + EndToStartClockwise
            totalAntiClockwise = startToEndAntiClockwise + EndToStartAntiClockwise

            overAllAmount.append(totalClockwise + totalAntiClockwise)


        return max(overAllAmount)
        