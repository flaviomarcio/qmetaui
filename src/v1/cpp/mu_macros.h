#pragma once

#define MU_HOSTING_ENDPOINT(v)\
    MUServerLink* get_##v(){\
        static MUServerLink* __##v=nullptr;\
        return this->readReturn(this, __##v, #v);\
    }\
    void set_##v(MUServerLink*link){Q_UNUSED(link)}\

#define MU_HOSTING_ENDPOINT_METHOD(v, m)\
    MUServerLink* get_##v##m(){\
        static MUServerLink* __##v=nullptr;\
        return this->readReturn(this, __##v, #v, #m);\
    }\
    void set_##v##m(MUServerLink*link){Q_UNUSED(link)}\

#define MU_INSTANCE(CLASS)\
    public:\
    static CLASS &i(){\
        static CLASS*__i=nullptr;\
        if(__i==nullptr)\
            __i=new CLASS();\
        return *__i;\
    }

#define MU_HOSTING_ROUTE(CLASS, protocol, host, port, route)\
public:\
virtual MUServerLink &bh(){\
    return Hosting::bh(#protocol, #host, port, #route);\
}

#define MU_HOSTING_ROUTE_METHOD(CLASS, protocol, host, port, route, method)\
public:\
virtual MUServerLink &bh(){\
    return Hosting::bh(#protocol, #host, port, #route, #method);\
}
