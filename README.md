# pthread_examples
pthread demos 

Worked through the examples on this youtube channel and added some features as well

https://www.youtube.com/playlist?list=PL-suslzEBiMrqFeagWE9MMWR9ZiYgWq89 

Used WSL2 as dev environment with Ubuntu 18.04 

gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Did not make a make file so build as seen below 

gcc multiple_thread_mutex.c -o multiple_thread_mutex -pthread 

And run like this... 

./multiple_thread_mutex 10 5 20 50

using vs code 

Update tasks.json file to include building w pthread 

 "args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}",
                "-pthread"
            ],
			
Add inputs into args of launch.json 

Single thread with global sum variable 

Multiple thread with each thread having its own data 

Multiple thread example with global shared variable sum (with mutexes) 

Producer / Consumer model with indiidual condition variables 