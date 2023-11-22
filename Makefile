TARGET: exe
exe: main.o mqtt_initializer.o mqtt_messagehandler.o db_handler.o
	gcc obj/main.o obj/mqtt_initializer.o  obj/mqtt_messagehandler.o  -o bin/mqtt_client.exe  -L libs/paho.mqtt.c/build/output  -lpaho-mqtt3c -L libs/cJSON  -lcjson  -lsqlite3
main.o:
	if [ ! -d "obj" ] && [ ! -d "bin" ]; then mkdir obj && mkdir bin && echo ""; else echo ""; fi
	gcc -c src/main.c -I include -o obj/main.o -L libs/paho.mqtt.c/build/output -lpaho-mqtt3c -L libs/cJSON  -lcjson -lsqlite3

mqtt_initializer.o:
	gcc -c -I include include/mqtt_initializer.c -o obj/mqtt_initializer.o -L libs/paho.mqtt.c/build/output  -lpaho-mqtt3c

mqtt_messagehandler.o:
	gcc -c -I libs/cJSON  -I include include/mqtt_messagehandler.c -o obj/mqtt_messagehandler.o -L libs/paho.mqtt.c/build/output -lpaho-mqtt3c -L libs/cJSON -lcjson -lsqlite3

db_handler.o:
	gcc -c -I include include/db_handler.c -o obj/db_handler.o -lsqlite3


clean:
	rm bin/*.exe
	rm obj/*.o
	rm -r obj
	rm -r bin
