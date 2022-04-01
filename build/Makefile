.PHONY : all clean

APP := cataract
CXX := g++
CXX_FLAGS := -Wall -Wextra -g
LINK_FLAGS :=

INC := "../include"
# INC := "/home/agamenon/Documents/C Projects/portScanner/include"
OBJS := main.o Cataract.o

all: output

output: $(OBJS)
	$(CXX) $(OBJS) -o $(APP) $(CXX_FLAGS) $(LINK_FLAGS) -I$(INC)

main.o:
	$(CXX) ../main.cpp -c $(CXX_FLAGS) $(LINK_FLAGS) -I$(INC)

Cataract.o:
	$(CXX) ../Cataract/Cataract.cpp -c $(CXX_FLAGS) $(LINK_FLAGS) -I$(INC)

clean:
	rm *.o $(APP)