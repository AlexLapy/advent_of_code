from helper import my_helper
import numpy as np


class Day_08():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_8/day_8.txt")

    # 1672
    def PrintSolutionA(self):
        print(self.find_visible_tree_from_outside())

    # 327180
    def PrintSolutionB(self):
        print(self.find_highest_scenic_score())

    def create_matrix_from_input(self):
        matrix = np.array([])

        for line in self.PuzzleInput:
            matrix = np.append(matrix, [int(num) for num in list(line)])

        return matrix.reshape((len(self.PuzzleInput), len(self.PuzzleInput[0])))

    def find_visible_tree_from_outside(self):

        trees_grid = self.create_matrix_from_input()

        visible_trees = np.ones(trees_grid.shape)
        visible_trees[1:-1, 1:-1] = 0

        for i in range(1, trees_grid.shape[0] - 1):
            # Looking from the top
            a_up = trees_grid[0:-1, i]
            b_up = trees_grid[1:, i]
            depth_up = self.find_depth_of_view_part_1(a_up, b_up)
            visible_trees[1:, i] += depth_up

            # Looking from the bottom
            a_bottom = np.flip(b_up)
            b_bottom = np.flip(a_up)
            depth_bottom = self.find_depth_of_view_part_1(a_bottom, b_bottom)
            visible_trees[0:-1, i] += np.flip(depth_bottom)

        for i in range(1, trees_grid.shape[1] - 1):
            # Looking from the left
            a_left = trees_grid[i, 0:-1]
            b_left = trees_grid[i, 1:]
            depth_left = self.find_depth_of_view_part_1(a_left, b_left)
            visible_trees[i, 1:] += depth_left

            # Looking from the right
            a_right = np.flip(b_left)
            b_right = np.flip(a_left)
            depth_right = self.find_depth_of_view_part_1(a_right, b_right)
            visible_trees[i, 0:-1] += np.flip(depth_right)

        visible_trees = np.where(visible_trees > 0, 1, 0)
        print(visible_trees)
        return np.sum(visible_trees)

    def find_depth_of_view_part_1(self, a, b):
        print("A = ", a)
        print("B = ", b)

        n = len(a)
        depth_array = np.zeros(n)

        tallest = a[0]
        for i in range(n):
            if a[i] < b[i] and b[i] > tallest:
                tallest = b[i]
                depth_array[i] = 1

        print("Depth_array =", depth_array)
        print("\n")
        return depth_array

    def find_depth_of_view_part_2(self, a, b):

        n = len(a)
        depth_array = np.zeros(n)

        depth_array[0] = 1

        current_tree_height = a[0]
        if n >= 2:
            for i in range(1, n):
                if b[i-1] < current_tree_height:
                    depth_array[i] = 1
                else:
                    break

        return depth_array

    def find_highest_scenic_score(self):

        trees_grid = self.create_matrix_from_input()

        best_score = 0
        for off_i in range(1, trees_grid.shape[0] - 1):
            for off_j in range(1, trees_grid.shape[1] - 1):

                if off_i == 3 and off_j == 3:
                    print("stop")
                # Looking down
                a_down = trees_grid[off_i:-1, off_j]
                b_down = trees_grid[off_i+1:, off_j]
                depth_down = self.find_depth_of_view_part_2(a_down, b_down)
                down_score = sum([x for x in depth_down])

                # Looking up
                a_up = np.flip(trees_grid[1:off_i+1, off_j])
                b_up = np.flip(trees_grid[:off_i:, off_j])
                depth_up = self.find_depth_of_view_part_2(a_up, b_up)
                up_score = sum([x for x in depth_up])

                # Looking right
                a_right = trees_grid[off_i, off_j:-1]
                b_right = trees_grid[off_i, off_j+1:]
                depth_right = self.find_depth_of_view_part_2(a_right, b_right)
                right_score = sum([x for x in depth_right])

                # Looking left
                a_left = np.flip(trees_grid[off_i, 1:off_j+1])
                b_left = np.flip(trees_grid[off_i, :off_j])
                depth_left = self.find_depth_of_view_part_2(a_left, b_left)
                left_score = sum([x for x in depth_left])

                print("Up score = ", up_score)
                print("Down score = ", down_score)
                print("Left score = ", left_score)
                print("Right score = ", right_score)

                current_score = up_score * down_score
                current_score *= left_score * right_score
                print("Current score = ", current_score, " at ", off_i, off_j)
                print("\n")

                if current_score > best_score:
                    best_score = current_score

        return best_score
