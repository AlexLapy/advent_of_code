
from helper import my_helper
from collections import defaultdict
import re

"""

Need optimization with itertools or ..
For-loop > while ...

"""


class Day_15():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_15/day_15.txt")
    

    #18965440   Puzzle01 took : 0:21:23.140209
    def PrintSolutionA(self):
        print("self.FindMaxProperties(False)")

    #15862900   Puzzle02 took : 0:04:33.365909
    def PrintSolutionB(self):
        print(self.FindMaxProperties(True))

    

    def FindMaxProperties(self, calories_bool):
        
        
        ingredients_map = defaultdict(dict)

        for line in self.PuzzleInput:

            words = re.findall(r'\w\w+', line)
            numbers = re.findall(r'-?\d+', line)

            ingredient_name = words[0]
            proportie_1_name = words[1]
            proportie_1_value = int(numbers[0])
            proportie_2_name = words[2]
            proportie_2_value = int(numbers[1])
            proportie_3_name = words[3]
            proportie_3_value = int(numbers[2])
            proportie_4_name = words[4]
            proportie_4_value = int(numbers[3])
            proportie_5_name = words[5]
            proportie_5_value = int(numbers[4])

            ingredients_map[ingredient_name][proportie_1_name] = proportie_1_value
            ingredients_map[ingredient_name][proportie_2_name] = proportie_2_value
            ingredients_map[ingredient_name][proportie_3_name] = proportie_3_value
            ingredients_map[ingredient_name][proportie_4_name] = proportie_4_value
            ingredients_map[ingredient_name][proportie_5_name] = proportie_5_value
            ingredients_map[ingredient_name]["quantity"] = 0


        i = 0
        total_score = 0
        while (i <= 100 ** len(ingredients_map)):

            value1 = i % 100
            value2 = (i // 100) % 100
            value3 = (i // 10000) % 100
            value4 = (i // 1000000) % 100
            if value1 + value2 + value3 + value4 > 100:
                i += 1
                continue
           

            for x, ingredient in enumerate(ingredients_map):
                if x == 0:
                    ingredients_map[ingredient]["quantity"] = value1
                if x == 1:
                    ingredients_map[ingredient]["quantity"] = value2
                if x == 2:
                    ingredients_map[ingredient]["quantity"] = value3
                if x == 3:
                    ingredients_map[ingredient]["quantity"] = value4

            
            if calories_bool:
                calories = 0
                for ingredient in ingredients_map:
                    calories += ingredients_map[ingredient][proportie_5_name] * ingredients_map[ingredient]["quantity"]

                if calories != 500:
                    i += 1
                    continue

            capacity = 0
            durablility = 0
            flavor = 0
            texture = 0
            
            for ingredient in ingredients_map:
                capacity += ingredients_map[ingredient][proportie_1_name] * ingredients_map[ingredient]["quantity"]
                durablility += ingredients_map[ingredient][proportie_2_name] * ingredients_map[ingredient]["quantity"]
                flavor += ingredients_map[ingredient][proportie_3_name] * ingredients_map[ingredient]["quantity"]
                texture += ingredients_map[ingredient][proportie_4_name] * ingredients_map[ingredient]["quantity"]

            capacity = capacity if capacity > 0 else 0
            durablility = durablility if durablility > 0 else 0
            flavor = flavor if flavor > 0 else 0
            texture = texture if texture > 0 else 0

            current_score = capacity * durablility * flavor * texture

            total_score = max(total_score, current_score)
            #if current_score > total_score:
            #    total_score = current_score

            i += 1

        return total_score
        
