from helper import my_helper
import numpy as np
import re


class Day_09():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_9/day_9.txt")

    # 13740
    def PrintSolutionA(self):
        print(self.find_sum_signal_strength())

    # zuprfecl
    def PrintSolutionB(self):
        print(self.find_capital_letter())

    def find_sum_signal_strength(self):

        important_cycles: list[int] = [20, 60, 100, 140, 180, 220]
        signal_strength: list[int] = []
        x_value: int = 1
        cycle: int = 0
        for line in self.PuzzleInput:

            action = re.findall(r"[a-z]+", line)[0]
            value = re.findall(r"[0-9]+", line)
            sign = re.findall(r"[-]", line)

            if action == "noop":
                cycle += 1
                if cycle in important_cycles:
                    signal_strength.append(x_value)
                continue

            if action == "addx":

                for _ in range(2):
                    cycle += 1
                    if cycle in important_cycles:
                        signal_strength.append(x_value)

                if sign:
                    x_value -= int(value[0])
                else:
                    x_value += int(value[0])

        print(signal_strength)
        return sum([signal * cycle for signal, cycle in
                    zip(signal_strength, important_cycles)])

    def find_capital_letter(self):

        crt_screen: np.array = np.zeros((6, 40))
        crt_screen = crt_screen.flatten()
        current_pixel_x: int = 0

        x_value: int = 1
        sprite_pos: int = x_value
        cycle: int = 0
        for line in self.PuzzleInput:

            action = re.findall(r"[a-z]+", line)[0]
            value = re.findall(r"[0-9]+", line)
            sign = re.findall(r"[-]", line)

            if action == "noop":
                cycle += 1
                current_pixel_x = (cycle - 1) % 40
                if current_pixel_x in [sprite_pos - 1,
                                       sprite_pos, sprite_pos + 1]:
                    crt_screen[cycle - 1] = 1
                else:
                    crt_screen[cycle - 1] = 0
                continue

            if action == "addx":

                for _ in range(2):
                    cycle += 1
                    current_pixel_x = (cycle - 1) % 40
                    if current_pixel_x in [sprite_pos - 1,
                                           sprite_pos, sprite_pos + 1]:
                        crt_screen[cycle - 1] = 1
                    else:
                        crt_screen[cycle - 1] = 0

                if sign:
                    x_value -= int(value[0])
                else:
                    x_value += int(value[0])

                sprite_pos = x_value

        final_screen = crt_screen.reshape((6, 40))
        return final_screen
