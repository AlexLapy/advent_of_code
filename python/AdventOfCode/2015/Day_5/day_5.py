
from helper import my_helper




class Day_05():

    vowels = {'a','e','i','o','u'}

    single = {'a','b','c','d','e','f','g',
               'h','i','j','k','l','m','n',
               'o','p','q','r','s','t','u',
               'v','w','x','y','z' }

    doubles = {'aa','bb','cc','dd','ee','ff','gg',
               'hh','ii','jj','kk','ll','mm','nn',
               'oo','pp','qq','rr','ss','tt','uu',
               'vv','ww','xx','yy','zz' }

    disallowed = {'ab', 'cd', 'pq', 'xy'}



    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_5/day_5.txt")
    

    #236
    def PrintSolutionA(self):
        print(self.FindNiceStringsV1())


    #51
    def PrintSolutionB(self):
        print(self.FindNiceStringsV2())


    def FindNiceStringsV1(self):

        niceStringsCounts = 0

        for line in self.PuzzleInput:
            
            doubleFound = False
            disallowedNotFound = True

            EnoughVowel = len(["Found" for word in line if word in Day_05.vowels]) >= 3
               
            doubleFound = len(["Found" for double in Day_05.doubles if double in line]) >= 1

            disallowedNotFound = len(["Found" for disallowed in Day_05.disallowed if disallowed in line]) == 0


            #for doubles in Day_05.doubles:
            #    if (doubles in line):
            #        doubleFound = True
            #        break

            #for disallowed in Day_05.disallowed:
            #    if (disallowed in line):
            #        disallowedNotFound = False
            #        break

            if ( EnoughVowel and doubleFound and disallowedNotFound):
                niceStringsCounts += 1

        return niceStringsCounts


    def FindNiceStringsV2(self):

        niceStringsCounts = 0

        for line in self.PuzzleInput:
            
            repeatsFound = False
            pairFound = False

            for i in range(len(line) - 2):
                if (line[i] == line[i + 2]):
                    repeatsFound = True
                    break

            for i in range(len(line) - 1):
                pair = line[i : i + 2]
                for i in range(i + 2, len(line) - 1):
                    if (pair == line[i : i + 2]):
                        pairFound = True
                        break
                if (pairFound):
                    break
            
            if (repeatsFound and pairFound):
                niceStringsCounts += 1
            
        return niceStringsCounts