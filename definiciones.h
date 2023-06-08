
#ifndef COMPILADORD_DEFINICIONES_H
#define COMPILADORD_DEFINICIONES_H

// Estructura de componente léxico
typedef struct {
    int compLexico;
    char *lexema;
} ComponenteLexico;

// Componentes léxicos del lenguaje D

#define ID 300
#define STRING_LITERAL 309
#define INTEGER_LITERAL 310
#define FLOATING_POINT_LITERAL 311

// Palabras reservadas
#define IMPORT 301
#define DOUBLE 302
#define INT 303
#define WHILE 304
#define FOREACH 305
#define RETURN 306
#define VOID 307
#define CAST 308
#define ABSTRACT 340
#define ALIAS 341
#define ALIGN 342
#define ASM 343
#define ASSERT 344
#define AUTO 345
#define BODY 346
#define BOOL 347
#define BREAK 348
#define BYTE 349
#define CASE 350
#define CATCH 351
#define CDOUBLE 352
#define CENT 353
#define CFLOAT 354
#define CHAR 355
#define CLASS 356
#define CONST 357
#define CONTINUE 358
#define CREAL 359
#define DCHAR 360
#define DEBUG 361
#define DEFAULT 362
#define DELEGATE 363
#define DELETE 364
#define DEPRECATED 365
#define DO 366
#define ELSE 367
#define ENUM 368
#define EXPORT 369
#define EXTERN 370
#define FALSE 371
#define FINAL 372
#define FINALLY 373
#define FLOAT 374
#define FOR 375
#define FOREACH_REVERSE 376
#define FUNCTION 377
#define GOTO 378
#define IDOUBLE 379
#define IF 380
#define IFLOAT 381
#define IMMUTABLE 382
#define IN 383
#define INOUT 384
#define INTERFACE 385
#define INVARIANT 386
#define IREAL 387
#define IS 388
#define LAZY 389
#define LONG 390
#define MACRO 391
#define MIXIN 392
#define MODULE 393
#define NEW 394
#define NOTHROW 395
#define null 396
#define OUT 397
#define OVERRIDE 398
#define PACKAGE 399
#define PRAGMA 400
#define PRIVATE 401
#define PROTECTED 402
#define PUBLIC 403
#define PURE 404
#define REAL 405
#define REF 406
#define SCOPE 407
#define SHARED 408
#define SHORT 409
#define STATIC 410
#define STRUCT 411
#define SUPER 412
#define SWITCH 413
#define SYNCHRONIZED 414
#define TEMPLATE 415
#define THIS 416
#define THROW 417
#define TRUE 418
#define TRY 419
#define TYPEID 420
#define TYPEOF 421
#define UBYTE 422
#define UCENT 423
#define UINT 424
#define ULONG 425
#define UNION 426
#define UNITTEST 427
#define USHORT 428
#define VERSION 429
#define WCHAR 430
#define WITH 431
#define file 432
#define file_full_path 433
#define module 434
#define line 435
#define function 436
#define pretty_function 437
#define gshared 438
#define traits 439
#define vector 440
#define parameters 441

// Operadores
#define DIVISION_IGUAL 312
#define  PUNTO_PUNTO 313
#define  PUNTO_PUNTO_PUNTO 314
#define  AND_IGUAL 315
#define  AND_AND 316
#define  OR_IGUAL 317
#define  OR_OR 318
#define MENOS_IGUAL 319
#define MENOS_MENOS 320
#define MAS_IGUAL 321
#define MAS_MAS 322
#define MENOR_IGUAL 323
#define MENOR_MENOR 324
#define MENOR_MENOR_IGUAL 325
#define MAYOR_IGUAL 326
#define MAYOR_MAYOR_IGUAL 327
#define MAYOR_MAYOR_MAYOR_IGUAL 328
#define MAYOR_MAYOR 329
#define MAYOR_MAYOR_MAYOR 330
#define DISTINTO 331
#define IGUAL_IGUAL 332
#define POR_IGUAL 333
#define MODULO_IGUAL 334
#define ELEVADO_IGUAL 335
#define ELEVADO_ELEVADO 336
#define ELEVADO_ELEVADO_IGUAL 337
#define TILDE_IGUAL 338
#define IGUAL_MAYOR 339


#endif //COMPILADORD_DEFINICIONES_H
