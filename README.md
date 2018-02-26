# SkyStack_dev
Localizing drone via GPS/camera feed alone


# Yo!
All you should need to do is type "git clone https://github.com/jmill269/SkyStack_dev.git", and
a new directory should pop up named SkyStack_dev. 'cd' into that directory and then you should
be able to start getting jiggy with it.


# Basic Commands
So, right now the only file in here is this README. Say I want to add a file called 'make_drone_land.py'.
Once that file is in the same repo as this README, you can type "git add make_drone_land.py" to add it to be
staged for committing. And if that's all you want to do for the day, type "git commit -am 'i added this file' ",
then "git push". The -a flag stands for all changes, and the -m stands for message. It's good practice to add
a message for each commit so you know what you did; it doesn't have to be long, stuff like "updated README" or
"fixed bugs in x file" is helpful enough.

You'll probably be prompted for your git username/password the first time, but afterwards you should just
be able to push without typing that in.

Also, at any time you can type "git status" to see the status of everything. It'll tell you if you have things
that aren't committed, things you need to "add", and a couple other things. I mainly use it to check whether or not
I've aadded all the things I wanna add/committed all my changes.



# Branching
I think working in two separate branches will be helpful, so we don't step on eachother's toes while working.
Here's a good link if you wanna read into it more: https://www.atlassian.com/git/tutorials/using-branches .

But the idea behind it is pretty simple. Basically, the "master" branch is the main branch that should
contain the most up-to-date working code. If you want to start working on something new, typing
"git branch whaterYouWannaNameTheBranch". This just creates the branch. To start working on it, type
"git checkout whateverYouWannaNameTheBranch" and then you'll be moved to that branch. It will contain
whatever files and changes that were saved in the master branch. If you ever want to view all the branches,
typing "git branch" will show the names of all current branches. You can also merge your working branch
into the master branch, but that honestly confuses me a little bit sometimes so we'll figure it out as we go.

Another option could just be to comment out portions of code that we change/edit and write a little blurb
about why we added or changed something, all in the master branch. This wouldn't be bad, branching is always cool in
theory but sometimes it can just get ever-so-slightly messy so really whatever works works.

I think that's pretty much it, there are a ton of helpful docs if you just type "git whatever my problem is" into google,
someone will have had the same issue at some point or atlassian.com will just explain it themselves.

