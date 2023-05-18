# jocoa

A simple compiler and packager for Java.

## Download Instruction

Head to the releases tab and download the latest .zip folder.

Extract it into `C:/jocoa/`.

Add `C:/jocoa/` to PATH.

## Json

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

    "classfiles": "classfiles"

}
```

`files` - List of relative path to all `.java` files.

`dependancies` - List of relative path the all `.jar` libraries.

`classfiles` - Name of folder `.class` files will be created in.

## Usage

Run `jocoa` in the base dir of your java project and your project should compile and run.