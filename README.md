# Image Remover #

This is another historical piece of code that I wrote about 20 years ago.
Back then, I was on our high school speech and debate team and my event was
Extemporaneous Speaking. In 'extemp' (as it was called) you had 30 minutes to
craft a speech answer a random question about current events in the US.

This event required you to read a LOT of news. Extemp speakers would 
subscribe to a vast collection of national and local newspapers and 
magazines, read all the articles, highlight them, cut them out and save them
inside well-organized hanging folders inside of their 'extemp box'. Along
with paper and pencil, this box was the only thing you were allowed to bring
into the prep room. Nothing electronic was allowed (not that there were great
options for that 20 years ago).

At the time, the internet was just starting for us commoners and all of the
big names in news were starting to publish news online. While it's great to
have another source for the news, if you wanted to file any of it in your box
you'd need to print it off. Of course, printing on inkjet printers was fairly
expensive, and printing color was downright irresponsible, so I needed to 
figure out how to ease this burden so I could print a LOT of stuff.

Images were the worst - they used lots of ink. Tables were almost as bad,
and sometimes the web pages had (*gasp*) colored text! I needed to get rid
of everything complicated from the web pages so they were just text - nice,
cheap, black and white text. I knew HTML, so I could probably have edited
each page by hand, but that's not my style. We're talking about a LOT of 
articles here; the longest-running extemp speakers would cart around three 
or more Tupperware tubs full of hanging folders and articles. We had to carry
around those collapsable carts and bungee cords to handle all of that 
nonsense. I wasn't going to edit 50 pounds worth of printed web pages by 
hand.

So, I wrote a program to do it. It's written in C and uses the string
library to identify graphics-heavy HTML constructs and remove the tags 
from the downloaded web page automatically. It accepted the path to the
HTML file on the command line and modified it in-place to remove the 
following tags:

* img
* map
* form
* bold text
* text input fields
* area tags
* colored text
* background colors
* radio buttons
* background images (so popular in the 90's)


The code is absolutely atrocious and displays my complete lack of knowledge of 
C. To be fair, I was just starting out then. Otherwise, the program worked 
quite well and enabled me to print off a LOT of articles.

I plan to clean up this archive and document the code more completely.

In the mean time, it sits here, an embarassment for all to see.



