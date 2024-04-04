import os
import sys
import re
import shutil


def scan_dir(path_to_dir: str, pathes: dict) -> None:
    walker = os.walk(path_to_dir)
    for (dirpath, dirnames, filenames) in walker:
        for file in filenames:
            pathes[file] = dirpath + '/' + file


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

# print(source_files)

shutil.copyfile(target, out_file)

included = {"#pragma once"}

flag = True

# '''
while flag:
    flag = False
    with open(out_file, "r") as file:
        out_file_temp = file.read()
        curr_includes = re.findall(r'^#include <.*?\.hpp>', out_file_temp, flags=re.MULTILINE)
        # includes = list(map(lambda x : x[10:-1], includes))
        # print(includes)
        # break
    while len(curr_includes) > 0 and curr_includes[0] in included:
        curr_includes.pop(0)
    # print(includes)
    if len(curr_includes) > 0:
        flag = True
        text_temp = curr_includes[0][10:-1]
        print(text_temp)
        with open(out_file, "r+") as file:
            file.truncate()
            for line in out_file_temp.split('\n'):
                # print(line)
                if line not in included:
                    # print(text_temp)
                    # print(line == text_temp)
                    if line == curr_includes[0] and text_temp in source_files.keys():
                        print(line)
                        included.add("#include <" + text_temp + ">")
                        with open(source_files[text_temp], 'r') as include_file:
                            for source_line in include_file.read().split('\n'):
                                if source_line not in included:
                                    file.write(source_line + '\n')
                                else:
                                    print("LINE : ", source_line)
                    else:
                        file.write(line + '\n')

print(included)
# '''
