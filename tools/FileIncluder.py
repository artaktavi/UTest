import os
import sys
import re
import shutil


def scan_dir(path_to_dir: str, pathes_dict: dict) -> None:
    walker = os.walk(path_to_dir)
    for (dirpath, dirnames, filenames) in walker:
        for file in filenames:
            pathes_dict[file] = dirpath + '/' + file


source_files = dict()

target = sys.argv[1]
out_file = sys.argv[2]

for dir_path in sys.argv[3:]:
    curr_path = os.path.abspath(os.getcwd()) + '/' + dir_path
    if os.path.isabs(dir_path):
        curr_path = dir_path
    if curr_path[-1] == '/':
        curr_path = curr_path[0:-1]
    scan_dir(curr_path, source_files)

shutil.copyfile(target, out_file)

lines_ignore = {"#pragma once"}


def include_to_file(old_file_text: str, path_to_file: str, include_text: str, include_line: str,
                    source_files_pathes: dict,
                    lines_to_ignore: set) -> None:
    with open(path_to_file, "r+") as file_to_write:
        file_to_write.truncate()
        for line in old_file_text.split('\n'):
            if line not in lines_to_ignore:
                if line == include_line:
                    lines_to_ignore.add("#include <" + include_text + ">")
                    if include_text in source_files_pathes.keys():
                        print("file included: " + include_text)
                        with open(source_files_pathes[include_text], 'r') as include_file:
                            for source_line in include_file.read().split('\n'):
                                if source_line not in lines_to_ignore:
                                    file_to_write.write(source_line + '\n')
                    else:
                        print(
                            "HeaderIncluder error : there is no include file: " + include_text + " in passed directories")
                else:
                    file_to_write.write(line + '\n')


flag = True

while flag:
    flag = False
    with open(out_file, "r") as file:
        out_file_old_text = file.read()
        curr_includes = re.findall(r'^#include <.*?\.hpp>', out_file_old_text, flags=re.MULTILINE)
    while len(curr_includes) > 0 and curr_includes[0] in lines_ignore:
        curr_includes.pop(0)
    if len(curr_includes) > 0:
        flag = True
        include_to_file(out_file_old_text, out_file, curr_includes[0][10:-1], curr_includes[0], source_files,
                        lines_ignore)
