#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include <stdlib.h>
#include <point_struct.h>
//#include <vld.h>
class Timer {
private:
    decltype(std::chrono::steady_clock::now()) _timestamp;
public:
    void start() {
        _timestamp = std::chrono::steady_clock::now(); 
    }
    uint64_t end() {
        auto curr = std::chrono::steady_clock::now();
        auto st = std::chrono::duration_cast<std::chrono::microseconds>(curr- _timestamp).count();
        return st;
    }
};

std::string file_read(std::string path)
{
    auto file = fopen(path.c_str(), "rb");//读进来的时候
    auto set = ftell(file);
    fseek(file, 0, SEEK_END);
    auto length = ftell(file) - set;

    char* buffer = new char[length];
    fseek(file, 0, SEEK_SET);
    fread(buffer, 1, length, file);
    fflush(file);
    fclose(file);
    
    std::string sss(buffer,length);
    delete buffer;
    return sss;
}

void bzh(std::string& strs)
{
    int y = 0;
    for (size_t i = 0; i < strs.length();) {
        if (strs[i] == '\"' && !y) {
            y++;
            i++;
            continue;
        }
        if (strs[i] == '\"') {
            y--;
            i++;
            continue;
        }
        if (y) {
            i++;
            continue;
        }
        if (strs[i] == ' ' || strs[i] == '\n' || strs[i] == '\t')
            strs.erase(i, 1);
        else
            i++;
    }
}


int main(void)
{
    Timer timer;
    std::unique_ptr<xx> x = std::make_unique<xx>();
    std::string str = file_read("../hahah.json");
    std::cout << sizeof(*x) << std::endl;

    timer.start();
    x->start();//初始化前需要开始
    x->json_init_xx(str);//用json字符串初始化
    x->end();//初始化完成后需要结束
    std::cout << "json_init\t" << timer.end() << "us" << std::endl;
    
    timer.start();
    std::string json = x -> to_json();
    std::cout << "to_json\t\t" << timer.end() << "us" << std::endl;
    std::cout << std::endl;

    std::string bson = x-> to_bson();
    x->clear();//再次初始化前需要clear

    timer.start();
    x->start();
    x->bson_init_xx(bson);
    x->end();
    std::cout << "bson_init\t" << timer.end() << "us" << std::endl;
    
    bson.clear();
    timer.start();
    bson = x->to_bson();
    std::cout << "to_bson\t\t" << timer.end() << "us" << std::endl;
    std::cout << std::endl;

    std::string msgpack = x->to_msgpack();
    x->clear();

    timer.start();
    x->start();
    x->msgpack_init_xx(msgpack);
    x->end();
    std::cout << "msgpack_init\t" << timer.end() << "us" << std::endl;

    msgpack.clear();
    timer.start();
    msgpack = x->to_msgpack();
    std::cout << "to_msgpack\t" << timer.end() << "us" << std::endl;
    std::cout << std::endl;
    
    x->clear();
    x->start();
    x->msgpack_init_xx(msgpack);
    x->end();
    //x->get_value(); //获得值
    timer.start();
    for (int i = 1; i <= 2; i ++)
    {
        auto& t = x->get_value("zhangqiuchi", i, false, "aaaa", 2);
        if (!x->get_value_is_empty(t))
        {
            t.value_type = xx::xxxx::u1;
            std::string sstr = "Hello World";
            t.str.str = new char[sstr.length()];
            memcpy((void*)t.str.str, sstr.c_str(), sstr.length());
            t.str.len = sstr.length();
        }
    }
    
    std::cout << timer.end() << std::endl;
    std::cout << x->to_json() << std::endl;
    return 0;
}