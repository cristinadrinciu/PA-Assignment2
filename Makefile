# Exemplu de Makefile pentru soluții scrise în C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: numarare trenuri drumuri scandal

# Nu compilați aici, nici măcar ca dependențe de reguli.
run-p1:
	./numarare
run-p2:
	./trenuri
run-p3:
	./drumuri
run-p4:
	./scandal

# Schimbați numele surselor (și, eventual, ale executabilelor - peste tot).
trenuri: trenuri.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
numare: numarare.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
drumuri: drumuri.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
scandal: scandal.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Vom șterge executabilele.
clean:
	rm -f numarare trenuri drumuri scandal

pack:
	zip -FSr 324CA_DrinciuCristina_Tema2.zip Makefile README.md numarare.cpp trenuri.cpp drumuri.cpp scandal.cpp