
from helper import my_helper
    


class Day_02():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_2/day_2.txt")
    

    #1586300
    def PrintSolutionA(self):
        print(self.FindWrappingPaperOrder())


    #3737498 
    def PrintSolutionB(self):
        print(self.FindRibbonOrder())


    def FindWrappingPaperOrder(self):

        surfaceArea = 0

        for line in self.PuzzleInput:
            splitLine = line.split('x')

            
            l = int(splitLine[0])
            w = int(splitLine[1])
            h = int(splitLine[2])

            s1 = 2 * l * w
            s2 = 2 * w * h
            s3 = 2 * h * l

            surfaceArea += ( s1 + s2 + s3 + min(s1, s2, s3) / 2)


        return surfaceArea


    def FindRibbonOrder(self):

        wrapRibbon = 0
        bowRibbon = 0

        for line in self.PuzzleInput:
            splitLine = line.split('x')

            
            l = int(splitLine[0])
            w = int(splitLine[1])
            h = int(splitLine[2])

            
            smallestPerimeter = min( (2 * l + 2 * w), (2 * w + 2 * h), (2 * h + 2 * l) )

            wrapRibbon += smallestPerimeter
            bowRibbon += (l * w * h)


        return (wrapRibbon + bowRibbon)

