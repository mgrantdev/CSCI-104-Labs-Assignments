For Problem 2, I choose to do Birthday Paradox and Probe Rate
=============================================================

Birthday Paradox:
Repeat 10000 times the following process and calculate their average:<br />
&emsp;&emsp;1. Initialize a hashtable of size 365<br />
&emsp;&emsp;2. Generate random strings and insert them until a collision occurs<br />
&emsp;&emsp;3. If a collision occurs, get how many items I have inserted, if it is less than or equal to 23, this trial confirms the birthday paradox<br />
&emsp;&emsp;Note: I didn't consider resize because according to https://en.wikipedia.org/wiki/Birthday_problem, if n = 200, the probability that<br />
&emsp;&emsp;there's still no collision is 1 - (99.9999999999999999999999999998%) which is nearly impossible. Resize only happens if n > 182 which<br />
&emsp;&emsp;is also nearly impossible even with 10000 trials<br />
Result: 0.5077, 0.5065, 0.5115, 0.5048, 0.5134, 0.5003, 0.5046, 0.5114, 0.5097, 0.5072, ......<br />
Run: Type make and then type ./birthday

<br />
Probe Rate:
Repeat 100 times the following process and calculate their average:<br />
&emsp;&emsp;1. Initialize a hashtable of size 11(this time, we want it to resize)<br />
&emsp;&emsp;2. Insert 3000 items to the hashtable, sum up their numbers of probes<br />
&emsp;&emsp;3. Divide the sum by 3000 to get the probe rate for this trial, sum up all probe rates and divide the final sum by 100<br />
Result: 0.66531, 0.666793, 0.6669, 0.66484, 0.666807, 0.664453, 0.663377, 0.668027, 0.665103, 0.665693, ......<br />
Run: Type make and then type ./probeRate
