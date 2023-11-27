TARGET: exe
exe: dir  main.o mqtt_initializer.o mqtt_messagehandler.o db_handler.o shellyplug-s.o trv.o
	gcc obj/main.o obj/mqtt_initializer.o  obj/mqtt_messagehandler.o  obj/db_handler.o obj/shellyplug-s.o obj/trv.o -o bin/mqtt_client.exe  -L libs/paho.mqtt.c/build/output  -lpaho-mqtt3c -L libs/cJSON  -lcjson  -lsqlite3
main.o:
	gcc -c src/main.c -I include -o obj/main.o -L libs/paho.mqtt.c/build/output -lpaho-mqtt3c -L libs/cJSON  -lcjson -lsqlite3

mqtt_initializer.o:
	gcc -c -I include include/mqtt_initializer.c -o obj/mqtt_initializer.o -L libs/paho.mqtt.c/build/output  -lpaho-mqtt3c

mqtt_messagehandler.o:
	gcc -c -I libs/cJSON  -I include include/mqtt_messagehandler.c -o obj/mqtt_messagehandler.o -L libs/paho.mqtt.c/build/output -lpaho-mqtt3c -L libs/cJSON -lcjson -lsqlite3

db_handler.o:
	gcc -c -I include -I libs/cJSON   include/db_handler.c -o obj/db_handler.o -lsqlite3 -L libs/cJSON -lcjson
shellyplug-s.o:
	gcc -c -I include include/shellyplug-s.c -o obj/shellyplug-s.o

trv.o:
	gcc -c -I include -I libs/cJSON  include/trv.c -o obj/trv.o -lcJSON

dir:
	if [ ! -d "obj" ] && [ ! -d "bin" ]; then mkdir obj && mkdir bin && echo ""; else echo ""; fi	
clean:
	rm bin/*.exe
	rm obj/*.o
	rm -r obj
	rm -r bin
