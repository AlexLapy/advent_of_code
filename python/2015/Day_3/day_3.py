
from helper import my_helper
    



class Day_03():

    choice = {  "<" : (-1,0),
            ">" : (1,0),
            "^" : (0,1),
            "v" : (0,-1)  }


    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_3/day_3.txt")
    


    #2592
    def PrintSolutionA(self):
        print(self.HouseCount())


    #2360
    def PrintSolutionB(self):
        print(self.HouseCountRobot())




    def HouseCount(self):
        x = 0
        y = 0

        houseVisited = { (0,0) }

        for direction in self.PuzzleInput[0]:

            move = Day_03.choice[direction]

            x += move[0]
            y += move[1]

            houseVisited.add((x,y))

        return len(houseVisited)



    def HouseCountRobot(self):
        santaX = 0
        santaY = 0

        robotX = 0
        robotY = 0

        houseVisited = { (0,0) }

        for i in range(len(self.PuzzleInput[0])):

            #Robot
            if (i % 2):
                move = Day_03.choice[self.PuzzleInput[0][i]]
                robotX += move[0]
                robotY += move[1]
                houseVisited.add( (robotX, robotY) )

            #Santa
            else:
                move = Day_03.choice[self.PuzzleInput[0][i]]
                santaX += move[0]
                santaY += move[1]
                houseVisited.add( (santaX, santaY) )

        return len(houseVisited)


 