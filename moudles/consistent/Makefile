ALL = consistent

all: $(ALL)

consistent : consistent.h hashring_example.cpp
	$(CXX) -Wno-deprecated $(CFLAGS) hashring_example.cpp -o consistent

.PHONY : clean

clean :
	rm $(ALL)
