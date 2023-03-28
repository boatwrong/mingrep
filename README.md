# miniature grep
* miniature reverse engineerd `grep` with just the purposes I typically use.
    * goal of project was to recreate program without looking at original source code.
        - mostly successful here, one brief readthrough was done on a particularly frustrating moment parsing arguments however I was more confusd after reading...

## build instructions
* project was built using make, gcc-12 using the makefile in the repository.

### TODO
* write test to benchmark versus the real deal
* Look into the -A flag 
	- prints 'n' lines after the line where expression was found
