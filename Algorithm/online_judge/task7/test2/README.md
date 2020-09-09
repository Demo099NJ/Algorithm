Night.
write at 1:34, 2020/6/11.

Emmmmm...continuation of this story:
After the continuous emergence of WA in OJ system, I know that either I didn't input completely when I input the graph, or I didn't traverse all the neighbors when I traversed the neighbors. So I wrote it again, but this time it was WA. After I once showed up with SIGSEGV, I realized that the number of neighbors may be small? So the neighbors of some vertices didn't be wrote into the graph? So I increased the number of neighbors from 100 to 200. But after that, OJ's feedback was TLE. I was a little speechless, but I still thought, was it too big? So I changed it to 150. At this time, AC finally appeared. I was ecstatic.
But I still have a question: at the beginning, 100 was not enough. Shouldn't SIGSEGV (runtime error) appear? Later, the space was increased. However, why did it time out again?
