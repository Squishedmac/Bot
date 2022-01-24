# Bot
A simple bot to automate a very mundane task thats made difficult by a very laggy server


Before i login to class everyday I had to mark my attendance, but because the server is so laggy marking attendance meant missing some of the class and i cant join the class and mark it later because the link expires, and despite attending class i would not get the attendance(online classes ammiright ).  There's a lot of html parsing because i didnt know an easier way around it, i tried cleaning it as much with some functions, but when the url is located as a part of a bigger word there doesnt seem to be a lot of ways around it.
The steps are really simple:
step 1: we need to login tot he website and get the cookies, its literally the most important step because we access the subject attendance links as links and not embedded links.
-to login we use post

step 2: we have the cookies now we access the subject site links , find the embedded link and POST the form data, I used chromes web dev for this.


This was a fun project too because it helps with some real world problems and i learnt about GET and POST and got more familiar with cURL.
