from timeit import default_timer as timer
from datetime import timedelta


from Day_9.day_9 import Day_09


def main():

    startSolA = timer()
    Solver = Day_09()
    Solver.PrintSolutionA()
    endSolA = timer()
    print(f"Puzzle01 took : { timedelta(seconds = endSolA - startSolA) }")

    startSolB = timer()
    Solver = Day_09()
    Solver.PrintSolutionB()
    endSolB = timer()
    print(f"Puzzle02 took : { timedelta(seconds = endSolB - startSolB) }")


if __name__ == "__main__":
    main()
