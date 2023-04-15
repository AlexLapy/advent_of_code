from timeit import default_timer as timer
from datetime import timedelta


from Day_4.day_4 import Day_04


def main():

    startSolA = timer()
    Solver = Day_04()
    Solver.PrintSolutionA()
    endSolA = timer()
    print(f"Puzzle01 took : { timedelta(seconds = endSolA - startSolA) }")

    startSolB = timer()
    Solver = Day_04()
    Solver.PrintSolutionB()
    endSolB = timer()
    print(f"Puzzle02 took : { timedelta(seconds = endSolB - startSolB) }")




if __name__ == "__main__":
    main()