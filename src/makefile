CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = project
OBJECTS = project_main.o board.o canenter.o getrand.o entity.o tile.o emptytile.o goal.o blocker.o movingentity.o projectile.o livingentity.o player.o enemy.o meleeenemy.o rangedenemy.o singlepowerup.o healthpack.o treasure.o livingentitydecorator.o stuckdecorator.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}


.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
