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

���ߣ�ManateeLazyCat
���ӣ�https://www.jianshu.com/p/bad193f67a09
��Դ������
��������Ȩ���������У��κ���ʽ��ת�ض�����ϵ���߻����Ȩ��ע��������