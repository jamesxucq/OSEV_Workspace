#define DECLARE_CLASS_CREATE(class_name) \
    static CObject* CreateClass## class_name ();  

#define IMPL_CLASS_CREATE(class_name) \
    static CObject* CreateClass## class_name (){ \
    return new class_name; \
};

#define REG_CLASS_CREATE(class_name) \
    RegisterFactoryCreate(class_name::CreateClass## class_name, #class_name); 