
OBJS := scan.o fft.o process.o signalSource.o sampleBuffer.o processInterface.o utility.o\
	bladerfSource.o	b210Source.o airspySource.o sdrplaySource.o

HEADERS := scan.h signalSource.h process.h fft.h messageQueue.h \
	bladerfSource.h b210Source.h airspySource.h
LIBS = -lfftw3f -lboost_program_options -lboost_system -lgnuradio-fft -lvolk

scan: $(OBJS) Makefile
	g++ -g -o scan $(OBJS) -L ../target/lib -lbladeRF -luhd -lairspy -lmirsdrapi-rsp -L /usr/lib/x86_64-linux-gnu $(LIBS)

clean:
	rm *.o

sampleBuffer.o: sampleBuffer.cpp buffer.cpp sampleBuffer.h

%.o: %.cpp $(HEADERS)  Makefile 
	g++ -g -D INCLUDE_B210 -o $@ -c -I ../target/include -std=gnu++11 $<

