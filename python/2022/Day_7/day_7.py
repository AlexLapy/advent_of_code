from helper import my_helper
import numpy as np


class folder:
    def __init__(self, name: str, parent=None):
        self.name: str = name
        self.parent: folder = parent
        self.children: list = []

    def add_parent(self, parent):
        self.parent: folder = parent

    def add_child(self, child):
        self.children.append(child)

    def get_children(self):
        return self.children

    def get_parent(self):
        return self.parent

    def get_name(self):
        return self.name

    def get_size(self):
        size = 0
        for child in self.children:
            if isinstance(child, file):
                size += child.get_size()
            elif isinstance(child, folder):
                size += child.get_size()
        return size

    def add_file(self, file_name, size):
        new_file: file = file(file_name, self, size)
        self.add_child(new_file)

    def add_folder(self, folder_name):
        new_folder: folder = folder(folder_name, self)
        self.add_child(new_folder)


class file():
    def __init__(self, name, parent, size):
        self.name: str = name
        self.parent: folder = parent
        self.size: int = int(size)

    def get_size(self):
        return self.size

    def get_name(self):
        return self.name

    def get_parent(self):
        return self.parent

    def add_parent(self, parent):
        self.parent = parent


class file_system():
    def __init__(self):
        self.root = folder("/", None)

    def find_folder_in_current_folder(self, parent: folder, folder_name: str) -> folder:
        for child in parent.get_children():
            if isinstance(child, folder):
                if child.get_name() == folder_name:
                    return child

    def find_file_in_current_folder(self, parent: folder, file_name: str) -> file:
        for child in parent.get_children():
            if isinstance(child, file):
                if child.get_name() == file_name:
                    return child

    def print_file_system(self):
        self.print_child(self.root)

    def print_child(self, child):
        if isinstance(child, folder):
            level = self.find_level_of_folder(child)
            print("\t" * level, end="")
            print(f"{child.get_name()}\t")

            if child.get_children() is not None:
                for child in child.get_children():
                    self.print_child(child)
                print("\n")

        elif isinstance(child, file):
            level = self.find_level_of_file(child)
            print("\t" * level, end="")
            print(f"{child.get_name():8} {child.get_size():,}")

    def get_total_size(self):
        total_size = 0
        for child in self.root.get_children():
            if isinstance(child, folder):
                total_size += child.get_size()
            if isinstance(child, file):
                total_size += child.get_size()
        return total_size

    def find_level_of_folder(self, folder_: folder):
        level = 0
        while folder_.get_parent() is not None:
            level += 1
            folder_ = folder_.get_parent()
        return level

    def find_level_of_file(self, file_: file):
        level = 0
        while file_.get_parent() is not None:
            level += 1
            file_ = file_.get_parent()
        return level

    def find_all_folders(self):
        all_folders = []
        self.find_all_folders_recursive(self.root, all_folders)
        return all_folders

    def find_all_folders_recursive(self, folder_: folder, all_folders: list):
        all_folders.append(folder_)
        for child in folder_.get_children():
            if isinstance(child, folder):
                self.find_all_folders_recursive(child, all_folders)


class Day_07():

    def __init__(self):
        self.PuzzleInput = my_helper.ReadAllLine("Day_7/day_7.txt")
        self.fs = file_system()

    # 1297159
    def PrintSolutionA(self):
        print(self.part_1())

    # 3866390
    def PrintSolutionB(self):
        print(self.part_2())

    def part_1(self):
        self.build_file_system()
        return self.find_sum_of_all_folders()

    def part_2(self):
        self.build_file_system()
        return self.space_of_folder_to_be_removed()

    def build_file_system(self):

        current_folder = self.fs.root
        for line in self.PuzzleInput[1:]:

            if line.startswith("$ cd .."):
                current_folder = current_folder.get_parent()

            elif line.startswith("$ cd"):
                folder_name = line.split(" ")[2]
                folder_ = self.fs.find_folder_in_current_folder(current_folder,
                                                                folder_name)
                if folder_ is None:
                    current_folder.add_folder(folder_name)
                current_folder = self.fs.find_folder_in_current_folder(
                    current_folder, folder_name)

            elif line.startswith("$ ls"):
                pass

            elif line.startswith("dir"):
                folder_name = line.split(" ")[1]
                if self.fs.find_folder_in_current_folder(current_folder, folder_name) is None:
                    current_folder.add_folder(folder_name)

            elif line.split(" ")[0].isnumeric():
                file_name = line.split(" ")[1]
                file_size = line.split(" ")[0]
                if self.fs.find_file_in_current_folder(current_folder, file_name) is None:
                    current_folder.add_file(file_name, file_size)

        # self.fs.print_file_system()

    def find_sum_of_all_folders(self):
        folders = self.fs.find_all_folders()
        folders_size = np.array([fld.get_size() for fld in folders
                                if isinstance(fld, folder)])
        return np.sum(folders_size[folders_size < 100_000])

    def space_of_folder_to_be_removed(self):
        max_space = 70_000_000
        needed_space = 30_000_000

        current_total_space = self.fs.get_total_size()
        to_be_deleted_space = needed_space - (max_space - current_total_space)

        folders: list[folder] = self.fs.find_all_folders()

        folders_size = np.array([fld.get_size() for fld in folders
                                if isinstance(fld, folder)])

        fs_with_enough_space = folders_size[folders_size >=
                                            to_be_deleted_space]
        return np.sort(fs_with_enough_space)[0]
