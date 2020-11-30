# BasicConnect

Firstly this project has a terrible name. I was going to do some testing/before writing what I hoped would be the "final" code - but I made pretty quick progress hence the name.... It will change.

## What does this do ??

This is written for Ham radio, specifically for aggregating Dx-Cluster feeds.

If you are not a radio ham, or interested in contests you probably have already fallen asleep... but in case you are a Ham - keep on going.

## Why is it needed ?

Awesome question - and the simple answer is it depends on your current contest logger. If you use something like RUMlogNG, then I do not think you need this - why ? Becuase RUMLogNG allows up to 4 Dx Cluster connections at the same time.

My favorite contest logger is SkoomLogger, but the software author, did not want to add the facility for multiple Dx-Cluster connections. 

So if your software logger has only 1 Dx Cluster connection - and you want more... this may be of use....

Or .... if you have a skimmer, which not in "public mode" i.e. it only feeds your station (This is what the Author of SkoomLogger and I disagreed about); and would like to "blend" your private data with public data, and to do that, I need two Cluster feeds - however only one was provided ....


# So how does this work ?

You need a PC (in theory running Mac, Windows or Linux) - which has an internet connection. Then you enter the AR-Clusyter nodes you wish to get data from, along with your filters (it is pointless if you are in Australia, seeing spots in the UK probably). Then Run the Cluster-Aggregator (badly named BasicConnect) - this will log into the remote Dx-Clusters, set you filters and then serve this data locally.

You now point your Dx-CLuster cripped 1 connection software to your machine running the program, and connect to port 6060.

## What if I disconnect and re-connect ?

This is handled by the Server. 

## If my logger disconnects but the Dx-Cluster aggregator stays running can I get the missing spots when I re-connect ?

Umm - good idea. I will add it on the hit list


# How to run ??

## V0.0a

Just execute BasicConnect like this

    ./BasicConnect 
    
There are other options available

  - -l  Log output to a File
  - -f  Specifiy a different (than my standard) cluster definition file
  
# Cluster Definition file 

## V0.0a

This is a TSV (Tab Seperated variable) file. But it will change.



## Other to do's

	- logging. Produce data files.
	- What to do if 1 connection fails ?
	- Handle major disconnections
	- Set Filter per band/timezone ? Umm probably not


