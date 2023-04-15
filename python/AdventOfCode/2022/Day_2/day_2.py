
from helper import my_helper


class Day_02():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_2/day_2.txt")
    
    # 10718
    def PrintSolutionA(self):
        print(self.Find_total_score_with_strategy_guide())

    #
    def PrintSolutionB(self):
        print(self.Find_total_score_with_strategy_guide_v2())


    def Find_total_score_with_strategy_guide(self):
        
        shapes = {"X" : 1, "Y" : 2, "Z" : 3}
   
        conditions = {"A Z" : 0, "B X" : 0, "C Y" : 0,
                      "A X" : 3, "B Y" : 3, "C Z" : 3,
                      "A Y" : 6, "B Z" : 6, "C X" : 6}

        score = 0
        for line in self.PuzzleInput:
            opponent, me = line.split(" ")

            score += conditions[line]
            score += shapes[me]

        return score
            
    def Find_total_score_with_strategy_guide_v2(self):
        
        shapes = {"X" : 1, "Y" : 2, "Z" : 3}
   
        conditions = {"A Z" : 0, "B X" : 0, "C Y" : 0,
                      "A X" : 3, "B Y" : 3, "C Z" : 3,
                      "A Y" : 6, "B Z" : 6, "C X" : 6}

        endings = {"X" : 0, "Y" : 3, "Z" : 6}

        score = 0
        for line in self.PuzzleInput:
            opponent, ending = line.split(" ")

            score += endings[ending]

            me_possibilities = [x if conditions[x] == endings[ending] else "   " for x in conditions.keys()]
            me = [x[-1] if x[0] == opponent else "" for x in me_possibilities]
            score += shapes["".join(me)]

        return score