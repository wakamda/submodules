CC:= g++
TARGET:= test
INCLUDE:= -I./
LIBS:= -lpthread -lstdc++
# C++语言编译参数  
CXXFLAGS:= -std=c++0x -g -Wall -D_REENTRANT
# C预处理参数
# CPPFLAGS:=
OBJECTS :=Service.o Thread.o
  
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)
  
# $@表示所有目标集  
%.o:%.cpp   
	$(CC) -c $(CXXFLAGS) $(INCLUDE) $< -o $@
  
.PHONY : clean
clean:   
	-rm -f $(OBJECTS) $(TARGET)