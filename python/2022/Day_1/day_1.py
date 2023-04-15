
from helper import my_helper

from collections import defaultdict


class Day_01():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_1/day_1.txt")

    # 69693
    def PrintSolutionA(self):
        print(sum(self.Find_elf_carrying_the_most()[0][1]))

    # 200945
    def PrintSolutionB(self):
        print(self.Find_3_elf_carrying_the_most())

    def Find_elf_carrying_the_most(self):

        elfs = defaultdict(list)

        index = 0

        for line in self.PuzzleInput:
            try:
                elfs[index].append(int(line))
            except Exception:
                index += 1

        self.sorted_elfs = sorted(
            elfs.items(), key=lambda item: sum(item[1]), reverse=True)

        return self.sorted_elfs

    def Find_3_elf_carrying_the_most(self):
        return sum([sum(x[1]) for x in self.Find_elf_carrying_the_most()[0:3]])
