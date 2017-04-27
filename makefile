to_clean = Report.o GeneralBugAnalyser.o BugAnalyser.Abstract.o

main: main.cpp src/GeneralBugAnalyser.o
	g++ main.cpp GeneralBugAnalyser.o Report.o BugAnalyser.Abstract.o -o main -std=c++11

src/BugAnalyser.Abstract.o: src/BugAnalyser.Abstract.cpp
	g++ -c src/BugAnalyser.Abstract.cpp -std=c++11

src/GeneralBugAnalyser.o: src/GeneralBugAnalyser.h src/GeneralBugAnalyser.cpp src/Report.o src/BugAnalyser.Abstract.o
	g++ -c src/GeneralBugAnalyser.cpp -std=c++11

src/Report.o: src/Report.h src/Report.cpp
	g++ -c src/Report.cpp -std=c++11

clean:
	rm -rf $(to_clean)

cleanall:
	rm -rf $(to_clean) main