
from helper import my_helper

import re
import json


class Day_12():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_12/day_12.txt")
    

    #
    def PrintSolutionA(self):
        print(self.FindSumNumberRegex())

    #
    def PrintSolutionB(self):
        print(self.FindSumNumberJson())

    

    def FindSumNumberRegex(self):

        text = self.PuzzleInput[0]

        #allNumber = re.findall(r'[-]?\d{1,4}', text)
        #allNumber = [int(x) for x in allNumber] --> map(int, iter)
        #return sum(allNumber)

        return sum(map(int, re.findall("-?[0-9]+", text)))
        

    def FindSumNumberJson(self):

        #JSON with recursive
        #data = json.loads(open('Day_12/day_12.txt', 'r').read())
        #return self.sum_numbers(data)
        
        #JSON with hook + regex
        data = open('Day_12/day_12.txt', 'r').read()
        stuff = str(json.loads(data, object_hook=self.hook))
        return sum(map(int, re.findall("-?[0-9]+", stuff)))



    def hook(self, obj):

        if "red" in obj.values(): 
            return {}

        else: 
            return obj


    #def sum_numbers(self, obj):

    #    if type(obj) == type(dict()):

    #        #Comment both for sol A
    #        if "red" in obj.values():
    #            return 0

    #        return sum(map(self.sum_numbers, obj.values()))

    #    if type(obj) == type(list()):
    #        return sum(map(self.sum_numbers, obj))

    #    if type(obj) in [str]:
    #        return 0

    #    if type(obj) in [int, float]:
    #        return obj

