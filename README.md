# Game of Life


## Students
### Matt Raymond

2270559

raymo116@mail.chapman.edu


### Christian Valencia

2275944

valen193@mail.chapman.edu


## Instructions

- Type `make` to compile the code.
- Type `./mRaymond_cValencia.gol` to execute program.
- Choose whether you want to run the program from a pre-constructed map or a random map.
    - If you select a pre-constructed map, then please provide a file path.
    - If you select a random map, then please provide the following.
        - An integer for the X size of the map.
        - An integer for the Y size of the map.
        - A floating point number x such that 0 < x < 1.
- Choose what mode you would like to play.
    - `Classic` is normal mode. The edges of the map act like cliffs, and anything off the map is dead.
    - `Donut` simulates the surface of a sphere, where something traveling off screen on the left will reappear on the right. It's the same for the top.
    - `Mirror` duplicated the contents of an edge onto the locations just outside of the map. For example, if the size of the map is l, then a cell on l-1 will be reflected onto l.
- Choose a viewing mode.
    - `Brief Pause` will give a short pause before continuing on automatically.
        - If you choose `Brief Pause`, you'll be required to enter an integer for the size of the delay in milliseconds.
    - `[Enter]` will ask you to press the enter key between each Generation.
    - `File Output` will save to a file called `mRaymond_cValencia.out`.
- Once started, the program will run through 1k generations unless it stabilizes first, at which point it will stop and ask you to press enter to exit the program.
    - The stability checks for two cases: no movement whatsoever, and repeating structures with a period of two generations.


## References

[Dynamic 2D Arrays](https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new#936702)

[Throwing Exceptions](https://stackoverflow.com/questions/8480640/how-to-throw-a-c-exception)

[Casting to String](https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c#5591169)

[ANSI Escape Codes](https://stackoverflow.com/questions/11474391/is-there-go-up-line-character-opposite-of-n)

[Sleeping](https://linux.die.net/man/2/nanosleep)

[Pausing](https://stackoverflow.com/questions/2252372/how-do-you-make-a-program-sleep-in-c-on-win-32)

[Error: free(): invalid next size (fast):](https://stackoverflow.com/questions/4729395/error-free-invalid-next-size-fast)

[Check if File Exists](https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c)
