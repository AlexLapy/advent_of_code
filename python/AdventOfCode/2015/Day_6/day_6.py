from helper import my_helper

import re
import numpy as np


class Day_06():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_6/day_6.txt")
    

    #400410
    def PrintSolutionA(self):
        print(self.FindNumberOfLitLights())


    #15343601
    def PrintSolutionB(self):
        print(self.FindBrightnessOfLights())




    def FindNumberOfLitLights(self):

        matrix = np.zeros((1000,1000))

        for line in self.PuzzleInput:

            command = re.findall(r'(on|off|toggle)',line)
            points = re.findall(r'\d+',line)
            points = [int(value) for value in points]

            matrix = my_helper.ApplyOnBoolMatrix(matrix, command[0], points[0], points[1],
                                                                     points[2], points[3])

        return np.count_nonzero(matrix)




    def FindBrightnessOfLights(self):

        matrix = np.zeros((1000,1000))

        for line in self.PuzzleInput:

            command = re.findall(r'(on|off|toggle)',line)
            points = re.findall(r'\d+',line)
            points = [int(value) for value in points]

            

            if (command[0] == 'on'):
                 matrix[points[0] : points[2] + 1, points[1] : points[3] + 1] += 1

            elif (command[0] == 'off'):
                 matrix[points[0] : points[2] + 1, points[1] : points[3] + 1] -= 1
                 matrix[matrix < 0] = 0
                 #np.clip(matrix, 0, None, out = matrix)
                 #matrix = matrix.clip(0)

            elif (command[0] == 'toggle'):
                 matrix[points[0] : points[2] + 1, points[1] : points[3] + 1] += 2


        return np.sum(matrix)
        