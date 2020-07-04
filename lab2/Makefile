%.o: %.cpp
all: Database.o Employee.o main.o Manager.o Person.o UseDatabase.o
	g++ -o database Database.o Employee.o main.o Manager.o Person.o UseDatabase.o
Database.o: Database.cpp
	g++ -o Database.o Database.cpp
Employee.o: Employee.cpp
	g++ -o Employee.o Employee.cpp
main.o: main.cpp
	g++ -o main.o main.cpp
Manager.o: Manager.cpp
	g++ -o Manager.o Manager.cpp
Person.o: Person.cpp
	g++ -o Person.o Person.cpp
UseDatabase.o: UseDatabase.cpp
	g++ -o UseDatabase.o UseDatabase.cpp