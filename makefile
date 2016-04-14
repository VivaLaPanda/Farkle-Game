P2.out: Proj2app.o SetLimits.o Game.o
	g++ -g -o P2.out Proj2app.o SetLimits.o Game.o

Proj2app.o: Proj2app.cpp Game.h SetLimits.h
	g++ -g -c Proj2app.cpp

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

Game.o: Game.cpp Game.h
	g++ -g -c Game.cpp

clean:
	rm *.o P2.out

run : P2.out
	clear
	./P2.out

submit : Proj2app.cpp Game.h Game.cpp makefile README.txt
	rm -rf ylnP2
	mkdir ylnP2
	cp Proj2app.cpp ylnP2
	cp Game.h ylnP2
	cp Game.cpp ylnP2
	cp makefile ylnP2
	cp README.txt ylnP2
	tar cfvz ylnP2.tgz ylnP2
	cp ylnP2.tgz ~tiawatts/cs215drop
