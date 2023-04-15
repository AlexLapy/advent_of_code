
from helper import my_helper


class Day_03():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_3/day_3.txt")
    
    # 7872
    def PrintSolutionA(self):
        print(self.Find_total_sum_of_priorites_solo())

    # 2497
    def PrintSolutionB(self):
        print(self.Find_total_sum_of_priorites_group())


    def Find_total_sum_of_priorites_solo(self):

        types = []

        for line in self.PuzzleInput:
            first_part = line[0:int(len(line)/2)]
            second_part = line[int(len(line)/2):]

            for type in first_part:
                if type in second_part:
                    types.append(type)
                    break
        
        return sum([ord(x) - 96 if x.islower() else ord(x) - 38 for x in types])

        
    def Find_total_sum_of_priorites_group(self):

        types = []

        for i, line in enumerate(self.PuzzleInput):

            first_part =  self.PuzzleInput[i] if i % 3 == 0 else ""
            second_part = self.PuzzleInput[i + 1] if i % 3 == 0 else ""
            third_part = self.PuzzleInput[i + 2] if i % 3 == 0 else ""

            for type in first_part:
                if type in second_part and type in third_part:
                    types.append(type)
                    break

            

        return sum([ord(x) - 96 if x.islower() else ord(x) - 38 for x in types])
        

        

