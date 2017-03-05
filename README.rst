=======
bipipes
=======

It would be cool if processes would be able to communicate themselves.

Suppose we have a shell that sets up a bidirectional pipe, say a `socketpair` between two processes:

    >sh ls ~ recurse ~ grep ~ string 'hello'

Here we have instead of the pipe symbol `|`, the bidirectional water symbol `~`. (Note this is different from the home directory notation.)

-----------------
listening
-----------------

A process like `ls` should be started with a socket descriptor and it should listen to the configuration request that comes through. A process like `recurse` might send it configuration information that otherwise has to be specified through flags such as `-R`. 

It is these flags that:

+ are difficult to remember;
+ should be auto-negotiated;
+ break the Unix philosophy of being able to do one thing and one thing only.

If we have to break that philosophy, then it might be worthwhile to consider how we break them and formalize it. Flags cannot be queried in a programmatic way, they cannot be documented in a standard way, and they are even hard to handle programmatically (see all the setopt, setopts, etc. variants).

-----------------
writing
-----------------

A process like `recurse` or `grep` should tell the process that feeds its standard input about what it would like to get. There is no reason to standardize this. We can even standardize on `json` or some binary format if that is our heart's desire.

-----------------
skipping
-----------------

For the `recurse` process this means that its sending something corresponding to the `-R` flag to `ls` and preferably tells it (or the shell) the socket descriptor of the next process. This means that the entire `recurse` process will not be used in the final stream!

-----------------
negotation
-----------------

Also very cool, if this is a process that runs for a while or if these processes start to know each other better, there might be optimization going on. Start sharing memory locations, optimize for cache hits, etc.
