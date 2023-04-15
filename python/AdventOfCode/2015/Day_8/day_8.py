
from helper import my_helper



class Day_08():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_8/day_8.txt")
    

    #1342
    def PrintSolutionA(self):
        print(self.FindSpace())

    #2074
    def PrintSolutionB(self):
        print(self.FindSpacev2())



    def FindSpace(self):

        space = 0
        for line in self.PuzzleInput:
            space += len(line) - len(eval(line))

        return space

    def FindSpacev2(self):

        surrondingsQuotes = 2
        space = 0
        for line in self.PuzzleInput:
            space += line.count('\\') + line.count('"') + surrondingsQuotes

        return space
