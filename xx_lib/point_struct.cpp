#include <point_struct.h>

//遍历 特判 一下进去的时候是啥时候就好了
size_t xx::traverse(size_t current, bool iss)
{
    size_t count = 0;
    for (size_t i = h[current]; i != -1; i = ne[i]) {
        count++;
        size_t j = e[i];
        if (iss) {
            if (cx[j].value_type == xxxx::u7 && cx[j].array_document == 4)
                traverse(j);
            else
                cxs.push(j);
        }
    }
    if (iss)
        cxs.push(current);
    return count - 1;
}

std::pair<std::vector<size_t>, bool> xx::find(std::size_t current, std::string key)
{
    std::vector<size_t> r;
    size_t key_c = find_tree.count(key);
    auto key_begin = find_tree.find(key);
    for (size_t i = 0; i < key_c; ++i)
        if (current == key_begin->second.first)
            r.push_back(((key_begin++)->second).second);
        else
            key_begin++;
    return { r, r.size() ? true : false };
}

std::pair<std::vector<size_t>, bool> xx::find(std::string document)
{
    std::vector<size_t> r;
    size_t key_c = find_document.count(document);
    auto key_begin = find_document.find(document);
    for (size_t i = 0; i < key_c; ++i)
        r.push_back((key_begin++)->second);
    return { r, r.size() ? true : false };
}

///////////////////////////////////////////////////////////////////////

void xx::bson_init_xx(std::string str)
{
    bson = bson_new_from_data((const uint8_t*)str.c_str(), str.length());
    bson_iter_init(&iter, bson);
    bson_init_xx();
    bson_destroy(bson);
    bson = nullptr;
}

void xx::msgpack_init_xx(std::string str)
{
    bool rst = msgpack_unpacker_init(&unpacker, str.length());
    if (!rst) {
        msgpack_unpacker_destroy(&unpacker);
        assert(false);
        return;
    }

    if (msgpack_unpacker_buffer_capacity(&unpacker) < str.length()) {
        rst = msgpack_unpacker_reserve_buffer(&unpacker, str.length());
    }

    memcpy(msgpack_unpacker_buffer(&unpacker), str.c_str(), str.length());
    msgpack_unpacker_buffer_consumed(&unpacker, str.length());
    msgpack_unpacked unpacked;
    msgpack_unpacked_init(&unpacked);

    if (msgpack_unpacker_next(&unpacker, &unpacked) == MSGPACK_UNPACK_SUCCESS) {
        msgpack_init_xx(unpacked.data);
        msgpack_unpacked_destroy(&unpacked);
    }
    msgpack_unpacker_destroy(&unpacker);
}

void xx::msgpack_init_xx(msgpack_object const& obj)
{
    if (obj.type != msgpack_object_type::MSGPACK_OBJECT_MAP)
        return;
    msgpack_object_map const* m = &obj.via.map;
    for (uint32_t i = 0; i < m->size; ++i) {
        msgpack_object_kv const* obj_ptr = &m->ptr[i];
        if (!obj_ptr)
            return;
        msgpack_set_data(*obj_ptr);
    }
    return;
}

void xx::bson_init_xx()
{
    bson_iter_t t = iter;
    while (bson_iter_next(&t)) {
        std::string key = std::string(bson_iter_key(&t));
        if (BSON_ITER_HOLDS_UTF8(&t)) {
            uint32_t length;
            const char* str = bson_iter_utf8(&t, &length);
            push_string(key, str, length);
        } else if (BSON_ITER_HOLDS_DOUBLE(&t)) {
            double a = bson_iter_double(&t);
            push_float_64(key, a);
        } else if (BSON_ITER_HOLDS_INT32(&t)) {
            int a = bson_iter_int32(&t);
            push_int(key, a);
        } else if (BSON_ITER_HOLDS_ARRAY(&t)) {
            begin_array(key);
            bson_iter_t tt = iter;
            bson_iter_recurse(&t, &iter);
            bson_init_xx();
            iter = tt;
            end_array(key);
        } else if (BSON_ITER_HOLDS_DOCUMENT(&t)) {

            begin_document(key);
            bson_iter_t tt = iter;
            bson_iter_recurse(&t, &iter);
            bson_init_xx();
            iter = tt;
            end_document(key);
        }
    }
}

std::string xx::to_bson()
{
    traverse(0);
    bson = bson_new();
    bson_xx_get_data(bson);
    std::string ans((const char*)bson_get_data((const bson_t*)bson), bson->len);
    bson_destroy(bson);
    return ans;
}

std::string xx::to_msgpack()
{
    size_t count = traverse(0);
    msgpack_packer_init(&_packer, &_sbuf, msgpack_sbuffer_write);
    msgpack_pack_map(&_packer, count);
    msgpack_xx_get_data(&_packer);
    std::string ans(_sbuf.data, _sbuf.size);
    msgpack_sbuffer_destroy(&_sbuf);
    return ans;
}

void xx::msgpack_xx_get_data(msgpack_packer* _packer)
{
    cxs.pop();
    while (!cxs.empty()) {
        size_t t_index = cxs.top();
        cxs.pop();
        xxxx t = cx[t_index];

        switch (t.value_type) {
        case xxxx::u1:
            msgpack_pack_str_with_body(_packer, t.key.c_str(), strlen(t.key.c_str()));
            msgpack_pack_str_with_body(_packer, t.str.str, t.str.len);
            break;
        case xxxx::u2:
            msgpack_pack_str_with_body(_packer, t.key.c_str(), strlen(t.key.c_str()));
            msgpack_pack_int32(_packer, t.integer);
            break;
        case xxxx::u3:
            msgpack_pack_str_with_body(_packer, t.key.c_str(), strlen(t.key.c_str()));
            msgpack_pack_uint32(_packer, t.unsigned_integer);
            break;
        case xxxx::u4:
            msgpack_pack_str_with_body(_packer, t.key.c_str(), strlen(t.key.c_str()));
            msgpack_pack_double(_packer, t.float_64);
            break;
        case xxxx::u5:
            msgpack_pack_str_with_body(_packer, t.key.c_str(), strlen(t.key.c_str()));
            msgpack_pack_double(_packer, t.float_32);
            break;
        case xxxx::u6:
            msgpack_pack_str_with_body(_packer, t.key.c_str(), strlen(t.key.c_str()));
            msgpack_pop_array(_packer, t_index);
            break;
        case xxxx::u7:
            if (t.array_document == 4) {
                msgpack_pack_str_with_body(_packer, t.key.c_str(), strlen(t.key.c_str()));
                cxs.push(t_index);
                size_t count = traverse(t_index, false);
                msgpack_pack_map(_packer, count);
                msgpack_xx_get_data(_packer);
            } else
                return;
            break;
        default:
            break;
        }
    }
}

void xx::bson_xx_get_data(bson_t* bson)
{
    cxs.pop();
    while (!cxs.empty()) {
        size_t t_index = cxs.top();
        cxs.pop();
        xxxx t = cx[t_index];
        switch (t.value_type) {
        case xxxx::u1:
            bson_append_utf8(bson, t.key.c_str(), -1, t.str.str, t.str.len);
            break;
        case xxxx::u2:
            bson_append_int32(bson, t.key.c_str(), -1, t.integer);
            break;
        case xxxx::u3:
            bson_append_int32(bson, t.key.c_str(), -1, (int32_t)t.unsigned_integer);
            break;
        case xxxx::u4:
            bson_append_double(bson, t.key.c_str(), -1, t.float_64);
            break;
        case xxxx::u5:
            bson_append_double(bson, t.key.c_str(), -1, (double)t.float_32);
            break;
        case xxxx::u6:
            bson_pop_array(bson, t_index);
            break;
        case xxxx::u7:
            if (t.array_document == 4) {
                cxs.push(t_index);
                bson_pop_document(bson, t.key);
            } else
                return;
            break;
        default:
            break;
        }
    }
}

void xx::msgpack_set_data(msgpack_object_kv const& obj)
{
    std::string key(obj.key.via.str.ptr, obj.key.via.str.size);
    if (obj.val.type == msgpack_object_type::MSGPACK_OBJECT_POSITIVE_INTEGER) {
        uint32_t v = obj.val.via.u64;
        push_uint(std::string (obj.key.via.str.ptr, obj.key.via.str.size), v);
    } else if (obj.val.type == msgpack_object_type::MSGPACK_OBJECT_NEGATIVE_INTEGER) {
        int32_t v = obj.val.via.i64;
        push_int(std::string (obj.key.via.str.ptr, obj.key.via.str.size), v);
    } else if (obj.val.type == msgpack_object_type::MSGPACK_OBJECT_FLOAT32) {
        float v = obj.val.via.f64;
        push_float_32(std::string (obj.key.via.str.ptr, obj.key.via.str.size), v);
    } else if (obj.val.type == msgpack_object_type::MSGPACK_OBJECT_FLOAT64) {
        double v = obj.val.via.f64;
        push_float_64(std::string (obj.key.via.str.ptr, obj.key.via.str.size), v);
    } else if (obj.val.type == msgpack_object_type::MSGPACK_OBJECT_STR) {
        uint32_t len = obj.val.via.str.size;
        push_string(std::string (obj.key.via.str.ptr, obj.key.via.str.size), obj.val.via.str.ptr, len);
    } else if (obj.val.type == msgpack_object_type::MSGPACK_OBJECT_ARRAY) {
        begin_array(std::string (obj.key.via.str.ptr, obj.key.via.str.size));
        for (uint32_t i = 0; i < obj.val.via.array.size; ++i) {
            msgpack_object_kv const& obj_item = { obj.key, obj.val.via.array.ptr[i] };
            msgpack_set_data(obj_item);
        }
        end_array(std::string (obj.key.via.str.ptr, obj.key.via.str.size));
    } else if (obj.val.type == msgpack_object_type::MSGPACK_OBJECT_MAP) {
        begin_document(std::string (obj.key.via.str.ptr, obj.key.via.str.size));
        msgpack_init_xx(obj.val);
        end_document(std::string (obj.key.via.str.ptr, obj.key.via.str.size));
    } else {
        return;
    }
}

bool xx::bson_pop_document(bson_t* bson, std::string key)
{
    bson_t child;
    bson_append_document_begin(bson, key.c_str(), -1, &child);
    bson_xx_get_data(&child);
    bson_append_document_end(bson, &child);
    return true;
}

bool xx::bson_pop_array(bson_t* bson, size_t index)
{
    bson_t arr;
    bson_append_array_begin(bson, cx[index].key.c_str(), -1, &arr);
    for (auto value : cx[index].array) {
        if (cx[value].value_type == xxxx::u6) {
            bson_pop_array(&arr, value);
            continue;
        }
        xxxx t = cx[value];
        switch (t.value_type) {
        case xxxx::u1:
            bson_append_utf8(&arr, t.key.c_str(), -1, t.str.str, t.str.len);
            break;
        case xxxx::u2:
            bson_append_int32(&arr, t.key.c_str(), -1, t.integer);
            break;
        case xxxx::u3:
            bson_append_int32(&arr, t.key.c_str(), -1, (int32_t)t.unsigned_integer);
            break;
        case xxxx::u4:
            bson_append_double(&arr, t.key.c_str(), -1, t.float_64);
            break;
        case xxxx::u5:
            bson_append_double(&arr, t.key.c_str(), -1, (double)t.float_32);
            break;
        case xxxx::u7:
            traverse(value);
            bson_pop_document(&arr, t.key);
            break;
        default:
            break;
        }
    }
    bson_append_array_end(bson, &arr);
    return true;
}

bool xx::msgpack_pop_array(msgpack_packer* _packer, size_t index)
{
    msgpack_pack_array(_packer, cx[index].array.size());
    for (auto value : cx[index].array) {
        if (cx[value].value_type == xxxx::u6) {
            msgpack_pop_array(_packer, value);
            continue;
        }
        xxxx t = cx[value];
        switch (t.value_type) {
        case xxxx::u1:
            msgpack_pack_str_with_body(_packer, t.str.str, t.str.len);
            break;
        case xxxx::u2:
            msgpack_pack_int32(_packer, t.integer);
            break;
        case xxxx::u3:
            msgpack_pack_uint32(_packer, t.unsigned_integer);
            break;
        case xxxx::u4:
            msgpack_pack_double(_packer, t.float_64);
            break;
        case xxxx::u5:
            msgpack_pack_double(_packer, t.float_32);
            break;
        case xxxx::u7: {
            size_t count = traverse(value);
            msgpack_pack_map(_packer, count);
            msgpack_xx_get_data(_packer);
            break;
        }
        default:
            break;
        }
    }
    return true;
}

void xx::json_init_xx(std::string str)
{
    rapidjson::Document doc;
    doc.Parse(str.c_str());
    if (doc.HasParseError())
        return;
    json_init_xx(doc);
}

void xx::json_init_xx(JsonItem const& item)
{
    if (!item.IsObject())
        return;
    auto obj = item.GetObj();
    for (auto iter = item.MemberBegin(); iter != item.MemberEnd(); iter++) {
        json_set_data(iter);
    }
}

void xx::json_set_data(JsonIter const& iter)
{
    std::string key(iter->name.GetString(), iter->name.GetStringLength());
    if (iter->value.IsInt() && iter->value.GetInt() >= 0) {
        uint32_t value = std::move(iter->value.GetInt());
        push_uint(key, value);
    } else if (iter->value.IsInt()) {
        int32_t value = std::move(iter->value.GetInt());
        push_int(key, value);
    } else if (iter->value.IsDouble()) {
        double value = std::move(iter->value.GetDouble());
        push_float_64(key, value);
    } else if (iter->value.IsFloat()) {
        float value = std::move(iter->value.GetFloat());
        push_float_32(key, value);
    } else if (iter->value.IsString()) {
        uint32_t len = std::move(iter->value.GetStringLength());
        push_string(key, iter->value.GetString(), len);
    } else if (iter->value.IsArray()) {
        auto value = std::move(iter->value.GetArray());
        json_set_array(value, key);
    } else if (iter->value.IsObject()) {
        auto value = std::move(iter->value.GetObj());
        begin_document(key);
        json_init_xx(value);
        end_document(key);
    } else
        return;
}

void xx::json_set_array(JsonArray const& array, std::string key)
{
    begin_array(key);

    auto len = array.Size();
    for (size_t i = 0; i < len; i++) {
        if (array[i].IsArray()) {
            auto value = std::move(array[i].GetArray());
            json_set_array(value, key);
            continue;
        }

        if (array[i].IsInt() && array[i].GetInt() >= 0) {
            uint32_t value = std::move(array[i].GetInt());
            push_uint(key, value);
        } else if (array[i].IsInt()) {
            int32_t value = std::move(array[i].GetInt());
            push_int(key, value);
        } else if (array[i].IsDouble()) {
            double value = std::move(array[i].GetDouble());
            push_float_64(key, value);
        } else if (array[i].IsFloat()) {
            float value = std::move(array[i].GetFloat());
            push_float_32(key, value);
        } else if (array[i].IsString()) {
            uint32_t len = std::move(array[i].GetStringLength());
            push_string(key, array[i].GetString(), len);
        } else if (array[i].IsObject()) {
            auto value = std::move(array[i].GetObj());
            begin_document(key);
            json_init_xx(value);
            end_document(key);
        } else
            return;
    }

    end_array(key);
}

std::string xx::to_json()
{
    traverse(0);
    rapidjson::Document doc;
    auto allocator = doc.GetAllocator();
    json_xx_get_data(doc, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    return std::string(buffer.GetString());
}

void xx::json_xx_get_data(JsonItem& item, JsonAlloca& alloca)
{
    item.SetObject();
    auto obj = item.GetObj();
    cxs.pop();
    while (!cxs.empty()) {
        size_t t_index = cxs.top();
        cxs.pop();
        xxxx t = cx[t_index];
        JsonItem child;
        switch (t.value_type) {
        case xxxx::u1: {
            child.SetString(rapidjson::StringRef<char>(t.str.str, t.str.len));

            char* str = new char[t.key.length()];
            memcpy(str, t.key.c_str(), t.key.length());
            sg.push_back(str);
            auto key = rapidjson::StringRef<char>(str, t.key.length());
            item.AddMember(key, child, alloca);
            break;
        }
        case xxxx::u2: {
            child.SetInt(t.integer);

            char* str = new char[t.key.length()];
            memcpy(str, t.key.c_str(), t.key.length());
            sg.push_back(str);

            item.AddMember(rapidjson::StringRef<char>(str, t.key.length()),
                child, alloca);
            break;
        }
        case xxxx::u3: {
            child.SetUint(t.unsigned_integer);

            char* str = new char[t.key.length()];
            memcpy(str, t.key.c_str(), t.key.length());
            sg.push_back(str);

            item.AddMember(rapidjson::StringRef<char>(str, t.key.length()),
                child, alloca);
            break;
        }
        case xxxx::u4: {
            child.SetDouble(t.float_64);

            char* str = new char[t.key.length()];
            memcpy(str, t.key.c_str(), t.key.length());
            sg.push_back(str);

            item.AddMember(rapidjson::StringRef<char>(str, t.key.length()),
                child, alloca);
            break;
        }
        case xxxx::u5: {
            child.SetFloat(t.float_32);

            char* str = new char[t.key.length()];
            memcpy(str, t.key.c_str(), t.key.length());
            sg.push_back(str);

            item.AddMember(rapidjson::StringRef<char>(str, t.key.length()),
                child, alloca);
            break;
        }
        case xxxx::u6: {
            json_pop_array(child, alloca, t_index);

            char* str = new char[t.key.length()];
            memcpy(str, t.key.c_str(), t.key.length());
            sg.push_back(str);

            item.AddMember(rapidjson::StringRef<char>(str, t.key.length()),
                child, alloca);
            break;
        }
        case xxxx::u7: {
            if (t.array_document == 4) {
                cxs.push(t_index);
                json_xx_get_data(child, alloca);

                char* str = new char[t.key.length()];
                memcpy(str, t.key.c_str(), t.key.length());
                sg.push_back(str);

                item.AddMember(rapidjson::StringRef<char>(str, t.key.length()),
                    child, alloca);
            } else
                return;
            break;
        }
        default:
            break;
        }
    }
}

bool xx::json_pop_array(JsonItem& item, JsonAllocator& allocator, size_t index)
{
    item.SetArray();
    auto jarr = item.GetArray();

    for (auto value : cx[index].array) {
        rapidjson::Value it;
        if (cx[value].value_type == xxxx::u6) {
            json_pop_array(it, allocator, value);
            jarr.PushBack(it, allocator);
            continue;
        }
        xxxx t = cx[value];
        switch (t.value_type) {
        case xxxx::u1:
            it.SetString(rapidjson::StringRef<char>(t.str.str, t.str.len));
            jarr.PushBack(it, allocator);
            break;
        case xxxx::u2:
            it.SetInt(t.integer);
            jarr.PushBack(it, allocator);
            break;
        case xxxx::u3:
            it.SetUint(t.unsigned_integer);
            jarr.PushBack(it, allocator);
            break;
        case xxxx::u4:
            it.SetDouble(t.float_64);
            jarr.PushBack(it, allocator);
            break;
        case xxxx::u5:
            it.SetFloat(t.float_32);
            jarr.PushBack(it, allocator);
            break;
        case xxxx::u7:
            traverse(value);
            json_xx_get_data(it, allocator);
            jarr.PushBack(it, allocator);
            break;
        default:
            break;
        }
    }
    return true;
}