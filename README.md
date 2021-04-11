# Http-Server-C
Learning how to make http server in C.

Redesign.

Features:
* Can serve any files from your file system
* Multithreading with queues on example
* Infinite threads creating
* Restrict number of threads and queue example
* Example of threads with wait signal

## TODO
- [x] Add dynamic memory allocation, now when image is bigger than 8000 bytes server will crash.
- [x] Free allocated memory. Valgrind should show 0 lost bytes. Now there is dynamic memory allocation.
- [x] Handle exceptions, when there's no such file avoid server crash.
- [x] Implement queue.
- [x] Multithreading with queue.
- [ ] Split process request to separate function.
- [ ] Split process response to separate function.
- [ ] Crete some unittests instead using driver program (main.c) for request parser.
- [ ] Handle GET http method.
- [ ] Handle POST http method.
- [ ] Handle PUT http method.
- [ ] Handle DELETE http method.
- [ ] Handle cookies.




## Test result

- 4.78s - 48.7s on thread 