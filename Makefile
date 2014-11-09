TYPE=random
SIZE=256*1024

all: 
	gcc -static -O3 -Wall -W -DDATANUM=$(SIZE) bubble.c -o bubble
	gcc -static -O3 -Wall -W -DDATANUM=$(SIZE) selection.c -o selection
	gcc -static -O3 -Wall -W -DDATANUM=$(SIZE) insertion.c -o insertion
	gcc -static -O3 -Wall -W -DDATANUM=$(SIZE) merge.c -o merge
	gcc -static -O3 -Wall -W -DDATANUM=$(SIZE) quick.c -o quick

run: 
	./bubble $(TYPE)
	./selection $(TYPE)
	./insertion $(TYPE)
	./merge $(TYPE)
	./quick $(TYPE)

clean:
	rm -f merge quick *_flymake* bubble insertion selection
