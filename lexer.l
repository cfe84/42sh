"\\n" | "\t" | " " | "\r" -> skip_blank()
"#.*\n" -> skip_comment()
"\n" -> EOL
EOF -> EOF
";" -> PVIRG
"!" -> BANG
"&" -> AMP
"&&" -> AMPAMP
"|" -> PIPE
"||" -> PIPEPIPE
">" -> R_CH
"<" -> L_CH
">>" -> D_R_CH
"<<" -> D_L_CH
"<<-" -> S_D_L_CH
"(" -> L_PAR
")" -> R_PAR
"{" -> L_BRA
"}" -> R_BRA
"if" -> IF
"else" -> ELSE
"for" -> FOR
"in" -> IN
"done" -> DONE
string -> WORD     /* Type special */
number -> NUMBER   /* Type special */
_ -> error()
