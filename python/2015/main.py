from timeit import default_timer as timer
from datetime import timedelta


from Day_15.day_15 import Day_15


def main():

    startSolA = timer()
    Solver = Day_15()
    Solver.PrintSolutionA()
    endSolA = timer()
    print(f"Puzzle01 took : { timedelta(seconds = endSolA - startSolA) }")

    startSolB = timer()
    Solver = Day_15()
    Solver.PrintSolutionB()
    endSolB = timer()
    print(f"Puzzle02 took : { timedelta(seconds = endSolB - startSolB) }")




if __name__ == "__main__":
    main()