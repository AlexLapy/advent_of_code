
from helper import my_helper
from collections import defaultdict
import re


class Day_05():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_5/day_5.txt")

    # ZSQVCCJLL
    def PrintSolutionA(self):
        print(self.find_crate_at_top_of_stack(crane_model=9000))

    # QZFJRWHGS
    def PrintSolutionB(self):
        print(self.find_crate_at_top_of_stack(crane_model=9001))

    def find_crate_at_top_of_stack(self, crane_model):

        stacks = defaultdict(list)

        # Find highest stack
        highest_stack = 0
        for line in self.PuzzleInput:
            if line[1] == "1":
                break
            highest_stack += 1

        # Fill the dict with the stacks
        for line in self.PuzzleInput[:highest_stack]:
            for num, col in enumerate(range(1, len(line), 4)):
                if line[col] != ' ':
                    stacks[num + 1].append(line[col])

        # Reverse the stacks list
        for key in stacks:
            stacks[key].reverse()

        # Move the boxes according to the procedure
        proc_start = highest_stack + 2
        for line in self.PuzzleInput[proc_start:]:
            procedure = re.findall(r'\d+', line)
            move, from_, to = procedure

            # Move the boxes from one stack to another
            if crane_model == 9000:
                for _ in range(int(move)):
                    stacks[int(to)].append(stacks[int(from_)].pop())

            if crane_model == 9001:
                temp_stack = []
                for _ in range(int(move)):
                    temp_stack.append(stacks[int(from_)].pop())
                temp_stack.reverse()
                stacks[int(to)].extend(temp_stack)

        # Return the top box of all stacks
        top_box_list = [stacks[key_num][-1]
                        for key_num in range(1, len(stacks) + 1)]
        return ''.join(top_box_list)
