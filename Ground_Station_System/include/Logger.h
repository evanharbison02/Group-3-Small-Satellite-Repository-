#ifndef LOGGER_H
#define LOGGER_H

#include "include/Types.h"

const char boot_logo[] = "\n"
"              .                       ·             .     |         ․                 .        _.oo.     *\n"
"  *               .          •                           -0-            _.u[[/;:,.         .odMMMMMM'         .            o\n"
"        °                                         ·       |           .o888UU[[[/;:-.  .o@P^    MMM^                .\n"
"   _____    ______ _   __ _____ ______ __  __                       oN88888UU[[[/;::-.        dP^       .                    \n"
"  /__  /   / ____// | / //_  _//_  __// / / /   o             .    dNMMNN888UU[[[/;:--.   .o@P^                        .     \n"
"    / /   / /___ /  |/ /  / /   / /  / /_/ /      .                MMMMMMN888UU[[/;::-. o@^       .         -o-              \n"
"   / /   / /___// /|  /  / /   / /  / __  /            *           NNMMMNN888UU[[[/~.o@p^                         .        \n"
"  / /__ / /___ / / | / _/ /_  / /  / / / /                 °       888888888UU[[[/o@^-..     *         .                    0 \n"
" /____//_____//_/  |/ |____/ /_/  /_/ /_/     °      .            oI8888UU[[[/o@P^:--..                         .\n"
" o              .                                 .           .@^  YUU[[[/o@^;::---..     .              •                 \n"
"      •                                ·                    oMP     ^/o@P^;:::---..              °                    #\n"
"    .     *           °                       #         .dMMM    .o@^ ^;::---...    .                  ·\n"
"              •                 .                      dMMMMMMM@^`       `^^^^               .             *            \n"
" ·                                    ․               YMMMUP^           .           °             .               .\n"
"        ·            °         o              .        ^^        *             .           .              °             .\n"
"\n";

error_t struct{
    error_id err;
    const char* message;
};





#endif