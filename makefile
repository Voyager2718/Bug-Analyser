to_clean = Report.o GeneralBugAnalyser.o

main: main.cpp src/GeneralBugAnalyser.o
	g++ main.cpp GeneralBugAnalyser.o Report.o BugAnalyser.Interface.o -o main -std=c++11

src/BugAnalyser.Interface.o: src/BugAnalyser.Interface.cpp
	g++ -c src/BugAnalyser.Interface.cpp -std=c++11

src/GeneralBugAnalyser.o: src/GeneralBugAnalyser.h src/GeneralBugAnalyser.cpp src/Report.o src/BugAnalyser.Interface.o
	g++ -c src/GeneralBugAnalyser.cpp -std=c++11

src/Report.o: src/Report.h src/Report.cpp
	g++ -c src/Report.cpp -std=c++11

clean:
	rm -rf $(to_clean)

cleanall:
	rm -rf $(to_clean) main