
from helper import my_helper



class Day_11():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_11/day_11.txt")
    

    #hepxxyzz --> 0:00:11.993435
    def PrintSolutionA(self):
        print(self.FindNextPassword(self.PuzzleInput[0]))

    #heqaabcc --> 0:00:42.538973
    def PrintSolutionB(self):
        print(self.FindNextPassword(self.FindNextPassword(self.PuzzleInput[0])))

    

    def FindNextPassword(self, password):
        
        req1 = [chr(97 + x) + chr(97 + x + 1) + chr( 97 + x + 2) for x in range(24)]
        req2 = {'i', 'o', 'l'}
        req3 = {'aa','bb','cc','dd','ee','ff','gg',
               'hh','ii','jj','kk','ll','mm','nn',
               'oo','pp','qq','rr','ss','tt','uu',
               'vv','ww','xx','yy','zz' }
   
        startPassword = password
        
        #Save alot of time (increment the first confusing letter)
        #Only for test 
        tmp = list(startPassword)
        for i in range(len(tmp)):
            if tmp[i] in req2:
                tmp[i] = chr(ord(tmp[i]) + 1)

                for j in range(len(tmp) - i - 1):
                    tmp[i + j + 1] = 'a'
                break

        startPassword = ''.join(tmp)
            

        nextPasswordFound = False
        while(nextPasswordFound == False):

            startPassword = startPassword[:-1] + chr(ord(startPassword[-1]) + 1)
            
            tmp = list(startPassword)
            
            for i in range(len(startPassword)-1):

                if (tmp[-(i+1)] == '{'):
                    tmp[-(i+1)] = 'a'
                    tmp[-(i+2)] = chr(ord(tmp[-(i+2)]) + 1)

            startPassword = ''.join(tmp)


            #req1
            req1Bool = False
            for straight in req1:
                if straight in startPassword:
                    req1Bool = True

            #req2
            req2Bool = False
            nbOfConfusingLettersFound = 0
            for confusingLetters in req2:
                if confusingLetters in startPassword:
                    nbOfConfusingLettersFound += 1
                    
                
            if (nbOfConfusingLettersFound == 0):
                req2Bool = True

            #req3
            req3Bool = False
            nbOfDoublesFound = 0
            for doubles in req3:
                if doubles in startPassword:
                    nbOfDoublesFound += 1

            if (nbOfDoublesFound >= 2):
                req3Bool = True

             
            if (req1Bool and req2Bool and req3Bool):
                nextPasswordFound = True


        return startPassword
