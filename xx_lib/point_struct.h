#ifndef __POINT_STRUCT_H__
#define __POINT_STRUCT_H__

#define private_function  private:
#define private_value     private:

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

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

//这个必须换成vector 空间占用有点过分
//constexpr unsigned int N = static_cast<unsigned int>(1e7 + 5);
class xx {
public:    
    //内部类 
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
        struct m_string {
            const char* str;//动态内存分配出来的之后需要进行释放掉
            size_t len;
        };

        int value_type = u0;//数据类型
        std::string key;//key
        std::vector<size_t> array;//u6
        //value数据
        union {
            m_string    str;//u1
            int32_t     integer; //u2
            uint32_t    unsigned_integer; //u3
            double      float_64; //u4
            float       float_32; //u5
            char        array_document;//3位4位 db,de 1位2位 ab,ae 6 array 7 doucment
        };

        xxxx(){}                                                                       //默认构造函数
        xxxx(std::string& key_value, int vt,  void* t) : key(key_value), value_type(vt) //调用这个
        {
            switch (vt)
            {
                case u1:    str = *(m_string*)t;                  break;
                case u2:    integer = *(int32_t*)t;               break;
                case u3:    unsigned_integer = *(uint32_t*)t;     break;
                case u4:    float_64 = *(double*)t;               break;
                case u5:    float_32 = *(float*)t;               break;
            }
        }
    };

    xx();                                                            //构造函数
    ~xx();                                                           //析构函数
    void clear();                                                    //清理
    
    void bson_init_xx(std::string str);                              //用bson的字符串初始化xx
    std::string to_bson();                                           //xx 中的数据按照bson字符串输出

    void msgpack_init_xx(std::string str);                           //用msgpack 的字符串初始化xx
    std::string to_msgpack();                                        //xx中的数据 按照msgpack字符串输出

    void json_init_xx(std::string str);                               //用json 的字符串初始化 xx
    std::string to_json();                                            //xx中的数据按照json字符串输出

    void start();                                                     //开始
    void end();                                                       //结束
    //更改  document 中的值
    xx::xxxx& get_value(std::string key, size_t key_tm = 1, bool istrue = false, std::string document_name = "", size_t document_tm = 1); 
    //更改    array   中的值
    //xx::xxxx& get_value(std::string key, std::vector<int> index, bool istrue = false, std::string document_name = "", size_t document_tm = 1, size_t key_tm = 1);
    //是否为空
    bool get_value_is_empty(xx::xxxx& v)
    {
        return 8 == v.array_document ? true : false;
    }
private:
    std::pair<std::vector<size_t>, bool> find(std::size_t current, std::string key);        //查找键的值
    std::pair<std::vector<size_t>, bool> find(std::string document);
private_value
    size_t current, idx;                                             //当前的父节点
    //size_t h[N], e[N], ne[N], idx;
    std::vector<size_t> h, e, ne;
    std::vector<xxxx> cx;                                            //存数据
    std::vector<char*>  sg;                                          //字符串垃圾桶
    
    std::stack<size_t> cs;                                           //存储父节点的下标
    std::stack<size_t> cxs;                                          //存储数据

    std::unordered_multimap<std::string, std::pair<size_t, size_t>> find_tree;                    //查找key对应的值
    std::unordered_multimap<std::string, size_t> find_document;                          
    
    //bson
    bson_t* bson;
    bson_iter_t iter;

    //msgpack
    msgpack_unpacker unpacker = {};
    msgpack_sbuffer  _sbuf = {};
    msgpack_packer   _packer = {};

private_function                                                        //private function
    size_t traverse(size_t current, bool iss = true);                   //遍历一遍就是存的结果
    void setcurrent();                                                  //入数组/文档 后设置当前的父亲
    void resetcurrent();                                                //出数组/文档 后重置当前的父亲
    void push_point(xxxx&& x);                                          //把树中的每一个点加入进来
    void begin_document(std::string& key);                              //文档的开始
    void end_document(std::string& key);                                //文档的结束
    void begin_array(std::string& key);                                 //数组的开始
    void end_array(std::string& key);                                   //数组的结束

    void push_string(std::string& key, const char* str, uint32_t& len); //加入字符串
    void push_int(std::string& key, int& integer);                      //加入整形
    void push_uint(std::string& key, uint32_t& unsigned_integer);       //加入无符号整形
    void push_float_64(std::string& key, double& float_64);             //加入64位的浮点数
    void push_float_32(std::string& key, float& float_32);              //加入32位的浮点数

    bool bson_pop_array(bson_t* bson, size_t index);                   //bson 得到xx::xxxx里面的array
    bool bson_pop_document(bson_t* bson, std::string key);             //bson 得到document
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
    h.resize(100);
    e.resize(100);
    ne.resize(100);

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
    std::string key = "";
    begin_document(key);
}

inline void xx::end()
{
    std::string key = "";
    end_document(key);
}

inline void xx::push_point(xxxx&& x)
{
    cx.emplace_back(x);
    if (cx.size() >= h.size())  
    {
        h.resize(cx.size() * 2);
        e.resize(cx.size() * 2);
        ne.resize(cx.size() * 2);
    }
    if (current != -1 && cx[current].value_type == xxxx::u6) {
        cx[current].array.emplace_back(cx.size() - 1);
        return;
    }
    if (x.array_document != 2 && x.array_document != 8)
        find_tree.insert({x.key, {current,cx.size() - 1}});//key 和 {current父亲, 插入的值}
    if (current != -1) //头插法
        e[idx] = cx.size() - 1, ne[idx] = h[current], h[current] = idx++;
}

inline void xx::setcurrent() //设置父节点 begin_doucment, begin_array
{
    cs.push(current);
    current = cx.size() - 1;   
}

inline void xx::resetcurrent() //恢复父节点  end_doucement, end_array
{
    current = cs.top();
    cs.pop();
}

inline void xx::begin_document(std::string& key)
{
    xxxx x;
    x.value_type = xxxx::u7;
    x.key = key;
    x.array_document = 4;
    push_point(std::move(x));
    setcurrent();
    h[current] = -1;
    find_document.insert({key, current});
}

inline void xx::end_document(std::string& key)
{
    xxxx x;
    x.value_type = xxxx::u7;
    x.key = "";
    x.array_document = 8;
    push_point(std::move(x));
    resetcurrent();
}

inline void xx::begin_array(std::string& key)
{
    xxxx x;
    x.value_type = xxxx::u6;
    x.key = key;
    x.array_document = 1;
    push_point(std::move(x));
    setcurrent();
    h[current] = -1;
}

inline void xx::end_array(std::string& key)
{
    resetcurrent();
}

inline void xx::push_string(std::string& key, const char* str, uint32_t& len)
{
    xxxx::m_string ms;
    ms.str = new char[len];
    ms.len = len;
    memcpy((void*)ms.str, str, len);
    push_point(xxxx (key, xxxx::u1, &ms));
}

inline void xx::push_int(std::string& key, int& integer)
{
    push_point(xxxx(key, xxxx::u2, &integer));
}

inline void xx::push_uint(std::string& key, uint32_t& unsigned_integer)
{
    push_point(xxxx(key, xxxx::u3, &unsigned_integer));
}

inline void xx::push_float_64(std::string& key, double& float_64)
{
    push_point(xxxx(key, xxxx::u4, &float_64));
}

inline void xx::push_float_32(std::string& key, float& float_32)
{
    push_point(xxxx(key, xxxx::u5, &float_32));
}

inline xx::xxxx& xx::get_value(std::string key, size_t key_tm, bool istrue, std::string document_name, size_t document_tm)
{
    size_t current = 0;
    if (istrue)
    {
        auto ans = find(document_name);
        current = ans.first.size() >= document_tm? ans.first[document_tm - 1] : 0;
    }
    auto ans = find(current, key);
    current = ans.first.size() >= key_tm? ans.first[key_tm - 1] : -1;
    if (-1 == current)
        return cx.back();
    return cx[current];
}

/*inline xx::xxxx& get_value(std::string key, std::vector<int> index, bool istrue, std::string document_name, size_t document_tm, size_t key_tm)
{

}*/

inline void xx::clear()
{
    h.clear(); e.clear(); ne.clear();
    h.resize(100); e.resize(100); ne.resize(100);

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
    find_document.clear();
    unpacker = {};
    _sbuf = {};
    _packer = {};
    idx = 0;
    current = -1; //初始化父节点为-1
}
#endif