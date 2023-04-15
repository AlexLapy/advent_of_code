
from helper import my_helper



class Day_10():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_10/day_10.txt")
    

    #492982 --> 4.09 sec --> 3.41
    def PrintSolutionA(self):
        print(self.LookAndSay(40))

    #6989950 --> 59.92 sec --> 47.64
    def PrintSolutionB(self):
        print(self.LookAndSay(50))


    
    # John Conway
    def LookAndSay(self, NbOfTurn):

        startNumber = self.PuzzleInput[0]
        
        tempList = []

        for turn in range(NbOfTurn):

            tempList.clear()

            i = 0
            while( i < len(startNumber)):

                step = 0
              
                while((i + step) != len(startNumber)):
                    if (startNumber[i + step] == startNumber[i]):
                        step+=1
                    else:
                        break

                tempList.append(str(step) + startNumber[i])
                i += step

              
            startNumber = ''.join(tempList)

            #startNumber = tempList[0]
            #for x in tempList[1:]:
            #    startNumber += x


        return len(startNumber)
                

                

