
from helper import my_helper
import re


class Day_05():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_4/day_4.txt")

    #
    def PrintSolutionA(self):
        print("")

    #
    def PrintSolutionB(self):
        print(self.find_crate_at_top_of_stack())

    def find_crate_at_top_of_stack(self):

        for line in self.PuzzleInput[:4]:
            print(line)
