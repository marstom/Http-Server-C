# Http-Server-C
Learning how to make http server in C.

I am not professional C developer, if there are bad practices in code feel free add comments.


This is my own http-server, I writing this to gain knowledge how http servers are working :smile:.
Features:
* Can serve CSS, HTML, JS files.
* Serve static page.
* Dynamic memory allocation.

## TODO
- [x] Add dynamic memory allocation, now when image is bigger than 8000 bytes server will crash.
- [x] Free allocated memory. Valgrind should show 0 lost bytes. Now there is dynamic memory allocation.
- [ ] Handle exceptions, no such resource 404, error 500 etc.

