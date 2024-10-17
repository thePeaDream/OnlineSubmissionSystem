main:main.cc
	g++ -o $@ $^ -std=c++11 -lpthread -fpermissive -L /lib64/mysql -lmysqlclient -ljsoncpp
.PHONY:clean
clean:
	rm -f main