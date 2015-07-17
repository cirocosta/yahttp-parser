// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hh"

// User implementation prologue.

#line 51 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 30 "parser.yy" // lalr1.cc:413

#include "yahttp/parser/driver.hh"

#line 57 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 143 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  HTTPParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  HTTPParser::HTTPParser (HTTPDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  HTTPParser::~HTTPParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  HTTPParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  HTTPParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  HTTPParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  HTTPParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  HTTPParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  HTTPParser::symbol_number_type
  HTTPParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  HTTPParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  HTTPParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 21: // header
        value.move< HTTPHeader > (that.value);
        break;

      case 20: // header_field
        value.move< HTTPHeaders > (that.value);
        break;

      case 7: // METHOD
        value.move< HTTPMethod > (that.value);
        break;

      case 16: // start_line
        value.move< HTTPStartLine > (that.value);
        break;

      case 13: // STATUS_CODE
        value.move< int > (that.value);
        break;

      case 8: // PATH
      case 9: // HTTP_VERSION
      case 10: // REASON_PHRASE
      case 11: // FIELD_NAME
      case 12: // FIELD_VALUE
      case 18: // reason_phrase
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  HTTPParser::stack_symbol_type&
  HTTPParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 21: // header
        value.copy< HTTPHeader > (that.value);
        break;

      case 20: // header_field
        value.copy< HTTPHeaders > (that.value);
        break;

      case 7: // METHOD
        value.copy< HTTPMethod > (that.value);
        break;

      case 16: // start_line
        value.copy< HTTPStartLine > (that.value);
        break;

      case 13: // STATUS_CODE
        value.copy< int > (that.value);
        break;

      case 8: // PATH
      case 9: // HTTP_VERSION
      case 10: // REASON_PHRASE
      case 11: // FIELD_NAME
      case 12: // FIELD_VALUE
      case 18: // reason_phrase
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  HTTPParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  HTTPParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  HTTPParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  HTTPParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  HTTPParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  HTTPParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  HTTPParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  HTTPParser::debug_level_type
  HTTPParser::debug_level () const
  {
    return yydebug_;
  }

  void
  HTTPParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline HTTPParser::state_type
  HTTPParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  HTTPParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  HTTPParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  HTTPParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 21 "parser.yy" // lalr1.cc:741
{
  // Initialize the initial location
  yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 475 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 21: // header
        yylhs.value.build< HTTPHeader > ();
        break;

      case 20: // header_field
        yylhs.value.build< HTTPHeaders > ();
        break;

      case 7: // METHOD
        yylhs.value.build< HTTPMethod > ();
        break;

      case 16: // start_line
        yylhs.value.build< HTTPStartLine > ();
        break;

      case 13: // STATUS_CODE
        yylhs.value.build< int > ();
        break;

      case 8: // PATH
      case 9: // HTTP_VERSION
      case 10: // REASON_PHRASE
      case 11: // FIELD_NAME
      case 12: // FIELD_VALUE
      case 18: // reason_phrase
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 53 "parser.yy" // lalr1.cc:859
    {}
#line 614 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 54 "parser.yy" // lalr1.cc:859
    {}
#line 620 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 57 "parser.yy" // lalr1.cc:859
    {}
#line 626 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 58 "parser.yy" // lalr1.cc:859
    {}
#line 632 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 63 "parser.yy" // lalr1.cc:859
    {
                                driver.message.start_line.status_code = yystack_[2].value.as< int > ();
                                driver.message.start_line.version = yystack_[4].value.as< std::string > ();
                              }
#line 641 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 69 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = ""; }
#line 647 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 70 "parser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
                  driver.message.start_line.reason_phrase += yystack_[0].value.as< std::string > ();
                }
#line 656 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 74 "parser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< std::string > () = " " + yystack_[0].value.as< std::string > ();
                  driver.message.start_line.reason_phrase += yylhs.value.as< std::string > ();
                }
#line 665 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 82 "parser.yy" // lalr1.cc:859
    {
                              driver.message.start_line.method = yystack_[4].value.as< HTTPMethod > ();
                              driver.message.start_line.path = yystack_[2].value.as< std::string > ();
                              driver.message.start_line.version = yystack_[0].value.as< std::string > ();
                            }
#line 675 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 89 "parser.yy" // lalr1.cc:859
    {}
#line 681 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 90 "parser.yy" // lalr1.cc:859
    {}
#line 687 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 93 "parser.yy" // lalr1.cc:859
    { driver.message.headers[yystack_[4].value.as< std::string > ()] = yystack_[1].value.as< std::string > (); }
#line 693 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 94 "parser.yy" // lalr1.cc:859
    { driver.message.headers[yystack_[4].value.as< std::string > ()] = yystack_[1].value.as< std::string > (); }
#line 699 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 95 "parser.yy" // lalr1.cc:859
    { driver.message.headers[yystack_[4].value.as< std::string > ()] = yystack_[1].value.as< std::string > (); }
#line 705 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 96 "parser.yy" // lalr1.cc:859
    { driver.message.headers[yystack_[4].value.as< std::string > ()] = yystack_[1].value.as< std::string > (); }
#line 711 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
    break;


#line 715 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  HTTPParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  HTTPParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char HTTPParser::yypact_ninf_ = -8;

  const signed char HTTPParser::yytable_ninf_ = -1;

  const signed char
  HTTPParser::yypact_[] =
  {
      -7,    -4,    -2,    10,     7,    -8,    -8,     4,     0,    -8,
      -6,     9,    11,    12,    14,    -8,    -6,    13,     8,    15,
      16,    -8,    -8,    -8,    18,    -5,    -3,    17,    20,    21,
      22,    24,    -8,    -8,    -8,    -8,    -8
  };

  const unsigned char
  HTTPParser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     4,     5,     0,     0,     1,
      11,     0,     0,     0,     0,     2,    11,     0,     7,     0,
       0,    12,    10,     8,     6,     0,     0,     0,     0,     0,
       0,     0,     9,    15,    14,    16,    13
  };

  const signed char
  HTTPParser::yypgoto_[] =
  {
      -8,    -8,    -8,    -8,    -8,    -8,     3,    -8
  };

  const signed char
  HTTPParser::yydefgoto_[] =
  {
      -1,     3,     4,     5,    24,     6,    15,    16
  };

  const unsigned char
  HTTPParser::yytable_[] =
  {
       1,     7,     2,     8,    13,    14,    28,    29,    30,    31,
       9,    10,    11,    12,    17,    19,    18,    20,    23,    21,
      25,    26,    22,    27,    33,    34,    35,    32,    36
  };

  const unsigned char
  HTTPParser::yycheck_[] =
  {
       7,     5,     9,     5,    10,    11,    11,    12,    11,    12,
       0,     4,     8,    13,     5,     3,     5,     3,    10,    16,
       5,     5,     9,     5,     4,     4,     4,    10,     4
  };

  const unsigned char
  HTTPParser::yystos_[] =
  {
       0,     7,     9,    15,    16,    17,    19,     5,     5,     0,
       4,     8,    13,    10,    11,    20,    21,     5,     5,     3,
       3,    20,     9,    10,    18,     5,     5,     5,    11,    12,
      11,    12,    10,     4,     4,     4,     4
  };

  const unsigned char
  HTTPParser::yyr1_[] =
  {
       0,    14,    15,    15,    16,    16,    17,    18,    18,    18,
      19,    20,    20,    21,    21,    21,    21
  };

  const unsigned char
  HTTPParser::yyr2_[] =
  {
       0,     2,     3,     0,     1,     1,     5,     0,     1,     3,
       5,     0,     2,     5,     5,     5,     5
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const HTTPParser::yytname_[] =
  {
  "\"End of File (EOF)\"", "error", "$undefined", "\":\"", "EOL", "SP",
  "OWS", "METHOD", "PATH", "HTTP_VERSION", "REASON_PHRASE", "FIELD_NAME",
  "FIELD_VALUE", "STATUS_CODE", "$accept", "http_message", "start_line",
  "status_line", "reason_phrase", "request_line", "header_field", "header", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  HTTPParser::yyrline_[] =
  {
       0,    53,    53,    54,    57,    58,    61,    69,    70,    74,
      80,    89,    90,    93,    94,    95,    96
  };

  // Print the state stack on the debug stream.
  void
  HTTPParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  HTTPParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1096 "/home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc" // lalr1.cc:1167
#line 99 "parser.yy" // lalr1.cc:1168


void yy::HTTPParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

