Project 1
=======

Problem Statement
--------
Implementing three kinds of scheduling algorithm, including FCFS(First-Come, Fisrt-Served), SRTF(Shorteset-Remaining-Time-First)and RR(Round Robin).

In this program, it takes an input file(.txt)which contains the workload for a set of process, and then output a text file which contains the record of context switching according to the information conveyed by the input file. 

Run
---------
	mkdir bin/
	make
	./bin/project1
    

Input format
---------
	Scheduling Algorithm: FCFS		P1	Arrival Time: 0 	Burst Time: 24
	P2	Arrival Time: 0 
	Burst Time: 3	
	P3	Arrival Time: 0 
	Burst Time: 3

Output format
---------
	P1 0 - 24	P2 24 - 27	P3 27 – 30	Average Waiting Time: 17 
	Average Turnaround Time: 27
	
Details 
---------
### First-Come, First-Served:此種方法只要找出最早到達的process，並在一次迴圈之中消耗完該process所有的時間。
過程中是non-preempted，因此不需要中斷process。### Shortest-Remaining-Time-First:Preempted版本的[Shortest Job First](http://en.wikipedia.org/wiki/Shortest_job_next)，在process做動作的當下，若有任何其他的process的burst time小於該process則中斷它，並由擁有最小burst time的process進行，等到此process做完後，再由擁有最小burst time的process進行。實作中每一次的迴圈只處理一個時間單位，這樣的處理對於算出正確的average waiting time, average turnaround time並不困難，卡住的地方是在要印出甘特圖的地方，因為甘特圖是要將處理中還未中斷的process印出來，而非像是程式裡的迴圈是以時間做為單位，解決方式是在process進行時，將他的id存起來，在之後的迴圈中比對，若是先前儲存的id與現在迴圈的id不一樣則印出，如此便解決了甘特圖的問題。
[src]: http://en.wikipedia.org/wiki/Shortest_job_next### Round Robin:每個process進行中會有兩種狀況，一種是process的burst time剩的比time quantum少，因此做完之後就不會再進queue裡；另一種是burst time大於time quantum，做完之後要進入queue中，等待下一次。