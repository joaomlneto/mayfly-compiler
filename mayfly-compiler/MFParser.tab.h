#define tVOID 257
#define tINTEGER 258
#define tNUMBER 259
#define tSTRING 260
#define tPUBLIC 261
#define tCONST 262
#define tIF 263
#define tTHEN 264
#define tELSE 265
#define tDO 266
#define tWHILE 267
#define tFOR 268
#define tIN 269
#define tSTEP 270
#define tUPTO 271
#define tDOWNTO 272
#define tCONTINUE 273
#define tBREAK 274
#define tRETURN 275
#define tPRINTLN 276
#define tINCREMENT 277
#define tDECREMENT 278
#define tLINTEGER 279
#define tLSTRING 280
#define tIDENTIFIER 281
#define tLNUMBER 282
#define xIF 283
#define tEQ 284
#define tNE 285
#define tLE 286
#define tGE 287
#define xPOINTED 288
#define xADDR 289
#define tUMINUS 290
#define xUMINUS 291
#define xUPLUS 292
typedef union {
  int                                i;	/* integer value */
  double                             d;   /* double value */
  std::string                       *s;	/* symbol name or string literal */
  cdk::node::Node                   *node;	/* node pointer */
  cdk::node::Sequence               *sequence;
  cdk::node::expression::Expression *expression; /* expression nodes */
  ExpressionType                    *type;
  mayfly::node::FunctionDeclaration *fdecl;
} YYSTYPE;
extern YYSTYPE yylval;
