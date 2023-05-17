with open("jocoa_lists.txt", "r") as file:

    lines = file.read().splitlines()

files = []
libs = []

add_files = False
add_libs = False

for line in lines:

    st_line = line.strip()

    if st_line != "\n" and st_line != "":

        sp_line = st_line.replace(" ", "")

        if sp_line.split("{")[0] == "files" and sp_line[len(sp_line) - 1] == "{":

            add_files = True
            add_libs = False

        if sp_line.split("{")[0] == "dependencies" and sp_line[len(sp_line) - 1] == "{":

            add_files = False
            add_libs = True

        if add_files and not st_line.__contains__("files") and not st_line.__contains__("{") and not st_line.__contains__("}"):

            files.append(st_line)

        if add_libs and not st_line.__contains__("dependencies") and not st_line.__contains__("{") and not st_line.__contains__("}"):

            libs.append(st_line)

        if add_files and st_line.__contains__("}"):

            add_files = False
            add_libs = False

        if add_libs and st_line.__contains__("}"):

            add_files = False
            add_libs = False

print(files)
print(libs)
