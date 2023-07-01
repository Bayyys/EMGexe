import sys
import os

def large_file(path):
    # 递归文件夹, 打印大于100MB的文件
    for root, dirs, files in os.walk(path):
        for file in files:
            file_path = os.path.join(root, file)
            if os.path.getsize(file_path) > 100 * 1024 * 1024:
                print(file_path, ":size:", os.path.getsize(file_path) / 1024 / 1024, "MB")

if __name__ == '__main__':
    large_file(os.getcwd())