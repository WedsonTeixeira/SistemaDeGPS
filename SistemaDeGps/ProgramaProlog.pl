:-dynamic(caminho/4).
:-use_module(library(pce)).

gps:-
    new(Tela, dialog("Sistema De Geolocalizacao")),
    send(Tela, size, size(650, 700)),
    new(Janela, window("",size(620, 550))),
    send(Tela, append, Janela),
    new(TOrigem, text_item("Origem")),
    send(Tela, append, TOrigem),
    new(TDestino, text_item("Destino")),
    send(Tela, append, TDestino),
    new(NRota, slider(quantidade, 1, 5, 1)),
    send(NRota, alignment, center),
    send(Tela, append, NRota),
    send(Tela, append, button(confirmar, message(@prolog,fun_bot_ok,TOrigem,TDestino,NRota,Janela,Tela))),
    send(Tela, default_button, confirmar),
    send(Tela, append, button("Limpar Campos", message(@prolog,fun_bot_lim,TOrigem,TDestino,NRota))),
    send(Tela,open),
    carregar().


fun_bot_ok(TOrigem, TDestino,NRota,Janela,Tela):-
    send(Janela,clear),
    get(TOrigem, value, Aux1),
    get(TDestino, value, Aux2),
    get(NRota, selection, Quantidade),
    atom_string(Aux1,Origem),
    atom_string(Aux2,Destino),
    new(OriTex, text("Origem: ")),
    new(OriCid, text(Origem)),
    new(DesTex, text("Destino: ")),
    new(DesCid, text(Destino)),

    verificarOD(Origem,Destino,Tela),

    send(OriTex, font,font(times, bold, 20)),
    send(OriCid, font,font(times, roman, 20)),
    send(OriCid, colour(colour(red))),
    send(DesTex, font,font(times, bold, 20)),
    send(DesCid, font,font(times, roman, 20)),
    send(DesCid, colour(colour(green))),
    send(Janela, display, OriTex, point(5,5)),
    send(Janela, display, OriCid, point(100,5)),
    send(Janela, display, DesTex, point(5,35)),
    send(Janela, display, DesCid, point(100,35)),

    gps(Origem,Destino,Quantidade,Janela).


fun_bot_lim(TOrigem,TDestino,NRota):-
    send(TOrigem,value,""),
    send(TDestino,value,""),
    send(NRota,selection,1).


verificarOD(Origem,Destino,_):-
    caminho(Origem,_,_,_),
    caminho(_,Destino,_,_),!.
verificarOD(_,_,Tela):-
    send(Tela, report, error,"Origem ou Destino não existe!"),fail.


gps(X,Y,Fim, Janela):-
    setof((D,X,Y,T,L),caminho2(X,Y,D,T,L),Lista),
    mostrar(0,Fim,Lista,Janela).

carregar():-
    open('BaseDeDadosProlog.txt',read,Entrada),
    leialinha(Entrada),
    close(Entrada).


leialinha(Entrada):-
    at_end_of_stream(Entrada),!.
leialinha(Entrada):-
    read(Entrada,caminho(Origem,Destino,Distancia,Tempo)),!,
    verificarR(Origem,Destino,Distancia,Tempo),
    leialinha(Entrada).
leialinha(Entrada):-
     leialinha(Entrada).



verificarR(Origem,Destino,Distancia,Tempo):-
    caminho(Origem,Destino,Distancia,Tempo),!.
verificarR(Origem,Destino,Distancia,Tempo):-
    assert(caminho(Origem,Destino,Distancia,Tempo)).

caminho2(Ini, Fim,Distancia,Tempo, Cam):-
        caminho1(Ini,[Fim],0,Distancia,0,Tempo,Cam).

caminho1(Cid, [Cid|Cids], Distancia,Distancia,Tempo, Tempo, [Cid|Cids]).
caminho1(Ini, [Adj|Cids], Distancia,DistanciaF,Tempo, TempoF, CamF):-
        caminho(Interm, Adj,D1,T1),
        \+ pertence(Interm, [Adj|Cids]),
        D2 is Distancia + D1,
        T2  is Tempo + T1,
        caminho1(Ini, [Interm, Adj|Cids],D2,DistanciaF, T2, TempoF,CamF).


pertence(X, [X|_]):-!.
pertence(X, [_|Cau]):-
    pertence(X,Cau).



mostrar(Inicio,Fim,[(D,_,_,T,R)|Cauda], Janela):-
    AuxInicio is Inicio+1,
    AuxInicio =< Fim,

    new(Texto1, text("Rota: ")),
    new(Texto2, text(AuxInicio)),

    new(Texto3, text("Tempo: ")),
    atom_concat(T," m",AuxT),
    new(Texto4, text(AuxT)),

    new(Texto5, text("Distancia: ")),
    atom_concat(D," Km",AuxD),
    new(Texto6, text(AuxD)),

    new(Texto7, text("Caminho: ")),
    converte(R, AuxLista),
    new(Texto8, text(AuxLista)),



    send(Texto1, font,font(times, bold, 14)),
    send(Texto2, font,font(times, roman, 14)),
    send(Texto3, font,font(times, bold, 14)),
    send(Texto4, font,font(times, roman, 14)),
    send(Texto5, font,font(times, bold, 14)),
    send(Texto6, font,font(times, roman, 14)),
    send(Texto7, font,font(times, bold, 14)),
    send(Texto8, font,font(times, roman, 14)),

    send(Janela, display, Texto1, point(5,80+((AuxInicio-1)*90))),
    send(Janela, display, Texto2, point(50,80+((AuxInicio-1)*90))),
    send(Janela, display, Texto3, point(5,100+((AuxInicio-1)*90))),
    send(Janela, display, Texto4, point(60,100+((AuxInicio-1)*90))),
    send(Janela, display, Texto5, point(5,120+((AuxInicio-1)*90))),
    send(Janela, display, Texto6, point(80,120+((AuxInicio-1)*90))),
    send(Janela, display, Texto7, point(5,140+((AuxInicio-1)*90))),
    send(Janela, display, Texto8, point(70,140+((AuxInicio-1)*90))),

    mostrar(AuxInicio,Fim,Cauda,Janela).

converte([X],B):-
    atom_concat(X,"",B),!.
converte([X|Y],B):-
    atom_concat(X,"->",Aux),
    converte(Y,R),
    atom_concat(Aux,R,B).

