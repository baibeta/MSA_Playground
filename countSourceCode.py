import os
import re

def count_lines(file_path):
    comment_line = 0
    code_line = 0
    with open(file_path, 'r') as f:
        lines = f.readlines()
        in_block_comment = False
        for line in lines:
            line = line.strip()
            if len(line) == 0:
                continue
            if in_block_comment:
                if '*/' in line:
                    in_block_comment = False
                    line = line[line.index('*/') + 2:]
                    if len(line.strip()) == 0:
                        continue
                else:
                    comment_line += 1
                    continue
            if line.startswith('//'):
                comment_line += 1
                continue
            if '/*' in line:
                in_block_comment = True
                if '*/' in line:
                    in_block_comment = False
                    line = line[line.index('*/') + 2:]
                    if len(line.strip()) == 0:
                        continue
                else:
                    comment_line += 1
                    continue
            if line.strip() != '':
                code_line += 1
    return code_line, comment_line

def main():
    code_lines = 0
    comment_lines = 0
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file.endswith('.c'):
                file_path = os.path.join(root, file)
                lines, comments = count_lines(file_path)
                code_lines += lines
                comment_lines += comments
    print('code lines:', code_lines)
    print('comment lines:', comment_lines)

if __name__ == '__main__':
    main()
