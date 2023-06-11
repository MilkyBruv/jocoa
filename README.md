# Jocoa

A simple Java compiler argument generator using C++ and Json.

## Installation

Download the source code, then run these commands (replace dirs with your own).

```
C:/> mkdir jocoa
C:/> cd "C:/path/to/sourcecode/"
C:/path/to/sourcecode/> make
```

Then add `C:/jocoa/` to PATH.

## Usage

Go to the root folder of your java project, then create a file called `jocoa.json`.

The json file will contain only 4 variables: `files`, `dependencies`, `natives`, and `classfiles`:

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

    "natives": "<.dll & .so dir>",

    "classfiles": "<.class target dir>"

}
```

`files` - List of relative path to all `.java` files.

`dependancies` - List of relative path the all `.jar` libraries.

`natives` - Path to `.dll` and `.so` files.

`classfiles` - Name of folder `.class` files will be created in.

To compile, run `jocoa` in the base dir of your java project and your project should compile and run.