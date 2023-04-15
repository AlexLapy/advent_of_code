from timeit import default_timer as timer
from datetime import timedelta


from Day_5.day_5 import Day_05


def main():

    startSolA = timer()
    Solver = Day_05()
    Solver.PrintSolutionA()
    endSolA = timer()
    print(f"Puzzle01 took : { timedelta(seconds = endSolA - startSolA) }")

    startSolB = timer()
    Solver = Day_05()
    Solver.PrintSolutionB()
    endSolB = timer()
    print(f"Puzzle02 took : { timedelta(seconds = endSolB - startSolB) }")


if __name__ == "__main__":
    main()
