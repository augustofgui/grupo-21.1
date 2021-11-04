all:  Imovel.o Casa.o Apartamento.o Chacara.o Geral.o main.cpp
	g++ -o pesquisa main.cpp Imovel.o Casa.o Apartamento.o Chacara.o Geral.o

Apartamento.o: Apartamento.cpp
	g++ -o Apartamento.o -c Apartamento.cpp

Casa.o: Casa.cpp
	g++ -o Casa.o -c Casa.cpp

Chacara.o: Chacara.cpp
	g++ -o Chacara.o -c Chacara.cpp

Geral.o: Geral.cpp
	g++ -o Geral.o -c Geral.cpp

Imovel.o: Imovel.cpp
	g++ -o Imovel.o -c Imovel.cpp

clean:
	rm -f *.o pesquisa

run:
	./pesquisa