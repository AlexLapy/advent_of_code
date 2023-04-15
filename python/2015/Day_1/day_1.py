
from helper import my_helper
    


class Day_01():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_1/day_1.txt")
    
    #232
    def PrintSolutionA(self):
        print(self.FindFloor())

    #1783
    def PrintSolutionB(self):
        print(self.FindPosition())


    def FindFloor(self):

        currentFloor = 0

        for char in self.PuzzleInput[0]:
            if char == '(':
                currentFloor += 1
            if char == ')':
                currentFloor -= 1

        return currentFloor

    def FindPosition(self):

        currentPosition = 0
        currentFloor = 0

        for char in self.PuzzleInput[0]:
            currentPosition += 1

            if char == '(':
                currentFloor += 1
            if char == ')':
                currentFloor -= 1

            if currentFloor == -1:
                return currentPosition

        return -1

