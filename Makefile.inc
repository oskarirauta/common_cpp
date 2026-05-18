COMMON_DIR?=./common
INCLUDES += -I$(COMMON_DIR)/include -I$(COMMON_DIR)/rva/include -I$(COMMON_DIR)/tsl/include
COMMON_OBJS:= \
	objs/common_scanner.o \
	objs/common.o

objs/common_scanner.o: $(COMMON_DIR)/src/scanner.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/common.o: $(COMMON_DIR)/src/common.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
