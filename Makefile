TARGET: exe
exe: main.o mqtt_initializer.o mqtt_messagehandler.o
	gcc obj/main.o obj/mqtt_initializer.o  obj/mqtt_messagehandler.o  -o bin/mqtt_client.exe -lpaho-mqtt3c
main.o:
	if [ ! -d "obj" ] && [ ! -d "bin" ]; then mkdir obj && mkdir bin && echo ""; else echo ""; fi
	gcc -c src/main.c -I include -o obj/main.o -lpaho-mqtt3c

mqtt_initializer.o:
	gcc -c -I include include/mqtt_initializer.c -o obj/mqtt_initializer.o -lpaho-mqtt3c

mqtt_messagehandler.o:
	gcc -c -I include include/mqtt_messagehandler.c -o obj/mqtt_messagehandler.o -lpaho-mqtt3c


clean:
	rm bin/*.exe
	rm obj/*.o
	rm -r obj
	rm -r bin
