%%
a { ECHO; }
b { REJECT; }
c { yymore (); }
d { yyless (1); }
e { /* IRIX 6.5 flex 2.5.4 underquotes its yyless argument.  */
    yyless ((input () != 0)); }
f { unput (yytext[0]); }
. { BEGIN INITIAL; }
%%
#ifdef YYTEXT_POINTER
extern char *yytext;
#endif
int
main (void)
{
  return ! yylex () + ! yywrap ();
}
