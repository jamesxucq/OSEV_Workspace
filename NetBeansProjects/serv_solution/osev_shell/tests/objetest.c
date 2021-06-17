// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>;
//
// test:test<(aa int)int> {xx = aa; return 0x00;}
// test:test<(aa int, bb int)int> {xx = bb; ax = aa; return 0x00;}

// test:tst<(yy int)int, (ex int)> {ex = yy; return 0x00;}

// rive:rive("tvtv", "test")>odb;
// test:test(11, 11) > tvtv;

// tvtv:find() | extend:pretty("oiii");

// tvtv:invoke("test:tst(33,55)", "db5dab4a32542f5901000000");
// tvtv:invoke("test:tst(55)");

// :echo("test", "ATTRIB|CONTENT");
// exte:echo("test");
// extend:echo("test")|extend:conve(GCC);
// odb:echo("test")|extend:conve(GCC);

// extend:echo("test")|extend:conve(GCC)|extend:save("test.cpp");
// odb:echo("test")|extend:conve(GCC)|extend:save("test.h");
// extend:echo("test")|extend:conve(GCC);


/*
 <?xml version="1.0" encoding="UTF-8"?><class_metada><object_id>fe739b30f77c335900000000</object_id><clas_name>test</clas_name><clas_attr><version>1</version><integrity>true</integrity></clas_attr></class_metada>
test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>
test:test<(aa int)int> {xx = aa; return 0x00;}
test:test<(aa int, bb int)int> {xx = bb; ax = aa; return 0x00;}
test:tst<(yy int)int, (ex int)> {ex = yy; return 0x00;}

 */