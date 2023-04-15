
from helper import my_helper
from collections import defaultdict
import re


class Day_06():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_6/day_6.txt")

    #
    def PrintSolutionA(self):
        print(self.find_packet_marker())

    #
    def PrintSolutionB(self):
        print(self.find_messsage_marker())

    def find_packet_marker(self):

        signal = self.PuzzleInput[0]
        string_len = 4
        for index in range(string_len, len(signal)):

            current_packet = signal[index-string_len:index]
            
            is_a_start_of_packet = len(set(current_packet)) == string_len
            if is_a_start_of_packet:
                return index
            
    def find_messsage_marker(self):

        signal = self.PuzzleInput[0]
        string_len = 14
        for index in range(string_len, len(signal)):

            current_packet = signal[index-string_len:index]
            
            is_a_start_of_packet = len(set(current_packet)) == string_len
            if is_a_start_of_packet:
                return index
