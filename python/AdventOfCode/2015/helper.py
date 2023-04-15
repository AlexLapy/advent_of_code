


class my_helper():


    @staticmethod
    def ReadAllLine(fileName):

        puzzleInput = []
        with open(fileName, encoding="utf-8") as inputFile:
                  puzzleInput = inputFile.read().splitlines()

        return puzzleInput


    @staticmethod
    def ApplyOnBoolMatrix(matrix, command, startX, startY, endX, endY):
        
        if (command == 'on'):
            matrix[startX : endX + 1, startY : endY + 1] = 1
        elif (command == 'off'):
            matrix[startX : endX + 1, startY : endY + 1] = 0
        elif (command == 'toggle'):
            matrix[startX : endX + 1, startY : endY + 1] = 1 - matrix[startX : endX + 1, startY : endY + 1]

        return matrix


    
        
        