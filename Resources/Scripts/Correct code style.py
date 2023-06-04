import os
for root, dirs, files in os.walk("./"):
    for file in files:
        if file.endswith(".js"):
            command = 'clang-format -i -style=Google '+os.path.join(root, file)
            print(command)
            os.system(command)
