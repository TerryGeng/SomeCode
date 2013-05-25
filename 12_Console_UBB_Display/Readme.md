A simple UBB parser in terminal (for text only)
===

This little program can parse some simple UBB code.

Now it only supports `[b]` .

### How To Use
Compile it with `-lncurses` . Like:

    > gcc UBB.c -o UBB -lncurses

Then, use

    > ./UBB <yourfile>

 _\<yourfile\>_ is your file that contains UBB code. Like

    > ./UBB Test.txt
