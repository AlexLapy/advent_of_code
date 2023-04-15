
from helper import my_helper


class Day_04():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_4/day_4.txt")
    
    # 
    def PrintSolutionA(self):
        print(self.Find_fully_contain_pairs())

    # 
    def PrintSolutionB(self):
        print(self.Find_overlap_pairs())


    def Find_fully_contain_pairs(self):

        count = 0

        for line in self.PuzzleInput:
            first_split = line.split(",")
            p11, p12 = [int(x) for x in first_split[0].split("-")]
            p21, p22 = [int(x) for x in first_split[1].split("-")]

            if (p11 >= p21 and p12 <= p22) or (p21 >= p11 and p22 <= p12):
                count += 1

        return count
        

    def Find_overlap_pairs(self):

        count = 0

        for line in self.PuzzleInput:
            first_split = line.split(",")
            p11, p12 = [int(x) for x in first_split[0].split("-")]
            p21, p22 = [int(x) for x in first_split[1].split("-")]
            a = [str(x) for x in list(range(p11,p12+1))]
            b = [str(x) for x in list(range(p21,p22+1))]

            for num in a:
                if num in b:
                    count += 1
                    break

        return count

