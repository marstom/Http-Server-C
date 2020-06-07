# Http-Server-C
Learning how to make http server in C.

I am not professional C developer, if there are bad practices in code feel free add comments.


This is my own http-server, I writing this to gain knowledge how http servers are working :smile:.
Features:
* Can serve images up to 8000 bytes.
* Can serve CSS, HTML, JS files.
* Serve static page.


## TODO
* Add dynamic memory allocation, now when image is bigger than 8000 bytes server will crash.
* Free allocated memory. Valgrind should show 0 lost bytes.