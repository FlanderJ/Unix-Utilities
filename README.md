# Unix-Utilities
C-program files contained in this repository are self-made simple versions of UNIX utilities known as cat, grep, zip and unzip.

my-cat.c:
- Reads the file specified by the user and prints its content into the console.
- Program can be run, for example; "prompt> ./my-cat main.c", where it prints the content of the file "main.c"
- Program can be invoked for one or more files.

mygrep.c:
- This program looks through a file specified by the user line by line and tries to find a user-specified term in the line. If the line contains this search term, then the line is printed into the console.
- For example; "prompt> ./my-grep foo bar.txt" searches the term "foo" from the file "bar.txt".
- Note! The matching is case-sensitive, thus terms "foo" and "Foo" won't match.
- If the search term is given and a file is not given, the program will read standard input to look for the term.

my-zip.c:
- A program that will compress the file that is given as an input file.
- The type of compression is simple run-length encoding (RLE)
- For example: "prompt> ./my-zip file.txt > file.z" the content file.txt is compressed and the outcome is saved into the file called "file.z".
- Can compress multiple files into one compressed file.

my-unzip.c:
- Does the reverse relate to my-zip.c. If a compressed file is given to it as an input argument it will decompress the content of that file and print the content in the standard output.
- For example; "./my-unzip file.z" will decompress the file "file.z" and print uncompressed content into standard output.

For more details in the comments of the code!
