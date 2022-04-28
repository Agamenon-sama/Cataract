.PHONY : all clean

APP := cataract
CXX := g++
CXX_FLAGS := -Wall -Wextra -g
LINK_FLAGS :=

INC := "../include"
OBJS := main.o Cataract.o

all: $(APP)

$(APP): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CXX_FLAGS) $(LINK_FLAGS) -I$(INC)

main.o: ../main.cpp
	$(CXX) $^ -c $(CXX_FLAGS) $(LINK_FLAGS) -I$(INC)

Cataract.o: ../Cataract/Cataract.cpp
	$(CXX) $^ -c $(CXX_FLAGS) $(LINK_FLAGS) -I$(INC)

clean:
	rm *.o $(APP)