# Jocoa

A simple Java compiler argument generator using C++ and Json.

## Installation

Download the source code, then use the make command to compile for your OS.

### Windows
```
C:/path/to/sourcecode/> make win
```

### Linux
```
usr@device:~/path/to/sourcecode/$ make linux
Enter Password for usr:
```

## Usage

To create a new project, use the `new` argument.

```
$ jocoa new ProjectName
```

This will create a basic Java project filetree with a basic entrypoint.

```jsonc
{

    "tasks": [

        {

            "task": "main",

            "files": [

                "src/main/*.java",
                "src/other/Other.java"

            ],

            "dependencies": [

                "lib/commons-v1.8.0.jar",
                "lib/other/my-crap.jar"

            ],

            "natives": "lib/natives",

            "classfiles": "bin"

        }

    ]

}
```
