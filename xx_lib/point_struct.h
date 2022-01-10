#ifndef __POINT_STRUCT_H__
#define __POINT_STRUCT_H__

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>

#include <limits.h>
#include <cstring>

#include <bson.h>
#include <msgpack.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/writer.h>

using JsonItem = rapidjson::Value;
using JsonAllocator = rapidjson::Document::AllocatorType;
using JsonIter = rapidjson::Value::ConstMemberIterator;
using JsonArray = rapidjson::GenericArray<true, rapidjson::Value>;
using JsonAlloca = rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>;

constexpr unsigned int N = static_cast<unsigned int>(1e7 + 5);//1000 0005 个数据 为啥+5呢 这是一个来自noier的习惯

class xx {
public:    
    class xxxx {
    public:
        enum { 
            u0,//啥也不是的东西（从0开始数数是浪漫的开始）！
            u1,//字符串
            u2,//整数
            u3,//无符号整数
            u4,//64位浮点数
            u5,//32位浮点数
            u6,//数组
            u7 //文档
        };
        int value_type = u0;//数据类型
        std::string key;//key
        
        struct m_string {
            const char* str;//动态内存分配出来的之后需要进行释放掉
            size_t len;
        };
        std::vector<size_t> array;//u6
        //value数据
        union {
            m_string str;//u1
            int32_t integer; //u2
            uint32_t unsigned_integer; //u3
            double float_64; //u4
            float float_32; //u5
            char array_document;//3位4位 db,de 1位2位 ab,ae 6 array 7 doucment
        };
        xxxx(){}
        xxxx(std::string key_value, int vt,  void* t) : key(key_value), value_type(vt)
        {
            switch (vt)
            {
                case u1:  {m_string* tt = (m_string*)t; str = *tt;}              break;
                case u2:  {int32_t*  tt = (int32_t*) t; integer = *tt;}          break;
                case u3:  {uint32_t* tt = (uint32_t*)t; unsigned_integer = *tt;} break;
                case u4:  {double*   tt = (double*)  t; float_64 = *tt;}         break;
                case u5:  {float*    tt = (float*)   t; float_32 = *tt;}         break;
            }
        }
    };

    xx();//构造函数
    ~xx();//析构函数
    
    void clear();

    void bson_init_xx(std::string str);                              //用bson的字符串初始化xx
    std::string to_bson();                                           //xx 中的数据按照bson字符串输出

    void msgpack_init_xx(std::string str);                           //用msgpack 的字符串初始化xx
    std::string to_msgpack();                                        //xx中的数据 按照msgpack字符串输出

    void json_init_xx(std::string str);                               //用json 的字符串初始化 xx
    std::string to_json();                                            //xx中的数据按照json字符串输出

    void start();                                                     //开始
    void end();                                                       //结束
private:
    std::pair<std::vector<xxxx>, bool> find(std::string key);         //查找键的值
    

private:
    size_t current;                                                  //当前的父节点
    size_t h[N], e[N], ne[N], idx;
    std::vector<xxxx> cx;                                            //存数据
    std::stack<size_t> cs;                                           //存储父节点的下标
    std::stack<size_t> cxs;                                          //存储数据
    std::vector<char*>  sg;                                          //字符串垃圾桶

    bson_t* bson;
    bson_iter_t iter;

    msgpack_unpacker unpacker = {};
    msgpack_sbuffer  _sbuf = {};
    msgpack_packer   _packer = {};

    std::multimap<std::string, uint32_t> find_tree;                   //查找key对应的值
private:                                                             //private function
    size_t traverse(size_t current, bool iss = true);                 //遍历一遍就是存的结果
    void setcurrent();                                                //入数组/文档 后设置当前的父亲
    void resetcurrent();                                              //出数组/文档 后重置当前的父亲
    void push_point(xxxx x);                                          //把树中的每一个点加入进来
    void begin_document(std::string key);                             //文档的开始
    void end_document(std::string key);                               //文档的结束
    void begin_array(std::string key);                                //数组的开始
    void end_array(std::string key);                                  //数组的结束

    void push_string(std::string key, const char* str, uint32_t& len);//加入字符串
    void push_int(std::string key, int& integer);                     //加入整形
    void push_uint(std::string key, uint32_t& unsigned_integer);      //加入无符号整形
    void push_float_64(std::string key, double& float_64);            //加入64位的浮点数
    void push_float_32(std::string key, float& float_32);             //加入32位的浮点数

    bool bson_pop_array(bson_t* bson, size_t index);                  //bson 得到xx::xxxx里面的array
    bool bson_pop_document(bson_t* bson, std::string key);            //bson 得到document
    bool msgpack_pop_array(msgpack_packer*  _packer, size_t index);
    bool json_pop_array(JsonItem& item, JsonAllocator& allocator, size_t index);
    void bson_init_xx();
    void bson_xx_get_data(bson_t* bson);                              
    void msgpack_init_xx(msgpack_object const& obj);
    void msgpack_set_data(msgpack_object_kv const& obj);
    void msgpack_xx_get_data(msgpack_packer*  _packer);
    void json_init_xx(JsonItem const& item);
    void json_set_data(JsonIter const& iter);
    void json_set_array(JsonArray const& array, std::string key);
    void json_xx_get_data(JsonItem& item, JsonAlloca& alloca);
};



inline xx::xx()
{
    memset(h, -1, sizeof(h));
    idx = 0;
    current = -1; //初始化父节点为-1
}

inline xx::~xx()
{
    for (auto c : cx) {
        if (c.value_type == xxxx::u1)
            delete[] c.str.str;
    }

    for (auto c : sg){
        delete[] c;
    }
}

inline void xx::start()
{
    begin_document("");
}

inline void xx::end()
{
    end_document("");
}

inline void xx::push_point(xxxx x)
{
    cx.push_back(x);
    if (current != -1 && cx[current].value_type == xxxx::u6) {
        cx[current].array.push_back(cx.size() - 1);
        return;
    }
    if (x.array_document != 2 && x.array_document != 8)
        find_tree.insert({ x.key, cx.size() - 1 });
    if (current != -1) //头插法
        e[idx] = cx.size() - 1, ne[idx] = h[current], h[current] = idx++;
}

inline void xx::setcurrent() //设置父节点 begin_doucment, begin_array
{
    cs.push(current);
    current = cx.size() - 1; //
}

inline void xx::resetcurrent() //恢复父节点  end_doucement, end_array
{
    current = cs.top();
    cs.pop();
}

inline void xx::begin_document(std::string key)
{
    xxxx x;
    x.value_type = xxxx::u7;
    x.key = key;
    x.array_document = 4;
    push_point(x);
    setcurrent();
}

inline void xx::end_document(std::string key)
{
    xxxx x;
    x.value_type = xxxx::u7;
    x.key = "";
    x.array_document = 8;
    push_point(x);
    resetcurrent();
}

inline void xx::begin_array(std::string key)
{
    xxxx x;
    x.value_type = xxxx::u6;
    x.key = key;
    x.array_document = 1;
    push_point(x);
    setcurrent();
}

inline void xx::end_array(std::string key)
{
    resetcurrent();
}

inline void xx::push_string(std::string key, const char* str, uint32_t& len)
{
    xxxx::m_string ms;
    ms.str = new char[len];
    ms.len = len;
    memcpy((void*)ms.str, str, len);
    xxxx x(key, xxxx::u1, &ms);
    push_point(x);
}

inline void xx::push_int(std::string key, int& integer)
{
    xxxx x( key, xxxx::u2, &integer);
    push_point(x);
}

inline void xx::push_uint(std::string key, uint32_t& unsigned_integer)
{
    xxxx x( key, xxxx::u3, &unsigned_integer);
    push_point(x);
}

inline void xx::push_float_64(std::string key, double& float_64)
{
    xxxx x( key, xxxx::u4, &float_64);
    push_point(x);
}

inline void xx::push_float_32(std::string key, float& float_32)
{
    xxxx x(key, xxxx::u5, &float_32);
    push_point(x);
}

inline void xx::clear()
{
    memset(h, -1, sizeof(h));
    memset(e, -1 , sizeof(e));
    memset(ne, -1, sizeof(ne));
   
    for (auto c : cx) {
        if (c.value_type == xxxx::u1)
            delete[] c.str.str;
    }
    cx.clear();

    for (auto c : sg){
        delete[] c;
    }
    sg.clear();

    while (!cxs.empty()) cxs.pop();
    while (!cs.empty()) cs.pop();
    find_tree.clear();
    
    unpacker = {};
    _sbuf = {};
    _packer = {};
    idx = 0;
    current = -1; //初始化父节点为-1
}
#endif