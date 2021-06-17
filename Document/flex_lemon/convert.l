%%
"colour"        { printf("color"); }
"flavour"       { printf("flavor"); }
"clever"        { printf("smart"); }
"conservative"  { printf("libreal"); }
.               { printf("%s", yytext); }
%%

int main(int argc, char **argv) {
    yylex();
}

作者：ManateeLazyCat
链接：https://www.jianshu.com/p/bad193f67a09
來源：简书
简书著作权归作者所有，任何形式的转载都请联系作者获得授权并注明出处。