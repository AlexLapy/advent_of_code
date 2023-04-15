
from helper import my_helper
    

import hashlib


class Day_04():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_4/day_4.txt")
    

    #346386
    def PrintSolutionA(self):
        print(self.FindMD5Value(5))


    #9958218
    def PrintSolutionB(self):
        print(self.FindMD5Value(6))


    def FindMD5Value(self,numberOfZeros):

        number = 0
        hashstart = self.PuzzleInput[0]
        
        while(number < 10**7):
            name = (hashstart + str(number))
            hashValue = hashlib.md5(name.encode('utf-8')).hexdigest()

            if all(v == '0' for v in hashValue[:numberOfZeros]):
                return number

            number += 1

 