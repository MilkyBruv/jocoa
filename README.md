# Jocoa

A simple Java compiler argument generator using C++ and Json.

## Installation

Head to the releases tab and download the latest .zip folder and extract it into `C:/jocoa/`, then add `C:/jocoa/` to PATH.

Or

Download the source code, then run these commands (replace dirs with your own).

```
C:/> mkdir jocoa
C:/> cd "C:/path/to/sourcecode/"
C:/path/to/sourcecode/> make
```

## Usage

Go to the root folder of your java project, then create a file called `jocoa.json`.

The json file will contain only 3 variables: `files`, `dependencies`, and `classfiles`:

```json
{

    "files": [

        "src/main/*.java",
        "src/main/coolStuff/*.java",
        "src/other/*.java"

    ],

    "dependencies": [

        "lib/common.jar",
        "lib/cool-stuff-0.4.5.jar",
        "lib/amazinglib/amazing-library-1.2.jar"

    ],

    "classfiles": "bin"

}
```

`files` - List of relative path to all `.java` files.

`dependancies` - List of relative path the all `.jar` libraries.

`classfiles` - Name of folder `.class` files will be created in.

Run `jocoa` in the base dir of your java project and your project should compile and run.